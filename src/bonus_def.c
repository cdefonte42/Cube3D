/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_def.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:51:40 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 11:51:42 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#if !BONUS

void	count_sprite(t_game *game, char *line)
{
	(void)game;
	(void)line;
}

bool	init_sprite(t_game *game)
{
	(void)game;
	return (true);
}
#endif
