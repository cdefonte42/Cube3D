/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:42:49 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/10/04 14:42:15 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	get_col_text(t_game *game, t_texture text, t_ray *ray)
{
	int		col_text;
	double	ratio;

	ratio = text.width / game->cube_size;
	if (ray->step_x == 0)
		col_text = (int)(ray->hit_point.pos[grid].x * ratio) % (text.width);
	else
		col_text = (int)(ray->hit_point.pos[grid].y * ratio) % (text.width);
	return (col_text);
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
	col_text = get_col_text(game, text, ray);
	if ((int)hpwall >= game->img.height)
		line_text_indent = ((hpwall - game->img.height) / 2) * text.width;
	else
		line_text_indent = 0;
	while (interval.inf < interval.sup)
	{
		line_text = (line_text_indent / (int)hpwall) % text.width;
		game->img.data[col_screen + interval.inf] = \
		fog_texture(text.data[col_text + line_text * text.width], \
		ray->hit_point.dist);
		interval.inf += game->img.size_line;
		line_text_indent += text.width;
	}
}
