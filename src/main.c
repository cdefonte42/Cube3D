/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/21 17:57:36 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	loop_hook(t_game *game);

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
	#ifdef BONUS
    mlx_mouse_hide(game.mlx_ptr, game.win);
	mlx_mouse_hook(game.win, NULL, NULL);
	mlx_loop_hook(game.mlx_ptr, loop_hook, &game);
	#endif
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
