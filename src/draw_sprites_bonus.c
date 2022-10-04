/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:13:31 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 15:06:11 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	draw_sprites_bonus(t_game *game)
{
	int		i;
	double	angle;

	angle = atan2(game->player.dir.y, game->player.dir.x);
	set_sprites_datas(game, angle);
	sort_sprites(game);
	i = game->bonus.nb_sp - 1;
	while (i >= 0)
	{
		draw_sprite(game, &game->bonus.sps[game->bonus.sort_sp[i]], angle);
		--i;
	}
	return (1);
}

void	set_sprites_datas(t_game *game, double angle)
{
	t_sprite	*head;
	double		px;
	double		py;
	int			i;

	px = game->player.pos.x;
	py = game->player.pos.y;
	i = 0;
	while (i < game->bonus.nb_sp)
	{
		head = &(game->bonus.sps[i]);
		head->dir = atan2(head->pos.y - py, head->pos.x - px);
		while (head->dir - angle > PI)
			head->dir -= 2.0 * PI;
		while (head->dir - angle < -PI)
			head->dir += 2.0 * PI;
		head->dist = sqrt(pow(px - head->pos.x, 2.0) + \
													pow(py - head->pos.y, 2.0));
		if (head->type == coin)
			head->screen_size = fmin(SCREEN_H, SCREEN_H / (head->dist * 2));
		else
			head->screen_size = fmin(SCREEN_H, SCREEN_H / (head->dist * 2));
		++i;
	}
}

void	sort_sprites(t_game *game)
{
	int	i;
	int	j;
	int	tmp;
	int	*orders;

	i = 0;
	orders = game->bonus.sort_sp;
	while (i < game->bonus.nb_sp)
	{
		j = i + 1;
		while (j < game->bonus.nb_sp)
		{
			if (game->bonus.sps[orders[i]].dist > \
				game->bonus.sps[orders[j]].dist)
			{
				tmp = orders[i];
				orders[i] = orders[j];
				orders[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	get_color_ratio(t_game *game, t_sprite *sprite, int i, int j)
{
	int	size;

	size = game->bonus.text_sp[sprite->type][sprite->anim_id].height;
	return (game->bonus.text_sp[sprite->type][sprite->anim_id].data[\
	i * size / sprite->screen_size + (j * size / sprite->screen_size) * \
	game->bonus.text_sp[sprite->type][sprite->anim_id].size_line]);
}

void	draw_sprite(t_game *game, t_sprite *sprite, double angle)
{
	int	h_offset;
	int	v_offset;
	int	i;
	int	j;

	h_offset = (sprite->dir - angle) * SCREEN_W / game->player.fov + SCREEN_W \
	/ 2 - sprite->screen_size / 2;
	v_offset = SCREEN_H / 2;
	i = -1;
	sprite->anim_id = (sprite->anim_id + 1) % sprite->anim_size;
	while (++i < sprite->screen_size)
	{
		if ((h_offset + i < 0 || h_offset + i >= SCREEN_W) || (game->player.\
rays[h_offset + i].hit_point.dist < sprite->dist * game->cube_size))
			continue ;
		j = -1;
		while (++j < sprite->screen_size)
		{
			if (v_offset + j < 0 || v_offset + j >= SCREEN_H)
				continue ;
			cb_put_pixel(&game->img, h_offset + i, v_offset + j, \
				fog_texture(get_color_ratio(game, sprite, i, j), \
				sprite->dist * game->cube_size));
		}
	}
}
