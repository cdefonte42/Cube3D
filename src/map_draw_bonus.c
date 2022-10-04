/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:03:35 by cdefonte          #+#    #+#             */
/*   Updated: 2022/10/03 19:39:24 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Remplit la position (x, y) en map unit de 64(cube size) pixels de color. */
void	fill_cube_grid(t_game *game, int y, int x, int color)
{
	int	origin_line;
	int	max_line;
	int	max_col;
	int	line;
	int	col;

	origin_line = y * game->map.rcube_size * game->map.grid.size_line;
	max_line = origin_line + game->map.rcube_size * game->map.grid.size_line;
	max_col = x * game->map.rcube_size + game->map.rcube_size;
	line = origin_line;
	while (line < max_line)
	{
		col = x * game->map.rcube_size;
		while (col < max_col)
		{
			game->map.grid.data[col + line] = color;
			++col;
		}
		line += game->map.grid.size_line;
	}
}

void	draw_map(t_game *game)
{
	cpy_img_pixels(game->map.grid, game->map.img);
	draw_player(game);
	draw_all_rays(game);
}

void	draw_inner_minimap(int i, t_game *game, int origin, int col)
{
	int		max_map;
	int		nb_pixels_minimap;

	nb_pixels_minimap = game->minimap.height * game->minimap.size_line;
	max_map = game->map.img.height * game->map.img.size_line;
	while (i < nb_pixels_minimap
		&& origin + i % game->minimap.size_line < max_map)
	{
		if (col + i % game->minimap.size_line >= game->map.img.size_line
			|| col + i % game->minimap.size_line <= 0)
			game->minimap.data[i] = BLACK;
		else
			game->minimap.data[i] = game->map.img.data[origin
				+ i % game->minimap.size_line];
		++i;
		if (i % game->minimap.size_line == 0)
			origin += game->map.img.size_line;
	}
	while (i < nb_pixels_minimap)
	{
		game->minimap.data[i] = BLACK;
		++i;
	}
}

static void	transparency_minimap(t_game *game)
{
	int	col;
	int	line;

	col = 0;
	line = 0;
	while (line < game->minimap.height)
	{
		col = 0;
		while (col < game->minimap.width)
		{
			if (game->minimap.data[col + \
				line * game->minimap.size_line] == BLACK)
			{
				game->minimap.data[col + line * game->minimap.size_line] = \
				fog_percentage(game->img.data[col + \
					line * game->img.size_line], 75);
			}
			++col;
		}
		++line;
	}
}

void	draw_minimap(t_game *game)
{
	int		i;
	int		col;
	int		line;
	int		origin;

	i = 0;
	col = game->player.pos.x * game->map.rcube_size
		- game->minimap.size_line / 2.0;
	line = game->player.pos.y * game->map.rcube_size
		- game->minimap.size_line / 2.0;
	origin = col + line * game->map.img.size_line;
	while (origin < 0)
	{
		game->minimap.data[i] = BLACK;
		++i;
		if (i % game->minimap.size_line == 0)
			origin += game->map.img.size_line;
	}
	draw_inner_minimap(i, game, origin, col);
	transparency_minimap(game);
}
