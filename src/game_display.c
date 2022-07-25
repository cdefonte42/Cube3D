/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:27:33 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/25 17:38:56 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Calcule la hauteur "percue" du mur (si loin, petit, et inversement).
Correction du fish eye grace a la projection (cos(a)) de la distance du hit 
point sur l'axe de view. */
// ATTENTION floating point exception: car division par 0!!
double	wall_height_ratio(t_ray ray, double dist_screen, double cube_size)
{
	double	hpwall;
	if (ray.hit_point.dist * cos(ray.angle) == 0.0)
		hpwall = dist_screen * cube_size / (ray.hit_point.dist);
	else
		hpwall = dist_screen * cube_size / (ray.hit_point.dist * cos(ray.angle));
	return (hpwall);
}

void	draw_uni_walls(int line, int max_line, int col, t_game *game)
{
	int		size_line;
	t_ray	*rays;

	size_line = game->img.size_line;
	rays = game->player.rays;
	while (line < max_line)
	{
		if (rays[col].hit_point.type == nwall)
			game->img.data[col + line * size_line] = BLUE;
		else if (rays[col].hit_point.type == swall)
			game->img.data[col + line * size_line] = RED;
		else if (rays[col].hit_point.type == wwall)
			game->img.data[col + line * size_line] = PURPLE;
		else if (rays[col].hit_point.type == ewall)
			game->img.data[col + line * size_line] = ORANGE;
		++line;
	}
}

void	get_interval(int *min_line, int *max_line, int screen_height, double hpwall)
{
	double	min;
	double	max;

	min = ((double)screen_height - hpwall) * 0.5;
	max = ((double)screen_height + hpwall) * 0.5;
	if (min < 0.0)
		min = 0.0;
	if (max > screen_height)
		max = screen_height;
	*min_line = (int)min;
	*max_line = (int)max;
}

/* NEED une optimisation non ? */
/* Remplit la game win de pixels en fonction des murs sol ciel etc */
void	draw_game(t_game *game)
{
	double	hpwall; // hauteur percue du wall
	t_ray	*rays = game->player.rays;
	int	nb_rays = game->width;
	int	col;
	int	min_line;
	int	max_line;

	col = 0;
	while (col < nb_rays)
	{
		hpwall = wall_height_ratio(rays[col], game->player.dist_screen, game->cube_size);
		get_interval(&min_line, &max_line, game->img.height, hpwall);
		draw_uni_walls(min_line, max_line, col, game);
		++col;
	}
}
