/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:26:52 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 11:26:53 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "parsing.h"

static bool	allocate_sprites(t_game *game)
{
	game->bonus.nb_sp += 4;
	game->bonus.sps = ft_calloc(game->bonus.nb_sp, sizeof(t_sprite));
	if (game->bonus.sps == NULL)
		return (false);
	game->bonus.sort_sp = ft_calloc(game->bonus.nb_sp, sizeof(int));
	if (game->bonus.sort_sp == NULL)
		return (false);
	return (true);
}

// +4 for the playersNb
bool	init_sprite(t_game *game)
{
	int		i;
	int		j;
	int		k;

	if (!allocate_sprites(game))
		return (false);
	i = 0;
	k = 4;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.tab[i][j] == 'X')
			{
				ft_memcpy(&game->bonus.sps[k], &(t_sprite){.pos.x = j + 0.5, \
				.pos.y = i + 0.5, .type = coin, .anim_size = COINS_NB}, \
				sizeof(t_sprite));
				++k;
			}
			++j;
		}
		++i;
	}
	return (true);
}

// Count how many sprites are in the map + 4 for the players
void	count_sprite(t_game *game, char *line)
{
	int		i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] == 'X')
			++(game->bonus.nb_sp);
		++i;
	}
}
