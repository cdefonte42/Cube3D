/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:12:21 by cdefonte          #+#    #+#             */
/*   Updated: 2022/09/29 11:43:56 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	init_coin_sprites(t_game *game)
{
	int		i;
	char	*path[COINS_NB];

	i = 0;
	ft_memcpy(path, (char *[COINS_NB]){"img/GoldCoinSprite/coin1.xpm", \
	"img/GoldCoinSprite/coin2.xpm", "img/GoldCoinSprite/coin3.xpm", \
	"img/GoldCoinSprite/coin4.xpm", "img/GoldCoinSprite/coin5.xpm", \
	"img/GoldCoinSprite/coin6.xpm"}, sizeof(char *) * COINS_NB);
	while (i < COINS_NB)
	{
		if (!cb_load_mlx_image(game->mlx_ptr, path[i], \
		&game->bonus.text_sp[coin][i]))
			return (error("Loading sprites coin image", NULL));
		++i;
	}
	return (true);
}

static bool	init_ply_sprites(t_game *game)
{
	int		i;
	char	*path[PLAYERS_NB];

	i = 0;
	ft_memcpy(path, (char *[PLAYERS_NB]){"img/player-0.xpm", "img/player-1.xpm",
		"img/player-2.xpm", "img/player-3.xpm"}, sizeof(char *) * PLAYERS_NB);
	while (i < PLAYERS_NB)
	{
		if (!cb_load_mlx_image(game->mlx_ptr, path[i], \
		&game->bonus.text_sp[player][i]))
			return (error("Loading sprites player image", NULL));
		++i;
	}
	return (true);
}

bool	init_sprites_text(t_game *game)
{
	int	i;

	if (!init_coin_sprites(game))
		return (false);
	if (!init_ply_sprites(game))
		return (false);
	i = 0;
	while (i < game->bonus.nb_sp)
	{
		game->bonus.sort_sp[i] = i;
		if (game->bonus.sps[i].anim_size == 0)
			game->bonus.sps[i].anim_size = 4;
		++i;
	}
	return (true);
}
