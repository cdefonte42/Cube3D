/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:09:58 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/27 19:02:06 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Matrice de rotation: x' = cos(alpha).x - sin(alpha).y et 
y' = sin(alpha).x + cos(alpha).y */
struct s_coord	rotate_vector(struct s_coord from, double angle)
{
	struct s_coord	res;

	res.x = cos(angle) * from.x - sin(angle) * from.y;
	res.y = sin(angle) * from.x + cos(angle) * from.y;
	res.z = CUBE_SIZE / 2;
	return (res);
}
