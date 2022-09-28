#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "socket.h"
#include "cubed.h"

static int	read_server(t_game *game, char *buffer);
static void	write_server(t_game *game, const char *buffer);

bool	send_pos(t_game *game)
{
	sprintf(game->bonus.buf, "%f:%f", game->player.pos.x, game->player.pos.y); // TODO: replace sprintf
	write_server(game, game->bonus.buf);
	// if(send(game->bonus.sock, msg, strlen(msg), 0) < 0)
	// {
	// 	free(msg);
	// 	perror("send()");
	// 	return (false);
	// }
	ft_bzero(game->bonus.buf, sizeof(char)*50);
	return (true);
}

// get info from server and print it to stdout
bool	get_pos(t_game *game)
{
	int	ret;

	FD_ZERO(&(game->bonus.rdfs));
	FD_SET(game->bonus.sock, &game->bonus.rdfs);
	if((ret = select(game->bonus.sock + 1, &game->bonus.rdfs, NULL, NULL, &(struct timeval){})) < 0)
	{
		perror("select()");
		ft_exit(game);
	}
	if (FD_ISSET(game->bonus.sock, &game->bonus.rdfs))
	{
		if (game->bonus.buf == NULL)
			return (false);
		int n = read_server(game, game->bonus.buf);
		if(n == 0)
		{
			printf("Server disconnected !\n");
			return (false);
		}
		game->bonus.buf[n] = '\0';
		if (game->bonus.buf[0] == 'n')
		{
			printf("New player with id %d !\n", ft_atoi(game->bonus.buf+2));
		}
		else if (game->bonus.buf[0] == 'd')
		{
			printf("Delete player with id %d !\n", ft_atoi(game->bonus.buf+2));
		}
		else if (game->bonus.buf[0] == 'p')
		{
			// int id = atoi(game->bonus.buf);
			int id = ft_atoi(game->bonus.buf+2);
			game->bonus.sps[id].pos.x = ft_atof(game->bonus.buf+4);
			game->bonus.sps[id].pos.y = ft_atof(ft_strchr(game->bonus.buf+4, ':')+1);
		}
	}
	ft_bzero(game->bonus.buf, sizeof(char)*50);
	return (true);
}


int init_connection(t_game *game, const char *address)
{
	SOCKET		sock;
	SOCKADDR_IN	sin = { 0 };

	struct hostent *hostinfo;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET)
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
	sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr_list[0];
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;
	if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		perror("connect()");
		exit(errno);
	}
	game->bonus.buf = ft_calloc(sizeof(char), 50);
	return sock;
}

// static void app(SOCKET sock, const char *name)
// {
// 	char buffer[BUF_SIZE];

// 	fd_set rdfs;
// 	/* send our name */
// 	write_server(sock, name);

// 	while(1)
// 	{
// 		FD_ZERO(&rdfs);

// 		/* add STDIN_FILENO */
// 		FD_SET(STDIN_FILENO, &rdfs);

// 		/* add the socket */
// 		FD_SET(sock, &rdfs);

// 		if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
// 		{
// 			perror("select()");
// 			ft_exit(errno);
// 		}

// 		/* something from standard input : i.e keyboard */
// 		if(FD_ISSET(STDIN_FILENO, &rdfs))
// 		{
// 			fgets(buffer, BUF_SIZE - 1, stdin);

// 			strcpy(buffer, "1.5:5.5");

// 			write_server(sock, buffer);
// 		}
// 		else if(FD_ISSET(sock, &rdfs))
// 		{
// 			int n = read_server(sock, buffer);
// 			/* server down */
// 			if(n == 0)
// 			{
// 				printf("Server disconnected !\n");
// 				break;
// 			}
// 			puts(buffer);
// 		}
// 	}
// }


static int read_server(t_game *game, char *buffer)
{
	int n = 0;

	if((n = read(game->bonus.sock, buffer, 50)) < 0)
	{
		perror("read()");
		ft_exit(game);
	}
	if (n < 50)
		buffer[n] = 0;
	else
		buffer[49] = 0;
	return n;
}

static void write_server(t_game *game, const char *buffer)
{
	if(write(game->bonus.sock, buffer, strlen(buffer)) < 0)
	{
		perror("send()");
		ft_exit(game);
	}
}

// int main(int argc, char **argv)
// {
// 	if(argc < 2)
// 	{
// 		printf("Usage : %s [address] [pseudo]\n", argv[0]);
// 		return ft_exit_FAILURE;
// 	}

// 	return ft_exit_SUCCESS;
// }
