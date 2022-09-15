/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:32:55 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/08 17:00:04 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
			{
				free(game->text[i].path);
				mlx_destroy_image(game->mlx_ptr, game->text[i].ptr);
			}
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
		ft_free_map_i(game->map.tab, game->map.height);
	if (game->win)
		mlx_destroy_window(game->mlx_ptr, game->win);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit (0);
}

/* Refresh les differents affichages (game screen, minimap). Implique le
recalcul de tous les rayons. */
void	refresh_game(t_game *game)
{
	raycasting(game);
	draw_map(game);
	draw_game(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.ptr, 0, 0);
	if (game->minimap.ptr != NULL && game->map.state == off)
	{
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win,
			game->minimap.ptr, 0, 0);
	}
	else
		mlx_put_image_to_window(game->mlx_ptr, game->win,
			game->map.img.ptr, 0, 0);
}

int	tab_hook(int keycode, void *param)
{
	t_game	*game;

	game = param;
	if (keycode == TAB)
	{
		if (game->map.state == off)
			game->map.state = on;
		else
			game->map.state = off;
		refresh_game(game);
	}
	return (0);
}

void	dispatch_player_move(t_game *game, int keycode)
{
	if (keycode == W_KEY)
	{
		back_front_mvx(game, 1, game->colision);
		back_front_mvy(game, 1, game->colision);
	}
	else if (keycode == S_KEY)
	{
		back_front_mvx(game, -1, game->colision);
		back_front_mvy(game, -1, game->colision);
	}
	else if (keycode == A_KEY)
	{
		stepaside_mvx(game, 1, game->colision);
		stepaside_mvy(game, 1, game->colision);
	}
	else if (keycode == D_KEY)
	{
		stepaside_mvx(game, -1, game->colision);
		stepaside_mvy(game, -1, game->colision);
	}
}

/* Appellee quand mlx_key_hook declenchee */
int	key_hook(int keycode, void *param)
{
	t_game	*game;

	game = param;
	if (keycode == ESC)
		ft_exit(game);
	if (keycode == R_ARW)
		game->player.dir = rotate_vector(game->player.dir,
				game->player.rot_speed);
	else if (keycode == L_ARW)
		game->player.dir = rotate_vector(game->player.dir,
				-game->player.rot_speed);
	else
		dispatch_player_move(game, keycode);
	refresh_game(game);
	return (0);
}
