/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:39:35 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/27 18:21:48 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	map_init(t_game *game)
{
	int	i;

	game->map.tab = ft_calloc(game->map.height, sizeof(char *));
	if (!game->map.tab)
		return (error("malloc failed", NULL));
	i = 0;
	while (i < game->map.height)
	{
		game->map.tab[i] = ft_calloc(game->map.width, sizeof(char));
		if (!game->map.tab[i])
			return (ft_free_map(game->map.tab), \
					error("malloc failed", NULL));
		i++;
	}
	return (true);
}

bool	map_fill(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("Invalid file", file), false);
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		if (is_wall(line))
		{
			if (line[ft_strlen(line) - 1] != '\n')
				ft_strlcpy(game->map.tab[i], line, ft_strlen(line) + 1); // +1 is cause problem unles the line is the last??
			else
				ft_strlcpy(game->map.tab[i], line, ft_strlen(line));
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}
