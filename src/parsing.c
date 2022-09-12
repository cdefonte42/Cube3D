/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:50:01 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/13 13:01:04 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

enum e_mapflags
{
	NO	= 0b1,
	SO	= 0b10,
	WE	= 0b100,
	EA	= 0b1000,
	F	= 0b10000,
	C	= 0b100000,
};

static bool	error(char *reason, char *suffix)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(reason, 2);
	if (suffix != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(suffix, 2);
	}
	ft_putchar_fd('\n', 2);
	return (false);
}

static bool	is_wall(char *line)
{
	if (line == NULL)
		return (false);
	return (*line == '1' || (*line != '\n' && ft_isspace(*line)));
}

static bool	is_color(int *color, char *line)
{
	char	*tmp;
	int		colors[3];
	int		i;

	tmp = line + 1;
	while (ft_isspace(*tmp))
		tmp++;
	i = 3;
	while (i--)
	{
		if (!ft_isdigit(*tmp))
			return (false);
		colors[i] = ft_atoi(tmp);
		if (colors[i] < 0 || colors[i] > 255)
			return (false);
		while (ft_isdigit(*tmp))
			tmp++;
		if (i && *tmp != ',')
			return (false);
		tmp++;
	}
	*color = (colors[0] << 16) + (colors[1] << 8) + colors[2];
	return (true);
}

static bool	is_path(t_game *game, int flag, char *line)
{
	char	*tmp;
	char	*path;

	tmp = line + 2;
	while (ft_isspace(*tmp))
		tmp++;
	if (*tmp == '\0')
		return (false);
	path = ft_strndup(tmp, ft_strlen(tmp) - 1);
	if (path == NULL)
		return (error("malloc failed", NULL));
	if (flag == NO)
		game->text[nwall].path = path;
	else if (flag == SO)
		game->text[swall].path = path;
	else if (flag == WE)
		game->text[wwall].path = path;
	else if (flag == EA)
		game->text[ewall].path = path;
	return (true);
}

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

static void	clean_parse(char *line, int fd)
{
	get_next_line(-1);
	close(fd);
}

static bool	check_line(t_game *game, char *line, int *player)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (true);
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]) && !ft_strchr("01NSEW", line[i]))
			return (error("Invalid character map", line));
		if (ft_strchr("NSEW", line[i]))
		{
			if (*player)
				return (error("Multiple player", line));
			*player = true;
		}
		i++;
	}
	return (true);
}

bool	map_check(t_game *game, char *line, int fd)
{
	int		player;

	player = false;
	while (line != NULL)
	{
		if (!check_line(game, line, &player))
			return (free(line), false);
		free(line);
		line = get_next_line(fd);
	}
	line = NULL;
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
		return (clean_parse(line, fd), error("Missing flags", NULL), false);
	flags = map_check(game, line, fd);
	return (clean_parse(line, fd), flags);
}

static bool	set_default_path(t_game *game)
{
	game->text[nwall].path = ft_strdup("./textures/north.xpm");
	if (game->text[nwall].path == NULL)
		return (error("malloc failed", NULL));
	game->text[swall].path = ft_strdup("./textures/south.xpm");
	if (game->text[swall].path == NULL)
		return (error("malloc failed", NULL));
	game->text[wwall].path = ft_strdup("./textures/west.xpm");
	if (game->text[wwall].path == NULL)
		return (error("malloc failed", NULL));
	game->text[ewall].path = ft_strdup("./textures/east.xpm");
	if (game->text[ewall].path == NULL)
		return (error("malloc failed", NULL));
	return (true);
}

bool	is_cub(char *file)
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
	if (is_cub(file) && map_checkheader(game, file) == false)
		return (false);
	if (game->text[nwall].path == NULL && !set_default_path(game))
		return (false);
	return (true);
}

#include <stdio.h>

int	main(int ac, char **av)
{
	t_game	game;

	game = (t_game){0};
	if (ac != 2)
		return (error("Invalid number of arguments", NULL));
	game.text = ft_calloc(sizeof(t_texture), 4);
	printf("%d\n", map_parsing(&game, av[1]));
	for (size_t i = 0; i < 4; i++)
	{
		printf("path: %s.\n", game.text[i].path);
		free(game.text[i].path);
	}
	free(game.text);
	return (0);
}
