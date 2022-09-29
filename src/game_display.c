/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:27:33 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/28 11:39:13 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <sys/time.h>
#include <time.h>

void	draw_sprite(t_game *game, t_sprite *sprite, double angle);
void	set_sprites_datas(t_game *game, double angle);
void	sort_sprites(t_game *game);

#if !BONUS

void	draw_sprite(t_game *game, t_sprite *sprite, double angle)
{
	(void) game;
	(void) sprite;
	(void) angle;
}

void	set_sprites_datas(t_game *game, double angle)
{
	(void) game;
	(void) angle;
}

void	sort_sprites(t_game *game)
{
	(void) game;
}

#endif

/* Calcule la hauteur "percue" du mur (si loin, petit, et inversement).
Correction du fish eye grace a la projection (cos(a)) de la distance du hit 
point sur l'axe de view. */
// ATTENTION floating point exception: car division par 0!!
double	wall_height_ratio(t_ray ray, double distScreen, double cubeSize)
{
	double	hpwall;

	if (ray.hit_point.dist * cos(ray.angle) == 0.0)
		hpwall = distScreen * cubeSize / (ray.hit_point.dist);
	else
		hpwall = distScreen * cubeSize / (ray.hit_point.dist * cos(ray.angle));
	return (hpwall);
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

void	draw_sky(int *pixels, int size_line, int max, int color)
{
	int	i;

	i = max;
	while (i >= 0)
	{
		pixels[i] = fog_percentage(color, 0x000000, (SCREEN_H/2-(i/size_line))/(double)(SCREEN_H/2)*100);
		i -= size_line;
	}
}


void	draw_floor(int *pixels, int size_line, int max, int color)
{
	int	i;

	i = 0;
	(void)color;
	while (i <= max)
	{
		pixels[i] = fog_percentage(color, 0x000000, 100-(SCREEN_H/2+(max-i)/size_line)/(double)(SCREEN_H)*100);
		// pixels[i] = i/size_line;
		i += size_line;
	}

}
// TODO: Useless need to remove !!!!!
void	draw_floor_or_sky(int *pixels, int size_line, int max, int color)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (i < max/2)
			pixels[i] = color;
		else
			pixels[i] = 0x000000;
		// pixels[i] = color;
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
	double			hpwall;
	int				nb_rays;
	int				col;
	t_interval		interval;
	int				img_pixl_max;

	col = 0;
	nb_rays = game->width;
	img_pixl_max = game->img.height * game->img.size_line;
	while (col < nb_rays)
	{
		hpwall = wall_height_ratio(game->player.rays[col], \
		game->player.dist_screen, game->cube_size);
		if (hpwall < 1.0)
			hpwall = 1.0;
		get_interval(&(interval.inf), &(interval.sup), game->img, hpwall);
		draw_buff_texture(game, col, interval, hpwall);
//		draw_door(game, col, interval, hpwall);
		draw_floor(&(game->img.data[col + interval.sup]), \
		game->img.size_line, img_pixl_max - interval.sup, game->floor_color);
		draw_sky(&(game->img.data[col]), game->img.size_line, \
		interval.inf, game->ceiling_color);
		++col;
	}
	double	angle = atan2(game->player.dir.y, game->player.dir.x);
	set_sprites_datas(game, angle);
	sort_sprites(game);
	int		i = game->bonus.nb_sp - 1;
	while (i >= 0)
	{
		draw_sprite(game, &game->bonus.sps[game->bonus.sort_sp[i]], angle);
		--i;
	}
}
