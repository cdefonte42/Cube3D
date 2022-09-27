#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "socket.h"

#include "cubed.h"


static int	read_server(SOCKET sock, char *buffer);
static void	write_server(SOCKET sock, const char *buffer);

bool	send_pos(t_game *game)
{
	sprintf(game->buf, "%f:%f", game->player.pos.x, game->player.pos.y);
	write_server(game->sock, game->buf);
	// if(send(game->sock, msg, strlen(msg), 0) < 0)
	// {
	// 	free(msg);
	// 	perror("send()");
	// 	return (false);
	// }
	ft_bzero(game->buf, sizeof(char)*50);
	return (true);
}

// get info from server and print it to stdout
bool	get_pos(t_game *game)
{
	int	ret;

	FD_ZERO(&(game->rdfs));
	FD_SET(game->sock, &game->rdfs);
	if((ret = select(game->sock + 1, &game->rdfs, NULL, NULL, &(struct timeval){})) < 0)
	{
		perror("select()");
		exit(errno);
	}
	if (FD_ISSET(game->sock, &game->rdfs))
	{
		if (game->buf == NULL)
			return (false);
		int n = read_server(game->sock, game->buf);
		if(n == 0)
		{
			printf("Server disconnected !\n");
			return (false);
		}
		game->buf[n] = '\0';
		if (game->buf[0] == 'n')
		{
			printf("New player with id %d !\n", ft_atoi(game->buf+2));
		}
		else if (game->buf[0] == 'd')
		{
			printf("Delete player with id %d !\n", ft_atoi(game->buf+2));
		}
		else if (game->buf[0] == 'p')
		{
			// int id = atoi(game->buf);
			int id = 0;
			game->sprites[id].x = atof(game->buf+2);
			game->sprites[id].y = atof(ft_strchr(game->buf+2, ':')+1);
		}
	}
	ft_bzero(game->buf, sizeof(char)*50);
	return (true);
}


int init_connection(t_game *game, const char *address)
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin = { 0 };

	struct hostent *hostinfo;

	if(sock == INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}

	hostinfo = gethostbyname(address);
	if (hostinfo == NULL)
	{
		fprintf (stderr, "Unknown host %s.\n", address);
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
	game->buf = ft_calloc(sizeof(char), 50);

	return sock;
}

void end_connection(int sock)
{
	closesocket(sock);
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
// 			exit(errno);
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


static int read_server(SOCKET sock, char *buffer)
{
	int n = 0;

	if((n = recv(sock, buffer, 50, 0)) < 0)
	{
		perror("recv()");
		exit(errno);
	}

	buffer[n] = 0;

	return n;
}

static void write_server(SOCKET sock, const char *buffer)
{
	if(send(sock, buffer, strlen(buffer), 0) < 0)
	{
		perror("send()");
		exit(errno);
	}
}

// int main(int argc, char **argv)
// {
// 	if(argc < 2)
// 	{
// 		printf("Usage : %s [address] [pseudo]\n", argv[0]);
// 		return EXIT_FAILURE;
// 	}

// 	return EXIT_SUCCESS;
// }
