/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:03:35 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/29 20:13:55 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Remplit la position (x, y) en map unit de 64(cube size) pixels de color. */
void	fill_cube(t_game *game, int y, int x, int color)
{
	int	*pixels = game->map.grid.data;
	int	origin_line = y * game->map.rcube_size * game->map.grid.size_line;
	int	origin_col = x * game->map.rcube_size;
	int	max_line = origin_line + game->map.rcube_size * game->map.grid.size_line;
	int	max_col = origin_col + game->map.rcube_size;

	for (int line = origin_line; line < max_line; line += game->map.grid.size_line)
	{
		for (int col = origin_col; col < max_col; ++col)
			pixels[col + line] = color;
	}
}

/* Draw (fill pixels) sur l'image de la map 2D viewed les pixels correspondants
aux walls. Va dabord chercher a quelle map unit position se trouve un wall,
puis fait appel a fill_cube pour remplir cette case. Iter l'operation sur toutes
les cases de la map. */
void	draw_walls(t_game *game)
{
	for (int i = 0; i < game->map.height; ++i)
	{
		for (int j = 0; j < game->map.width; ++j)
		{
			if (game->map.tab[i][j] == '1')
				fill_cube(game, i, j, GREY);
		}
	}
}

/* Draw les lignes en blanc de la grille associee a la map */
void	draw_grid(t_game *game)
{
	int *pixels = game->map.grid.data;
	int	size_line = game->map.grid.size_line;
	int	max_line = size_line * game->map.rcube_size * game->map.height;

	for (int line = 0; line <= max_line; line += size_line)
	{
		for (int col = 0; col < size_line; col += game->map.rcube_size)
			pixels[col + line] = WHITE;	// lignes verticales
	}
	for (int line = 0; line <= max_line; line += game->map.rcube_size * size_line)
	{
		for (int col = 0; col < size_line; ++col)
			pixels[col + line] = WHITE;	// lignes horizontales
	}
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
