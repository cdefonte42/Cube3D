/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:27:33 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/26 17:46:42 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Calcule la hauteur "percue" du mur (si loin, petit, et inversement).
Correction du fish eye grace a la projection (cos(a)) de la distance du hit 
point sur l'axe de view. */
// ATTENTION floating point exception: car division par 0!!
double	wall_height_ratio(t_ray ray, double distScreen, double cubeSize, double max)
{
	double	hpwall;

	if (ray.hit_point.dist * cos(ray.angle) == 0.0)
		hpwall = distScreen * cubeSize / (ray.hit_point.dist);
	else
		hpwall = distScreen * cubeSize / (ray.hit_point.dist * cos(ray.angle));
	if (hpwall > max)
		return (max);
	return (hpwall);
}

/* Colori en couleur uni, en fonction du type de wall (nord, sud, est, ouest);
pixels pointe vers l'adresse du premier pixel a colorier dans l'image;
max (en pixel), represente le dernier pixel / la fin du mur (a ne PAS 
colorier!). */
void	draw_uni_walls(t_type type, int *pixels, int size_line, int max)
{
	int		i;
	int		color;

	i = 0;
	if (type == nwall)
		color = BLUE;
	else if (type == swall)
		color = RED;
	else if (type == wwall)
		color = PURPLE;
	else
		color = ORANGE;
	while (i < max)
	{
		pixels[i] = color;
		i += size_line;
	}
}

/* Set les le minimun et le maximum de l'interval de coloration d'une slice de
mur. Les valeurs sont set en pixels. */
void	get_interval(int *min_line, int *max_line, t_img img, double hpwall)
{
	double	min;
	double	max;

	min = ((double)img.height - hpwall) * 0.5;
	max = ((double)img.height + hpwall) * 0.5;
	if (min < 0.0)
		min = 0.0;
	if (max > img.height)
		max = img.height;
	*min_line = (int)min * img.size_line;
	*max_line = (int)max * img.size_line;
}

/* Permet de colorier le ciel, ou le sol. pixels est l'adresse du premier pixel
a colorier, size_line est la valeur a incrementer a chaque tour, et max est
l'index du dernier pixels (a ne PAS colorier). */
void	draw_floor_or_sky(int *pixels, int size_line, int max, int color)
{
	int	i;

	i = 0;

	while (i < max)
	{
		pixels[i] = color;
		i += size_line;
	}
}

/* Remplit la game win de pixels en fonction des murs sol ciel etc.
	hpwall : Hauteur "percue" du mur (ratio hauteur mur / distance de celui ci)
	it_inff et it_max : en pixels! Interval entre le haut et le bas du mur
						(line min et line max a peindre).
*/
void	draw_game(t_game *game)
{
	double	hpwall;
	int		nb_rays;
	int		col;
	int		it_inf;
	int		it_sup;
	int		img_pixl_max = game->img.height * game->img.size_line;

	col = 0;
	nb_rays = game->width;
	while (col < nb_rays)
	{
		hpwall = wall_height_ratio(game->player.rays[col], \
		game->player.dist_screen, game->cube_size, img_pixl_max);

		get_interval(&it_inf, &it_sup, game->img, hpwall);

		if (game->player.rays[col].hit_point.type != nwall)
			draw_uni_walls(game->player.rays[col].hit_point.type, \
			&(game->img.data[col + it_inf]), game->img.size_line, it_sup - it_inf);
		else
			draw_buff_texture(game, col, it_inf, it_sup);

		draw_floor_or_sky(&(game->img.data[col + it_sup]), \
		game->img.size_line, img_pixl_max - it_sup, GREEN);

		draw_floor_or_sky(&(game->img.data[col]), game->img.size_line, \
		it_inf, CYAN);
		++col;
	}
}
