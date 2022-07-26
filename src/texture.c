/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:42:49 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/26 21:18:10 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_buff_texture(t_game *game, int col_screen, int it_inf, int it_sup, double hpwall)
{
	int	col_text;
	int	line_text;
	int	line_screen;
	t_ray	*ray = &(game->player.rays[col_screen]);
	t_img	*img = &(game->img);
	t_texture	text = game->text[ray->hit_point.type];
	
	if (ray->hit_point.type == nwall || ray->hit_point.type == swall)
		col_text = (int)ray->hit_point.pos[grid].x % game->cube_size;
	else
		col_text = (int)ray->hit_point.pos[grid].y % game->cube_size;
	int	line_text_indent;
	int	screen_size = img->height;
	int	hwall = (int)hpwall;
	if (hwall >= screen_size)
	{
		line_text_indent = (hpwall - screen_size) / 2;
		hwall = screen_size;
	}
	else
		line_text_indent =  0;
	line_text = 0;
	line_screen = it_inf;

	int l = 0; // represente le nombre de lignes faites
	while (line_screen < it_sup)
	{
		line_text = ((line_text_indent / (int)hpwall) % game->cube_size) + ((l / hwall) % game->cube_size);
		img->data[col_screen + line_screen] = text.data[col_text + line_text * text.size_line];
		line_screen += img->size_line;
		l+= game->cube_size;
	}
	
}
