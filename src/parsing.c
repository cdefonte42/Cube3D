/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:50:01 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/26 12:39:19 by cdefonte         ###   ########.fr       */
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

static bool	set_default_flags(t_game *game)
{
	game->ceiling_color = DARK_GREY;
	game->floor_color = GREY;
	game->text[nwall].path = ft_strdup("img/tech_nwall_64.xpm");
	if (game->text[nwall].path == NULL)
		return (error("malloc failed", NULL));
	game->text[swall].path = ft_strdup("img/tech_swall_64.xpm");
	if (game->text[swall].path == NULL)
		return (error("malloc failed", NULL));
	game->text[wwall].path = ft_strdup("img/tech_wwall_64.xpm");
	if (game->text[wwall].path == NULL)
		return (error("malloc failed", NULL));
	game->text[ewall].path = ft_strdup("img/tech_ewall_64.xpm");
	if (game->text[ewall].path == NULL)
		return (error("malloc failed", NULL));
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
	if (game->text != NULL && game->text[nwall].path == NULL \
		&& !set_default_flags(game))
		return (false);
	if (!map_init(game))
		return (false);
	if (!map_fill(game, file))
		return (false);
	if (!map_check(game))
		return (false);
	return (true);
}
