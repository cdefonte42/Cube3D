/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/18 17:00:55 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>

void	raytracing(t_game *game)
{
	
}

/* Print 1 fois tous les bits de la texture sur le screen, a une origine donnee (x,y) */
// params a changer en t_wn*, et ajouter enum orientation pour choisir la bonne texture
// changer x et y en t_pos pour les coordonnees d'origine
// Attention ne check pas si on depasse le screen!!!
void	put_texture_origin(unsigned int x, unsigned int y, t_screen *screen, t_texture *text)
{
	unsigned int	text_line = 0;
	unsigned int	screen_line = 0;
	unsigned int	i = 0;// x + y * (screen->size_line / 4);
	unsigned int	nb_pixels_text;

	nb_pixels_text = text->width * text->height;
	while (i < nb_pixels_text)
	{
		screen->data[(i % text->width) + screen_line + (y * (screen->size_line / 4)) + x] = text->data[(i % text->width) + text_line];
		++i;
		if (i % text->width == 0)
		{
			text_line += (text->size_line / 4);
			screen_line += screen->size_line / 4;
		}
	}
}

/* Permet de texturiser, avec une texture donee, le screen sur une width et une height; */
void	put_sized_texture(unsigned int width, unsigned int height, t_screen *screen, t_texture *text)
{
	unsigned int	x = 0;
	unsigned int	y = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			put_texture_origin(x, y, screen, text);
			y += 64;
		}
		x += 64;
	}
}

/*Appellee quand red cross clicked ou ESC press*/
int	ft_exit(t_game *game)
{
	int	i;

	i = 0;
	while (game->map && game->map[i])
		free(game->map[i++]);
	if (game->map)
		free(game->map);
	i = 0;
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);	//NON  DISPO SUR MAC
		mlx_loop_end(game->mlx_ptr);			//NON DISPO SUR MAC
		free(game->mlx_ptr);
	}
	exit (0);
}

/* Appellee quand mlx_key_hook declenchee */
int	key_hook(int keycode, void *param)
{
	t_game *game;

	game = param;
	if (keycode == ESC)
		ft_exit(game);
	return (0);
}

int	main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	/* ____ MLX INIT ___*/
	t_game	game;
	game.map = NULL;
	game.title = "Cub3D";
	game.width = SCREEN_W;
	game.height = SCREEN_H;
	game.player.fov = 60.0 * PI / 180.0;
	game.player.dist_screen = 60.0 * PI / 180.0;
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
		return (printf("Error init mlx ptr\n"), ft_exit(&game), 1);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.width, game.height, game.title);
	if (!game.win_ptr)
		return (printf("Error init win ptr\n"), ft_exit(&game), 1);

	/*_____ WALL texture LOAD _____*/
	t_texture	wall;
	wall.ptr = mlx_xpm_file_to_image(game.mlx_ptr, "img/wall_64_64.xpm", (int *)&wall.width, (int *)&wall.height);
	if (wall.ptr == NULL)
		return (printf("Error occurs new image wall\n"), ft_exit(&game), 1);
	wall.data = (int *)mlx_get_data_addr(wall.ptr, &wall.bpp, &wall.size_line, &wall.endian);
	printf("data size = %lu, bpp=%d, size_line=%d, endian=%d\n", sizeof(wall.data), wall.bpp, wall.size_line, wall.endian);

	/*_____ IMG/SCREEN CREATION _____*/
	t_screen	screen;
	screen.ptr = mlx_new_image(game.mlx_ptr, SCREEN_W, SCREEN_H);
	if (screen.ptr == NULL)
		return (printf("Error occurs new image screen\n"), ft_exit(&game), 1);
	screen.data = (int *)mlx_get_data_addr(screen.ptr, &screen.bpp, &screen.size_line, &screen.endian);
	game.screen = screen;
	printf("screen data size = %lu, bpp=%d, size_line=%d, endian=%d\n", sizeof(screen.data), screen.bpp, screen.size_line, screen.endian);

	raytracing(&game);
	/* Filling screen with texturized pixels */
//	put_sized_texture(192, 192, &screen, &wall);
//	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, screen.ptr, 0, 0);

	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_hook(game.win_ptr, 17, 0, &ft_exit, &game);
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
