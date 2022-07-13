/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:15:23 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/13 13:06:46 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Free tous les elements d'un char **map*/
void	ft_free_map(char **map)
{
	char	**tmp;

	if (!map)
		return ;
	tmp = map;
	while (map && *map)
	{
		free(*map);
		map++;
	}
	free(*map);
	free(tmp);
}
