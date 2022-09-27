#ifndef CLIENT_H
# define CLIENT_H

# include <sys/select.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h> /* close */
# include <netdb.h> /* gethostbyname */

# define INVALID_SOCKET -1
# define SOCKET_ERROR -1
# define closesocket(s) close(s)

typedef int	SOCKET;
typedef struct	sockaddr_in SOCKADDR_IN;
typedef struct	sockaddr SOCKADDR;
typedef struct	in_addr IN_ADDR;

#define CRLF "\r\n"
#define PORT 1977

#define BUF_SIZE 1024

#include "cubed.h"
/*
static void	init(void);
static void	end(void);
static void	app(SOCKET sock, const char *name);
static void	end_connection(int sock);
*/

void	end_connection(int sock);
int		init_connection(t_game *game, const char *address);
bool	get_pos(t_game *game);
bool	send_pos(t_game *game);

#endif /* guard */