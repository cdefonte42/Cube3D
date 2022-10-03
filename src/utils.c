/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:15:23 by cdefonte          #+#    #+#             */
/*   Updated: 2022/09/29 16:29:04 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Free tous les elements d'un char **map*/
void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		free(map[i++]);
	if (map)
		free(map);
}

void	ft_free_map_i(char **map, int height)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (i < height)
		{
			free(map[i]);
			map[i] = NULL;
			i++;
		}
		free(map);
		map = NULL;
	}
}

static void	clear_texture(void *mlx_ptr, t_texture *textures, int size, bool al)
{
	int	i;

	i = 0;
	if (textures == NULL || size <= 0)
		return ;
	while (i < size)
	{
		if (textures[i].path != NULL)
			free(textures[i].path);
		if (textures[i].ptr)
			mlx_destroy_image(mlx_ptr, textures[i].ptr);
		++i;
	}
	if (al)
		free(textures);
}

void	exit_bonus(t_game *game)
{
	clear_texture(game->mlx_ptr, game->bonus.text_sp[player], 4, false);
	clear_texture(game->mlx_ptr, game->bonus.text_sp[coin], 6, false);
	if (game->bonus.sort_sp)
		free(game->bonus.sort_sp);
	if (game->bonus.sps)
		free(game->bonus.sps);
	if (game->bonus.buf != NULL)
		free(game->bonus.buf);
	if (game->bonus.sock > 0)
		close(game->bonus.sock);
	if (game->mlx_ptr && game->win)
	{
		mlx_mouse_show(game->mlx_ptr, game->win);
		mlx_do_key_autorepeaton(game->mlx_ptr);
	}
	if (game->map.img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->map.img.ptr);
	if (game->map.grid.ptr)
		mlx_destroy_image(game->mlx_ptr, game->map.grid.ptr);
	if (game->minimap.ptr)
		mlx_destroy_image(game->mlx_ptr, game->minimap.ptr);
}

/*Appellee quand red cross clicked ou ESC press*/
int	ft_exit(t_game *game)
{
	if (!game)
		return (0);
	exit_bonus(game);
	clear_texture(game->mlx_ptr, game->text, nb_textures, true);
	if (game->player.rays)
		free(game->player.rays);
	if (game->img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.ptr);
	if (game->map.tab)
		ft_free_map_i(game->map.tab, game->map.height);
	if (game->win)
		mlx_destroy_window(game->mlx_ptr, game->win);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(0);
}
