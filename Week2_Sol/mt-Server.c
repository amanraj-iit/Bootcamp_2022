/* run using ./server <port> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>

#include <pthread.h>

#define MAX_CONN 10

void error(char *msg)
{
	perror(msg);
	exit(1);
}

void *pthread_fn(void *newsock)
{

	char buffer[256];
	int n;
	int newsockfd;
	newsockfd = *(int *)newsock;

	while (1)
	{

		/* read message from client */
		bzero(buffer, 256);
		n = read(newsockfd, buffer, 255);

		if (n < 0)
		{
			error("ERROR reading from socket");
			exit(1);
		}

		printf("Here is the message: %s", buffer);

		/* send reply to client */

		n = write(newsockfd, buffer, strlen(buffer));
		printf("write return code:%d\n", n);
		if (n < 0)
			error("ERROR writing to socket");
		if (n == 0)
		{
			printf("CONNECTION BROKEN for socket:%d\n", newsockfd);
			close(newsockfd);
			return 0;
		}
	}
	return (void *)0;
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int i = 0;
	pthread_t pth_h[MAX_CONN];

	if (argc < 2)
	{
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}

	/* create socket */

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");

	/* fill in port number to listen on. IP address can be anything (INADDR_ANY)
	 */

	bzero((char *)&serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/* bind socket to this port number on this machine */

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");

	/* listen for incoming connection requests */

	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	/* accept a new request, create a newsockfd */

	while (1)
	{
		if (i < 10)
		{
			i++;
			newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
			if (newsockfd < 0)
				error("ERROR on accept");

			pthread_create(&pth_h[i], NULL, pthread_fn, &newsockfd);
		}
	}

	return 0;
}
