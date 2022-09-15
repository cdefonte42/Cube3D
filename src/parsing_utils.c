/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:09:15 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/15 17:38:04 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clean_parse(char *line, int fd)
{
	get_next_line(-1);
	close(fd);
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
}

bool	error(char *reason, char *suffix)
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

bool	is_wall(char *line)
{
	if (line == NULL)
		return (false);
	return (*line == '1' || (*line != '\n' && ft_isspace(*line)));
}

bool	is_color(int *color, char *line)
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

bool	is_path(t_game *game, int flag, char *line)
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
