/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:42:49 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/22 15:50:59 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

typedef struct s_RGB {
    double r;
    double g;
     double b;
} t_RGB;

t_RGB colorConverter(int hexValue)
{
  t_RGB rgbColor;
  rgbColor.r = ((hexValue >> 16) & 0xFF);  // Extract the RR byte
  rgbColor.g = ((hexValue >> 8) & 0xFF);   // Extract the GG byte
  rgbColor.b = ((hexValue) & 0xFF);        // Extract the BB byte

  return rgbColor; 
}


int applied_fog(int texture_color, float dist)
{
	t_RGB			color;
	t_RGB			fog = {};
	
	color = colorConverter(texture_color);
	fog = colorConverter(0x000000);
	int r = (1 - fmin(dist/800, 1.0)) * color.r + fmin(dist/800, 1.0) * fog.r;
	int g = (1 - fmin(dist/800, 1.0)) * color.g + fmin(dist/800, 1.0) * fog.g;
	int b = (1 - fmin(dist/800, 1.0)) * color.b + fmin(dist/800, 1.0) * fog.b;
	return r << 16 | g << 8 | b;
}

void	draw_buff_texture(t_game *game, int col_screen, t_interval interval, \
double hpwall)
{
	int			col_text;
	int			line_text;
	t_ray		*ray;
	t_texture	text;
	int			line_text_indent;

	ray = &(game->player.rays[col_screen]);
	text = game->text[ray->hit_point.type];
	if (ray->hit_point.type == nwall || ray->hit_point.type == swall)
		col_text = (int)ray->hit_point.pos[grid].x % game->cube_size;
	else
		col_text = (int)ray->hit_point.pos[grid].y % game->cube_size;
	if ((int)hpwall >= game->img.height)
		line_text_indent = ((hpwall - game->img.height) / 2) * game->cube_size;
	else
		line_text_indent = 0;
	while (interval.inf < interval.sup)
	{
		line_text = (line_text_indent / (int)hpwall) % game->cube_size;
		game->img.data[col_screen + interval.inf] = applied_fog(text.data[col_text + line_text * game->cube_size], ray->hit_point.dist);
			// text.data[col_text + line_text * text.size_line];
		interval.inf += game->img.size_line;
		line_text_indent += game->cube_size;
	}
}
