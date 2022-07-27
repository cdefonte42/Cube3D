/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_points.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:47:18 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/27 22:07:42 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	check_hit_point_is_wall(t_game *game, t_ray ray)
{
	int	x;
	int	y;

	x = (int)ray.hit_point.pos[grid].x / game->cube_size;
	y = (int)ray.hit_point.pos[grid].y / game->cube_size;
	if ((ray.hit_point.type == vline) && ray.stepX <= 0)
		--x;
	if ((ray.hit_point.type == hline) && ray.stepY <= 0)
		--y;
	if ((x < 0 || x >= game->map.width) || (y < 0 || y >= game->map.height))
		return (true);
	if (game->map.tab[y][x] == '1')
		return (true);
	return (false);
}

void	next_hit_point(t_ray *ray)
{
	double	len_till_vline;
	double	len_till_hline;

	len_till_vline = fabs(ray->stepX / ray->dir[grid].x);
	len_till_hline = fabs(ray->stepY / ray->dir[grid].y);
	if (len_till_vline <= len_till_hline)
	{
		ray->hit_point.type = vline;
		ray->hit_point.dist += len_till_vline;
		ray->hit_point.pos[grid].x = ray->pos[grid].x + ray->stepX;
		ray->hit_point.pos[grid].y = ray->pos[grid].y + \
		len_till_vline * ray->dir[grid].y;
	}
	else
	{
		ray->hit_point.type = hline;
		ray->hit_point.dist += len_till_hline;
		ray->hit_point.pos[grid].x = ray->pos[grid].x + \
		len_till_hline * ray->dir[grid].x;
		ray->hit_point.pos[grid].y = ray->pos[grid].y + ray->stepY;
	}
}

void	set_htpt_dist(t_ray *ray)
{
	ray->hit_point.dist = sqrt(pow(fabs(ray->hit_point.pos[grid].x - \
	ray->pos[grid].x), 2) + pow(fabs(ray->hit_point.pos[grid].y - \
	ray->pos[grid].y), 2));
}

void	set_htpt_type(t_ray *ray)
{
	if (ray->hit_point.type == vline)
	{
		if (ray->dir[grid].x >= 0)
			ray->hit_point.type = ewall;
		else
			ray->hit_point.type = wwall;
	}
	else if (ray->hit_point.type == hline)
	{
		if (ray->dir[grid].y >= 0)
			ray->hit_point.type = swall;
		else
			ray->hit_point.type = nwall;
	}
}

void	set_wall_hit_point(t_game *game, t_ray *ray)
{
	while (check_hit_point_is_wall(game, *ray) == false)
	{
		if (ray->hit_point.type == vline)
		{
			if (ray->stepX < 0)
				ray->stepX -= game->cube_size;
			else
				ray->stepX += game->cube_size;
		}
		else if (ray->hit_point.type == hline)
		{
			if (ray->stepY < 0)
				ray->stepY -= game->cube_size;
			else if (ray->stepY > 0)
				ray->stepY += game->cube_size;
		}
		next_hit_point(ray);
	}
	set_htpt_type(ray);
	set_htpt_dist(ray);
}
