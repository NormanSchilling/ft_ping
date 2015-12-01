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
# include <netinet/ip_icmp.h>
# include "../libft/libft.h"

# define PACKETSIZE	64

typedef struct addrinfo		t_addrinfo;
typedef struct sockaddr_in	t_sockaddrin;
typedef struct timeval		t_timeval;

typedef struct	packet
{
	struct icmphdr hdr;
	char msg[PACKETSIZE - sizeof(struct icmphdr)];
}				t_packet;

typedef struct		ping
{
	t_packet		packet;
	t_addrinfo		*info;
	t_sockaddrin	src;
	t_sockaddrin	dest;
	t_timeval		start;
	t_timeval		end;
	int				sock;
	int				count;
	double			avg;
	double			max;
	double			min;
	double			sumDuration;
	double			duration;
	char			*host;
}					t_ping;


t_ping	ping;


#endif
