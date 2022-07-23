/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:03:07 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/23 20:26:57 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	set_ray_steps(t_game *game, t_ray *ray)
{
	double	int_part;
	double	cube_size;

	cube_size = game->cube_size;
	if (ray->dir[grid].x > 0)
		ray->stepX = cube_size - (modf(ray->pos[map].x, &int_part) * cube_size);
	else
		ray->stepX = - (modf(ray->pos[map].x, &int_part) * cube_size);
	if (ray->dir[grid].y > 0)
		ray->stepY = cube_size - (modf(ray->pos[map].y, &int_part) * cube_size);
	else
		ray->stepY = - (modf(ray->pos[map].y, &int_part) * cube_size);
}

/* Eq droite: Or(t) = Op + t * Od Avec Or = infinite rays(t). Op = point origine ray.
Od = vecteur directeur (du screen/plan de projection) = (last ray vector - first ray vector).
t = longueur */ 
t_ray	get_mid_ray(t_game *game)
{
	t_ray	ray;

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
	set_ray_steps(game, &ray);
	return (ray);
}

/* Copie toutes les donnees du ray 'src' (must be the mid ray!) dans tous les 
rays du tableau. Ceci afin d'initialiser leur donnees et calculs (?) 
Peut etre pas utile si on pouvait faire comme en c++ des membres static: 
une seule et meme instance de variable commune a tous. Comment? En mettant la
var dans le player, mais du coup devrait se balader avec le player partout... */
void	cpy_ray(t_ray *tab, t_ray src, int nb_rays)
{
	while (--nb_rays >= 0)
		tab[nb_rays] = src;
}

void	set_rays_dir(t_ray *rays, int nb_rays, double d_angle)
{
	int		index_mid_ray = nb_rays / 2 - 1;
	int		i = 0;
	int		coeff = 160;
	t_ray	mid_ray = rays[index_mid_ray];

	while (i < index_mid_ray) // "rays de gauche" par rapport au mid ray => angle <0
	{
		rays[i].dir[grid] = rotate_vector_angle(mid_ray.dir[grid], coeff * -d_angle);
		rays[i].dir[map] = rays[i].dir[grid];
		--coeff;
		++i;
	}
	i = index_mid_ray + 1;
	coeff = 1;
	while (i < nb_rays) // "rays de droite" par rapport au mid ray => angle>0
	{
		rays[i].dir[grid] = rotate_vector_angle(rays[i].dir[grid], coeff * d_angle);
		rays[i].dir[map] = rays[i].dir[grid];
		++i;
		++coeff;
	}
}

bool	check_hit_point_is_wall(t_game *game, t_ray ray)
{
	int	x;
	int	y;

	x = (int)ray.hit_point.pos[grid].x / 64;
	y = (int)ray.hit_point.pos[grid].y / 64;
	if (ray.hit_point.type == vline && ray.stepX < 0)
		--x;
	if (ray.hit_point.type == hline && ray.stepY < 0)
		--y;
	if (game->map.tab[y][x] == '1')
		return (true);
	return (false);
}

/*Then calculate the hit point x and y coordinates; MAIS EN FAIT pour optimiser,
on a besoin que des x et y a des valeurs multiples de CUBE_SIZE et pas precis*/
void	set_ray_first_line_hit_point(t_ray *ray)
{
	double	len_till_Vline;
	double	len_till_Hline;

	len_till_Vline = fabs(ray->stepX / ray->dir[grid].x);
	len_till_Hline = fabs(ray->stepY / ray->dir[grid].y);
	if (len_till_Vline < len_till_Hline)
	{
		ray->hit_point.type = vline;
		ray->hit_point.dist = len_till_Vline;
		ray->hit_point.pos[grid].x = ray->pos[grid].x + ray->stepX;
		ray->hit_point.pos[grid].y = ray->pos[grid].y + len_till_Vline * ray->dir[grid].y;
	}
	else if (len_till_Vline > len_till_Hline)
	{
		ray->hit_point.type = hline;
		ray->hit_point.dist = len_till_Hline;
		ray->hit_point.pos[grid].x = ray->pos[grid].x + len_till_Hline * ray->dir[grid].x;
		ray->hit_point.pos[grid].y = ray->pos[grid].y + ray->stepY;
	}
	else
	{
		ray->hit_point.type = apex;
		ray->hit_point.pos[grid].x = ray->pos[grid].x + ray->stepX;
		ray->hit_point.pos[grid].y = ray->pos[grid].y + ray->stepY;
	
	}
}

void	set_wall_hit_point(t_game *game, t_ray *ray)
{
	/* while check_hit_point_is_wall(game, ray) == false
		faire le calcul: need to know le delta x et le delta y !!!
	*/
	(void)ray;
	(void)game;
}

void	set_ray_deltas(t_game *game, t_ray *ray)
{
	(void)game;
	(void)ray;
}

void	raycasting(t_game *game)
{
	t_ray	mid_ray;
	int		nb_rays;
	double	d_angle;// delta angle en radian = angle increment = angle entre chaque ray;

	mid_ray = get_mid_ray(game);
	nb_rays = game->width;
	d_angle = atan(1 / game->player.dist_screen);
	cpy_ray(game->player.rays, mid_ray, nb_rays);
	set_rays_dir(game->player.rays, nb_rays, d_angle);
	for (int i = 0; i < nb_rays; ++i)
	{
		set_ray_steps(game, &(game->player.rays[i]));
		set_ray_first_line_hit_point(&(game->player.rays[i]));
		//set_wall_hit_point(game, game->player.rays[i]);
	}
}

