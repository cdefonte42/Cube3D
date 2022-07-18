/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/18 09:26:19 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>

/* Print toute la texture sur le creen, a partir de l'origine (x,y) */
void	put_texture_origin(unsigned int x, unsigned int y, t_img *screen, t_img *text)
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

/*Appellee quand red cross clicked ou ESC press*/
int	ft_exit(t_win *win)
{
	int	i;

	i = 0;
	while (win->map && win->map[i])
		free(win->map[i++]);
	if (win->map)
		free(win->map);
	i = 0;
	if (win->win_ptr)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win->mlx_ptr)
	{
		mlx_destroy_display(win->mlx_ptr);	//NON  DISPO SUR MAC
		mlx_loop_end(win->mlx_ptr);			//NON DISPO SUR MAC
		free(win->mlx_ptr);
	}
	exit (0);
}

/* Appellee quand mlx_key_hook declenchee */
int	key_hook(int keycode, void *param)
{
	t_win *win;

	win = param;
	if (keycode == ESC)
		ft_exit(win);
	return (0);
}

int	main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	/* ____ MLX INIT ___*/
	t_win	win;
	win.map = NULL;
	win.title = "Cub3D";
	win.width = SCREEN_W;
	win.height = SCREEN_H;
	win.mlx_ptr = NULL;
	win.win_ptr = NULL;
	win.mlx_ptr = mlx_init();
	if (!win.mlx_ptr)
		return (printf("Error init mlx ptr\n"), ft_exit(&win), 1);
	win.win_ptr = mlx_new_window(win.mlx_ptr, win.width, win.height, win.title);
	if (!win.win_ptr)
		return (printf("Error init win ptr\n"), ft_exit(&win), 1);

	/*_____ WALL IMG LOAD _____*/
	t_img	wall;
	wall.ptr = mlx_xpm_file_to_image(win.mlx_ptr, "img/wall_64_64.xpm", (int *)&wall.width, (int *)&wall.height);
	if (wall.ptr == NULL)
		return (printf("Error occurs new image wall\n"), ft_exit(&win), 1);
	wall.data = (int *)mlx_get_data_addr(wall.ptr, &wall.bpp, &wall.size_line, &wall.endian);
	printf("data size = %lu, bpp=%d, size_line=%d, endian=%d\n", sizeof(wall.data), wall.bpp, wall.size_line, wall.endian);

	/*_____ IMG CREATION _____*/
	t_img	screen;
	screen.ptr = mlx_new_image(win.mlx_ptr, SCREEN_W, SCREEN_H);
	if (screen.ptr == NULL)
		return (printf("Error occurs new image screen\n"), ft_exit(&win), 1);
	screen.data = (int *)mlx_get_data_addr(screen.ptr, &screen.bpp, &screen.size_line, &screen.endian);
	printf("screen data size = %lu, bpp=%d, size_line=%d, endian=%d\n", sizeof(screen.data), screen.bpp, screen.size_line, screen.endian);

	put_texture_origin(0, 0, &screen, &wall);
	put_texture_origin(100, 100, &screen, &wall);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, screen.ptr, 0, 0);

	mlx_key_hook(win.win_ptr, key_hook, &win);
	mlx_hook(win.win_ptr, 17, 0, &ft_exit, &win);
	mlx_loop(win.mlx_ptr);
	ft_exit(&win);
	return (0);
}
