#include "unp.h"

void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	pid = wait(&stat);

	printf("Child %d terminated \n", pid);

	return;
}