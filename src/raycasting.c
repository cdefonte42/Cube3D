/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:03:07 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/20 13:21:03 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Eq droite: Or(t) = Op + t * Od Avec Or = infinite rays(t). Op = point origine ray.
Od = vecteur directeur (du screen/plan de projection) = (last ray vector - first ray vector).
t = longueur */ 
void	raytracing(t_game *game)
{
	t_ray	oray;	// ray aligne avec la view/dir du player;

	oray.vec.x = game->player.pos.x + 1 * game->player.dir.x; 
	oray.vec.y = game->player.pos.y + 1 * game->player.dir.y; 

	printf("oray dir x = %f y = %f\n", oray.vec.x, oray.vec.y);
}
