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
