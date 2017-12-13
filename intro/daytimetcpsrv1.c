#include "../lib/unp.h"
#include <time.h>

int main(int argc, char** argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr, connaddr;
	char buff[MAXLINE];
	time_t ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&connaddr, 0, sizeof(connaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(TESTPORT);
	servaddr.sin_addr.s_addr = inet_addr(TESTHOST);

	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for(; ;)
	{
		socklen_t len = sizeof(connaddr);

		connfd = Accept(listenfd, (SA*)&connaddr, &len);

		printf("Accept %d\n", connfd);

		Inet_ntop(AF_INET, &connaddr.sin_addr, buff, sizeof(buff) );

		int nPort = ntohs(connaddr.sin_port);

		printf("Connect from %s:%d \n", buff, nPort);

		ticks = time(NULL);

		snprintf(buff, sizeof(buff),  "%.24s\r\n", ctime(&ticks));

		printf("Write %s\n", buff);

		Write(connfd, buff, strlen(buff));

		Close(connfd);
	}
}