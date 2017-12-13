#include "../lib/unp.h"
#include <time.h>

int main(int argc, char** argv)
{
	int listenfd, connfd;

	struct sockaddr_in servaddr;

	char buff[MAXLINE];

	time_t ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(TESTHOST);
	servaddr.sin_port = htons(TESTPORT);

	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for( ; ; )
	{
		connfd = Accept(listenfd, (SA*)NULL, NULL);
		
		printf("Accept %d\n", connfd);

		ticks = time(NULL);

		snprintf(buff, sizeof(buff),  "%.24s\r\n", ctime(&ticks));

		printf("Write %s\n", buff);

		Write(connfd, buff, strlen(buff));

		Close(connfd);
	} 
}