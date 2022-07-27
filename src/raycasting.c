/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:03:07 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/27 22:33:59 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	set_ray_steps(t_game *game, t_ray *ray)
{
	double	int_part;
	double	cube_size;

	cube_size = game->cube_size;
	if (ray->dir[grid].x >= 0)
		ray->stepX = cube_size - (modf(ray->pos[map].x, &int_part) * cube_size);
	else
		ray->stepX = - (modf(ray->pos[map].x, &int_part) * cube_size);
	if (ray->dir[grid].y >= 0)
		ray->stepY = cube_size - (modf(ray->pos[map].y, &int_part) * cube_size);
	else
		ray->stepY = - (modf(ray->pos[map].y, &int_part) * cube_size);
}

/* Eq droite: Or(t) = Op + t * Od Avec Or = infinite rays(t). Op = point 
origine ray.
Od = vecteur directeur (du screen/plan de projection) = (last ray vector - 
first ray vector). t = longueur */
t_ray	get_mid_ray(t_game *game)
{
	t_ray	ray;

	ray.angle = 0.0;
	ray.pos[view].x = 0.0;
	ray.pos[view].y = 0.0;
	ray.pos[grid].x = game->player.pos.x * game->cube_size;
	ray.pos[grid].y = game->player.pos.y * game->cube_size;
	ray.pos[map].x = game->player.pos.x;
	ray.pos[map].y = game->player.pos.y;
	ray.dir[view].x = 0.0;
	ray.dir[view].y = 1.0;
	ray.dir[grid].x = game->player.dir.x;
	ray.dir[grid].y = game->player.dir.y;
	ray.dir[map].x = game->player.dir.x;
	ray.dir[map].y = game->player.dir.y;
	ray.hit_point.dist = 0.0;
	set_ray_steps(game, &ray);
	return (ray);
}

/* Copie toutes les donnees du ray 'src' (must be the mid ray!) dans tous les 
rays du tableau. Ceci afin d'initialiser leur donnees et calculs (?) 
Peut etre pas utile si on pouvait faire comme en c++ des membres static: 
une seule et meme instance de variable commune a tous. Comment? En mettant la
var dans le player, mais du coup devrait se balader avec le player partout...*/
void	cpy_ray(t_ray *tab, t_ray src, int nb_rays)
{
	while (--nb_rays >= 0)
		tab[nb_rays] = src;
}

void	set_rays_angle(t_game *game, t_ray *rays, int nb_rays)
{
	int		index_mid_ray;
	int		i;
	int		n;

	index_mid_ray = nb_rays / 2 - 1;
	i = index_mid_ray - 1;
	n = 1;
	while (i >= 0)
	{
		rays[i].angle = -atan(n / game->player.dist_screen);
		++n;
		--i;
	}
	i = index_mid_ray + 1;
	n = 1;
	while (i < nb_rays)
	{
		rays[i].angle = atan(n / game->player.dist_screen);
		++n;
		++i;
	}
}

void	raycasting(t_game *game)
{
	t_ray	mid_ray;
	t_ray	*rays;
	int		nb_rays;
	int		i;

	mid_ray = get_mid_ray(game);
	nb_rays = game->width;
	rays = game->player.rays;
	cpy_ray(rays, mid_ray, nb_rays);
	set_rays_angle(game, rays, nb_rays);
	i = 0;
	while (i < nb_rays)
	{
		rays[i].dir[grid] = rotate_vector(mid_ray.dir[grid], rays[i].angle);
		rays[i].dir[map] = rays[i].dir[grid];
		set_ray_steps(game, &(rays[i]));
		next_hit_point(&(rays[i]));
		set_wall_hit_point(game, &(rays[i]));
		++i;
	}
}
