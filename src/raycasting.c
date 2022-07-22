/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:03:07 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/22 19:06:35 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Dessine un carre, de size haut et size large (en pixel), a la position origin */
void	draw_square(t_game *game, t_pos origin, int size, int color)
{
	int	size_line = game->map.img.size_line / 4;
	int	*pixels = game->map.img.data;
	int	line;
	int	col;
	int	max_line;
	int	max_col;

	//printf("x = %f y = %f size line = %d\n", origin.x, origin.y, size_line);
	line = ((int)origin.y - size / 2) * size_line;
	col = (int)origin.x - (size / 2);
	max_line = line + size * size_line;
	max_col = col + size;
	while (line < max_line && line < (int)game->map.img.height * size_line)
	{
		col = (int)origin.x - (size / 2);
		while (col < max_col && col < size_line)
		{
			//printf("col = %d, line = %d\n", col, line);
			pixels[col + line] = color;
			++col;
		}
		line += size_line;
	}
	
}
//
//void	draw_rays_hit_points(t_game *game, t_ray ray, int nb_rays, int color)
//{
//	
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
	int	length = 0;
	while (fabs(length * ray.dir[grid].y) <= Dy && (line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[line * size_line + col] = color;
		++length;
		col = ray.pos[grid].x + length * ray.dir[grid].x; // t: longeur de la ligne;
		line = ray.pos[grid].y + length * ray.dir[grid].y;
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
	int	length = 0;
	while (fabs(length * ray.dir[grid].x) <= Dx && (line < max_line && line >= 0) && (col < size_line && col >= 0))
	{	
		pixels[line * size_line + col] = color;
		++length;
		col = ray.pos[grid].x + length * ray.dir[grid].x; // t: longeur de la ligne;
		line = ray.pos[grid].y + length * ray.dir[grid].y;
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
	double	int_part;

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
	ray.stepX = game->cube_size - modf(ray.pos[map].x, &int_part) * game->cube_size;
	ray.stepY = game->cube_size - modf(ray.pos[map].y, &int_part) * game->cube_size;
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

void	set_rays_dir(t_game *game, t_ray *rays, int nb_rays)
{
	int		index_mid_ray = nb_rays / 2 - 1;
	double	d_angle;	// delta angle en radian = angle increment
						// = angle entre chaque ray;
	int		i = 0;
	int		coeff = 160;
	t_ray	mid_ray = rays[index_mid_ray];

	d_angle = atan(1 / game->player.dist_screen);
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

//bool	check_hit_point_is_wall(t_game *game, t_ray ray)
//{
//	return (false);
//}

void	set_rays_steps(t_game *game, t_ray *rays, int nb_rays)
{
	int		i;
	double	int_part;
	double	cube_size;

	i = 0;
	cube_size = game->cube_size;
	while (i < nb_rays)
	{
			rays[i].stepX = cube_size - modf(rays[i].pos[map].x, &int_part) * cube_size;
			rays[i].stepY = cube_size - modf(rays[i].pos[map].y, &int_part) * cube_size;
		++i;
	}
}

void	set_rays_first_hit_point(t_ray *rays, int nb_rays)
{
	int		i;
	double	len_till_Vline;
	double	len_till_Hline;

	i = 0;
	while (i < nb_rays)
	{
		len_till_Vline = fabs(rays[i].stepX / rays[i].dir[grid].x);
		len_till_Hline = fabs(rays[i].stepY / rays[i].dir[grid].y);
		if (len_till_Vline < len_till_Hline)
		{
			rays[i].hit_point.type = vline;
			if (rays[i].dir[grid].x < 0)
				rays[i].hit_point.pos[grid].x = rays[i].pos[grid].x - rays[i].stepX;
			else
				rays[i].hit_point.pos[grid].x = rays[i].pos[grid].x + rays[i].stepX;
			rays[i].hit_point.pos[grid].y = rays[i].pos[grid].y + len_till_Vline * rays[i].dir[grid].y;
		}
		else if (len_till_Vline > len_till_Hline)
		{
			rays[i].hit_point.type = hline;
			rays[i].hit_point.pos[grid].x = rays[i].pos[grid].x + len_till_Hline * rays[i].dir[grid].x;
			if (rays[i].dir[grid].y < 0)
				rays[i].hit_point.pos[grid].y = rays[i].pos[grid].y - rays[i].stepY;
			else
				rays[i].hit_point.pos[grid].y = rays[i].pos[grid].y + rays[i].stepY;
		}
		else
		{
			rays[i].hit_point.type = apex;
			rays[i].hit_point.pos[grid].x = rays[i].pos[grid].x + rays[i].stepX;
			rays[i].hit_point.pos[grid].y = rays[i].pos[grid].y + rays[i].stepY;
		
		}
		++i;
	}
}

t_ray*	raycasting(t_game *game)
{
	t_ray	*rays;
	t_ray	mid_ray = get_mid_ray(game);
	int		nb_rays = game->width;

	rays = malloc(sizeof(t_ray) * game->width); // A PROTEGER
	cpy_ray(rays, mid_ray, nb_rays);
	set_rays_dir(game, rays, nb_rays);
	set_rays_steps(game, rays, nb_rays);
//	set_rays_first_Hline_hit_point(rays, nb_rays);
//	set_rays_first_Vline_hit_point(rays, nb_rays);
	set_rays_first_hit_point(rays, nb_rays);
	//draw_rays_hit_points(game, rays, nb_rays, LIME);
	return (rays);
}

