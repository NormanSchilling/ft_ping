#include "ft_ping.h"

void sighandler(int);

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

void			display(void *buff, int count, double duration)
{
	struct iphdr	*ip = buff;
	char src[INET_ADDRSTRLEN];
	char dest[INET_ADDRSTRLEN];

	inet_ntop( AF_INET, (void *)&ip->saddr, src, sizeof(src) );
	inet_ntop( AF_INET, (void *)&ip->daddr, dest, sizeof(dest) );

	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%lf ms\n",
		ntohs(ip->tot_len) - (ip->ihl * 4),
		src,
		count,
		ip->ttl,
		duration
	);
}

void	ft_ping()
{
	int 					val;
	size_t					i;
	int						bytes;
	socklen_t				len;
	char					dest[INET_ADDRSTRLEN];

	ping.min = -1;
	ping.max = 0;
	val = 64;
	ft_bzero(&(ping.dest), sizeof(ping.dest));
	if (getaddrinfo(ping.host, NULL, NULL, &(ping.info)) != 0)
	{
		printf("cannot provide addrinfo\n");
		exit(-1);
	}
	if ((ping.sock = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
	{
		printf("Error socket in ping\n");
		exit(-1);
	}
	if ( setsockopt(ping.sock, SOL_IP, IP_TTL, (void*)&val, sizeof(val)) != 0)
	{
		printf("Error setsockopt\n");
		exit (-1);
	}
	ping.dest.sin_family = ping.info->ai_family;
	ping.dest.sin_port = 0;
	ping.dest.sin_addr.s_addr = ((struct sockaddr_in *)ping.info->ai_addr)->sin_addr.s_addr;

	ping.count = 1;
	inet_ntop( AF_INET, (void *)&(ping.dest.sin_addr), dest, sizeof(dest) );
	printf("PING %s (%s) %d bytes of data\n", ping.host, dest, PACKETSIZE);

	while (1)
	{
		ft_bzero(&(ping.packet), sizeof(ping.packet));
		ping.packet.hdr.type = ICMP_ECHO;
		ping.packet.hdr.un.echo.id = getpid();
		i = 0;
		while (i < sizeof(ping.packet.msg) - 1)
		{
			ping.packet.msg[i] = i+'0';
			i++;
		}
		ping.packet.msg[i] = 0;
		ping.packet.hdr.un.echo.sequence = ping.count;
		ping.packet.hdr.checksum = checksum(&(ping.packet), PACKETSIZE);

		gettimeofday(&(ping.start), NULL);
		if ( sendto(ping.sock, &(ping.packet), sizeof(ping.packet), 0, (struct sockaddr*)&(ping.dest), sizeof(ping.dest)) <= 0 )
			perror("sendto");

		len = sizeof(ping.src);
		bytes = recvfrom(ping.sock, &(ping.packet), sizeof(ping.packet), 0, (struct sockaddr*)&(ping.src), &len);
		gettimeofday(&(ping.end), NULL);
		ping.duration = ((ping.end.tv_sec * 1000) + (ping.end.tv_usec / 1000.0)) - ((ping.start.tv_sec * 1000) + (ping.start.tv_usec / 1000.0));
		if (ping.duration < ping.min || ping.min == -1)
			ping.min = ping.duration;
		if (ping.duration > ping.max)
			ping.max = ping.duration;
		ping.sumDuration = ping.sumDuration + ping.duration;
		ping.avg = ping.sumDuration / ping.count;
		if ( bytes < 0 )
			perror("recvfrom");
		else
			display(&(ping.packet), ping.count, ping.duration);
		ping.count++;
		sleep(1);
	}
}

void sighandler(int num)
{
	(void)num;
	printf("\n--- %s ping statistics ---\n", ping.host);
	printf("%d packets transmitted, %d received, %d packet loss,\nround-trip min/avg/max = %lf/%lf/%lf",
		ping.count - 1, ping.count - 1, 0, ping.min, ping.avg, ping.max);

	exit(1);
}

int main(int argc, char **argv)
{
	signal(SIGINT, sighandler);
	if (argc  >= 2)
	{
		ping.host = argv[1];
		ft_ping();
	}
	else
		ft_usage();
	return (0);
}