/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:06:40 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/15 17:29:27 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	isspace_null(char c)
{
	if (c == '\0' || ft_isspace(c))
		return (true);
	return (false);
}

static bool	isplayer(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
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

bool	map_check(t_game *game) // TODO: Removing debug info, Dont work with \t
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.tab[i][j] == '0' || isplayer(game->map.tab[i][j])) // || game->map.tab[i][j] == '2' pour bonus ?
			{
				if (i == 0 || i == game->map.height - 1 || j == 0 || \
				j == game->map.width - 1)
					return (error("Map not closed", game->map.tab[i]), \
					printf("%d\n%02d %s\n", j, i, game->map.tab[i]), false);
				if (check_diagonal(game, i, j) || check_side(game, i, j))
					return (error("Map not closed", game->map.tab[i]), \
					printf("%d\n%02d %s\n%02d %s\n%02d %s\n", j, i-1, \
					game->map.tab[i-1], i, game->map.tab[i], \
					i+1,game->map.tab[i+1]), false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
