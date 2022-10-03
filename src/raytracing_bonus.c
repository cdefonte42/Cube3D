/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:33:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/08 17:47:18 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_sized_ray(t_game *game, t_ray ray, int color)
{
	int	max_line;
	int	line;
	int	col;
	int	t;
	int	length;

	max_line = game->map.rcube_size * game->map.height;
	line = 0;
	col = 0;
	t = 0;
	length = (int)(ray.hit_point.dist * game->map.ratio);
	while ((t < length && t < 160) && (line < max_line && line >= 0)
		&& (col < game->map.img.size_line && col >= 0))
	{	
		game->map.img.data[(line * game->map.img.size_line + col)] = color;
		++t;
		col = ray.pos[grid].x * game->map.ratio + t * ray.dir[grid].x;
		line = ray.pos[grid].y * game->map.ratio + t * ray.dir[grid].y;
	}
}

static void	draw_middle_ray(t_game *game)
{
	t_ray	*rays;
	int		index_mid_ray;

	index_mid_ray = game->width / 2 - 1;
	rays = game->player.rays;
	draw_sized_ray(game, rays[index_mid_ray], YELLOW);
}

static void	draw_cone_fov(t_game *game, double player_a)
{
	int		i;
	float	angle;
	double	t;
	double	cx;
	double	cy;

	i = 0;
	while (i < game->img.width - 1)
	{
		angle = player_a - game->player.fov / 2 + \
			game->player.fov * i / (game->width - 1);
		t = 0;
		while (t <= 10.0)
		{
			cx = game->player.pos.x + t * cos(angle);
			cy = game->player.pos.y + t * sin(angle);
			game->map.img.data[(int)(cx * 16.0) + (int)(cy * 16.0) *\
				game->map.img.size_line] = DARK_GREY;
			if (game->map.tab[(int)cy][(int)cx] == '1' ||
				game->map.tab[(int)cy][(int)cx] == 'C')
				break ;
			t += .01;
		}
		++i;
	}
}

/* Le ray du milieu (direction view player) est dessine avec un code couleur 
specifique. */
void	draw_all_rays(t_game *game)
{
	draw_cone_fov(game, atan2(game->player.dir.y, game->player.dir.x));
	draw_middle_ray(game);
}
