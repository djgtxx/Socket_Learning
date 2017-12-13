#include "unp.h"

void str_cli(FILE* fp, int fd)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	while(Fgets(sendline, MAXLINE, fp) != NULL)
	{
		size_t len = strlen(sendline);

		Writen(fd, sendline, len);

		if(Readline(fd, recvline, MAXLINE) == 0)
		{
			err_quit("str_cli: server terminated prematurely");
		}
		Fputs(recvline, stdout);
	}
}