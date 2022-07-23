/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:32:55 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/23 13:06:38 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*Appellee quand red cross clicked ou ESC press*/
// Manque pas mal de destroy, notemment le tableau de texture 
int	ft_exit(t_game *game)
{
	if (!game)
		return (0);
	if (game->player.rays)
		free(game->player.rays);
	if (game->screen.ptr)
		mlx_destroy_image(game->mlx_ptr, game->screen.ptr);
	if (game->map.img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->map.img.ptr);
	if (game->map.tab)
		ft_free_map(game->map.tab);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->map.win)
		mlx_destroy_window(game->mlx_ptr, game->map.win);
	if (game->mlx_ptr)
	{
		//mlx_destroy_display(game->mlx_ptr);	//NON  DISPO SUR MAC
		//mlx_loop_end(game->mlx_ptr);			//NON DISPO SUR MAC
		free(game->mlx_ptr);
	}
	exit (0);
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
		game->player.dir = rotate_vector_angle(game->player.dir, game->player.rot_speed);
		game->player.angle += game->player.rot_speed;
		cpy_img_pixels(game->map.grid, game->map.img);
		draw_player(game);
		raycasting(game);
		ray_tests(game);
		mlx_put_image_to_window(game->mlx_ptr, game->map.win, game->map.img.ptr, 0, 0);
	}
	else if (keycode == L_ARW)
	{
		game->player.dir = rotate_vector_angle(game->player.dir, -game->player.rot_speed);
		game->player.angle -= game->player.rot_speed;
		cpy_img_pixels(game->map.grid, game->map.img);
		draw_player(game);
		raycasting(game);
		ray_tests(game);
		mlx_put_image_to_window(game->mlx_ptr, game->map.win, game->map.img.ptr, 0, 0);
	}
	else if (keycode == UP_ARW)
	{
		game->player.pos.x += cos(game->player.angle) * game->player.mv_speed;
		game->player.pos.y += sin(game->player.angle) * game->player.mv_speed;
		cpy_img_pixels(game->map.grid, game->map.img);
		draw_player(game);
		raycasting(game);
		ray_tests(game);
		mlx_put_image_to_window(game->mlx_ptr, game->map.win, game->map.img.ptr, 0, 0);
	}
	else if (keycode == DOWN_ARW)
	{
		game->player.pos.x -= cos(game->player.angle) * game->player.mv_speed;
		game->player.pos.y -= sin(game->player.angle) * game->player.mv_speed;
		cpy_img_pixels(game->map.grid, game->map.img);
		draw_player(game);
		raycasting(game);
		ray_tests(game);
		mlx_put_image_to_window(game->mlx_ptr, game->map.win, game->map.img.ptr, 0, 0);
	}
	return (0);
}

int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (-1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->width, game->height, game->title);
	if (!game->win_ptr)
		return (-1);
	return (0);
}
