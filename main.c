/*
 * Send a UDP datagram to the daytime server on local host.
 * Read the reply, and print the time and date on the server.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sockaddr_in sa_in;

int
main()
{
	enum { buffsize = 256 };
	char buff[buffsize];

	struct sockaddr_in serv;
	int sockfd;
	int nsent, nreceived;

	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socker error");
		exit(1);
	}

	bzero((char *) &serv, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(13);

	nsent = sendto(sockfd, buff, buffsize, 0, (sa_in *) &serv, sizeof(serv));
	if (nsent != buffsize) {
		perror("sendo");
		exit(2);
	}

	nreceived = recvfrom(sockfd, buff, buffsize, 0, (sa_in *) NULL, (socklen_t *) NULL);
	if (nreceived < 2) {
		perror("recvfrom");
		exit(2);
	}

	buff[nreceived - 2] = 0;

	printf("%s\n", buff);

	return 0;
}
