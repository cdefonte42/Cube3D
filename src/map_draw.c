/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:03:35 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/23 18:40:12 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Remplit la position (x, y) en map unit de 64(cube size) pixels de color. */
void	fill_cube(t_game *game, int y, int x, int color)
{
	int	*pixels = game->map.grid.data;
	int	size_line = game->map.grid.size_line / 4;
	int	origin_line = y * game->cube_size * size_line;
	int	origin_col = x * game->cube_size;
	int	max_line = origin_line + game->cube_size * size_line;
	int	max_col = origin_col + game->cube_size;;

	for (int line = origin_line; line < max_line; line += size_line)
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
				fill_cube(game, i, j, GREEN);
		}
	}
}

/* Draw les lignes en blanc de la grille associee a la map */
void	draw_grid(t_game *game)
{
	int *pixels = game->map.grid.data;
	int	size_line = game->map.grid.size_line / 4;
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

/* Draw (fill pixels) sur l'image de la map 2D viewed les pixels correspondants
au player. */
void	draw_player(t_game *game)
{
	int	size_line = game->map.grid.size_line / 4;
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

/* Cree une nouvelle window et son MLX image associee, pour dessiner pixels par
pixels la map en top 2D view. Return 0 si OK, -1 si erreur de Malloc. */
// NE PUT pas l'image dessinee
void	draw_map(t_game *game)
{
	draw_walls(game);
	draw_grid(game);
}


