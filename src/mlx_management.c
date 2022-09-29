/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:32:55 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/29 16:29:28 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "socket.h"

/* Refresh les differents affichages (game screen, minimap). Implique le
recalcul de tous les rayons. */
void	refresh_game(t_game *game)
{
	raycasting(game);
	if (BONUS)
		draw_map(game);
	draw_game(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.ptr, 0, 0);
	if (!BONUS)
		return ;
	if (game->minimap.ptr != NULL && !game->map.state)
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
		game->map.state = !game->map.state;
		if (!BONUS)
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
	if (!BONUS)
		refresh_game(game);
	return (0);
}
