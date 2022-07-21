/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:03:07 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/21 20:29:51 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_all_hit_points(t_game *game, t_ray ray, int color)
{
//	int	size_line = game->map.img.size_line / 4;
//	int	*pixels = game->map.img.data;
//
//	pixels[ray.hit_point[grid].x * 
	(void)game;
	(void)ray;
	(void)color;
	//printf("ray hit x = %f y = %f \n", ray.hit_point[grid].x, ray.hit_point[grid].y);
}

//void	first_Vwall_hit(t_game *game, t_ray ray)
//{
//	ray.hit_point
//}

void	draw_ray_until_first_Hline(t_game *game, t_ray ray, int color)
{
	int	size_line = game->map.img.size_line / 4;
	int	max_line = game->cube_size * game->map.height;
	int	*pixels = game->map.img.data;
	int	line = 0;
	int	col = 0;

	double	part_int;
	double	Dy = 64.0 - modf(ray.pos[map].y, &part_int) * 64.0;
	int	x = 0;
	while (fabs(x * ray.dir[grid].y) <= Dy && (line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[line * size_line + col] = color;
		++x;
		col = ray.pos[grid].x + x * ray.dir[grid].x; // t: longeur de la ligne;
		line = ray.pos[grid].y + x * ray.dir[grid].y;
	}
}

void	draw_ray_until_first_Vline(t_game *game, t_ray ray, int color)
{
	int	size_line = game->map.img.size_line / 4;
	int	max_line = game->cube_size * game->map.height;
	int	*pixels = game->map.img.data;
	int	line = 0;
	int	col = 0;

	double	part_int;
	double	Dx = 64.0 - modf(ray.pos[map].x, &part_int) * 64.0;
	int	x = 0;
	while (fabs(x * ray.dir[grid].x) <= Dx && (line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[line * size_line + col] = color;
		++x;
		col = ray.pos[grid].x + x * ray.dir[grid].x; // t: longeur de la ligne;
		line = ray.pos[grid].y + x * ray.dir[grid].y;
	}
}

void	draw_ray(t_game *game, t_ray ray, int color)
{
	int	size_line = game->map.img.size_line / 4;
	int	max_line = game->cube_size * game->map.height;
	int	*pixels = game->map.img.data;
	int	line = 0;
	int	col = 0;

	//t = longueur du vecteur (de la ligne)
	int t = 0; // A transformer en Dx et Dy double pour passer d'un carre a l'autre
	while ((line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[(line * size_line + col)] = color;
		++t;
		col = ray.pos[grid].x + t * ray.dir[grid].x;
		line = ray.pos[grid].y + t * ray.dir[grid].y;
	}
}

/* Eq droite: Or(t) = Op + t * Od Avec Or = infinite rays(t). Op = point origine ray.
Od = vecteur directeur (du screen/plan de projection) = (last ray vector - first ray vector).
t = longueur */ 
t_ray	get_mid_ray(t_game *game)
{
	t_ray	ray;

	ray.pos[view].x = 0; // pour repasser en sys en map: + pos[map].x;
	ray.pos[view].y = 0;
	ray.pos[grid].x = game->player.pos.x * game->cube_size;
	ray.pos[grid].y = game->player.pos.y * game->cube_size;
	ray.pos[map].x = game->player.pos.x;
	ray.pos[map].y = game->player.pos.y;
	ray.dir[view].x = 0;
	ray.dir[view].y = 1; // ATTENTION pour la suite: faut faire la rotation entre dir view et dir grid (ou map car dir map = dir grid)!
	ray.dir[grid].x = game->player.dir.x;
	ray.dir[grid].y = game->player.dir.y;
	ray.dir[map].x = game->player.dir.x;
	ray.dir[map].y = game->player.dir.y;
//	int t = 10 * game->cube_size; // t: longeur de la ligne;
//	ray.vec[view].x = ray.pos[view].x + t * ray.dir[view].x;
//	ray.vec[view].y = ray.pos[view].y + t * ray.dir[view].y; 
//	ray.length = sqrt(pow(ray.vec[view].x, 2) + pow(ray.vec[view].y, 2));
	
	return (ray);
}

void	cpy_ray(t_ray *tab, t_ray src, int nb_rays)
{
	while (--nb_rays >= 0)
		tab[nb_rays] = src;
}

t_ray*	raycasting(t_game *game)
{
	t_ray	*rays;
	t_ray	mid_ray = get_mid_ray(game);
	int		nb_rays = game->width;
	int		index_mid_ray = nb_rays / 2 - 1;
	double	d_angle;	// delta angle en radian = angle increment = angle entre chaque ray;

	d_angle = atan(1 / game->player.dist_screen);

	rays = malloc(sizeof(t_ray) * game->width); // A PROTEGER
	cpy_ray(rays, mid_ray, nb_rays);
	int	i = 0;
	int	coeff = 160;
	while (i < index_mid_ray) // "rays de gauche" par rapport au mid ray => angle <0
	{
		rays[i].dir[grid] = rotate_vector_angle(mid_ray.dir[grid], coeff * -d_angle);
		rays[i].dir[map] = rays[i].dir[grid];
		//rays[i].length = mid_ray.length;
		--coeff;
		++i;
	}
	i = index_mid_ray + 1;
	coeff = 1;
	while (i < nb_rays) // "rays de droite" par rapport au mid ray => angle>0
	{
		rays[i].dir[grid] = rotate_vector_angle(rays[i].dir[grid], coeff * d_angle);
		rays[i].dir[map] = rays[i].dir[grid];
		//rays[i].length = mid_ray.length;
		++i;
		++coeff;
	}
	return (rays);
}

