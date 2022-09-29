/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:08:02 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 16:08:03 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.h"

// TODO: replace sprintf
bool	send_pos(t_game *game)
{
	int	n;

	n = sprintf(game->bonus.buf, "%.6f:%.6f", \
				game->player.pos.x, game->player.pos.y);
	set_eof(game->bonus.buf, n, BUFFER_SIZE);
	write_server(game, game->bonus.buf);
	ft_bzero(game->bonus.buf, sizeof(char) * BUFFER_SIZE);
	return (true);
}
typedef struct timeval	t_t;

static void	set_player_pos(t_game *game, double x, double y)
{
	game->bonus.sps[ft_atoi(game->bonus.buf + 2)].pos.x = x;
	game->bonus.sps[ft_atoi(game->bonus.buf + 2)].pos.y = y;
}

static void	parse_info(t_game *game)
{
	if (game->bonus.buf[0] == 'n')
	{
		set_player_pos(game, ft_atof(game->bonus.buf + 4), \
			ft_atof(ft_strchr(game->bonus.buf + 4, ':') + 1));
	}
	else if (game->bonus.buf[0] == 'd')
	{
		printf("Delete player with id%d !\n", ft_atoi(game->bonus.buf + 2));
		set_player_pos(game, 0, 0);
	}
	else if (game->bonus.buf[0] == 'p')
	{
		set_player_pos(game, ft_atof(game->bonus.buf + 4), \
			ft_atof(ft_strchr(game->bonus.buf + 4, ':') + 1));
	}
}

// get info from server and print it to stdout
bool	get_pos(t_game *game)
{
	int	ret;

	FD_ZERO(&(game->bonus.rdfs));
	FD_SET(game->bonus.sock, &game->bonus.rdfs);
	ret = select(game->bonus.sock + 1, &game->bonus.rdfs, NULL, NULL, &(t_t){});
	if (ret < 0)
	{
		perror("select()");
		ft_exit(game);
	}
	if (FD_ISSET(game->bonus.sock, &game->bonus.rdfs))
	{
		if (game->bonus.buf == NULL)
			return (false);
		ret = read_server(game, game->bonus.buf);
		if (ret == 0)
			return (error("Server disconnected.", NULL));
		parse_info(game);
	}
	ft_bzero(game->bonus.buf, sizeof(char) * BUFFER_SIZE);
	return (true);
}

int	init_connection(t_game *game, const char *address)
{
	t_socket			sock;
	t_sockaddr_in		sin;
	struct hostent		*hostinfo;

	ft_bzero(&sin, sizeof(sin));
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}
	hostinfo = gethostbyname(address);
	if (hostinfo == NULL)
	{
		error("Unknown host", address);
		exit(EXIT_FAILURE);
	}
	sin.sin_addr = *(t_in_addr *)hostinfo->h_addr_list[0];
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;
	if (connect(sock, (t_sockaddr *)&sin, sizeof(t_sockaddr)) == SOCKET_ERROR)
		return (perror("connect()"), -1);
	game->bonus.buf = ft_calloc(sizeof(char), BUFFER_SIZE);
	return (sock);
}
