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

/* Check que chaque ligne de map a la meme taille */
int	ft_isok_len(char **map)
{
	size_t	len;
	int		i;

	if (!map || !*map)
		return (-1);
	len = ft_strlen(*map);
	i = 0;
	while (map && map[i])
	{
		if (len != ft_strlen(map[i]))
			return (ft_putstr_fd("Error\nAll lines must have the same \
length.\n", 2), -1);
		i++;
	}
	return (0);
}

/* Check que tous les str de tab contiennent des char admis (0, 1, P, E ou C) */
int	ft_isok_char(char **map)
{
	int	i;
	int	j;

	if (!map || !map[0])
		return (-1);
	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'P'
				&& map[i][j] != 'E' && map[i][j] != 'C')
				return (ft_putstr_fd("Error\nMap must contain only '0' \
'1' 'E' 'P' and 'C'.\n", 2), -1);
			j++;
		}
		i++;
	}
	return (0);
}

/* Open un fichier en .ber et retourne le nombre de lignes.
Retourne -1 si erreur.*/
int	ft_nb_line(char *filename)
{
	int		fd;
	char	*gnl;
	int		nb_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	nb_line = 0;
	gnl = get_next_line(fd);
	while (gnl != NULL && ++nb_line < 2147483647)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
	get_next_line(-1);
	if (close(fd) == -1)
		return (-1);
	return (nb_line);
}
