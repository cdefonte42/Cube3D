/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:33:53 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/29 16:33:55 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_H
# define SOCKET_H

# include <sys/select.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h> /* close */
# include <netdb.h> /* gethostbyname */

# include "cubed.h"

# define INVALID_SOCKET -1
# define SOCKET_ERROR -1

# define BUFFER_SIZE 100
# define PORT 1977

typedef int					t_socket;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;
typedef struct in_addr		t_in_addr;

/* private */
int		read_server(t_game *game, char *buffer);
void	write_server(t_game *game, const char *buffer);
void	set_eof(char *buf, int n, int size);

/* public */
int		init_connection(t_game *game, const char *address);
bool	get_pos(t_game *game);
bool	send_pos(t_game *game);

#endif /* guard */