/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:06:40 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 16:00:08 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#if BONUS
# define NOWALL "NSEWCOX0"
#else
# define NOWALL "NSEW0"
#endif

static bool	isspace_null(char c)
{
	if (c == '\0' || ft_isspace(c))
		return (true);
	return (false);
}

static bool	check_diagonal(t_game *game, int y, int x)
{
	if (isspace_null(game->map.tab[y - 1][x - 1])
		|| isspace_null(game->map.tab[y - 1][x + 1])
		|| isspace_null(game->map.tab[y + 1][x - 1])
		|| isspace_null(game->map.tab[y + 1][x + 1]))
		return (true);
	return (false);
}

static bool	check_side(t_game *game, int y, int x)
{
	if (isspace_null(game->map.tab[y - 1][x])
		|| isspace_null(game->map.tab[y + 1][x])
		|| isspace_null(game->map.tab[y][x - 1])
		|| isspace_null(game->map.tab[y][x + 1]))
		return (true);
	return (false);
}

bool	map_check(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.tab[i][j] && ft_strchr(NOWALL, game->map.tab[i][j]))
			{
				if (i == 0 || i == game->map.height - 1 || j == 0 || \
				j == game->map.width - 1)
					return (error("Map not closed", game->map.tab[i]));
				if (check_diagonal(game, i, j) || check_side(game, i, j))
					return (error("Map not closed", game->map.tab[i]));
			}
			j++;
		}
		i++;
	}
	return (true);
}
