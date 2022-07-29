/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:00:03 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/29 22:05:59 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	back_front_mvx(t_game *game, int keycode, double limit)
{
	double	tabx;
	double	taby;
	double	int_part;
	double	stepx;
	double	mvx;

	mvx = game->player.dir.x * keycode * game->player.mv_speed;
	modf(game->player.pos.x, &tabx);
	modf(game->player.pos.y, &taby);
	if (mvx >= 0)
		++tabx;
	else
		--tabx;
	if (mvx >= 0)
		stepx = 1.0 - limit - modf(game->player.pos.x, &int_part);
	else
		stepx = modf(game->player.pos.x, &int_part) - limit;
	if (fabs(mvx) < stepx || game->map.tab[(int)taby][(int)tabx] != '1')
	{
		if (fabs(mvx) < stepx
			|| modf(game->player.pos.y, &int_part) > 5 / game->cube_size)
			game->player.pos.x += mvx;
		else if (game->map.tab[(int)--taby][(int)tabx] != '1')
			game->player.pos.x += mvx;
	}
}

void	back_front_mvy(t_game *game, int keycode, double limit)
{
	double	tabx;
	double	taby;
	double	int_part;
	double	stepy;
	double	mvy;

	mvy = game->player.dir.y * keycode * game->player.mv_speed;
	modf(game->player.pos.x, &tabx);
	modf(game->player.pos.y, &taby);
	if (mvy >= 0)
		++taby;
	else
		--taby;
	if (mvy >= 0)
		stepy = 1.0 - limit - modf(game->player.pos.y, &int_part);
	else
		stepy = modf(game->player.pos.y, &int_part) - limit;
	if (fabs(mvy) < stepy || game->map.tab[(int)taby][(int)tabx] != '1')
	{
		if (fabs(mvy) < stepy
			|| modf(game->player.pos.x, &int_part) > 5 / game->cube_size)
			game->player.pos.y += mvy;
		else if (game->map.tab[(int)taby][(int)--tabx] != '1')
			game->player.pos.y += mvy;
	}
}

void	stepaside_mvx(t_game *game, int keycode, double limit)
{
	double	tabx;
	double	taby;
	double	int_part;
	double	stepx;
	double	mvx;

	mvx = game->player.dir.y * keycode * game->player.mv_speed;
	modf(game->player.pos.x, &tabx);
	modf(game->player.pos.y, &taby);
	if (mvx >= 0)
		++tabx;
	else
		--tabx;
	if (mvx >= 0)
		stepx = 1.0 - limit - modf(game->player.pos.x, &int_part);
	else
		stepx = modf(game->player.pos.x, &int_part) - limit;
	if (fabs(mvx) < stepx || game->map.tab[(int)taby][(int)tabx] != '1')
	{
		if (fabs(mvx) < stepx
			|| modf(game->player.pos.y, &int_part) > 5 / game->cube_size)
			game->player.pos.x += mvx;
		else if (game->map.tab[(int)--taby][(int)tabx] != '1')
			game->player.pos.x += mvx;
	}
}

void	stepaside_mvy(t_game *game, int keycode, double limit)
{
	double	tabx;
	double	taby;
	double	mvy;
	double	int_part;
	double	stepy;

	mvy = -game->player.dir.x * keycode * game->player.mv_speed;
	modf(game->player.pos.x, &tabx);
	modf(game->player.pos.y, &taby);
	if (mvy >= 0)
		++taby;
	else
		--taby;
	if (mvy >= 0)
		stepy = 1.0 - limit - modf(game->player.pos.y, &int_part);
	else
		stepy = modf(game->player.pos.y, &int_part) - limit;
	if (fabs(mvy) < stepy || game->map.tab[(int)taby][(int)tabx] != '1')
	{
		if (fabs(mvy) < stepy
			|| modf(game->player.pos.x, &int_part) > 5 / game->cube_size)
			game->player.pos.y += mvy;
		else if (game->map.tab[(int)taby][(int)--tabx] != '1')
			game->player.pos.y += mvy;
	}
}
