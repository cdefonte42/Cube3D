/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:00:03 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/29 00:28:05 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	colisionX(t_game *game, int keycode)
{
	double	tabx;
	double	taby;

	modf(game->player.pos.x, &tabx);
	modf(game->player.pos.y, &taby);
	
	double	dir_mvx = game->player.dir.x * keycode * game->player.mv_speed;

	if (dir_mvx >= 0)
		++tabx;
	else
		--tabx;

	double	int_part;
	double	stepX;
	if (dir_mvx >= 0)
		stepX = 1.0 - modf(game->player.pos.x, &int_part);
	else
		stepX = modf(game->player.pos.x, &int_part);

	if (fabs(dir_mvx) <= stepX / 4 || game->map.tab[(int)taby][(int)tabx] != '1')
	{
		if (fabs(dir_mvx) <= stepX / 8 || modf(game->player.pos.y, &int_part) > 5 / game->cube_size)
			game->player.pos.x += game->player.dir.x * keycode * game->player.mv_speed;
		else if (game->map.tab[(int)--taby][(int)tabx] != '1')
			game->player.pos.x += game->player.dir.x * keycode * game->player.mv_speed;
	}
}

void	colisionY(t_game *game, int keycode)
{
	double	tabx;
	double	taby;

	modf(game->player.pos.x, &tabx);
	modf(game->player.pos.y, &taby);
	
	double	dir_mvy = game->player.dir.y * keycode * game->player.mv_speed;

	if (dir_mvy >= 0)
		++taby;
	else
		--taby;

	double	int_part;
	double	stepY;
	if (dir_mvy >= 0)
		stepY = 1.0 - modf(game->player.pos.y, &int_part);
	else
		stepY = modf(game->player.pos.y, &int_part);

	if (fabs(dir_mvy) <= stepY / 8 || game->map.tab[(int)taby][(int)tabx] != '1')
	{
		if (fabs(dir_mvy) <= stepY / 8 || modf(game->player.pos.x, &int_part) > 5 / game->cube_size)
			game->player.pos.y += game->player.dir.y * keycode * game->player.mv_speed;
		else if (game->map.tab[(int)taby][(int)--tabx] != '1')
			game->player.pos.y += game->player.dir.y * keycode * game->player.mv_speed;
	}
}

void	colision_sideX(t_game *game, int keycode)
{
	double	tabx;
	double	taby;

	modf(game->player.pos.x, &tabx);
	modf(game->player.pos.y, &taby);
	
	double	dir_mvx = game->player.dir.y * keycode * game->player.mv_speed;

	if (dir_mvx >= 0)
		++tabx;
	else
		--tabx;

	double	int_part;
	double	stepX;
	if (dir_mvx >= 0)
		stepX = 1.0 - modf(game->player.pos.x, &int_part);
	else
		stepX = modf(game->player.pos.x, &int_part);

	if (fabs(dir_mvx) <= stepX / 4 || game->map.tab[(int)taby][(int)tabx] != '1')
		game->player.pos.x += game->player.dir.y * keycode * game->player.mv_speed;
}

void	colision_sideY(t_game *game, int keycode)
{
	double	tabx;
	double	taby;

	modf(game->player.pos.x, &tabx);
	modf(game->player.pos.y, &taby);
	
	double	dir_mvy = -game->player.dir.x * keycode * game->player.mv_speed;

	if (dir_mvy >= 0)
		++taby;
	else
		--taby;

	double	int_part;
	double	stepY;
	if (dir_mvy >= 0)
		stepY = 1.0 - modf(game->player.pos.y, &int_part);
	else
		stepY = modf(game->player.pos.y, &int_part);

	if (fabs(dir_mvy) <= stepY / 8 || game->map.tab[(int)taby][(int)tabx] != '1')
		game->player.pos.y -= game->player.dir.x * keycode * game->player.mv_speed;
}

bool	set_colision_deltas(t_game *game, int way, int keycode)
{
	if (keycode == W_KEY || keycode == S_KEY)
	{
		colisionY(game, way);
		colisionX(game, way);
	}
	else
	{
		colision_sideX(game, way);
		colision_sideY(game, way);
	}
	return (false);
}
