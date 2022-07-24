/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:27:33 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/24 12:44:03 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_game(t_game *game)
{
	double	hwall;
	t_ray	*rays = game->player.rays;
	int	i = 0;
	int	nb_rays = game->screen.width;
	int	col = 0;
	int line;
	int	*pixels = game->screen.data;
	int	size_line = game->screen.size_line / 4;
	while (col < nb_rays)
	{
		line = 0;
		while (line < game->screen.height)
		{
			pixels[col + line]
			line += size_line;
		}
		++col;
	}
}
