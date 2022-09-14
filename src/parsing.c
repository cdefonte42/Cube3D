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
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
}

static void	set_player_pos(t_player *p, char c, int x, int y)
{
	ft_memcpy(&p.pos, &(t_pos){.x = i, .y = y, 0}, sizeof(t_pos));
	if (c == 'N')
		ft_memcpy(&p.dir, &(t_dir){.x = 0.f, .y = -1.f, .z = 0.f}, \
				sizeof(t_dir)); // TODO: Cyrielle: check if this is correct
	else if (c == 'S')
		ft_memcpy(&p.dir, &(t_dir){.x = 0.f, .y = 1.f, .z = 0.f}, \
				sizeof(t_dir));
	else if (c == 'W')
		ft_memcpy(&p.dir, &(t_dir){.x = -1.f, .y = 0.f, .z = 0.f}, \
				sizeof(t_dir));
	else if (c == 'E')
		ft_memcpy(&p.dir, &(t_dir){.x = 1.f, .y = 0.f, .z = 0.f}, \
				sizeof(t_dir));
}

static bool	check_line(t_game *game, int y, char *line, int *player)
{
	int		i;
	bool	valid_line;

	i = 0;
	valid_line = false;
	if (line == NULL)
		return (true);
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]) && !ft_strchr("01NSEW", line[i]))
			return (error("Invalid character map", line));
		if (ft_strchr("01NSEW", line[i]))
			valid_line = true;
		if (ft_strchr("NSEW", line[i]))
		{
			if (*player)
				return (error("Multiple player", line));
			*player = true;
			set_player_pos(&game->player, line[i], i, y);
		}
		i++;
	}
	if (!valid_line)
		return (error("Empty line in map", NULL));
	return (true);
}

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

static bool	set_default_flags(t_game *game)
{
	game->ceiling_color = 0x432F1A;
	game->floor_color = 0x432F1A;
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
			ft_strlcpy(game->map.tab[i], line, ft_strlen(line));
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}

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

bool	check_diagonal(t_game *game, int y, int x)
{
	if (isspace_null(game->map.tab[y - 1][x - 1])
		|| isspace_null(game->map.tab[y - 1][x + 1])
		|| isspace_null(game->map.tab[y + 1][x - 1])
		|| isspace_null(game->map.tab[y + 1][x + 1]))
		return (true);
	return (false);
}

bool	check_side(t_game *game, int y, int x)
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
			if (game->map.tab[i][j] == '0' || isplayer(game->map.tab[i][j])) //  || game->map.tab[i][j] == '2' pour bonus ?
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

bool	map_parsing(t_game *game, char *file)
{
	if (is_cub(file) && map_checkheader(game, file) == false)
		return (false);
	if (game->text[nwall].path == NULL && !set_default_flags(game))
		return (false);
	if (!map_init(game))
		return (false);
	if (!map_fill(game, file))
		return (false);
	if (!map_check(game))
		return (false);
	return (true);
}

#include <stdio.h>

int	main(int ac, char **av)
{
	t_game	game;

	game = (t_game){0};
	//ft_bzero(&game, sizeof(t_game));
	if (ac != 2)
		return (error("Invalid number of arguments", NULL));
	game.text = ft_calloc(sizeof(t_texture), 4);
	printf("%d\n", map_parsing(&game, av[1]));

	printf("Player spawn at x %f y %f \n", game.player.pos.x, game.player.pos.y);
	printf("Looking at x %f y %f \n", game.player.dir.x, game.player.dir.y);
	printf("Floor color 0x%X\nCeiling color 0x%X\n", game.floor_color, game.ceiling_color);
	for (size_t i = 0; i < 4; i++)
	{
		printf("path: %s.\n", game.text[i].path);
		free(game.text[i].path);
	}
	free(game.text);
	ft_free_map_i(game.map.tab, game.map.height);
	return (0);
}
