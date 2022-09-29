/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:13:31 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/28 17:13:32 by mbraets          ###   ########.fr       */
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

// TODO: Rename the function and move it to utils.c
void	cb_put_pixel(t_img *data, int x, int y, int color)
{
	int	*dst;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return ;
	dst = data->data + (y * data->size_line + x * (data->bpp / 32));
	*(unsigned int *)dst = color;
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

// static void	draw_sprite_pixels(t_game *game, t_sprite *sprite)
// {

// } 

void	draw_sprite(t_game *game, t_sprite *sprite, double angle)
{
	int	sprite_screen_size;
	int	h_offset;
	int	v_offset;
	int	size;
	int	color;
	int	i;
	int	j;

	sprite_screen_size = fmin(SCREEN_H, SCREEN_H / (sprite->dist * 2));
	h_offset = (sprite->dir - angle) * SCREEN_W / game->player.fov + SCREEN_W \
	/ 2 - sprite_screen_size / 2;
	v_offset = SCREEN_H / 2 + 24;
	size = game->bonus.text_sp[sprite->type][sprite->anim_id].height;
	sprite->anim_id = (sprite->anim_id + 1) % sprite->anim_size;
	i = -1;
	while (++i < sprite_screen_size)
	{
		if ((h_offset + i < 0 || h_offset + i >= SCREEN_W) || (game->player.\
rays[h_offset + i].hit_point.dist < sprite->dist * game->cube_size))
			continue ;
		j = -1;
		while (++j < sprite_screen_size)
		{
			if (v_offset + j < 0 || v_offset + j >= SCREEN_H)
				continue ;
			color = game->bonus.text_sp[sprite->type][sprite->anim_id].data[\
			i * size / sprite_screen_size + (j * size / sprite_screen_size) * \
			game->bonus.text_sp[sprite->type][sprite->anim_id].size_line];
			if (((color >> 24) & 0xFF) != 0xFF)
				cb_put_pixel(&game->img, h_offset + i, v_offset + j, \
				fog_texture(color, sprite->dist * game->cube_size));
		}
	}
}
