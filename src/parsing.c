/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:50:01 by mbraets           #+#    #+#             */
/*   Updated: 2022/10/10 12:12:22 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	map_checkcharacters(t_game *game, char *line, int fd)
{
	int		player;
	int		y;

	player = false;
	game->map.height++;
	y = 0;
	while (line != NULL)
	{
		count_sprite(game, line);
		game->map.height++;
		if (game->map.width < (int)ft_strlen(line))
			game->map.width = ft_strlen(line);
		if (!check_line(game, y, line, &player))
			return (clean_parse(line, fd), false);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	line = NULL;
	if (!player)
		return (error("Missing player", NULL));
	close(fd);
	if (game->map.width >= 1500 || game->map.height >= 1500)
		return (error("Map too big", NULL));
	return (true);
}

static bool	is_cub(char *file)
{
	int	len;

	if (file == NULL)
		return (false);
	len = ft_strlen(file);
	if (len < 5)
		return (error("Invalid file name", file));
	if (ft_strncmp(file + len - 4, ".cub", 4) == 0)
		return (true);
	error("Invalid file extension", file);
	return (false);
}

bool	map_parsing(t_game *game, char *file)
{
	if (!is_cub(file))
		return (false);
	if (map_checkheader(game, file) == false)
		return (false);
	if (!map_init(game))
		return (false);
	if (!map_fill(game, file))
		return (false);
	if (!map_check(game))
		return (false);
	if (BONUS && !init_sprite(game))
		return (false);
	return (true);
}
