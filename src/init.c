/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:13:54 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/24 14:25:15 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	init_map(t_game *game, int argc, char **argv)
{
	int		nb_pixelX;
	int		nb_pixelY;

	game->map.tab = ft_clean_map(argc, argv); // A PROTEGER
	game->map.width = ft_strlen(game->map.tab[0]);
	game->map.height = ft_tabtablen(game->map.tab);
	nb_pixelX = game->map.width * game->cube_size + 1;
	nb_pixelY = game->map.height * game->cube_size + 1;
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

int	init_player(t_game *game)
{
	game->player.fov = (60.0 * PI) / 180.0;
	game->player.dist_screen = (game->width / 2) / tan(game->player.fov / 2);
	game->player.pos.x = 8.5; //exprime en map unit, soit *64 pour pixels
	game->player.pos.y = 3.5;
	game->player.pos.z = 0.0;
	game->player.dir.x = -0.450; // ATTENTION compris entre -1 et 1!!! EXPRIME EN MAP
	game->player.dir.y = 0.55;
	game->player.dir.z = 0.0;
	//game->player.angle = atan(game.player.dir.y / game.player.dir.x);
	game->player.rot_speed = (4 * PI) / 180; // se tourne de 4 degres
	game->player.mv_speed = 5.0 / 64.0; // se deplace de 5 pixels en appuyant 1 fois sur touche, sur l'axe du player
	game->player.rays = malloc(sizeof(t_ray) * game->width);
	if (!game->player.rays)
		return (-1);
	return (0);
}

int	init_game(t_game *game, int argc, char **argv)
{
	game->width = SCREEN_W;
	game->height = SCREEN_H;
	game->cube_size = 64.0;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (-1);
	game->win = mlx_new_window(game->mlx_ptr, SCREEN_W, SCREEN_H, "Cub3d");
	if (!game->win)
		return (-1);
	game->img.ptr = mlx_new_image(game->mlx_ptr, SCREEN_W, SCREEN_H);
	if (!game->img.ptr)
		return (-1);
	
	if (init_map(game, argc, argv) == -1)
		return (-1);
	if (init_player(game) == -1)
		return (-1);
	return (0);
}
