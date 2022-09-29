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

inline static void	handle_key(bool condition, bool *k, bool v)
{
	if (condition)
		*k = v;
}

int	press_hook(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_exit(game);
	handle_key(keycode == R_ARW, &game->player.keyboard.right, true);
	handle_key(keycode == L_ARW, &game->player.keyboard.left, true);
	handle_key(keycode == W_KEY, &game->player.keyboard.w, true);
	handle_key(keycode == S_KEY, &game->player.keyboard.s, true);
	handle_key(keycode == A_KEY, &game->player.keyboard.a, true);
	handle_key(keycode == D_KEY, &game->player.keyboard.d, true);
	handle_key(keycode == SHIFT, &game->player.keyboard.shift, true);
	handle_key(keycode == TAB, &game->map.state, true);
	return (0);
}

int	release_hook(int keycode, t_game *game)
{
	handle_key(keycode == R_ARW, &game->player.keyboard.right, false);
	handle_key(keycode == L_ARW, &game->player.keyboard.left, false);
	handle_key(keycode == W_KEY, &game->player.keyboard.w, false);
	handle_key(keycode == S_KEY, &game->player.keyboard.s, false);
	handle_key(keycode == A_KEY, &game->player.keyboard.a, false);
	handle_key(keycode == D_KEY, &game->player.keyboard.d, false);
	handle_key(keycode == SHIFT, &game->player.keyboard.shift, false);
	handle_key(keycode == TAB, &game->map.state, false);
	if (keycode == SPACE)
		handle_use_key(game);
	return (0);
}

int	in_hook(t_game *game)
{
	game->player.keyboard.mouse = true;
	return (0);
}

int	out_hook(t_game *game)
{
	game->player.keyboard.mouse = false;
	return (0);
}
