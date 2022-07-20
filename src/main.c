/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/20 22:58:03 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	fill_cube(t_game *game, int y, int x, int color)
{
	int *pixels = game->map.img.data;
	int	size_line = game->map.img.size_line / 4;	// nb de pixels par lignes
	int	origin_line = y * game->cube_size * size_line;
	int	origin_col = x * game->cube_size;
	int	max_line = origin_line + game->cube_size * size_line;
	int	max_col = origin_col + game->cube_size;;

	for (int line = origin_line; line < max_line; line += size_line)
	{
		for (int col = origin_col; col < max_col; ++col)
			pixels[col + line] = color;
	}
}

void	draw_grid(t_game *game)
{
	int *pixels = game->map.img.data;
	int	size_line = game->map.img.size_line / 4;	// nb de pixels par lignes
	int	max_line = size_line * game->cube_size * game->map.height;

	for (int line = 0; line <= max_line; line += size_line)
	{
		for (int col = 0; col < size_line; col += game->cube_size)
			pixels[col + line] = 0xFFFFFF;	// lignes verticales en blanc
	}
	for (int line = 0; line <= max_line; line += game->cube_size * size_line)
	{
		for (int col = 0; col < size_line; ++col)
			pixels[col + line] = 0xFFFFFF;	// lignes horizontales en blanc
	}
}

void	draw_walls(t_game *game)
{
	for (int i = 0; i < game->map.height; ++i)
	{
		for (int j = 0; j < game->map.width; ++j)
		{
			if (game->map.tab[i][j] == '1')
				fill_cube(game, i, j, 0x008000);
		}
	}
}

t_pos	convert_system(t_pos from, enum e_sys_ids to)
{
	t_pos	res;

	res.sid = to;
	if (from.sid == map && to == grid)
	{
		res.x = 64.0 * from.x;
		res.y = 64.0 * from.y;
	}
	else if (from.sid == grid && to == map)
	{
		res.x = from.x / 64.0;
		res.y = from.y / 64.0;
	}
	return (res);
}

void	draw_player(t_game *game)
{
	int	size_line = game->map.img.size_line / 4;	// nb de pixels par lignes
	int	origin_line = (game->player.pos.y * game->cube_size - 5) * size_line;
	int	origin_col = game->player.pos.x * game->cube_size - 5;
	int	max_line = origin_line + 10 * size_line;
	int	max_col = origin_col + 10;
	int	*pixels = game->map.img.data;

	for (int line = origin_line; line < max_line; line += size_line)
	{
		for (int col = origin_col; col < max_col; ++col)
		{
			pixels[col + line] = 0xFF0000;

		}
	}
}

//void	draw_line(t_game *game)
//{
//	int	nb_ray = game->width;
//	t_ray	ray;
//
//	ray.increment = tan(game->player.fov / 2) / (game->width / 2);
//	
//}

int	draw_map(t_game *game)
{
	int		nb_pixelX = game->map.width * game->cube_size + 1;
	int		nb_pixelY = game->map.height * game->cube_size + 1;

	game->map.win = mlx_new_window(game->mlx_ptr, nb_pixelX, nb_pixelY,\
	"Grid representation window");
	if (!game->map.win)
		return (-1);
	game->map.img.ptr = mlx_new_image(game->mlx_ptr, nb_pixelX, nb_pixelY);
	if (!game->map.img.ptr)
		return (printf("draw_map: failed to init map img\n"), -1);
	game->map.img.data = (int *)mlx_get_data_addr(game->map.img.ptr, &game->map.img.bpp, \
	&game->map.img.size_line, &game->map.img.endian);

	draw_walls(game);
	draw_grid(game);
	draw_player(game);

	mlx_put_image_to_window(game->mlx_ptr, game->map.win, game->map.img.ptr, 0, 0);
	return (0);
}

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
	game.player.pos.sid = map;
	game.player.pos.x = 6.5; //exprime en map unit, soit *64 pour pixels
	game.player.pos.y = 2.5;
	game.player.pos.z = 0.0;
	game.player.dir.sid = map;
	game.player.dir.x = -0.5; // ATTENTION compris entre -1 et 1!!!
	game.player.dir.y = 0.8; // North
	game.player.dir.z = 0.0;

	if (init_mlx(&game) == -1)
		return (printf("Error init mlx\n"), ft_exit(&game), 1);

	if (draw_map(&game) == -1)
		return (ft_exit(&game), 1);
	
	raytracing(&game);

	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_key_hook(game.map.win, key_hook, &game);
	mlx_hook(game.win_ptr, 17, 0, &ft_exit, &game);
	mlx_hook(game.map.win, 17, 0, &ft_exit, &game);
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
