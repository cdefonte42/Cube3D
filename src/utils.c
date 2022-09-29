/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:15:23 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/20 14:52:47 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	cb_load_mlx_image(void *mlx_ptr, char *path, t_texture *texture)
{
	texture->ptr = mlx_xpm_file_to_image(mlx_ptr, path, \
	&texture->width, &texture->height);
	if (!texture->ptr)
		return (false);
	texture->data = (int *)mlx_get_data_addr(texture->ptr, \
	&texture->bpp, &texture->size_line, &texture->endian);
	texture->size_line /= 4;
	return (true);
}

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
