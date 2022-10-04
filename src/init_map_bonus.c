/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:25:51 by cdefonte          #+#    #+#             */
/*   Updated: 2022/09/29 15:18:20 by cdefonte         ###   ########.fr       */
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

static int	init_img(t_game *game, t_img *img, int pxlx, int pxly)
{
	img->ptr = mlx_new_image(game->mlx_ptr, pxlx, pxly);
	if (!img->ptr)
		return (-1);
	img->data = (int *)mlx_get_data_addr(img->ptr, \
	&img->bpp, &img->size_line, &img->endian);
	img->size_line /= 4;
	img->height = pxly;
	img->width = pxlx;
	return (0);
}

/* Draw (fill pixels) sur l'image de la map 2D viewed les pixels correspondants
aux walls. Va dabord chercher a quelle map unit position se trouve un wall,
puis fait appel a fill_cube pour remplir cette case. Iter l'operation sur toutes
les cases de la map. */
void	draw_grid_walls(t_game *game)
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
				fill_cube_grid(game, i, j, GREY);
			else if (game->map.tab[i][j] == 'O' || game->map.tab[i][j] == 'C')
				fill_cube_grid(game, i, j, PURPLE);
			++j;
		}
		++i;
	}
}

int	init_map(t_game *game)
{
	int		nb_pixel_x;
	int		nb_pixel_y;

	game->map.state = false;
	game->map.rcube_size = 16;
	game->map.ratio = (double)game->map.rcube_size / (double)game->cube_size;
	nb_pixel_x = game->map.width * game->map.rcube_size + 1;
	nb_pixel_y = game->map.height * game->map.rcube_size + 1;
	if (init_img(game, &game->map.img, nb_pixel_x, nb_pixel_y) == 1)
		return (-1);
	if (init_img(game, &(game->map.grid), nb_pixel_x, nb_pixel_y) == 1)
		return (-1);
	draw_grid_walls(game);
	return (0);
}
