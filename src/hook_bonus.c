/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:54:24 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/28 11:43:11 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <time.h>

#include "socket.h"

static inline bool is_press_key(t_keyboard keyboard)
{
	return (keyboard.w == true || keyboard.d  == true || keyboard.a  == true || keyboard.s  == true );
}

int	loop_hook(t_game *game)
{
	clock_t	current_ticks;
	clock_t	delta_ticks;
	int		x;
	int		y;

	if (game->bonus.sock > 0)
	{
		if (!get_pos(game))
			ft_exit(game);
		if (is_press_key(game->player.keyboard))
		{
			if (!send_pos(game))
				ft_exit(game);
		}
	}
	current_ticks = clock();

	refresh_game(game);

	delta_ticks = clock() - current_ticks; //the time, in us, that took to render
	//if (delta_ticks > 0)
		//fps = CLOCKS_PER_SEC / delta_ticks;
	// while (clock() < current_ticks + CLOCKS_PER_SEC / 30)
        // ;
	if (delta_ticks < CLOCKS_PER_SEC / 20) // Useless ?
		usleep((CLOCKS_PER_SEC / 20 - delta_ticks));
	// printf(" %ld, %ld\n", CLOCKS_PER_SEC / delta_ticks, delta_ticks);
	// printf("FPS : %ld\n", fps);
    // mlx_mouse_show(game->mlx_ptr, game->win);

	// printf("FPS : %f\n", game->player.mv_speed );
	// game->player.mv_speed = 0.1;

	mlx_mouse_get_pos(game->mlx_ptr, game->win, &x, &y);
	if (game->player.keyboard.mouse && x != SCREEN_W/2)
	{
		mlx_mouse_move(game->mlx_ptr, game->win, SCREEN_W/2, SCREEN_H/2);
		game->player.dir = rotate_vector(game->player.dir,
			(x-SCREEN_W/2)/(double)360);
		// printf("%d\n", (x-SCREEN_W/2));
	}
	if (game->player.keyboard.shift)
		game->player.mv_speed = 0.4;
	else
		game->player.mv_speed = 0.1;
	if (game->player.keyboard.w)
	{
		back_front_mvx(game, 1, game->colision);
		back_front_mvy(game, 1, game->colision);
	}
	if (game->player.keyboard.s)
	{
		back_front_mvx(game, -1, game->colision);
		back_front_mvy(game, -1, game->colision);
	}
	if (game->player.keyboard.a)
	{
		stepaside_mvx(game, 1, game->colision);
		stepaside_mvy(game, 1, game->colision);
	}
	if (game->player.keyboard.d)
	{
		stepaside_mvx(game, -1, game->colision);
		stepaside_mvy(game, -1, game->colision);
	}
	if (game->player.keyboard.left)
		game->player.dir = rotate_vector(game->player.dir,
				-game->player.rot_speed);
	if (game->player.keyboard.right)
		game->player.dir = rotate_vector(game->player.dir,
				game->player.rot_speed);
	++game->bonus.tick; // TODO: Unused
	return (0);
}

void	change_state_door(t_game *game, t_ray ray)
{
	int	x;
	int	y;

	x = (int)ray.hit_point.pos[grid].x / game->cube_size;
	y = (int)ray.hit_point.pos[grid].y / game->cube_size;
	if (ray.step_y == 0 && ray.step_x <= 0)
		--x;
	if (ray.step_x == 0 && ray.step_y <= 0)
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
		change_state_door(game, ray);
	else
	{
		set_ray_steps(game, &ray);
		next_hit_point(&ray);
		if (ray.hit_point.type == vline)
			ray.step_y = 0;
		else
			ray.step_x = 0;
		if (check_hit_point_is_door(game, ray) == true)
			change_state_door(game, ray);
	}
}

int	press_hook(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_exit(game);
	if (keycode == R_ARW)
		game->player.keyboard.right = true;
	else if (keycode == L_ARW)
		game->player.keyboard.left = true;
	if (keycode == W_KEY)
		game->player.keyboard.w = true;
	else if (keycode == S_KEY)
		game->player.keyboard.s = true;
	else if (keycode == A_KEY)
		game->player.keyboard.a = true;
	else if (keycode == D_KEY)
		game->player.keyboard.d = true;
	if (keycode == TAB)
		game->map.state = true;
	return (0);
}

int	release_hook(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_exit(game);
	if (keycode == R_ARW)
		game->player.keyboard.right = false;
	else if (keycode == L_ARW)
		game->player.keyboard.left = false; 
	if (keycode == W_KEY)
		game->player.keyboard.w = false;
	else if (keycode == S_KEY)
		game->player.keyboard.s = false;
	else if (keycode == A_KEY)
		game->player.keyboard.a = false;
	else if (keycode == D_KEY)
		game->player.keyboard.d = false;
	if (keycode == TAB)
		game->map.state = false;
	if (keycode == SPACE)
		space_hook(game);	
	return (0);
}
int	in_hook(t_game *game)
{
	(void)game;
	game->player.keyboard.mouse = true;
	return (0);
}

int	out_hook(t_game *game)
{
	(void)game;
	game->player.keyboard.mouse = false;
	return (0);
}
