/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:03:35 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/21 18:43:29 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Remplit la position (x, y) en map unit de 64(cube size) pixels de color. */
void	fill_cube(t_game *game, int y, int x, int color)
{
	int *pixels = game->map.img.data;
	int	size_line = game->map.img.size_line / 4;
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
	int *pixels = game->map.img.data;
	int	size_line = game->map.img.size_line / 4;
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
	int	size_line = game->map.img.size_line / 4;
	int	origin_line = (game->player.pos.y * game->cube_size - 5) * size_line;
	int	origin_col = game->player.pos.x * game->cube_size - 5;
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

/* Cree une nouvelle window et son MLX image associee, pour dessiner pixels par
pixels la map en top 2D view. Return 0 si OK, -1 si erreur de Malloc. */
// NE PUT pas l'image dessinee
int	draw_map(t_game *game)
{
	int		nb_pixelX = game->map.width * game->cube_size + 1;
	int		nb_pixelY = game->map.height * game->cube_size + 1;

	game->map.win = mlx_new_window(game->mlx_ptr, nb_pixelX, nb_pixelY,\
	"Grid representation window");
	if (!game->map.win)
		return (-1);
	game->map.img.ptr = mlx_new_image(game->mlx_ptr, nb_pixelX, nb_pixelY);
	if (!game->map.img.ptr)
		return (printf("draw_map: failed to init map img\n"), -1);
	game->map.img.data = (int *)mlx_get_data_addr(game->map.img.ptr, &game->map.img.bpp, \
	&game->map.img.size_line, &game->map.img.endian);

	draw_walls(game);
	draw_grid(game);
	draw_player(game);
	return (0);
}
