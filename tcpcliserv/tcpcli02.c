#include "../lib/unp.h"

int main(int argc, char **argv)
{
	int socketfd;

	struct sockaddr_in servaddr;

	memset(&servaddr, 0, sizeof(servaddr));

	socketfd = Socket(AF_INET, SOCK_STREAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(TESTPORT);
	// servaddr.sin_addr.s_addr = inet_addr(TESTHOST);
	Inet_pton(AF_INET, TESTHOST, &servaddr.sin_addr.s_addr);

	Connect(socketfd, (SA*)&servaddr, sizeof(servaddr));

	str_cli(stdin, socketfd);

	exit(0);
}