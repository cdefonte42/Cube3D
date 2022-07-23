/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:33:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/23 18:33:45 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_ray_until_first_Hline(t_game *game, t_ray ray, int color)
{
	int	size_line = game->map.img.size_line / 4;
	int	max_line = game->cube_size * game->map.height;
	int	*pixels = game->map.img.data;
	int	line = 0;
	int	col = 0;

	double	part_int;
	double	Dy = 64.0 - modf(ray.pos[map].y, &part_int) * 64.0;
	int	length = 0;
	while (fabs(length * ray.dir[grid].y) <= Dy && (line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[line * size_line + col] = color;
		++length;
		col = ray.pos[grid].x + length * ray.dir[grid].x; // t: longeur de la ligne;
		line = ray.pos[grid].y + length * ray.dir[grid].y;
	}
}

void	draw_ray_until_first_Vline(t_game *game, t_ray ray, int color)
{
	int	size_line = game->map.img.size_line / 4;
	int	max_line = game->cube_size * game->map.height;
	int	*pixels = game->map.img.data;
	int	line = 0;
	int	col = 0;

	double	part_int;
	double	Dx = 64.0 - modf(ray.pos[map].x, &part_int) * 64.0;
	int	length = 0;
	while (fabs(length * ray.dir[grid].x) <= Dx && (line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[line * size_line + col] = color;
		++length;
		col = ray.pos[grid].x + length * ray.dir[grid].x; // t: longeur de la ligne;
		line = ray.pos[grid].y + length * ray.dir[grid].y;
	}
}

void	draw_ray(t_game *game, t_ray ray, int color)
{
	int	size_line = game->map.img.size_line / 4;
	int	max_line = game->cube_size * game->map.height;
	int	*pixels = game->map.img.data;
	int	line = 0;
	int	col = 0;

	//t = longueur du vecteur (de la ligne)
	int t = 0; // A transformer en Dx et Dy double pour passer d'un carre a l'autre
	while ((line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[(line * size_line + col)] = color;
		++t;
		col = ray.pos[grid].x + t * ray.dir[grid].x;
		line = ray.pos[grid].y + t * ray.dir[grid].y;
	}
}