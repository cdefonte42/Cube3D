/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/24 14:51:30 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	main(int argc, char** argv)
{
	t_game	game;

	if (init_game(&game, argc, argv) == -1)
		return (printf("Error init mlx\n"), ft_exit(&game), 1);
	draw_map(&game);
	refresh_game(&game);

	mlx_key_hook(game.win, key_hook, &game);
	mlx_key_hook(game.map.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, &ft_exit, &game);
	mlx_hook(game.map.win, 17, 0, &ft_exit, &game);
	mlx_hook(game.win, 2, 1L<<0, &key_hook, &game);
	mlx_hook(game.map.win, 2, 1L<<0, &key_hook, &game);
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
