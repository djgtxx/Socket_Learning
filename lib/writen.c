#include "unp.h"

ssize_t writen(int fd, const void* vptr, size_t n)
{
	size_t nleft = n;
	ssize_t nwrite;

	const char* ptr = vptr;

	while(nleft > 0)
	{
		if( (nwrite = write(fd, ptr, nleft)) <= 0 )
		{
			if(nwrite < 0 && errno == EINTR)
			{
				nwrite = 0;
			}else
			{
				return -1;
			}
		}

		ptr += nwrite;
		nleft -= nwrite;
	}
	return n;
}

void Writen(int fd, void *ptr, size_t nbytes)
{
	if (writen(fd, ptr, nbytes) != nbytes)
		err_sys("writen error");
}