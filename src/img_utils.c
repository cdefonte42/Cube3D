/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:10:57 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/24 16:43:51 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
/* Reset l'image img en black */
void	erase_img(t_img *img)
{
	int	size = img->height * (img->size_line / 4);
	int	i;

	i = 0;
	while (i < size)
	{
		img->data[i] = BLACK;
		++i;
	}
}

/* Set les pixels de dest aux memes valeurs que ceux de src. ATTENTION, dest
et src doivent avoir les memes dimensions! Permet de "sauvegarder" une img
temporairement par exemple. */
void	cpy_img_pixels(t_img from, t_img to)
{
	int	size = from.height * (from.size_line / 4);
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
	int	size_line = game->map.img.size_line / 4;
	int	*pixels = game->map.img.data;
	int	line;
	int	col;
	int	max_line;
	int	max_col;

	line = ((int)origin.y - size / 2) * size_line;
	col = (int)origin.x - (size / 2);
	max_line = line + size * size_line;
	max_col = col + size;
	while (line < max_line && line < (int)game->map.img.height * size_line)
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
