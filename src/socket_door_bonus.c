/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_door_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:15:23 by mbraets           #+#    #+#             */
/*   Updated: 2022/10/04 13:15:25 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.h"
#include "cubed.h"

void	send_door_state(t_game *game, int x, int y)
{
	int		n;
	char	state;

	state = game->map.tab[y][x];
	n = sprintf(game->bonus.buf, "%c:%d:%d", state, x, y);
	set_eof(game->bonus.buf, n, BUFFER_SIZE);
	write_server(game, game->bonus.buf);
	ft_bzero(game->bonus.buf, sizeof(char) * BUFFER_SIZE);
}

void	close_door(t_game *game)
{
	int	x;
	int	y;

	x = ft_atoi(game->bonus.buf + 2);
	y = ft_atoi(ft_strchr(game->bonus.buf + 2, ':') + 1);
	if (x < 0 || y < 0 || x > game->map.width || y > game->map.height)
		return ;
	game->map.tab[y][x] = 'C';
}

void	open_door(t_game *game)
{
	int	x;
	int	y;

	x = ft_atoi(game->bonus.buf + 2);
	y = ft_atoi(ft_strchr(game->bonus.buf + 2, ':') + 1);
	if (x < 0 || y < 0 || x > game->map.width || y > game->map.height)
		return ;
	game->map.tab[y][x] = 'O';
}
