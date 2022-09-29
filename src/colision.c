/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:00:03 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/29 15:26:55 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#if BONUS
# define WALL "1C"
#else
# define WALL "1"
#endif

void	back_front_mvx(t_game *game, int keycode, double limit)
{
	double	x;
	double	y;
	double	int_part;
	double	stepx;
	double	mvx;

	mvx = game->player.dir.x * keycode * game->player.mv_speed;
	modf(game->player.pos.x, &x);
	modf(game->player.pos.y, &y);
	if (mvx >= 0)
		++x;
	else
		--x;
	if (mvx >= 0)
		stepx = 1.0 - limit - modf(game->player.pos.x, &int_part);
	else
		stepx = modf(game->player.pos.x, &int_part) - limit;
	if (fabs(mvx) < stepx || !ft_strchr(WALL, game->map.tab[(int)y][(int)x]))
	{
		if (fabs(mvx) < stepx
			|| modf(game->player.pos.y, &int_part) > 5 / game->cube_size)
			game->player.pos.x += mvx;
		else if (!ft_strchr(WALL, game->map.tab[(int)--y][(int)x]))
			game->player.pos.x += mvx;
	}
}

void	back_front_mvy(t_game *game, int keycode, double limit)
{
	double	x;
	double	y;
	double	int_part;
	double	stepy;
	double	mvy;

	mvy = game->player.dir.y * keycode * game->player.mv_speed;
	modf(game->player.pos.x, &x);
	modf(game->player.pos.y, &y);
	if (mvy >= 0)
		++y;
	else
		--y;
	if (mvy >= 0)
		stepy = 1.0 - limit - modf(game->player.pos.y, &int_part);
	else
		stepy = modf(game->player.pos.y, &int_part) - limit;
	if (fabs(mvy) < stepy || !ft_strchr(WALL, game->map.tab[(int)y][(int)x]))
	{
		if (fabs(mvy) < stepy
			|| modf(game->player.pos.x, &int_part) > 5 / game->cube_size)
			game->player.pos.y += mvy;
		else if (!ft_strchr(WALL, game->map.tab[(int)y][(int)--x]))
			game->player.pos.y += mvy;
	}
}

void	stepaside_mvx(t_game *game, int keycode, double limit)
{
	double	x;
	double	y;
	double	int_part;
	double	stepx;
	double	mvx;

	mvx = game->player.dir.y * keycode * game->player.mv_speed;
	modf(game->player.pos.x, &x);
	modf(game->player.pos.y, &y);
	if (mvx >= 0)
		++x;
	else
		--x;
	if (mvx >= 0)
		stepx = 1.0 - limit - modf(game->player.pos.x, &int_part);
	else
		stepx = modf(game->player.pos.x, &int_part) - limit;
	if (fabs(mvx) < stepx || !ft_strchr(WALL, game->map.tab[(int)y][(int)x]))
	{
		if (fabs(mvx) < stepx
			|| modf(game->player.pos.y, &int_part) > 5 / game->cube_size)
			game->player.pos.x += mvx;
		else if (!ft_strchr(WALL, game->map.tab[(int)--y][(int)x]))
			game->player.pos.x += mvx;
	}
}

void	stepaside_mvy(t_game *game, int keycode, double limit)
{
	double	x;
	double	y;
	double	mvy;
	double	int_part;
	double	stepy;

	mvy = -game->player.dir.x * keycode * game->player.mv_speed;
	modf(game->player.pos.x, &x);
	modf(game->player.pos.y, &y);
	if (mvy >= 0)
		++y;
	else
		--y;
	if (mvy >= 0)
		stepy = 1.0 - limit - modf(game->player.pos.y, &int_part);
	else
		stepy = modf(game->player.pos.y, &int_part) - limit;
	if (fabs(mvy) < stepy || !ft_strchr(WALL, game->map.tab[(int)y][(int)x]))
	{
		if (fabs(mvy) < stepy
			|| modf(game->player.pos.x, &int_part) > 5 / game->cube_size)
			game->player.pos.y += mvy;
		else if (!ft_strchr(WALL, game->map.tab[(int)y][(int)--x]))
			game->player.pos.y += mvy;
	}
}
