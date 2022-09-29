/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:07:58 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/15 17:47:47 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cubed.h"
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

enum e_mapflags
{
	NO	= 0b1,
	SO	= 0b10,
	WE	= 0b100,
	EA	= 0b1000,
	F	= 0b10000,
	C	= 0b100000,
};

/* UTILS */
bool	error(char *reason, const char *suffix);
bool	is_wall(char *line);
bool	is_color(int *color, char *line);
bool	is_path(t_game *game, int flag, char *line);
void	clean_parse(char *line, int fd);

/* Check flags */
int		map_checkheader(t_game *game, char *file);

/* Check maps */
bool	check_line(t_game *game, int y, char *line, int *player);
bool	map_checkcharacters(t_game *game, char *line, int fd);
bool	map_check(t_game *game);
bool	map_init(t_game *game);
bool	map_fill(t_game *game, char *file);

#endif