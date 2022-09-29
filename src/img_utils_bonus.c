/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:10:57 by cdefonte          #+#    #+#             */
/*   Updated: 2022/09/08 16:49:03 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
/* Reset l'image img en black */
void	erase_img(t_img *img)
{
	int	size;
	int	i;

	size = img->height * img->size_line;
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
	int	size;
	int	i;

	size = from.height * from.size_line;
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
	int	size_line;
	int	line;
	int	col;
	int	max_line;
	int	max_col;

	size_line = game->map.img.size_line;
	line = ((origin.y * game->map.ratio) - size / 2) * size_line;
	col = (origin.x * game->map.ratio) - (size / 2);
	max_line = line + size * size_line;
	max_col = col + size;
	while (line < max_line && line < game->map.img.height * size_line)
	{
		col = (int)origin.x - (size / 2);
		while (col < max_col && col < size_line)
		{
			game->map.img.data[col + line] = color;
			++col;
		}
		line += size_line;
	}
}

/* Draw (fill pixels) sur l'image de la map 2D viewed les pixels correspondants
au player. */
void	draw_player(t_game *game)
{
	int	size_line;
	int	max_line;
	int	max_col;
	int	col;
	int	line;

	size_line = game->map.grid.size_line;
	line = ((int)(game->player.pos.y * game->map.rcube_size - 5) * size_line);
	col = game->player.pos.x * game->map.rcube_size - 5;
	max_line = line + 10 * size_line;
	max_col = col + 10;
	while (line < max_line)
	{
		col = game->player.pos.x * game->map.rcube_size - 5;
		while (col < max_col)
		{
			game->map.img.data[col + line] = ORANGE;
			++col;
		}
		line += size_line;
	}
}
