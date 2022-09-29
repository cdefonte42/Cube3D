/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:17:13 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 15:04:47 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

typedef struct s_rgb {
	int	r;
	int	g;
	int	b;
}	t_rgb;

static t_rgb	color_converter(int hex_value)
{
	t_rgb rgb_color;
	rgb_color.r = ((hex_value >> 16) & 0xFF);  // Extract the RR byte
	rgb_color.g = ((hex_value >> 8) & 0xFF);   // Extract the GG byte
	rgb_color.b = ((hex_value) & 0xFF);        // Extract the BB byte

	return (rgb_color); 
}

int	fog_texture(int texture_color, float dist)
{
	t_rgb	color;
	t_rgb	fog;
	int		alpha;

	alpha = (texture_color >> 24) & 0xFF;

	color = color_converter(texture_color);
	fog = color_converter(0x000000);
	color.r = (1 - fmin(dist/800, 1.0)) * color.r + fmin(dist/800, 1.0) * fog.r;
	color.g = (1 - fmin(dist/800, 1.0)) * color.g + fmin(dist/800, 1.0) * fog.g;
	color.b = (1 - fmin(dist/800, 1.0)) * color.b + fmin(dist/800, 1.0) * fog.b;
	return (alpha << 24 | color.r << 16 | color.g << 8 | color.b);
}


int	fog_percentage(int color, int fog, double percentage)
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
