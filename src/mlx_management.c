/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:32:55 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/29 15:16:10 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#ifndef LINUX
void	mlx_destroy_display(void *);
#endif

/*Appellee quand red cross clicked ou ESC press*/
int	ft_exit(t_game *game)
{
	int	i;

	i = 0;
	if (!game)
		return (0);
	if (game->text)
	{
		while (i < nb_textures)
		{
			if (game->text[i].ptr)
				mlx_destroy_image(game->mlx_ptr, game->text[i].ptr);
			++i;
		}
		free(game->text);
	}
	if (game->player.rays)
		free(game->player.rays);
	if (game->img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.ptr);
	if (game->map.img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->map.img.ptr);
	if (game->map.grid.ptr)
		mlx_destroy_image(game->mlx_ptr, game->map.grid.ptr);
	if (game->map.tab)
		ft_free_map(game->map.tab);
	if (game->win)
		mlx_destroy_window(game->mlx_ptr, game->win);
	if (game->map.win)
		mlx_destroy_window(game->mlx_ptr, game->map.win);
	if (game->mlx_ptr)
	{
		#ifdef __linux__
		mlx_destroy_display(game->mlx_ptr);
		#endif
		//mlx_loop_end(game->mlx_ptr);			//NON DISPO SUR MAC
		free(game->mlx_ptr);
	}
	exit (0);
}

/* Refresh les differents affichages (game screen, minimap). Implique le
recalcul de tous les rayons. */
void	refresh_game(t_game *game)
{
	raycasting(game);
	cpy_img_pixels(game->map.grid, game->map.img);
	draw_player(game);	// pour MINIMAP
	draw_all_rays(game);	// pour MINIMAP (et DEBUG)
	draw_game(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.ptr, 0, 0);
	mlx_put_image_to_window(game->mlx_ptr, game->win, game->map.img.ptr, 0,0);
//	mlx_put_image_to_window(game->mlx_ptr, game->map.win, game->map.img.ptr, 0,0);
//	mlx_put_image_to_window(game->mlx_ptr, game->map.win, game->map.img.ptr, -(game->player.pos.x * game->cube_size) + game->height / 8 , -(game->player.pos.y * game->cube_size) + game->height / 8);
}

/* Appellee quand mlx_key_hook declenchee */
int	key_hook(int keycode, void *param)
{
	t_game *game;

	game = param;
	if (keycode == ESC)
		ft_exit(game);
	if (keycode == R_ARW)
	{
		game->player.dir = rotate_vector(game->player.dir, game->player.rot_speed);
//		game->player.angle += game->player.rot_speed;
		refresh_game(game);
	}
	else if (keycode == L_ARW)
	{
		game->player.dir = rotate_vector(game->player.dir, -game->player.rot_speed);
//		game->player.angle -= game->player.rot_speed;
		refresh_game(game);
	}
	else if (keycode == W_KEY)
	{
		back_front_mvx(game, 1, game->colision);
		back_front_mvy(game, 1, game->colision);
		refresh_game(game);
	}
	else if (keycode == S_KEY)
	{
		back_front_mvx(game, -1, game->colision);
		back_front_mvy(game, -1, game->colision);
		refresh_game(game);
	}
	else if (keycode == A_KEY)
	{
		stepaside_mvx(game, 1, game->colision);
		stepaside_mvy(game, 1, game->colision);
		refresh_game(game);
	}
	else if (keycode == D_KEY)
	{
		stepaside_mvx(game, -1, game->colision);
		stepaside_mvy(game, -1, game->colision);
		refresh_game(game);
	}
	return (0);
}
