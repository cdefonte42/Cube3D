/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:32:55 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/28 15:22:29 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	clear_texture(t_game *game)
{
	int	i;

	i = 0;
	if (game->text)
	{
		while (i < door)
		{
			free(game->text[i].path);
			if (game->text[i].ptr)
				mlx_destroy_image(game->mlx_ptr, game->text[i].ptr);
			++i;
		}
		free(game->text);
	}
}

/*Appellee quand red cross clicked ou ESC press*/
int	ft_exit(t_game *game)
{
	if (!game)
		return (0);
	clear_texture(game);
	if (game->player.rays)
		free(game->player.rays);
	if (game->img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.ptr);
	if (game->map.img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->map.img.ptr);
	if (game->map.grid.ptr)
		mlx_destroy_image(game->mlx_ptr, game->map.grid.ptr);
	if (game->minimap.ptr)
		mlx_destroy_image(game->mlx_ptr, game->minimap.ptr);
	if (game->map.tab)
		ft_free_map_i(game->map.tab, game->map.height);
	if (game->mlx_ptr && game->win)
	{
		mlx_mouse_show(game->mlx_ptr, game->win);
		mlx_do_key_autorepeaton(game->mlx_ptr);
	}
	if (game->win)
		mlx_destroy_window(game->mlx_ptr, game->win);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(0);
}

/* Refresh les differents affichages (game screen, minimap). Implique le
recalcul de tous les rayons. */
void	refresh_game(t_game *game)
{
	raycasting(game);
	draw_map(game);
	draw_game(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.ptr, 0, 0);
	if (game->minimap.ptr != NULL && game->map.state == off)
	{
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win,
			game->minimap.ptr, 0, 0);
	}
	else
		mlx_put_image_to_window(game->mlx_ptr, game->win,
			game->map.img.ptr, 0, 0);
}

int	tab_hook(int keycode, void *param)
{
	t_game	*game;

	game = param;
	if (keycode == TAB)
	{
		if (game->map.state == off)
			game->map.state = on;
		else
			game->map.state = off;
		#ifndef BONUS
		refresh_game(game);
		#endif
	}
	return (0);
}

void	change_state_door(t_game *game, t_ray ray)
{
	int	x;
	int	y;

	x = (int)ray.hit_point.pos[grid].x / game->cube_size;
	y = (int)ray.hit_point.pos[grid].y / game->cube_size;
	if ((ray.hit_point.type == vline) && ray.step_x <= 0)
		--x;
	if ((ray.hit_point.type == hline) && ray.step_y <= 0)
		--y;
	if (game->map.tab[y][x] == 'O')
		game->map.tab[y][x] = 'C';
	else if (game->map.tab[y][x] == 'C')
		game->map.tab[y][x] = 'O';
}

void	space_hook(t_game *game)
{
	t_ray	ray;

	ray = game->player.rays[SCREEN_W / 2 -1];
	if (ray.hit_point.type == door && ray.hit_point.dist <= game->cube_size)
	{
		change_state_door(game, ray);
	}
	else
	{
		set_ray_steps(game, &ray);
		next_hit_point(&ray);
		if (check_hit_point_is_door(game, ray) == true)
			change_state_door(game, ray);
	}

}

void	dispatch_player_move(t_game *game, int keycode)
{
	if (keycode == W_KEY)
	{
		back_front_mvx(game, 1, game->colision);
		back_front_mvy(game, 1, game->colision);
	}
	else if (keycode == S_KEY)
	{
		back_front_mvx(game, -1, game->colision);
		back_front_mvy(game, -1, game->colision);
	}
	else if (keycode == A_KEY)
	{
		stepaside_mvx(game, 1, game->colision);
		stepaside_mvy(game, 1, game->colision);
	}
	else if (keycode == D_KEY)
	{
		stepaside_mvx(game, -1, game->colision);
		stepaside_mvy(game, -1, game->colision);
	}
}

/* Appellee quand mlx_key_hook declenchee */
int	key_hook(int keycode, void *param)
{
	t_game	*game;

	game = param;
	if (keycode == ESC)
		ft_exit(game);
	if (keycode == R_ARW)
		game->player.dir = rotate_vector(game->player.dir,
				game->player.rot_speed);
	else if (keycode == L_ARW)
		game->player.dir = rotate_vector(game->player.dir,
				-game->player.rot_speed);
	else
		dispatch_player_move(game, keycode);

	#ifndef BONUS
	refresh_game(game);
	#endif
	return (0);
}
