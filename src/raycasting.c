/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:03:07 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/20 22:39:02 by cdefonte         ###   ########.fr       */
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
	res.z = CUBE_SIZE / 2;	// useless for now
	return (res);
}

void	draw_ray(t_game *game, t_ray ray)
{
	t_pos	pos_grid;
	pos_grid.x = game->player.pos.x * 64.0;
	pos_grid.y = game->player.pos.y * 64.0;

	int	size_line = game->map.img.size_line / 4;	// nb de pixels par lignes
	int	*pixels = game->map.img.data;
	double	line = 0;
	double	col = 0;

	int t = 0;
	while (t < ray.length && (line < 64.0 * game->height * size_line && line >= 0.0) && (col < 64.0 * game->width && col >= 0.0))
	{	
//		line = ray.pos.x * game->cube_size * size_line;
//		col = game->player.pos.x * game->cube_size;
		
		pixels[(int)(line * (double)size_line + col)] = 0xFFFF00;
		++t;
		col = pos_grid.x + (double)t * game->player->dir.x; // t: longeur de la ligne;
		line = pos_grid.y + (double)t * game->player->dir.y; 
		printf("line = %f col = %f t = %d\n dirX = %f dirY = %f\n", line, col, t, game->player->dir.x, game->player->dir.y);
	}
}

/* Eq droite: Or(t) = Op + t * Od Avec Or = infinite rays(t). Op = point origine ray.
Od = vecteur directeur (du screen/plan de projection) = (last ray vector - first ray vector).
t = longueur */ 
void	raytracing(t_game *game)
{
	t_ray	ray;

	ray.increment = tan(game->player.fov / 2) / (game->width / 2);
	ray.pos.x = 0; // pour repasser en sys en map: + pos[map].x;
	ray.pos.y = 0;
	ray.pos.sid = view;
	ray.dir.x = 0;
	ray.dir.y = 1;
	ray.dir.sid = view; // ATTENTION pour la suite: faut faire la rotation entre dir view et dir grid (ou map car dir map = dir grid)!
	ray.vec.x = ray.pos.x + 3 * 64 * ray.dir.x; // t: longeur de la ligne;
	ray.vec.y = ray.pos.y + 3 * 64 * ray.dir.y; 
	ray.vec.sid = view;
	ray.length = sqrt(pow(ray.vec.x, 2) + pow(ray.vec.y, 2));

	draw_ray(game, ray);
}
