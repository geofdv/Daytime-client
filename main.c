/*
 * Actually, it's the daytime client, not a server.
 *
 * Send a UDP datagram to the daytime server on some other host.
 * read the reply, and print the time and date on the server.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	enum { buffsize = 150 };
	struct sockaddr_in serv;
	char buff[buffsize];
	int sockfd, n;
	int numWritten;

	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socker error");
		exit(1);
	}

	bzero((char *) &serv, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(13);

	numWritten = sendto(sockfd, buff, buffsize, 0, (struct sockaddr *) &serv, sizeof(serv));
	if (numWritten != buffsize) {
		perror("sendo");
		exit(2);
	}

	n = recvfrom(sockfd, buff, buffsize, 0, (struct sockaddr *) NULL, (socklen_t *) NULL);
	if (n < 2) {
		perror("recvfrom");
		exit(2);
	}

	buff[n - 2] = 0;

	printf("%s\n", buff);

	return 0;
}
