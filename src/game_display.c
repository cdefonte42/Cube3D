/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:27:33 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/26 19:10:26 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_sprites(t_game *game);

/* Calcule la hauteur "percue" du mur (si loin, petit, et inversement).
Correction du fish eye grace a la projection (cos(a)) de la distance du hit 
point sur l'axe de view. */
// ATTENTION floating point exception: car division par 0!!
double	wall_height_ratio(t_ray ray, double distScreen, double cubeSize)
{
	double	hpwall;

	if (ray.hit_point.dist * cos(ray.angle) == 0.0)
		hpwall = distScreen * cubeSize / (ray.hit_point.dist);
	else
		hpwall = distScreen * cubeSize / (ray.hit_point.dist * cos(ray.angle));
	return (hpwall);
}

/* Set les le minimun et le maximum de l'interval de coloration d'une slice de
mur. Les valeurs sont set en pixels. */
void	get_interval(int *min_line, int *max_line, t_img img, double hpwall)
{
	double	min;
	double	max;

	min = ((double)img.height - hpwall) * 0.5;
	max = ((double)img.height + hpwall) * 0.5;
	if (min < 0.0)
		min = 0.0;
	if (max > img.height)
		max = img.height;
	*min_line = (int)min * img.size_line;
	*max_line = (int)max * img.size_line;
}

/* Permet de colorier le ciel, ou le sol. pixels est l'adresse du premier pixel
a colorier, size_line est la valeur a incrementer a chaque tour, et max est
l'index du dernier pixels (a ne PAS colorier). */

int	applied_color_by_percentage(int color, int fog, double percentage)
{
	int	red;
	int	green;
	int	blue;
(void)fog;
	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	red = (red * percentage) / 100;
	green = (green * percentage) / 100;
	blue = (blue * percentage) / 100;
	return (red << 16 | green << 8 | blue);
}

void	draw_sky(int *pixels, int size_line, int max, int color)
{
	int	i;

	i = max;
	while (i >= 0)
	{
		// printf("%d %f\n", i, (SCREEN_H-(i/size_line))/(double)(SCREEN_H)*100);
		pixels[i] = applied_color_by_percentage(color, 0x000000, (SCREEN_H/2-(i/size_line))/(double)(SCREEN_H/2)*100);
		i -= size_line;
	}
}


void	draw_floor(int *pixels, int size_line, int max, int color)
{
	int	i;

	i = 0;
	(void)color;
	while (i <= max)
	{
		// printf("%f\n", 100-(SCREEN_H/2+(max/size_line-i/size_line))/(double)(SCREEN_H)*100);
		pixels[i] = applied_color_by_percentage(color, 0x000000, 100-(SCREEN_H/2+(max-i)/size_line)/(double)(SCREEN_H)*100);
		// pixels[i] = i/size_line;
		i += size_line;
	}

}

void	draw_floor_or_sky(int *pixels, int size_line, int max, int color)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (i < max/2)
			pixels[i] = color;
		else
			pixels[i] = 0x000000;
		// pixels[i] = color;
		i += size_line;
	}
}

/* Remplit la game win de pixels en fonction des murs sol ciel etc.
	hpwall : Hauteur "percue" du mur (ratio hauteur mur / distance de celui ci)
	it_inff et it_max : en pixels! Interval entre le haut et le bas du mur
						(line min et line max a peindre).
*/
void	draw_game(t_game *game)
{
	double			hpwall;
	int				nb_rays;
	int				col;
	t_interval		interval;
	int				img_pixl_max;

	col = 0;
	nb_rays = game->width;
	img_pixl_max = game->img.height * game->img.size_line;
	while (col < nb_rays)
	{
		hpwall = wall_height_ratio(game->player.rays[col], \
		game->player.dist_screen, game->cube_size);
		if (hpwall < 1.0)
			hpwall = 1.0;
		get_interval(&(interval.inf), &(interval.sup), game->img, hpwall);
		draw_buff_texture(game, col, interval, hpwall);
		draw_floor(&(game->img.data[col + interval.sup]), \
		game->img.size_line, img_pixl_max - interval.sup, game->floor_color);
		draw_sky(&(game->img.data[col]), game->img.size_line, \
		interval.inf, game->ceiling_color);
		++col;
	}
	draw_sprites(game);
}
void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	int	*dst;

	dst = data->data + (y * data->size_line + x * (data->bpp / 32));
	*(unsigned int*)dst = color;
}

void	draw_sprites(t_game *game)
{
	double	distX = game->sprites[0].x - game->player.pos.x;
	double	distY = game->sprites[0].y - game->player.pos.y;
	double	sprite_dir = atan2(distY, distX);
	double	angle = atan2(game->player.dir.y, game->player.dir.x);

	while (sprite_dir - angle >  M_PI) sprite_dir -= 2*M_PI; 
    while (sprite_dir - angle < -M_PI) sprite_dir += 2*M_PI;
	
	distX = game->player.pos.x - game->sprites[0].x;
	distY = game->player.pos.y - game->sprites[0].y;

	double	sprite_dist = sqrt(pow(distX, 2.0) + pow (distY, 2.0));
//	printf("angle = %f et dist = %f\n", sprite_dir, sprite_dist);

	int sprite_screen_size = fmin(500, SCREEN_H/sprite_dist);

	int h_offset = (sprite_dir - angle)*(SCREEN_W/2)/(M_PI) + (SCREEN_W/2)/2 - sprite_screen_size/2;
    int v_offset = SCREEN_H/2 - sprite_screen_size/2;

	printf("sprite size = %d , h %d v %d \n", sprite_screen_size, h_offset, v_offset);

    for (int i=0; i<sprite_screen_size; i++) {
        if (i<0 || i>=SCREEN_W/2) continue;
        for (int j=0; j<sprite_screen_size; j++) {
            if (j<0 || j>=SCREEN_H) continue;
            my_mlx_pixel_put(&game->img, SCREEN_H/2 + h_offset+i, v_offset+j, RED);
			//game->img.data[SCREEN_H/2 + h_offset+i + v_offset+(j*game->img.bpp/4)] = 0xFF0000;
        }
    }
}

////	t_ray	rays = game->player.rays;
//
//	double	distX = game->sprites[0].x - game->player.pos.x;
//	double	distY = game->sprites[0].y - game->player.pos.y;
//
//	// distant du sprite au player
////	double len = sqrt(distX * distX + distY * distY);
//
//	printf("distX = %f distY = %f\n", distX, distY);
//	printf("dirX = %f dirY = %f\n", game->player.dir.x, game->player.dir.y);
//
////	double	projX = len * game->player.dir.x;
////	double	projY = len * game->player.dir.y;
//
//	double	projX = distX + distY * game->player.dir.y;
//	double	projY = distY + distX * game->player.dir.x;
//	printf("proj X = %f proj Y = %f\n", projX, projY);
//	printf("\n");
