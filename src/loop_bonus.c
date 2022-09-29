/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:24:57 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 17:24:58 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#include <time.h>

#include "socket.h"

static inline bool	is_player_move(t_keyboard keyboard)
{
	return (keyboard.w == true || keyboard.d == true \
	|| keyboard.a == true || keyboard.s == true);
}

static void	handle_movement(t_game *game)
{
	if (game->player.keyboard.shift)
		game->player.mv_speed = 0.4;
	else
		game->player.mv_speed = 0.1;
	if (game->player.keyboard.w)
	{
		back_front_mvx(game, 1, game->colision);
		back_front_mvy(game, 1, game->colision);
	}
	if (game->player.keyboard.s)
	{
		back_front_mvx(game, -1, game->colision);
		back_front_mvy(game, -1, game->colision);
	}
	if (game->player.keyboard.a)
	{
		stepaside_mvx(game, 1, game->colision);
		stepaside_mvy(game, 1, game->colision);
	}
	if (game->player.keyboard.d)
	{
		stepaside_mvx(game, -1, game->colision);
		stepaside_mvy(game, -1, game->colision);
	}
}

static void	handle_camera(t_game *game)
{
	int		x;
	int		y;

	if (game->player.keyboard.left)
		game->player.dir = rotate_vector(game->player.dir,
				-game->player.rot_speed);
	if (game->player.keyboard.right)
		game->player.dir = rotate_vector(game->player.dir,
				game->player.rot_speed);
	mlx_mouse_get_pos(game->mlx_ptr, game->win, &x, &y);
	if (game->player.keyboard.mouse && x != SCREEN_W / 2)
	{
		mlx_mouse_move(game->mlx_ptr, game->win, SCREEN_W / 2, SCREEN_H / 2);
		game->player.dir = rotate_vector(game->player.dir, \
			(x - SCREEN_W / 2) / (double)360);
	}
}

int	loop_hook(t_game *game)
{
	clock_t	current_ticks;
	clock_t	delta_ticks;

	if (game->bonus.sock > 0)
	{
		if (!get_pos(game))
			ft_exit(game);
		if (is_player_move(game->player.keyboard))
			if (!send_pos(game))
				ft_exit(game);
	}
	current_ticks = clock();
	refresh_game(game);
	delta_ticks = clock() - current_ticks;
	if (delta_ticks < CLOCKS_PER_SEC / 20)
		usleep((CLOCKS_PER_SEC / 20 - delta_ticks));
	handle_movement(game);
	handle_camera(game);
// ++game->bonus.tick; // NOTE: uncomment to enable tick counter
	return (0);
}
