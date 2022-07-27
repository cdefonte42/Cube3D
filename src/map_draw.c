/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:03:35 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/27 13:33:08 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Remplit la position (x, y) en map unit de 64(cube size) pixels de color. */
void	fill_cube(t_game *game, int y, int x, int color)
{
	int	*pixels = game->map.grid.data;
	int	origin_line = y * game->cube_size * game->map.grid.size_line;
	int	origin_col = x * game->cube_size;
	int	max_line = origin_line + game->cube_size * game->map.grid.size_line;
	int	max_col = origin_col + game->cube_size;;

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
	int	max_line = size_line * game->cube_size * game->map.height;

	for (int line = 0; line <= max_line; line += size_line)
	{
		for (int col = 0; col < size_line; col += game->cube_size)
			pixels[col + line] = WHITE;	// lignes verticales
	}
	for (int line = 0; line <= max_line; line += game->cube_size * size_line)
	{
		for (int col = 0; col < size_line; ++col)
			pixels[col + line] = WHITE;	// lignes horizontales
	}
}

/* Cree une nouvelle window et son MLX image associee, pour dessiner pixels par
pixels la map en top 2D view. Return 0 si OK, -1 si erreur de Malloc. */
// NE PUT pas l'image dessinee
void	draw_map(t_game *game)
{
	draw_walls(game);
	draw_grid(game);
}


