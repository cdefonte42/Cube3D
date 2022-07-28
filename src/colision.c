/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:00:03 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/29 00:56:10 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	colisionx(t_game *game, int keycode)
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
		stepx = 1.0 - modf(game->player.pos.x, &int_part);
	else
		stepx = modf(game->player.pos.x, &int_part);
	if (fabs(mvx) <= stepx / 4 || game->map.tab[(int)taby][(int)tabx] != '1')
	{
		if (fabs(mvx) <= stepx / 4
			|| modf(game->player.pos.y, &int_part) > 5 / game->cube_size)
			game->player.pos.x += mvx;
		else if (game->map.tab[(int)--taby][(int)tabx] != '1')
			game->player.pos.x += mvx;
	}
}

void	colisiony(t_game *game, int keycode)
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
		stepy = 1.0 - modf(game->player.pos.y, &int_part);
	else
		stepy = modf(game->player.pos.y, &int_part);
	if (fabs(mvy) <= stepy / 4 || game->map.tab[(int)taby][(int)tabx] != '1')
	{
		if (fabs(mvy) <= stepy / 4
			|| modf(game->player.pos.x, &int_part) > 5 / game->cube_size)
			game->player.pos.y += mvy;
		else if (game->map.tab[(int)taby][(int)--tabx] != '1')
			game->player.pos.y += mvy;
	}
}

void	colision_sidex(t_game *game, int keycode)
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
		stepx = 1.0 - modf(game->player.pos.x, &int_part);
	else
		stepx = modf(game->player.pos.x, &int_part);
	if (fabs(mvx) <= stepx / 4 || game->map.tab[(int)taby][(int)tabx] != '1')
	{
		if (fabs(mvx) <= stepx / 4
			|| modf(game->player.pos.y, &int_part) > 5 / game->cube_size)
			game->player.pos.x += mvx;
		else if (game->map.tab[(int)--taby][(int)tabx] != '1')
			game->player.pos.x += mvx;
	}
}

void	colision_sidey(t_game *game, int keycode)
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
		stepy = 1.0 - modf(game->player.pos.y, &int_part);
	else
		stepy = modf(game->player.pos.y, &int_part);
	if (fabs(mvy) <= stepy / 4 || game->map.tab[(int)taby][(int)tabx] != '1')
	{
		if (fabs(mvy) <= stepy / 4
			|| modf(game->player.pos.x, &int_part) > 5 / game->cube_size)
			game->player.pos.y -= mvy;
		else if (game->map.tab[(int)taby][(int)--tabx] != '1')
			game->player.pos.y -= mvy;
	}
}

bool	set_colision_deltas(t_game *game, int way, int keycode)
{
	if (keycode == W_KEY || keycode == S_KEY)
	{
		colisiony(game, way);
		colisionx(game, way);
	}
	else
	{
		colision_sidex(game, way);
		colision_sidey(game, way);
	}
	return (false);
}
