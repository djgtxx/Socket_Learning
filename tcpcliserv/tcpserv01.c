#include "../lib/unp.h"

int main(int argc, char** argv)
{
	int listenfd, connfd;

	socklen_t clilen;

	struct sockaddr_in servaddr, cliaddr;

	memset(&servaddr, 0, sizeof(servaddr));

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(TESTPORT);
	servaddr.sin_addr.s_addr = inet_addr(TESTHOST);

	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for( ; ; )
	{
		clilen = sizeof(cliaddr);

		connfd = Accept(listenfd, (SA*)&servaddr, &clilen);

		printf("Accept %d\n", connfd);

		pid_t pid;

		if( (pid = Fork()) == 0)
		{
			Close(listenfd);
			str_echo(connfd);
			Close(connfd);
			exit(0);
		}
		Close(connfd);
	}
}