/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:42:49 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/26 17:50:07 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_buff_texture(t_game *game, int col_screen, int it_inf, int it_sup)
{
	int	col_text;
	int	line_text;
	int	line_screen;
	t_ray	*ray = &(game->player.rays[col_screen]);
	t_img	*img = &(game->img);
	t_texture	text = game->text[nwall];
	
	col_text = col_screen % game->text[nwall].width;
	line_text = 0;
	line_screen = it_inf;
	
	(void)ray;

	while (line_screen < it_sup)
	{
		
		img->data[col_screen + line_screen] = text.data[col_text + line_text * text.size_line];
		line_text = (line_screen / img->size_line) % text.height;
		line_screen += img->size_line;
	}
	
}
