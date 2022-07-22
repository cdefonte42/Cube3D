/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:10:57 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/22 19:39:53 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Set les pixels de dest aux memes valeurs que ceux de src. ATTENTION, dest
et src doivent avoir les memes dimensions! Permet de "sauvegarder" une img
temporairement par exemple. */
void	cpy_img_pixels(t_screen from, t_screen to)
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

int	init_map(t_game *game)
{
	int		nb_pixelX = game->map.width * game->cube_size + 1;
	int		nb_pixelY = game->map.height * game->cube_size + 1;

	game->map.win = mlx_new_window(game->mlx_ptr, nb_pixelX, nb_pixelY,\
	"Grid representation window");
	if (!game->map.win)
		return (-1);
	game->map.grid.ptr = mlx_new_image(game->mlx_ptr, nb_pixelX, nb_pixelY);
	if (!game->map.grid.ptr)
		return (-1);
	game->map.img.ptr = mlx_new_image(game->mlx_ptr, nb_pixelX, nb_pixelY);
	if (!game->map.img.ptr)
		return (-1);
	game->map.grid.data = (int *)mlx_get_data_addr(game->map.grid.ptr, &game->map.grid.bpp, \
	&game->map.grid.size_line, &game->map.grid.endian);
	game->map.grid.height = nb_pixelY;
	game->map.grid.width = nb_pixelX;
	game->map.img.data = (int *)mlx_get_data_addr(game->map.img.ptr, &game->map.img.bpp, \
	&game->map.img.size_line, &game->map.img.endian);
	game->map.img.height = nb_pixelY;
	game->map.img.width = nb_pixelX;

	return (0);
}
