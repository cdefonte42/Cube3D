/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:00:03 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/23 18:29:56 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Si la distance entre le mur et le player est inferieure a la distance a 
parcourir, alors il y a colision. */
// PLUS OU MOINS OK puisque collision en marche arriere pas faite....
bool	check_for_colision(t_game *game, int keycode)
{
	t_ray	mid_ray;

	mid_ray = game->player.rays[(game->width / 2) - 1];

	if (keycode == UP_ARW && mid_ray.hit_point.dist <= game->player.mv_speed * 64.0)
		return (true);
	return (false);
}
