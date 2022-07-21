/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:09:58 by cdefonte          #+#    #+#             */
/*   Updated: 2022/07/21 19:10:35 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* Matrice de rotation: x' = cos(alpha).x - sin(alpha).y et y' = sin(alpha).x + cos(alpha).y */
struct s_coord	rotate_vector_angle(struct s_coord from, double angle)
{
	struct s_coord	res;

	res.x = cos(angle) * from.x - sin(angle) * from.y;
	res.y = sin(angle) * from.x + cos(angle) * from.y;
//	if (angle >= 0.0 && angle <= PI / 2)
//	{
//		printf("1\n");
//		res.x = cos(angle) * from.x - sin(angle) * from.y;
//		res.y = sin(angle) * from.x + cos(angle) * from.y;
//	}
//	else if (angle <= 0 && angle >= - PI / 2)
//	{
//		printf("2\n");
//		res.x = cos(angle) * from.x + sin(angle) * from.y;
//		res.y = -sin(angle) * from.x + cos(angle) * from.y;
//	}
//	else if (angle >= PI / 2 && angle <= PI)
//	{
//		printf("3\n");
//		res.x = -sin(angle) * from.x - cos(angle) * from.y;
//		res.y = cos(angle) * from.x - sin(angle) * from.y;
//	}
//	else if ((angle >= PI && angle <= PI + PI / 2) || (angle <= - PI / 2 && angle >= - PI))
//	{
//		printf("4\n");
//		res.x = -cos(angle) * from.x + sin(angle) * from.y;
//		res.y = -sin(angle) * from.x - cos(angle) * from.y;
//	}
//	if ((from.x >= 0.0 && from.x <= 1.0) && (from.y >= 0.0 && from.y <= 1)) // angle
//	{
//		res.x = cos(angle) * from.x - sin(angle) * from.y;
//		res.y = sin(angle) * from.x + cos(angle) * from.y;
//	}
//	else if ((from.x >= -1.0 && from.x <= 0.0) && (from.y >= 0.0 && from.y <= 1.0)) // angle + PI/2
//	{
//		res.x = -sin(angle) * from.x - cos(angle) * from.y;
//		res.y = cos(angle) * from.x - sin(angle) * from.y;
//	}
//	else if ((from.x >= -1.0 && from.x <= 0.0) && (from.y >= -1.0 && from.y <= 0.0))
//	{
//		res.x = -cos(angle) * from.x + sin(angle) * from.y;
//		res.y = -sin(angle) * from.x - cos(angle) * from.y;
//	}
//	else if ((from.x >= 0.0 && from.x <= 1.0) && (from.y >= -1.0 && from.y <= 0.0))
//	{
//		res.x = cos(angle) * from.x + sin(angle) * from.y;
//		res.y = -sin(angle) * from.x + cos(angle) * from.y;
//	}
	res.z = CUBE_SIZE / 2;	// useless for now
	return (res);
}
