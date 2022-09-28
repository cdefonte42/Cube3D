/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:12:21 by cdefonte          #+#    #+#             */
/*   Updated: 2022/09/28 10:53:59 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	init_sprites_text(t_game *game)
{
	int		i;
	char	*path[6];

	i = 0;

	ft_memcpy(path, (char *[6]){"img/GoldCoinSprite/coin1.xpm", "img/GoldCoinSprite/coin2.xpm", \
	"img/GoldCoinSprite/coin3.xpm", "img/GoldCoinSprite/coin4.xpm", "img/GoldCoinSprite/coin5.xpm", "img/GoldCoinSprite/coin6.xpm"}, sizeof(char *) * 6);
	while (i < 6)
	{
		game->bonus.text_sp[i].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
		path[i], &game->bonus.text_sp[i].width, &game->bonus.text_sp[i].height);
		if (!game->bonus.text_sp[i].ptr)
			return (error("loading sprites img", NULL), -1);
		game->bonus.text_sp[i].data = (int *)mlx_get_data_addr(game->bonus.text_sp[i].ptr, \
		&game->bonus.text_sp[i].bpp, &game->bonus.text_sp[i].size_line, &game->bonus.text_sp[i].endian);
		game->bonus.text_sp[i].size_line /= 4;
		++i;
	}
	i = 0;
	while (i < game->bonus.nb_sp)
	{
		game->bonus.sort_sp[i] = i;
		++i;
	}
	return (0);
}
