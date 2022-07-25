/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:27:33 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/25 16:54:43 by Cyrielle         ###   ########.fr       */
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

void	draw_uni_walls(t_type wall_type, int *pixel)
{
	if (wall_type == nwall)
		*pixel = BLUE;
	else if (wall_type == swall)
		*pixel = RED;
	else if (wall_type == wwall)
		*pixel = PURPLE;
	else if (wall_type == ewall)
		*pixel = ORANGE;
}

/* NEED une optimisation non ? */
/* Remplit la game win de pixels en fonction des murs sol ciel etc */
void	draw_game(t_game *game)
{
	double	hpwall; // hauteur percue du wall
	t_ray	*rays = game->player.rays;
	int		nb_rays = game->width;
	int		col = 0;
	int		line;
	double	min_line;
	double	max_line;
	int	size_line = game->img.size_line / 4;
	while (col < nb_rays)
	{
		hpwall = wall_height_ratio(rays[col], game->player.dist_screen, game->cube_size);
		min_line = ((double)game->img.height - hpwall) * 0.5;
		max_line = ((double)game->img.height + hpwall) * 0.5;
		if (min_line < 0.0)
			min_line = 0.0;
		if (max_line > (double)game->img.height)
			max_line = (double)game->img.height;
		line = (int)min_line;
		while (line < (int)max_line)
		{
			draw_uni_walls(rays[col].hit_point.type, &(game->img.data[col + line * size_line]));
			++line;
		}
		++col;
	}
}
