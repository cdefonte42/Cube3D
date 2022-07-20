/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/20 12:45:42 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"



int	main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	/* ____ MLX INIT ___*/
	t_game	game;
	game.map = ft_clean_map(argc, argv);
	game.title = "Cub3D";
	game.width = SCREEN_W;
	game.height = SCREEN_H;
	game.cube_size = 64.0;
	game.player.fov = (60.0 * PI) / 180.0;
	game.player.dist_screen = game.width / tan(game.player.fov);
	game.player.pos.sid = map;
	game.player.pos.x = 6.5; //exprime en map unit, soit *64 pour pixels
	game.player.pos.y = 2.5;
	game.player.pos.z = 0.0;
	game.player.dir.sid = map;
	game.player.dir.x = 0.0;
	game.player.dir.y = -1.0; // North
	game.player.dir.z = 0.0;


	raytracing(&game);

	if (init_mlx(&game) == -1)
		return (printf("Error init mlx\n"), ft_exit(&game), 1);

	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_hook(game.win_ptr, 17, 0, &ft_exit, &game);
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
