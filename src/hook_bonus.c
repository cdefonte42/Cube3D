/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:54:24 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/21 18:01:54 by mbraets          ###   ########.fr       */
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
	if (x != SCREEN_W/2)
	{
		mlx_mouse_move(game->mlx_ptr, game->win, SCREEN_W/2, SCREEN_H/2);
		game->player.dir = rotate_vector(game->player.dir,
			(x-SCREEN_W/2)/(double)360);
		// printf("%d\n", (x-SCREEN_W/2));
	}
	return (0);
}