/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/29 20:36:12 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <time.h>

clock_t current_ticks, delta_ticks;
clock_t fps = 0;

int	loop(t_game *game)
{
	(void) game;
	current_ticks = clock();

	refresh_game(game);

	delta_ticks = clock() - current_ticks; //the time, in ms, that took to render
	if (delta_ticks > 0)
		fps = CLOCKS_PER_SEC / delta_ticks;
	if (delta_ticks < CLOCKS_PER_SEC / 20) // Useless ?
		usleep((CLOCKS_PER_SEC / 20 - delta_ticks));
	// printf("FPS : %ld\n%ld %ld\n", fps, delta_ticks, CLOCKS_PER_SEC / 20);

    // mlx_mouse_show(game->mlx_ptr, game->win);

	int x = 0;
	int y = 0;
	mlx_mouse_get_pos(game->mlx_ptr, game->win, &x, &y);
	if (x != SCREEN_W/2 || y != SCREEN_H/2)
	{
		mlx_mouse_move(game->mlx_ptr, game->win, SCREEN_W/2, SCREEN_H/2);
		game->player.dir = rotate_vector(game->player.dir,
			(x-SCREEN_W/2)/(double)360);
		// printf("%d\n", (x-SCREEN_W/2));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (init_game(&game, argc, argv) == -1)
		return (ft_exit(&game), 1);
	refresh_game(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_key_hook(game.win, tab_hook, &game);
//	mlx_key_hook(game.map.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, &ft_exit, &game);
//	mlx_hook(game.map.win, 17, 0, &ft_exit, &game);
	mlx_hook(game.win, 2, 1L << 0, &key_hook, &game);
//	mlx_hook(game.map.win, 2, 1L<<0, &key_hook, &game);
    mlx_mouse_hide(game.mlx_ptr, game.win);
	mlx_mouse_hook(game.win, NULL, NULL);
	mlx_loop_hook(game.mlx_ptr, loop, &game);
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
