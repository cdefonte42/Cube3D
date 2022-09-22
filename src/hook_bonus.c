/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:54:24 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/22 15:20:08 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <time.h>

int	loop_hook(t_game *game)
{
	static clock_t	current_ticks;
	static clock_t	delta_ticks;
	static clock_t	fps = 0;
	int				x;
	int				y;

	current_ticks = clock();

	refresh_game(game);

	delta_ticks = clock() - current_ticks; //the time, in ms, that took to render
	if (delta_ticks > 0)
		fps = CLOCKS_PER_SEC / delta_ticks;
	if (delta_ticks < CLOCKS_PER_SEC / 20) // Useless ?
		usleep((CLOCKS_PER_SEC / 20 - delta_ticks));

	// printf("FPS : %ld\n", fps);
    // mlx_mouse_show(game->mlx_ptr, game->win);

	mlx_mouse_get_pos(game->mlx_ptr, game->win, &x, &y);
	if (game->player.keyboard.mouse && x != SCREEN_W/2)
	{
		mlx_mouse_move(game->mlx_ptr, game->win, SCREEN_W/2, SCREEN_H/2);
		game->player.dir = rotate_vector(game->player.dir,
			(x-SCREEN_W/2)/(double)360);
		// printf("%d\n", (x-SCREEN_W/2));
	}
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
	if (game->player.keyboard.left)
		game->player.dir = rotate_vector(game->player.dir,
				-game->player.rot_speed);
	if (game->player.keyboard.right)
		game->player.dir = rotate_vector(game->player.dir,
				game->player.rot_speed);
	return (0);
}

int	press_hook(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_exit(game);
	if (keycode == R_ARW)
		game->player.keyboard.right = !game->player.keyboard.right;
	else if (keycode == L_ARW)
		game->player.keyboard.left = !game->player.keyboard.left;
	if (keycode == W_KEY)
		game->player.keyboard.w = !game->player.keyboard.w;
	else if (keycode == S_KEY)
		game->player.keyboard.s = !game->player.keyboard.s;
	else if (keycode == A_KEY)
		game->player.keyboard.a = !game->player.keyboard.a;
	else if (keycode == D_KEY)
		game->player.keyboard.d = !game->player.keyboard.d;
	if (keycode == TAB)
		game->map.state = !game->map.state;
	return (0);
}

int	in_hook(t_game *game)
{
	(void)game;
	printf("in hook\n");
	game->player.keyboard.mouse = true;
	return (0);
}

int	out_hook(t_game *game)
{
	(void)game;
	printf("out hook\n");
	game->player.keyboard.mouse = false;
	return (0);
}