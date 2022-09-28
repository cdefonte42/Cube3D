/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:06:35 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/28 12:01:28 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#ifdef BONUS 
# define OK_CHARS "01NSEWXD"
#else
# define OK_CHARS "01NSEW"
#endif

static int	isvalidflag(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
		return (NO);
	if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
		return (SO);
	if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
		return (WE);
	if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
		return (EA);
	if (ft_strncmp(line, "F", 1) == 0 && ft_isspace(line[1]))
		return (F);
	if (ft_strncmp(line, "C", 1) == 0 && ft_isspace(line[1]))
		return (C);
	return (0);
}

static int	checkflags(t_game *game, int *flags, char *line)
{
	int	flags_tmp;
	int	flag;

	flag = isvalidflag(line);
	if (line == NULL || line[0] == '\n')
		return (true);
	flags_tmp = *flags;
	(*flags) = -1;
	if (flag == 0)
		return (error("Invalid flag", line));
	if (flags_tmp & flag)
		return (error("Duplicate flag", line));
	if (flag >= NO && flag <= EA && !is_path(game, flag, line))
		return (error("Invalid path", line));
	else if ((flag == F && !is_color(&(game->floor_color), line)) || \
	(flag == C && !is_color(&(game->ceiling_color), line)))
		return (error("Invalid color", line));
	flags_tmp |= flag;
	(*flags) = flags_tmp;
	return (true);
}

static void	set_player_pos(t_player *p, char c, int x, int y)
{
	ft_memcpy(&p->pos, &(t_pos){.x = x, .y = y, 0}, sizeof(t_pos));
	if (c == 'N')
		ft_memcpy(&p->dir, &(t_dir){.x = 0., .y = -1., .z = 0.}, \
				sizeof(t_dir));	
	else if (c == 'S')
		ft_memcpy(&p->dir, &(t_dir){.x = 0., .y = 1., .z = 0.}, \
				sizeof(t_dir));
	else if (c == 'W')
		ft_memcpy(&p->dir, &(t_dir){.x = -1., .y = 0., .z = 0.}, \
				sizeof(t_dir));
	else if (c == 'E')
		ft_memcpy(&p->dir, &(t_dir){.x = 1., .y = 0., .z = 0.}, \
				sizeof(t_dir));
}

bool	check_line(t_game *game, int y, char *line, int *player)
{
	int		i;
	bool	valid_line;

	i = 0;
	valid_line = false;
	if (line == NULL)
		return (true);
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]) && !ft_strchr(OK_CHARS, line[i]))
			return (error("Invalid character map", line));
		if (ft_strchr(OK_CHARS, line[i]))
			valid_line = true;
		if (ft_strchr("NSEW", line[i]))
		{
			if (*player)
				return (error("Multiple player", line));
			*player = true;
			set_player_pos(&game->player, line[i], i, y);
		}
		++i;
	}
	if (!valid_line)
		return (error("Empty line in map", NULL));
	return (true);
}

int	map_checkheader(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		flags;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("Invalid file", file), false);
	flags = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_wall(line) || !checkflags(game, &flags, line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (line == NULL)
		return (close(fd), error("Missing map", NULL), false);
	if (flags == -1)
		return (clean_parse(line, fd), false);
	if (flags != 0 && flags != -1 && flags != 0b111111)
		return (clean_parse(line, fd), error("Missing flags", NULL));
	return (map_checkcharacters(game, line, fd));
}
