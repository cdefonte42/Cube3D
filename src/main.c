/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/09/28 14:55:10 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "X11/X.h"

int	loop_hook(t_game *game);
int	press_hook(int key, t_game *game);
int	in_hook(t_game *game);
int	out_hook(t_game *game);

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (init_game(&game, argc, argv) == -1)
		return (ft_exit(&game), 1);
	init_sprites_text(&game);
	refresh_game(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_key_hook(game.win, tab_hook, &game);
//	mlx_key_hook(game.map.win, key_hook, &game);
	mlx_hook(game.win, DestroyNotify, 0, &ft_exit, &game);
//	mlx_hook(game.map.win, 17, 0, &ft_exit, &game);
	mlx_hook(game.win, KeyPress, 1L << 0, &key_hook, &game);
	
//	mlx_hook(game.map.win, 2, 1L<<0, &key_hook, &game);
	#ifdef BONUS
    mlx_mouse_hide(game.mlx_ptr, game.win);
	mlx_hook(game.win, KeyPress, KeyPressMask, &press_hook, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &press_hook, &game);
	mlx_hook(game.win, FocusIn, FocusChangeMask, &in_hook, &game);
	mlx_hook(game.win, FocusOut, FocusChangeMask, &out_hook, &game);
	mlx_mouse_hook(game.win, NULL, NULL);
	mlx_do_key_autorepeatoff(game.mlx_ptr); // no difference seen with or without this line
	mlx_loop_hook(game.mlx_ptr, loop_hook, &game);
	#endif
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
