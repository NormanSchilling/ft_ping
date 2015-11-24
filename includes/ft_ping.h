#ifndef FT_PING_H
# define FT_PING_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <signal.h>
# include <sys/time.h>
# include <netdb.h>
# include <linux/ip.h>
# include "../libft/libft.h"

# define PACKETSIZE	64

typedef struct	s_headicmp
{
	uint8_t		type;
	uint8_t		code;
	uint16_t	checksum;
}				t_headicmp;

typedef struct			s_ping
{
	struct s_headicmp	head;
	uint16_t			id;
	char				msg[16];
}						t_ping;

typedef struct addrinfo		t_addrinfo;
typedef struct sockaddr_in	t_sockaddrin;

#endif
