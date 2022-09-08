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
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			return (true);
		i++;
	}
	return (false);
}

static bool	is_color(char *line)
{
	return (true);
}

static bool	is_path(char *line)
{
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

static int	checkflags(int *flags, char *line)
{
	if (line == NULL || line[0] == '\n')
		return (1);
	if (isvalidflag(line) == 0)
	{
		*flags = -1;
		return (error("Invalid flag", line));
	}
	if (*flags & isvalidflag(line))
	{
		*flags = -1;
		return (error("Duplicate flag", line));
	}
	if (isvalidflag(line) == F || isvalidflag(line) == C)
	{
		if (!is_color(line))
			return (error("Invalid color", line));
	}
	else
	{
		if (!is_path(line))
			return (error("Invalid path", line));
	}
	*flags |= isvalidflag(line);
	return (true);
}

int	map_checkheader(char *file)
{
	int		fd;
	char	*line;
	int		flags;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("Invalid file", file));
	flags = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_wall(line))
			break ;
		if (!checkflags(&flags, line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	get_next_line(-1);
	close(fd);
	if (line == NULL)
		return (error("Missing map", NULL));
	free(line);
	if (flags != -1 && flags != 0b111111)
		return (error("Missing flags", NULL));
	return (flags);
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

bool	map_parsing(char *file)
{
	if (is_cub(file) && map_checkheader(file) > 0)
		return (true);
	return (false);
}

#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac != 2)
		return (error("Invalid number of arguments", NULL));
	printf("%d\n", map_parsing(av[1]));
	return (0);
}
