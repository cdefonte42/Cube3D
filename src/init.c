/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:13:54 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/28 12:56:01 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	init_minimap(t_game *game)
{
	if (game->map.img.height > game->height * 0.25 || \
	game->map.img.width > game->width * 0.25)
	{
		game->minimap.height = game->height * 0.25;
			game->minimap.width = game->minimap.height;
		game->minimap.ptr = mlx_new_image(game->mlx_ptr, game->minimap.width, \
			game->minimap.height);
		if (!game->minimap.ptr)
			return (-1);
		game->minimap.data = (int *)mlx_get_data_addr(game->minimap.ptr, \
		&game->minimap.bpp, &game->minimap.size_line, &game->minimap.endian);
		game->minimap.size_line /= 4;
	}
	else
		game->minimap.ptr = NULL;
	return (0);
}

int	init_map(t_game *game, int argc, char **argv)
{
	int		nb_pixel_x;
	int		nb_pixel_y;

	if (argc != 2)
		return (error("Invalid number of arguments", NULL), -1);
	game->text = ft_calloc(sizeof(t_texture), nb_textures);
	if (!map_parsing(game, argv[1]))
		return (-1);
	// game->map.tab = ft_clean_map(argc, argv); // A PROTEGER
	// game->map.width = ft_strlen(game->map.tab[0]);
	// game->map.height = ft_tabtablen(game->map.tab);
	game->map.state = off;
	game->map.rcube_size = 16;
	game->map.ratio = (double)game->map.rcube_size / (double)game->cube_size;
	nb_pixel_x = game->map.width * game->map.rcube_size + 1;
	nb_pixel_y = game->map.height * game->map.rcube_size + 1;
	game->map.grid.ptr = mlx_new_image(game->mlx_ptr, nb_pixel_x, nb_pixel_y);
	if (!game->map.grid.ptr)
		return (-1);
	game->map.img.ptr = mlx_new_image(game->mlx_ptr, nb_pixel_x, nb_pixel_y);
	if (!game->map.img.ptr)
		return (-1);
	game->map.grid.data = (int *)mlx_get_data_addr(game->map.grid.ptr, \
	&game->map.grid.bpp, &game->map.grid.size_line, &game->map.grid.endian);
	game->map.grid.size_line /= 4;
	game->map.grid.height = nb_pixel_y;
	game->map.grid.width = nb_pixel_x;
	game->map.img.data = (int *)mlx_get_data_addr(game->map.img.ptr, \
	&game->map.img.bpp, &game->map.img.size_line, &game->map.img.endian);
	game->map.img.size_line /= 4;
	game->map.img.height = nb_pixel_y;
	game->map.img.width = nb_pixel_x;
	draw_walls(game);
	return (0);
}

int	init_player(t_game *game)
{
	game->player.fov = (70.0 * PI) / 180.0;
	game->player.dist_screen = (game->width / 2) / tan(game->player.fov / 2);
	// Replace = 2.5 by += .5 to spawn in the middle
	game->player.pos.x += 0.5; //exprime en map unit, soit *64 pour pixels
	game->player.pos.y += 0.5;
	game->player.pos.z = 0.0;
	// game->player.dir.x = 0.0; // ATTENTION compris entre -1 et 1!!! EXPRIME EN MAP
	// game->player.dir.y = 1.0;
	game->player.dir.z = 0.0;
	//game->player.angle = atan(game.player.dir.y / game.player.dir.x);
	game->player.rot_speed = (4.0 * PI) / 180; // se tou0rne de 4 degres
	game->player.mv_speed = 8.0 / game->cube_size; // se deplace de 5 pixels en appuyant 1 fois sur touche, sur l'axe du player
	game->player.rays = malloc(sizeof(t_ray) * game->width);
	if (!game->player.rays)
		return (-1);
	return (0);
}

static void	revert_texture(t_game *game, int i)
{
	int			j;
	int			k;
	int			tmp;
	t_texture	*text;

	text = &game->text[i];
	j = 0;
	while (j < text->width / 2)
	{
	k = 0;
		while (k < text->height)
		{
			tmp = text->data[k * text->width + j];
			text->data[k * text->width + j] = text->data[k * text->width + \
			text->width - j - 1];
			text->data[k * text->width + text->width - j - 1] = tmp;
			k++;
		}
		j++;
	}
}

/* Cree les pointeurs images sur des xpm files avec mlx_xpm_file_to_image(), et
remplit le int *data tableau contenant les pixels values. */
// NOTE : pas beau, copie colle, d'ou l'interet de rajouter un char *filename
// a la structure s_img 
int	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < door)
	{
		game->text[i].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	game->text[i].path, &game->text[i].width, &game->text[i].height);
		if (!game->text[i].ptr)
			return (error("loading wall img", NULL), -1);
		game->text[i].data = (int *)mlx_get_data_addr(game->text[i].ptr, \
		&game->text[i].bpp, &game->text[i].size_line, &game->text[i].endian);
		game->text[i].size_line /= 4;
		i++;
	}
	game->text[i].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
"img/west_wall_64_64.xpm", &game->text[i].width, &game->text[i].height);
	if (!game->text[i].ptr)
		return (error("loading wall img", NULL), -1);
	game->text[i].data = (int *)mlx_get_data_addr(game->text[i].ptr, \
	&game->text[i].bpp, &game->text[i].size_line, &game->text[i].endian);
	game->text[i].size_line /= 4;
	revert_texture(game, wwall);
	revert_texture(game, swall);

	return (0);
}

int	init_game(t_game *game, int argc, char **argv)
{
	game->width = SCREEN_W;
	game->height = SCREEN_H;
	game->cube_size = CUBE_SIZE;
	game->colision = 8 / (double)game->cube_size;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (-1);
	if (init_map(game, argc, argv) == -1)
		return (-1);
	if (init_textures(game) == -1)
		return (-1);
	game->win = mlx_new_window(game->mlx_ptr, SCREEN_W, SCREEN_H, "Cub3d");
	if (!game->win)
		return (-1);
	game->img.ptr = mlx_new_image(game->mlx_ptr, SCREEN_W, SCREEN_H);
	if (!game->img.ptr)
		return (-1);
	game->img.data = (int *)mlx_get_data_addr(game->img.ptr, &game->img.bpp, \
		&game->img.size_line, &game->img.endian);
	game->img.size_line /= 4;
	game->img.width = SCREEN_W;
	game->img.height = SCREEN_H;
	
	if (init_minimap(game) == -1)
		return (-1);
	if (init_player(game) == -1)
		return (-1);
	return (0);
}
