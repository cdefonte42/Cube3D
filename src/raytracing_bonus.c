/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:33:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/08 17:47:18 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_ray_until_first_hline(t_game *game, t_ray ray, int color)
{
	int		max_line;
	int		line;
	int		col;
	double	dy;
	int		length;

	max_line = game->map.rcube_size * game->map.ratio;
	line = 0;
	col = 0;
	length = 0;
	dy = game->map.rcube_size
		- modf(ray.pos[map].y, NULL) * game->map.rcube_size;
	while (fabs(length * ray.dir[grid].y) <= dy && (line < max_line
			&& line >= 0) && (col < game->map.img.size_line && col >= 0))
	{	
		game->map.img.data[line * game->map.img.size_line + col] = color;
		++length;
		col = ray.pos[grid].x * game->map.ratio + length * ray.dir[grid].x;
		line = ray.pos[grid].y * game->map.ratio + length * ray.dir[grid].y;
	}
}

void	draw_ray_until_first_vline(t_game *game, t_ray ray, int color)
{
	int		max_line;
	int		line;
	int		col;
	double	dx;
	int		length;

	dx = game->map.rcube_size
		- modf(ray.pos[map].x, NULL) * game->map.rcube_size;
	max_line = game->map.rcube_size * game->map.height;
	length = 0;
	line = 0;
	col = 0;
	while (fabs(length * ray.dir[grid].x) <= dx && (line < max_line
			&& line >= 0) && (col < game->map.img.size_line && col >= 0))
	{	
		game->map.img.data[line * game->map.img.size_line + col] = color;
		++length;
		col = ray.pos[grid].x * game->map.ratio + length * ray.dir[grid].x;
		line = ray.pos[grid].y * game->map.ratio + length * ray.dir[grid].y;
	}
}

void	draw_ray(t_game *game, t_ray ray, int color)
{
	int	max_line;
	int	*pixels;
	int	line;
	int	col;
	int	t;

	max_line = game->map.rcube_size * game->map.height;
	pixels = game->map.img.data;
	line = 0;
	col = 0;
	t = 0;
	while ((line < max_line && line >= 0)
		&& (col < game->map.img.size_line && col >= 0))
	{	
		pixels[(line * game->map.img.size_line + col)] = color;
		++t;
		col = ray.pos[grid].x * game->map.ratio + t * ray.dir[grid].x;
		line = ray.pos[grid].y * game->map.ratio + t * ray.dir[grid].y;
	}
}

/* Draw 1 ray sur 6 (a changer si besoin) et leur hit point correspondant.
Le ray du milieu (direction view player) est dessine avec un code couleur 
specifique. */
void	draw_all_rays(t_game *game)
{
	t_ray	*rays;
	int		index_mid_ray;
	int		i;

	index_mid_ray = game->width / 2 - 1;
	rays = game->player.rays;
	i = 0;
	while (i < game->width - 1)
	{
		draw_ray(game, rays[i], PURPLE);
		draw_square(game, rays[i].hit_point.pos[grid], 5, LIME);
		i += 30;
	}
	draw_ray(game, rays[index_mid_ray], YELLOW);
	draw_square(game, rays[index_mid_ray].hit_point.pos[grid], 5, PINK);
}

void	draw_sized_ray(t_game *game, t_ray ray, int length, int color)
{
	int	max_line;
	int	*pixels;
	int	line;
	int	col;
	int	t;

	max_line = game->map.rcube_size * game->map.height;
	pixels = game->map.img.data;
	line = 0;
	col = 0;
	t = 0;
	while (t < length && (line < max_line && line >= 0)
		&& (col < game->map.img.size_line && col >= 0))
	{	
		pixels[(line * game->map.img.size_line + col)] = color;
		++t;
		col = ray.pos[grid].x * game->map.ratio + t * ray.dir[grid].x;
		line = ray.pos[grid].y * game->map.ratio + t * ray.dir[grid].y;
	}
}
