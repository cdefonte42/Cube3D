/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:42:49 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/19 13:50:17 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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

int	texturize_screen_tests(t_game *game)
{

	/*_____ WALL texture LOAD _____*/
	t_texture	wall;
	wall.ptr = mlx_xpm_file_to_image(game->mlx_ptr, "img/wall_64_64.xpm", (int *)&wall.width, (int *)&wall.height);
	if (wall.ptr == NULL)
		return (printf("Error occurs new image wall\n"), ft_exit(game), 1);
	wall.data = (int *)mlx_get_data_addr(wall.ptr, &wall.bpp, &wall.size_line, &wall.endian);
	printf("data size = %lu, bpp=%d, size_line=%d, endian=%d\n", sizeof(wall.data), wall.bpp, wall.size_line, wall.endian);

	/*_____ IMG/SCREEN CREATION _____*/
	t_screen	screen;
	screen.ptr = mlx_new_image(game->mlx_ptr, SCREEN_W, SCREEN_H);
	if (screen.ptr == NULL)
		return (printf("Error occurs new image screen\n"), ft_exit(game), 1);
	screen.data = (int *)mlx_get_data_addr(screen.ptr, &screen.bpp, &screen.size_line, &screen.endian);
	game->screen = screen;
	printf("screen data size = %lu, bpp=%d, size_line=%d, endian=%d\n", sizeof(screen.data), screen.bpp, screen.size_line, screen.endian);
	/* Filling screen with texturized pixels */
//	put_sized_texture(192, 192, &screen, &wall);
//	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, screen.ptr, 0, 0);
	return (0);
}
