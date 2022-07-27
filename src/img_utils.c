/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:10:57 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/27 14:09:31 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
/* Reset l'image img en black */
void	erase_img(t_img *img)
{
	int	size = img->height * img->size_line;
	int	i;

	i = 0;
	while (i < size)
	{
		img->data[i] = BLACK;
		++i;
	}
}

/* Set les pixels de to aux memes valeurs que ceux de from. ATTENTION, from
et to doivent avoir les memes dimensions! Permet de "sauvegarder" une img
temporairement par exemple. */
void	cpy_img_pixels(t_img from, t_img to)
{
	int	size = from.height * from.size_line;
	int	i;

	i = 0;
	while (i < size)
	{
		to.data[i] = from.data[i];
		++i;
	}
}

/* Dessine un carre, de size haut et size large (en pixel), a la 
position origin (en grid unit)*/
// Un peu la meme chose que draw_player et fill_cube dans draw_map.c
void	draw_square(t_game *game, t_pos origin, int size, int color)
{
	int	size_line = game->map.img.size_line;
	int	*pixels = game->map.img.data;
	int	line;
	int	col;
	int	max_line;
	int	max_col;

	line = ((int)origin.y - size / 2) * size_line;
	col = (int)origin.x - (size / 2);
	max_line = line + size * size_line;
	max_col = col + size;
	while (line < max_line && line < game->map.img.height * size_line)
	{
		col = (int)origin.x - (size / 2);
		while (col < max_col && col < size_line)
		{
			pixels[col + line] = color;
			++col;
		}
		line += size_line;
	}
}

/* Draw (fill pixels) sur l'image de la map 2D viewed les pixels correspondants
au player. */
void	draw_player(t_game *game)
{
	int	size_line = game->map.grid.size_line;
	int	origin_line = ((int)(game->player.pos.y * game->cube_size - 5) * size_line);
	int	origin_col = (game->player.pos.x * game->cube_size - 5);
	int	max_line = origin_line + 10 * size_line;
	int	max_col = origin_col + 10;
	int	*pixels = game->map.img.data;

	for (int line = origin_line; line < max_line; line += size_line)
	{
		for (int col = origin_col; col < max_col; ++col)
		{
			pixels[col + line] = ORANGE;

		}
	}
	t_ray	*rays = game->player.rays;
	int	i = 0;
	int	len = game->cube_size / 4;
	while (i < game->width - 1)
	{
		draw_sized_ray(game, rays[i], len, ORANGE);
		i += 6;
	}
}
