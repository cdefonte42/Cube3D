/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/19 15:57:29 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

/* Eq droite: Or(t) = Op + t * Od Avec Or = infinite rays(t). Op = 1er ray.
Od = vecteur directeur (du screen/plan de projection) = (last ray vector - first ray vector). t = en gros distance parcourue sur le plan de proj par rapport a Op pour un
ray donne. */ 
void	raytracing(t_game *game)
{
	t_pos	p_pos;
	t_vec	H_next_line;	// vecteur appartenant au ray courant et ayant pour origine le player, permettant d'atteindre la prochaine ligne horizontale;
	t_vec	V_next_line;

	p_pos = game.player.pos;
	H_next_line.x = p_pos.x 

}

int	main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	/* ____ MLX INIT ___*/
	t_game	game;
	game.map = ft_clean_map(argc, argv);
	game.title = "Cub3D";
	game.width = SCREEN_W;
	game.height = SCREEN_H;
	game.player.fov = (60.0 * PI) / 180.0;
	game.player.dist_screen = game.width / tan(game.player.fov);

	game.player.pos.sid = grid;
	game.player.pos.x = 6.5; //exprime en grid unit, soit *64 pour pixels
	game.player.pos.y = 2.5;
	game.player.pos.z = 0.0;
	game.player.dir.sid = grid;
	game.player.dir.x = 0.0;
	game.player.dir.y = -1.0; // North
	game.player.dir.z = 0.0;


	raytracing(&game);

	if (init_mlx(&game) == -1)
		return (printf("Error init mlx\n"), ft_exit(&game), 1);

	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_hook(game.win_ptr, 17, 0, &ft_exit, &game);
	mlx_loop(game.mlx_ptr);
	ft_exit(&game);
	return (0);
}
