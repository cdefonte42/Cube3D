/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/21 18:38:16 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	/* ____ MLX INIT ___*/
	t_game	game;
	game.map.tab = ft_clean_map(argc, argv);
	game.map.width = ft_strlen(game.map.tab[0]);
	game.map.height = ft_tabtablen(game.map.tab);
	game.screen.ptr = NULL;
	game.map.img.ptr = NULL;
	game.title = "Cub3D";
	game.width = SCREEN_W;
	game.height = SCREEN_H;
	game.cube_size = 64.0;
	game.player.fov = (60.0 * PI) / 180.0;
	game.player.dist_screen = (game.width / 2) / tan(game.player.fov / 2);
	game.player.pos.x = 6.5; //exprime en map unit, soit *64 pour pixels
	game.player.pos.y = 2.5;
	game.player.pos.z = 0.0;
	game.player.dir.x = 0.5; // ATTENTION compris entre -1 et 1!!! EXPRIME EN MAP
	game.player.dir.y = -0.2; // North
	game.player.dir.z = 0.0;

	if (init_mlx(&game) == -1)
		return (printf("Error init mlx\n"), ft_exit(&game), 1);

	if (draw_map(&game) == -1)
		return (ft_exit(&game), 1);
	mlx_put_image_to_window(game.mlx_ptr, game.map.img.ptr, 0, 0);
	
	t_ray	*rays;
	rays = raycasting(&game); // A PROTEGER
//	int	i = 0;
//	while (i < game.width - 1)
//	{
//		draw_ray(&game, rays[i], CYAN);
//		i += 6;
//	}
	draw_ray(&game, rays[159], YELLOW);
	draw_ray(&game, rays[0], CYAN);
	draw_ray(&game, rays[319], CYAN);
	draw_ray_until_first_Vline(&game, rays[159], RED);
	draw_ray_until_first_Vline(&game, rays[0], PURPLE);
	draw_ray_until_first_Vline(&game, rays[319], PURPLE);
	draw_all_hit_points(rays[159], 

	free(rays);

	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_key_hook(game.map.win, key_hook, &game);
	mlx_hook(game.win_ptr, 17, 0, &ft_exit, &game);
	mlx_hook(game.map.win, 17, 0, &ft_exit, &game);
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
