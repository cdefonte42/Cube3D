/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_points.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:47:18 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/28 14:34:13 by cdefonte         ###   ########.fr       */
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

void	next_hit_point(t_ray *ray)
{
	double	len_till_vline;
	double	len_till_hline;

	len_till_vline = fabs(ray->step_x / ray->dir[grid].x);
	len_till_hline = fabs(ray->step_y / ray->dir[grid].y);
	if (len_till_vline <= len_till_hline)
	{
		ray->hit_point.type = vline;
		ray->hit_point.dist += len_till_vline;
		ray->hit_point.pos[grid].x = ray->pos[grid].x + ray->step_x;
		ray->hit_point.pos[grid].y = ray->pos[grid].y + \
		len_till_vline * (ray->dir[grid].y);
	}
	else
	{
		ray->hit_point.type = hline;
		ray->hit_point.dist += len_till_hline;
		ray->hit_point.pos[grid].x = ray->pos[grid].x + \
		len_till_hline * (ray->dir[grid].x);
		ray->hit_point.pos[grid].y = ray->pos[grid].y + ray->step_y;
	}
}

void	set_htpt_dist(t_ray *ray)
{
	ray->hit_point.dist = sqrt(pow(fabs(ray->hit_point.pos[grid].x - \
	ray->pos[grid].x), 2) + pow(fabs(ray->hit_point.pos[grid].y - \
	ray->pos[grid].y), 2));
}

/* Set le bon type de mur (door, est, west, north, south wall) ET set a 0 le 
step qui n'est "pas utile", cad que si c'est une vline, seulement le step_x est
utilise, donc on peut mettre step_x a 0. Permet plus tard (dans draw texture) de
selectionner dans quel sens faire le ratio de la texture (x ou y). */
void	set_htpt_type(t_game *game, t_ray *ray)
{
	if (ray->hit_point.type == vline)
		ray->step_y = 0;
	else
		ray->step_x = 0;
	if (check_hit_point_is_door(game, *ray) == true)
		ray->hit_point.type = door;
	else if (ray->hit_point.type == vline)
	{
		if (ray->dir[grid].x >= 0)
			ray->hit_point.type = wwall;
		else
			ray->hit_point.type = ewall;
	}
	else if (ray->hit_point.type == hline)
	{
		if (ray->dir[grid].y >= 0)
			ray->hit_point.type = nwall;
		else
			ray->hit_point.type = swall;
	}
}

void	set_wall_hit_point(t_game *game, t_ray *ray)
{
	while (check_hit_point_is_wall(game, *ray) == false)
	{
		if (ray->hit_point.type == vline)
		{
			if (ray->step_x <= 0)
				ray->step_x -= game->cube_size;
			else
				ray->step_x += game->cube_size;
		}
		else if (ray->hit_point.type == hline)
		{
			if (ray->step_y <= 0)
				ray->step_y -= game->cube_size;
			else
				ray->step_y += game->cube_size;
		}
		next_hit_point(ray);
	}
	set_htpt_type(game, ray);
	set_htpt_dist(ray);
}
