#include "unp.h"

ssize_t readn(int fd, void* vptr, size_t n)
{
	ssize_t nread;
	size_t nleft = n;

	char* ptr = vptr;

	while(nleft > 0)
	{
		if( (nread = read(fd, ptr, nleft) < 0) )
		{
			if(errno == EINTR)
			{
				nread = 0;
			}
		}else if(nread == 0)
		{
			break;
		}

		ptr += nread;
		nleft -= nread;
	}	
}