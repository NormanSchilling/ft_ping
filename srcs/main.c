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

void display_msg(void *buf, int bytes)
{
	struct iphdr		*ip;

	ip = buf;
	printf("IPv%d: size=%d, protocol=%d TTL=%d\n",
	ip->version, bytes, ip->protocol, ip->ttl);
}

void	ping(char *addrip)
{
	int 					val;
	int						sock;
	int						i;
	int						bytes;
	t_ping					packet;
	t_addrinfo				*info;
	t_sockaddrin			addr;
	// struct timeval			start;
	// struct timeval			end;
	unsigned char			buf[PACKETSIZE];
	// char					str[INET_ADDRSTRLEN];

	val = 255;
	packet.id = 0;
	packet.head.type = 8;
	packet.head.code = getpid();
	packet.head.checksum = checksum(&bytes, PACKETSIZE);
	addr.sin_family = AF_INET;

	if (getaddrinfo(addrip, NULL, NULL, &info) != 0)
	{
		printf("cannot provide addrinfo\n");
		exit(-1);
	}
	if ((sock = socket(PF_INET, SOCK_RAW, 1)) == -1)
	{
		printf("Error socket in ping\n");
		exit(-1);
	}
	if ( setsockopt(sock, SOL_SOCKET, IP_TTL, (void*)&val, sizeof(val)) != 0)
	{
		printf("Error setsockopt\n");
		exit (-1);
	}

	// if (inet_pton(AF_INET, addrip, &(addr.sin_addr)) == -1)
	// {
	// 	printf("Error : inet_pton\n");
	// 	exit(-1);
	// }

	// inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
	// if (str != NULL)
	// 	printf("%s\n", str);
	while(1)
	{
		i = 0;
		while ( i < 16 )
		{
			packet.msg[i] = i + '0';
			i++;
		}

		// gettimeofday(&start, NULL);
		if ( sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&addr, sizeof(addr)) <= 0 )
			perror("sendto");

		ft_bzero(buf, sizeof(buf));
		printf("ok");

		bytes = recvfrom(sock, &buf, sizeof(buf), 0, (struct sockaddr*)&info->ai_addr, &(info->ai_addrlen));
		// gettimeofday(&end, NULL);

		if ( bytes < 0 )
			perror("recvfrom");
		else
			display_msg(buf, bytes);
		packet.id++;
		sleep(1);
	}
}


int main(int argc, char **argv)
{
	signal(SIGCHLD, SIG_IGN);
	if (argc  >= 2)
	{
		ping(argv[1]);
	}
	else
		ft_usage();
	return (0);
}