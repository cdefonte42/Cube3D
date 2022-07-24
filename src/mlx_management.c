/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:32:55 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/24 16:48:16 by Cyrielle         ###   ########.fr       */
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
	if (game->img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.ptr);
	if (game->map.img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->map.img.ptr);
	if (game->map.tab)
		ft_free_map(game->map.tab);
	if (game->win)
		mlx_destroy_window(game->mlx_ptr, game->win);
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

/* Refresh les differents affichages (game screen, minimap). Implique le
recalcul de tous les rayons. */
void	refresh_game(t_game *game)
{
	cpy_img_pixels(game->map.grid, game->map.img);
	raycasting(game);
	draw_player(game);	// pour MINIMAP
	draw_all_rays(game);	// pour MINIMAP (et DEBUG)
	erase_img(&(game->img));
	draw_game(game);
	mlx_put_image_to_window(game->mlx_ptr, game->map.win, game->map.img.ptr, 0, 0);
	mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.ptr, 0, 0);
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
		//game->player.angle += game->player.rot_speed;
		refresh_game(game);
	}
	else if (keycode == L_ARW)
	{
		game->player.dir = rotate_vector_angle(game->player.dir, -game->player.rot_speed);
		//game->player.angle -= game->player.rot_speed;
		refresh_game(game);
	}
	else if (keycode == UP_ARW && !check_for_colision(game, keycode))
	{
		game->player.pos.x += game->player.dir.x * game->player.mv_speed;
		game->player.pos.y += game->player.dir.y * game->player.mv_speed;
		refresh_game(game);
	}
	else if (keycode == DOWN_ARW)
	{
		game->player.pos.x -= game->player.dir.x * game->player.mv_speed;
		game->player.pos.y -= game->player.dir.y * game->player.mv_speed;
		refresh_game(game);
	}
	return (0);
}
