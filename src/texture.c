/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:42:49 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/08 16:25:44 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
		game->img.data[col_screen + interval.inf] = \
			text.data[col_text + line_text * text.size_line];
		interval.inf += game->img.size_line;
		line_text_indent += game->cube_size;
	}
}
