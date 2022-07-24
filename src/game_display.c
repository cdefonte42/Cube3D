/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:27:33 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/24 22:05:06 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"


/* NEED une optimisation non ? */
/* Remplit la game win de pixels en fonction des murs sol ciel etc */
void	draw_game(t_game *game)
{
	int	hpwall; // hauteur percue du wall
	t_ray	*rays = game->player.rays;
	int	nb_rays = game->width;
	int	col = 0;
	int line;
	int	min_line;
	int	max_line;
	int	size_line = game->img.size_line / 4;
	while (col < nb_rays)
	{
		// ATTENTION floating point exception: car division par 0!!
		if (col == game->width / 2 - 1 || rays[col].hit_point.dist * cos(rays[col].angle) == 0.0)
			hpwall = (int)(game->player.dist_screen * game->cube_size / (rays[col].hit_point.dist));
		else
			hpwall = (int)(game->player.dist_screen * game->cube_size / (rays[col].hit_point.dist * cos(rays[col].angle)));
		if (hpwall > (int)game->img.height)
			hpwall = game->img.height;
		min_line = (game->img.height - hpwall) / 2;
		max_line = (game->img.height + hpwall) / 2;
		if (min_line < 0)
			min_line = 0;
		if (max_line > (int)game->img.height)
			max_line = game->img.height;
		line = min_line;
		while (line < max_line && line < game->height)
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
		++col;
	}
}
