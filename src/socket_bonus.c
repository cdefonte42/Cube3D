/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:32:55 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 16:32:56 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.h"

void	set_eof(char *buf, int n, int size)
{
	if (n < size)
		buf[n] = 0;
	else
		buf[size - 1] = 0;
}

int	read_server(t_game *game, char *buffer)
{
	int	n;

	n = read(game->bonus.sock, buffer, BUFFER_SIZE);
	if (n < 0)
	{
		perror("read()");
		ft_exit(game);
	}
	set_eof(game->bonus.buf, n, BUFFER_SIZE);
	return (n);
}

void	write_server(t_game *game, const char *buffer)
{
	if (write(game->bonus.sock, buffer, ft_strlen(buffer)) < 0)
	{
		perror("send()");
		ft_exit(game);
	}
}
