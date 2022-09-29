/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:25:51 by cdefonte          #+#    #+#             */
/*   Updated: 2022/09/29 11:52:03 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	init_minimap(t_game *game)
{
	if (game->map.img.height > game->height * 0.25 || \
	game->map.img.width > game->width * 0.25)
	{
		game->minimap.height = game->height * 0.25;
			game->minimap.width = game->minimap.height;
		game->minimap.ptr = mlx_new_image(game->mlx_ptr, game->minimap.width, \
			game->minimap.height);
		if (!game->minimap.ptr)
			return (-1);
		game->minimap.data = (int *)mlx_get_data_addr(game->minimap.ptr, \
		&game->minimap.bpp, &game->minimap.size_line, &game->minimap.endian);
		game->minimap.size_line /= 4;
	}
	else
		game->minimap.ptr = NULL;
	return (0);
}

int	init_map(t_game *game)
{
	int		nb_pixel_x;
	int		nb_pixel_y;

	game->map.state = off;
	game->map.rcube_size = 16;
	game->map.ratio = (double)game->map.rcube_size / (double)game->cube_size;
	nb_pixel_x = game->map.width * game->map.rcube_size + 1;
	nb_pixel_y = game->map.height * game->map.rcube_size + 1;
	game->map.grid.ptr = mlx_new_image(game->mlx_ptr, nb_pixel_x, nb_pixel_y);
	if (!game->map.grid.ptr)
		return (-1);
	game->map.img.ptr = mlx_new_image(game->mlx_ptr, nb_pixel_x, nb_pixel_y);
	if (!game->map.img.ptr)
		return (-1);
	game->map.grid.data = (int *)mlx_get_data_addr(game->map.grid.ptr, \
	&game->map.grid.bpp, &game->map.grid.size_line, &game->map.grid.endian);
	game->map.grid.size_line /= 4;
	game->map.grid.height = nb_pixel_y;
	game->map.grid.width = nb_pixel_x;
	game->map.img.data = (int *)mlx_get_data_addr(game->map.img.ptr, \
	&game->map.img.bpp, &game->map.img.size_line, &game->map.img.endian);
	game->map.img.size_line /= 4;
	game->map.img.height = nb_pixel_y;
	game->map.img.width = nb_pixel_x;
	draw_walls(game);
	return (0);
}
