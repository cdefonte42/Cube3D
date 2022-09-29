/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:38:06 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 12:38:06 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	init_texture_door(t_game *game)
{
	if (!cb_load_mlx_image(game->mlx_ptr, "img/door_64.xpm", &game->text[door]))
		return (error("Loading door image", NULL));
	return (true);
}
