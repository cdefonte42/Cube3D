/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:03:35 by cdefonte          #+#    #+#             */
/*   Updated: 2022/09/08 13:04:12 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Remplit la position (x, y) en map unit de 64(cube size) pixels de color. */
void	fill_cube(t_game *game, int y, int x, int color)
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

/* Draw (fill pixels) sur l'image de la map 2D viewed les pixels correspondants
aux walls. Va dabord chercher a quelle map unit position se trouve un wall,
puis fait appel a fill_cube pour remplir cette case. Iter l'operation sur toutes
les cases de la map. */
void	draw_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.tab[i][j] == '1')
				fill_cube(game, i, j, GREY);
			++j;
		}
		++i;
	}
}

void	draw_vertical_lines(int *pixels, int size_line, int max_line, int rcube)
{
	int	line;
	int	col;

	line = 0;
	while (line <= max_line)
	{
		col = 0;
		while (col < size_line)
		{
			pixels[col + line] = WHITE;
			col += rcube;
		}
		line += size_line;
	}
}

void	draw_hrztl_lines(int *pixels, int size_line, int max_line, int rcube)
{
	int	line;
	int	col;
	int	line_inc;

	line = 0;
	line_inc = rcube * size_line;
	while (line <= max_line)
	{
		col = 0;
		while (col < size_line)
		{
			pixels[col + line] = WHITE;
			++col;
		}
		line += line_inc;
	}
}

/* Draw les lignes en blanc de la grille associee a la map */
void	draw_grid(t_game *game)
{
	int	*pixels;
	int	size_line;
	int	max_line;

	pixels = game->map.grid.data;
	size_line = game->map.grid.size_line;
	max_line = size_line * game->map.rcube_size * game->map.height;
	draw_vertical_lines(pixels, size_line, max_line, game->map.rcube_size);
	draw_hrztl_lines(pixels, size_line, max_line, game->map.rcube_size);
}

void	draw_map(t_game *game)
{
	cpy_img_pixels(game->map.grid, game->map.img);
	draw_player(game);
	draw_all_rays(game);
}

void	draw_minimap(t_game *game)
{
	erase_img(&(game->minimap));
	double	x = game->player.pos.x;
	double	y = game->player.pos.y;
	int	nb_pixels_minimap = game->minimap.height * game->minimap.size_line;
	int	i = 0;
	int	col = x * game->map.rcube_size - game->minimap.size_line / 2.0;
	int	line = y * game->map.rcube_size - game->minimap.size_line / 2.0;
	int	origin = col + line * game->map.img.size_line;

	int	max_map = game->map.img.height * game->map.img.size_line;

	while (origin < 0)
	{
		game->minimap.data[i] = BLACK;
		++i;
		if (i % game->minimap.size_line == 0)
			origin += game->map.img.size_line;
	}
	while (i < nb_pixels_minimap && origin + i % game->minimap.size_line < max_map)
	{
		if (col + i % game->minimap.size_line >= game->map.img.size_line || col + i % game->minimap.size_line <= 0)
			game->minimap.data[i] = BLACK;
		else
			game->minimap.data[i] = game->map.img.data[origin + i % game->minimap.size_line];
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
