#include "ft_ping.h"

void ft_usage()
{
	printf("Usage : [-h help], [-v Verbose Output], destination" );
}

unsigned short checksum(void *b, int len)
{
	unsigned short		*buf;
	unsigned int		sum;
	unsigned short		result;

	buf = b;
	sum = 0;
	for ( sum = 0; len > 1; len -= 2 )
		sum += *buf++;
	if ( len == 1 )
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

void display_msg(int bytes)
{
	printf("%d\n", bytes);
}

void manager_msg(int sock)
{
	struct sockaddr_in	addr;
	unsigned char		buf[PACKETSIZE];
	// socklen_t			len;
	int					bytes;
	t_ping				packet;
	int					i;

	ft_bzero(buf, sizeof(buf));
	packet.id = 0;
	packet.head.type = 8;
	packet.head.code = getpid();
	packet.head.checksum = checksum(&bytes, PACKETSIZE);
	addr.sin_family = AF_INET;

	i = 0;
	while ( i < 16 )
	{
		packet.msg[i] = i + '0';
		i++;
	}
	packet.msg[i] = 0;

	if ( sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&addr, sizeof(addr)) <= 0 )
		perror("sendto");

	// len = sizeof(addr);
	// bytes = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &len);
	// if ( bytes < 0 )
	// 	perror("recvfrom");
	// else
	// 	display_msg(bytes);
}

void create(char *addrip)
{
	int 					val;
	int						sock;
	struct addrinfo			*info;

	val = 255;
	if (getaddrinfo(addrip, NULL, NULL, &info) != 0)
	{
		printf("cannot provide addrinfo\n");
		exit(-1);
	}
	if ((sock = socket(PF_INET, SOCK_RAW, 1)) == -1)
	{
		printf("Error socket\n");
		exit(-1);
	}
	if ( setsockopt(sock, SOL_SOCKET, IP_TTL, (void*)&val, sizeof(val)) != 0)
	{
		printf("Error setsockopt\n");
		exit (-1);
	}
	manager_msg(sock);
}

int main(int argc, char **argv)
{
	signal(SIGCHLD, SIG_IGN);
	if (argc  >= 2)
	{
		create(argv[1]);
	}
	else
		ft_usage();
	return (0);
}