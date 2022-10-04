/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:53:51 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 17:53:52 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "socket.h"

static void	change_state_door(t_game *game, t_ray ray)
{
	int	x;
	int	y;

	x = (int)ray.hit_point.pos[grid].x / game->cube_size;
	y = (int)ray.hit_point.pos[grid].y / game->cube_size;
	if (ray.step_y == 0 && ray.step_x <= 0)
		--x;
	if (ray.step_x == 0 && ray.step_y <= 0)
		--y;
	if (game->map.tab[y][x] == 'O')
		game->map.tab[y][x] = 'C';
	else if (game->map.tab[y][x] == 'C')
		game->map.tab[y][x] = 'O';
	if (game->bonus.sock > 0)
		send_door_state(game, x, y);
}

void	handle_use_key(t_game *game)
{
	t_ray	ray;

	ray = game->player.rays[SCREEN_W / 2 -1];
	if (ray.hit_point.type == door && ray.hit_point.dist <= game->cube_size)
		change_state_door(game, ray);
	else
	{
		set_ray_steps(game, &ray);
		next_hit_point(&ray);
		if (ray.hit_point.type == vline)
			ray.step_y = 0;
		else
			ray.step_x = 0;
		if (check_hit_point_is_door(game, ray) == true)
			change_state_door(game, ray);
	}
}
