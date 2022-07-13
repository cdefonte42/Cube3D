/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:26:03 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/13 13:03:46 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Enleve les '\n' en fin de colonne de la **map */
char	**ft_remove_n(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		if (map[i][j] == '\n')
			return (ft_free_map(map), ft_putstr_fd("Error\nNo new line \
accepted.\n", 2), NULL);
		while (map[i][j])
		{
			if (map[i][j] == '\n')
				map[i][j] = '\0';
			j++;
		}
		i++;
	}
	return (map);
}

/* Alloue un char **tab */
char	**ft_new_map(char *filename, int nb_line)
{
	char	**map;
	int		fd;
	int		i;

	if (nb_line <= 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *) * (nb_line + 1));
	if (!map)
		return (NULL);
	i = -1;
	while (++i < nb_line)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
			return (ft_free_map(map), get_next_line(-1), NULL);
	}
	map[nb_line] = 0;
	get_next_line(-1);
	if (close(fd) == -1)
		return (ft_free_map(map), NULL);
	return (ft_remove_n(map));
}

/* Check que la map est bien entouree de walls 
Need une map sans les '\n' */
int	ft_check_walls(char **map)
{
	int		i;
	size_t	j;
	int		end;

	if (!map || !*map)
		return (-1);
	i = 0;
	end = ft_tabtablen(map) - 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && (i == 0 || i == end || j == 0
				|| j == ft_strlen(map[i]) - 1))
				return (ft_putstr_fd("Error\nMap must be surrounded by \
walls!\n", 2), -1);
			j++;
		}
		i++;
	}
	return (0);
}

/* Retourne la map cleaned */
char	**ft_clean_map(int argc, char **argv)
{
	char	**map;
	int		len;
	int		nb_line;

	if (argc != 2)
		return (ft_putstr_fd("Error\nYou need 1 argument.\n", 2), NULL);
	len = ft_strlen(argv[1]);
	if (ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		return (ft_putstr_fd("Error\n.cub extension needed.\n", 2), NULL);
	nb_line = ft_nb_line(argv[1]);
	if (nb_line >= 0 && nb_line <= 2)
		return (ft_putstr_fd("Error\nMap must contain at least 3 \
lines.\n", 2), NULL);
	else if (nb_line < 0)
		return (ft_putstr_fd("Error\nCannot open file. You should check \
the pathname.\n", 2), NULL);
	map = ft_new_map(argv[1], nb_line);
	if (!map)
		return (NULL);
	if (ft_isok_char(map) != 0 || ft_isok_len(map) != 0
		|| ft_check_walls(map) != 0)
		return (ft_free_map(map), NULL);
	return (map);
}
