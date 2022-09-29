/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_points_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:32:55 by cdefonte          #+#    #+#             */
/*   Updated: 2022/09/29 14:33:14 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#if BONUS
# define OK_CHAR "1C"
#else
# define OK_CHAR "1"
#endif

bool	check_hit_point_is_wall(t_game *game, t_ray ray)
{
	int	x;
	int	y;

	x = (int)ray.hit_point.pos[grid].x / game->cube_size;
	y = (int)ray.hit_point.pos[grid].y / game->cube_size;
	if ((ray.hit_point.type == vline) && ray.step_x <= 0)
		--x;
	if ((ray.hit_point.type == hline) && ray.step_y <= 0)
		--y;
	if (x <= 0 || x >= game->map.width || y <= 0 || y >= game->map.height)
		return (true);
	if (ft_strchr(OK_CHAR, game->map.tab[y][x]))
		return (true);
	return (false);
}

bool	check_hit_point_is_door(t_game *game, t_ray ray)
{
	int	x;
	int	y;

	x = (int)ray.hit_point.pos[grid].x / game->cube_size;
	y = (int)ray.hit_point.pos[grid].y / game->cube_size;
	if ((ray.hit_point.type == vline) && ray.step_x <= 0)
		--x;
	if ((ray.hit_point.type == hline) && ray.step_y <= 0)
		--y;
	if (x <= 0 || x >= game->map.width || y <= 0 || y >= game->map.height)
		return (false);
	if (game->map.tab[y][x] == 'O' || game->map.tab[y][x] == 'C')
		return (true);
	return (false);
}
