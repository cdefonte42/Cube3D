/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/23 22:35:06 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	ray_tests(t_game *game)
{
	t_ray	*rays = game->player.rays;
	int	i = 0;
	while (i < game->width - 1)
	{
		draw_ray(game, rays[i], PURPLE);
		draw_square(game, rays[i].hit_point.pos[grid], 5, LIME);
		i += 6;
	}
	draw_ray(game, rays[159], YELLOW);
	draw_square(game, rays[159].hit_point.pos[grid], 5, PINK);
}

int	main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	/* ____ MLX INIT ___*/
	t_game	game;
	game.map.tab = ft_clean_map(argc, argv); // A PROTEGER
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
	game.player.pos.x = 8.5; //exprime en map unit, soit *64 pour pixels
	game.player.pos.y = 3.5;
	game.player.pos.z = 0.0;
	game.player.dir.x = -0.450; // ATTENTION compris entre -1 et 1!!! EXPRIME EN MAP
	game.player.dir.y = 0.55;
	game.player.dir.z = 0.0;
	//game.player.angle = atan(game.player.dir.y / game.player.dir.x);
	game.player.rot_speed = (4 * PI) / 180;
	game.player.mv_speed = 5.0 / 64.0; // se deplace de 5 pixels en appuyant 1 fois sur touche, sur l'axe du player
	game.player.rays = malloc(sizeof(t_ray) * game.width); // A PROTEGER

	if (init_mlx(&game) == -1)
		return (printf("Error init mlx\n"), ft_exit(&game), 1);
	if (init_map(&game) == -1)
		return (printf("Error init map datas\n"), ft_exit(&game), 1);
	draw_map(&game);
	cpy_img_pixels(game.map.grid, game.map.img);
	raycasting(&game);
	draw_player(&game);
	draw_square(&game, game.player.rays[159].hit_point.pos[grid], 5, PINK);

	ray_tests(&game);


	mlx_put_image_to_window(game.mlx_ptr, game.map.win, game.map.img.ptr, 0, 0);
	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_key_hook(game.map.win, key_hook, &game);
	mlx_hook(game.win_ptr, 17, 0, &ft_exit, &game);
	mlx_hook(game.map.win, 17, 0, &ft_exit, &game);
	mlx_hook(game.map.win, 2, 1L<<0, &key_hook, &game);
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
