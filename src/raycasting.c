/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:03:07 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/21 12:36:31 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Matrice de rotation: x' = cos(alpha).x - sin(alpha).y et y' = sin(alpha).x + cos(alpha).y */
struct s_coord	rotate_vector(struct s_coord from, enum e_sys_ids to, double angle)
{
	struct s_coord	res;

	res.sid = to;
	res.x = cos(angle) * from.x - sin(angle) * from.y;
	res.y = sin(angle) * from.x + cos(angle) * from.y;
//	if ((from.x >= 0.0 && from.x <= 1.0) && (from.y >= 0.0 && from.y <= 1)) // angle
//	{
//		res.x = cos(angle) * from.x - sin(angle) * from.y;
//		res.y = sin(angle) * from.x + cos(angle) * from.y;
//	}
//	else if ((from.x >= -1.0 && from.x <= 0.0) && (from.y >= 0.0 && from.y <= 1.0)) // angle + PI/2
//	{
//		res.x = -sin(angle) * from.x - cos(angle) * from.y;
//		res.y = cos(angle) * from.x - sin(angle) * from.y;
//	}
//	else if ((from.x >= -1.0 && from.x <= 0.0) && (from.y >= -1.0 && from.y <= 0.0))
//	{
//		res.x = -cos(angle) * from.x + sin(angle) * from.y;
//		res.y = -sin(angle) * from.x - cos(angle) * from.y;
//	}
//	else if ((from.x >= 0.0 && from.x <= 1.0) && (from.y >= -1.0 && from.y <= 0.0))
//	{
//		res.x = cos(angle) * from.x + sin(angle) * from.y;
//		res.y = -sin(angle) * from.x + cos(angle) * from.y;
//	}
	res.z = CUBE_SIZE / 2;	// useless for now
	return (res);
}

void	draw_ray(t_game *game, t_ray ray)
{
	t_pos	pos_grid;
	pos_grid.x = game->player.pos.x * game->cube_size;
	pos_grid.y = game->player.pos.y * game->cube_size;

	t_dir	ray_dirgrid = rotate_vector(ray.dir, grid, atan(game->player.dir.y / game->player.dir.x));

	int	size_line = game->map.img.size_line / 4;	// nb de pixels par lignes
	int	max_line = game->cube_size * game->map.height;
	int	*pixels = game->map.img.data;
	int	line = 0;
	int	col = 0;

	int t = 0; // A transformer en Dx et Dy double pour passer d'un carre a l'autre
	while ((line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[(line * size_line + col)] = 0xFFFF00;
		++t;
		col = pos_grid.x + floor(t * ray_dirgrid.x); // t: longeur de la ligne;
		line = pos_grid.y + floor(t * ray_dirgrid.y);
	}
}

/* Eq droite: Or(t) = Op + t * Od Avec Or = infinite rays(t). Op = point origine ray.
Od = vecteur directeur (du screen/plan de projection) = (last ray vector - first ray vector).
t = longueur */ 
t_ray	raycasting(t_game *game)
{
	t_ray	ray;

	ray.increment = tan(game->player.fov / 2) / (game->width / 2);
	ray.pos.x = 0; // pour repasser en sys en map: + pos[map].x;
	ray.pos.y = 0;
	ray.pos.sid = view;
	ray.dir.x = 0;
	ray.dir.y = 1;
	ray.dir.sid = view; // ATTENTION pour la suite: faut faire la rotation entre dir view et dir grid (ou map car dir map = dir grid)!
	int t = 10 * game->cube_size; // t: longeur de la ligne;
	ray.vec.x = ray.pos.x + t * ray.dir.x;
	ray.vec.y = ray.pos.y + t * ray.dir.y; 
	ray.vec.sid = view;
	ray.length = sqrt(pow(ray.vec.x, 2) + pow(ray.vec.y, 2));
	
	return (ray);
}

void	iter_ray(t_game *game)
{
	t_ray	*rays;
	int		nb_rays = game->width;
	t_ray	mid_ray = raycasting(game);
	double	d_angle;	// delta angle en radian = angle increment = angle entre chaque ray;

	d_angle = atan(1 / game->player.dist_screen);
	draw_ray(game, mid_ray);

	rays = malloc(sizeof(t_ray) * game->width); // A PROTEGER
	int i = nb_rays / 2 - 1 - 1; // on demarre a -1 ray par rapport a celui du milieu
	while (i >= 0) // "rays de gauche" par rapport au mid ray
	{
		rays[i].dir = rotate_vector(mid_ray.dir, view, -d_angle);
		rays[i].pos = mid_ray.pos;
		--i;
	}
	rays[nb_rays / 2 - 1] = mid_ray;
	free(rays);
}
