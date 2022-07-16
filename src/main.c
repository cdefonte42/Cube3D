/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/16 17:40:54 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>

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
		//mlx_destroy_display(win->mlx_ptr);	//NON  DISPO SUR MAC
		//mlx_loop_end(win->mlx_ptr);			//NON DISPO SUR MAC
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

int	main(void) //(int argc, char** argv)
{
	/* ____ MLX INIT ___*/
	t_win	win;
	win.map = NULL;
	win.title = "Cub3D";
	win.width = SCREEN_W;
	win.height = SCREEN_H;
	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, win.width, win.height, win.title);

	/*_____ WALL IMG LOAD _____*/
	t_img	wall;
	wall.ptr = mlx_xpm_file_to_image(win.mlx_ptr, "img/wall_64_64.xpm", &wall.width, &wall.height);
	wall.data = mlx_get_data_addr(wall.ptr, &wall.bpp, &wall.size_line, &wall.endian);
	printf("data size = %lu, bpp=%d, size_line=%d, endian=%d\n", sizeof(wall.data), wall.bpp, wall.size_line, wall.endian);

	/*_____ IMG CREATION _____*/
	t_img	screen;
	screen.ptr = mlx_new_image(win.win_ptr, SCREEN_W, SCREEN_H);
	screen.data = mlx_get_data_addr(screen.ptr, &screen.bpp, &screen.size_line, &screen.endian);
	printf("screen data size = %lu, bpp=%d, size_line=%d, endian=%d\n", sizeof(screen.data), screen.bpp, screen.size_line, screen.endian);
	/* Afficher toutes les 4 lignes de l'image de wall : */
//	unsigned int	y = 0;
//	unsigned int	x = 0;
//	unsigned int	tab_size = (unsigned int)win.width * (unsigned int)win.height * 4;
//


	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, screen.ptr, 0, 0);
	mlx_key_hook(win.win_ptr, key_hook, &win);
	mlx_hook(win.win_ptr, 17, 0, &ft_exit, &win);
	mlx_loop(win.mlx_ptr);
	ft_exit(&win);
	return (0);
}
