/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:12:21 by cdefonte          #+#    #+#             */
/*   Updated: 2022/09/27 16:56:54 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	init_sprites_text(t_game *game)
{
	int		i;
	char	*path[4];

	i = 0;
	ft_memcpy(path, (char *[4]){"img/sprites_1.xpm", "img/sprites_2.xpm", \
	"img/sprites_3.xpm", "img/sprites_4.xpm"}, sizeof(char *) * 4);
	while (i < 4)
	{
		game->text_sprite[i].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
		path[i], &game->text_sprite[i].width, &game->text_sprite[i].height);
		if (!game->text_sprite[i].ptr)
			return (error("loading sprites img", NULL), -1);
		game->text_sprite[i].data = (int *)mlx_get_data_addr(game->text_sprite[i].ptr, \
		&game->text_sprite[i].bpp, &game->text_sprite[i].size_line, &game->text_sprite[i].endian);
		game->text_sprite[i].size_line /= 4;
		++i;
	}
	// A CHANGER SELON PARSING MAP NB ENNEMIES
	game->nb_sprites = 2;
	game->sprites = ft_calloc(2, sizeof(t_sprite));
	game->sort_sprite = ft_calloc(2, sizeof(int *));
	ft_memcpy(&game->sprites[0], &(t_sprite){.pos.x = 4.5, .pos.y = 2.5, .pos.z = 0.0, .dist = 0.0, .dir = 0.0}, sizeof(t_sprite));
	ft_memcpy(&game->sprites[1], &(t_sprite){.pos.x = 6.5, .pos.y = 2.5, .pos.z = 0.0, .dist = 0.0, .dir = 0.0}, sizeof(t_sprite));
	return (0);
}
