/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:52:53 by cdefonte          #+#    #+#             */
/*   Updated: 2022/09/29 11:54:05 by cdefonte         ###   ########.fr       */
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

void	revert_texture(t_game *game, int i)
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
