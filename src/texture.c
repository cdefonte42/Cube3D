/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:42:49 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/26 20:54:40 by cdefonte         ###   ########.fr       */
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
	t_texture	text = game->text[nwall];
	
	col_text = (int)ray->hit_point.pos[grid].x % game->cube_size;
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

	if (col_screen == 0)
		printf("hpwall = %f screen height = %d indent = %d\n", hpwall, screen_size, line_text_indent);
	int l = 0; // represente le nombre de lignes faites
	while (line_screen < it_sup)
	{
		line_text = ((line_text_indent / (int)hpwall) % game->cube_size) + ((l / hwall) % game->cube_size);
		if (col_screen == 0 && l == 0)
			printf("line texture = %d\n", line_text);
		img->data[col_screen + line_screen] = text.data[col_text + line_text * text.size_line];
		line_screen += img->size_line;
		l+= game->cube_size;
	}
	
}
