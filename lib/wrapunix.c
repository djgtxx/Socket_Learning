#include "unp.h"

void Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}


// void Write(int fd, void *ptr, size_t nbytes)
// {
// 	if (write(fd, ptr, nbytes) != nbytes)
// 		err_sys("write error");
// }

/**
 * [Fork description] 函数共返回两次，一次是在调用进程中(称为父进程)返回，返回值是新派生进程(称为子进程)的进程ID号
 * 在子进程中又返回一次，返回值为0，因此，返回值本身告知进程是子进程还是父进程
 * @return  [description]
 */
pid_t Fork(void)
{
	pid_t	pid;

	//在子进程中为0，在父进程中为子进程id，出错则为-1
	if ( (pid = fork()) == -1)
		err_sys("fork error");
	return(pid);
}