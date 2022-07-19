/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:15:23 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/19 13:42:18 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Free tous les elements d'un char **map*/
void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		free(map[i++]);
	if (map)
		free(map);
}

/*Appellee quand red cross clicked ou ESC press*/
int	ft_exit(t_game *game)
{
	ft_free_map(game->map);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		//mlx_destroy_display(game->mlx_ptr);	//NON  DISPO SUR MAC
		//mlx_loop_end(game->mlx_ptr);			//NON DISPO SUR MAC
		free(game->mlx_ptr);
	}
	exit (0);
}
