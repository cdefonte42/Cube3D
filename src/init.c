/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:13:54 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/29 12:52:04 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	init_player(t_game *game)
{
	game->player.fov = (70.0 * PI) / 180.0;
	game->player.dist_screen = (game->width / 2) / tan(game->player.fov / 2);
	game->player.pos.x += 0.5;
	game->player.pos.y += 0.5;
	game->player.pos.z = 0.0;
	game->player.dir.z = 0.0;
	game->player.rot_speed = (4.0 * PI) / 180;
	game->player.mv_speed = 8.0 / game->cube_size;
	game->player.rays = ft_calloc(sizeof(t_ray), game->width);
	if (!game->player.rays)
		return (-1);
	return (0);
}

/* Cree les pointeurs images sur des xpm files avec mlx_xpm_file_to_image(), et
remplit le int *data tableau contenant les pixels values. */
int	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < door)
	{
		if (!cb_load_mlx_image(game->mlx_ptr, game->text[i].path, \
		&(game->text[i])))
			return (error("Loading wall image", NULL), -1);
		++i;
	}
	revert_texture(game, wwall);
	revert_texture(game, swall);
	if (BONUS && !init_texture_door(game))
		return (-1);
	return (0);
}

static int	init_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx_ptr, SCREEN_W, SCREEN_H, "Cub3d");
	if (!game->win)
		return (-1);
	game->img.ptr = mlx_new_image(game->mlx_ptr, SCREEN_W, SCREEN_H);
	if (!game->img.ptr)
		return (-1);
	game->img.data = (int *)mlx_get_data_addr(game->img.ptr, &game->img.bpp, \
		&game->img.size_line, &game->img.endian);
	game->img.size_line /= 4;
	game->img.width = SCREEN_W;
	game->img.height = SCREEN_H;
	return (0);
}

int	init_game(t_game *game, char **argv)
{
	game->width = SCREEN_W;
	game->height = SCREEN_H;
	game->cube_size = CUBE_SIZE;
	game->colision = 8 / (double)game->cube_size;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (-1);
	game->text = ft_calloc(sizeof(t_texture), nb_textures);
	if (!map_parsing(game, argv[1]))
		return (-1);
	if (init_textures(game) == -1)
		return (-1);
	if (init_window(game) == -1)
		return (-1);
	if (init_map(game) == -1)
		return (-1);
	if (init_minimap(game) == -1)
		return (-1);
	if (init_player(game) == -1)
		return (-1);
	return (0);
}
