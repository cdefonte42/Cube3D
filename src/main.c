/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/24 14:22:54 by Cyrielle         ###   ########.fr       */
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

	if (init_game(&game, argc, argv) == -1)
		return (printf("Error init mlx\n"), ft_exit(&game), 1);
	draw_map(&game);
	cpy_img_pixels(game.map.grid, game.map.img);
	raycasting(&game);
	draw_player(&game);
	ray_tests(&game);


	mlx_put_image_to_window(game.mlx_ptr, game.map.win, game.map.img.ptr, 0, 0);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_key_hook(game.map.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, &ft_exit, &game);
	mlx_hook(game.map.win, 17, 0, &ft_exit, &game);
	mlx_hook(game.map.win, 2, 1L<<0, &key_hook, &game);
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
