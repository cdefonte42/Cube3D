/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:03:07 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/21 16:57:29 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Matrice de rotation: x' = cos(alpha).x - sin(alpha).y et y' = sin(alpha).x + cos(alpha).y */
struct s_coord	rotate_vector_angle(struct s_coord from, enum e_sys_ids to, double angle)
{
	struct s_coord	res;

	res.sid = to;
	res.x = cos(angle) * from.x - sin(angle) * from.y;
	res.y = sin(angle) * from.x + cos(angle) * from.y;
//	if (angle >= 0.0 && angle <= PI / 2)
//	{
//		printf("1\n");
//		res.x = cos(angle) * from.x - sin(angle) * from.y;
//		res.y = sin(angle) * from.x + cos(angle) * from.y;
//	}
//	else if (angle <= 0 && angle >= - PI / 2)
//	{
//		printf("2\n");
//		res.x = cos(angle) * from.x + sin(angle) * from.y;
//		res.y = -sin(angle) * from.x + cos(angle) * from.y;
//	}
//	else if (angle >= PI / 2 && angle <= PI)
//	{
//		printf("3\n");
//		res.x = -sin(angle) * from.x - cos(angle) * from.y;
//		res.y = cos(angle) * from.x - sin(angle) * from.y;
//	}
//	else if ((angle >= PI && angle <= PI + PI / 2) || (angle <= - PI / 2 && angle >= - PI))
//	{
//		printf("4\n");
//		res.x = -cos(angle) * from.x + sin(angle) * from.y;
//		res.y = -sin(angle) * from.x - cos(angle) * from.y;
//	}
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

void	draw_first_line(t_game *game, t_ray ray, int color)
{
	int	size_line = game->map.img.size_line / 4;	// nb de pixels par lignes
	int	max_line = game->cube_size * game->map.height;
	int	*pixels = game->map.img.data;
	int	line = 0;
	int	col = 0;

	//int t = 0; // A transformer en Dx et Dy double pour passer d'un carre a l'autre
	double	part_int;
	double	Dx = 64.0 - modf(game->player.pos.x, &part_int) * 64.0;
	double	Dy = 64.0 - modf(game->player.pos.y, &part_int) * 64.0;
	int	x = 0;
	int	y = 0;
	while ((x * ray.dir[grid].x) <= Dx && (y * ray.dir[grid].y) <= Dy && (line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[line * size_line + col] = color;
		++x;
		++y;
		col = ray.pos[grid].x + x * ray.dir[grid].x; // t: longeur de la ligne;
		line = ray.pos[grid].y + y * ray.dir[grid].y;
	}
}

void	draw_ray(t_game *game, t_ray ray, int color)
{
	int	size_line = game->map.img.size_line / 4;	// nb de pixels par lignes
	int	max_line = game->cube_size * game->map.height;
	int	*pixels = game->map.img.data;
	int	line = 0;
	int	col = 0;

	int t = 0; // A transformer en Dx et Dy double pour passer d'un carre a l'autre
	while ((line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[(line * size_line + col)] = color;
		++t;
		col = ray.pos[grid].x + t * ray.dir[grid].x; // t: longeur de la ligne;
		line = ray.pos[grid].y + t * ray.dir[grid].y;
	}
}

/* Eq droite: Or(t) = Op + t * Od Avec Or = infinite rays(t). Op = point origine ray.
Od = vecteur directeur (du screen/plan de projection) = (last ray vector - first ray vector).
t = longueur */ 
t_ray	get_mid_ray(t_game *game)
{
	t_ray	ray;

	ray.increment = tan(game->player.fov / 2) / (game->width / 2);
	ray.pos[view].x = 0; // pour repasser en sys en map: + pos[map].x;
	ray.pos[view].y = 0;
	ray.pos[view].sid = view;
	ray.pos[grid].x = game->player.pos.x * game->cube_size;
	ray.pos[grid].y = game->player.pos.y * game->cube_size;
	ray.pos[grid].sid = grid;
	ray.dir[view].x = 0;
	ray.dir[view].y = 1;
	ray.dir[view].sid = view; // ATTENTION pour la suite: faut faire la rotation entre dir view et dir grid (ou map car dir map = dir grid)!
	ray.dir[grid].x = game->player.dir.x;
	ray.dir[grid].y = game->player.dir.y;
	ray.dir[grid].sid = grid;
	int t = 10 * game->cube_size; // t: longeur de la ligne;
	ray.vec[view].x = ray.pos[view].x + t * ray.dir[view].x;
	ray.vec[view].y = ray.pos[view].y + t * ray.dir[view].y; 
	ray.vec[view].sid = view;
	ray.length = sqrt(pow(ray.vec[view].x, 2) + pow(ray.vec[view].y, 2));
	
	return (ray);
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
	int	i = 0;
	int	coeff = 160;
	while (i < index_mid_ray) // "rays de gauche" par rapport au mid ray => angle <0
	{
		rays[i].dir[grid] = rotate_vector_angle(mid_ray.dir[grid], view, coeff * -d_angle);
		rays[i].pos[grid] = mid_ray.pos[grid];
		rays[i].length = mid_ray.length;
		--coeff;
		++i;
	}
	i = index_mid_ray + 1;
	coeff = 1;
	while (i < nb_rays) // "rays de droite" par rapport au mid ray => angle>0
	{
		rays[i].dir[grid] = rotate_vector_angle(mid_ray.dir[grid], view, coeff * d_angle);
		rays[i].pos[grid] = mid_ray.pos[grid];
		rays[i].length = mid_ray.length;
		++i;
		++coeff;
	}
	rays[index_mid_ray] = mid_ray;
	return (rays);
}

