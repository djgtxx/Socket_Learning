#ifndef _unp_h__
#define _unp_h__

#include	<sys/socket.h>	/* basic socket definitions */
#include	<errno.h>
#include	<sys/types.h>	/* basic system data types */
#include	<stdio.h>
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */

#define	TESTHOST	"127.0.0.1"	/* test host */
#define	TESTPORT	9999	/* test port */
#define	MAXLINE		4096	/* max text line length */
#define	LISTENQ		1024	/* 2nd argument to listen() */

#define	SA struct sockaddr

void 		str_echo(int sockfd);
void 		str_cli(FILE* fp, int fd);

void	 	err_quit(const char *, ...);
int		 	Socket(int, int, int);

void 		Bind(int fd, struct sockaddr* sa, socklen_t salen);
void	 	Listen(int, int);
int		 	Accept(int, SA *, socklen_t *);
void	 	Writen(int, void *, size_t);
void	 	Close(int);
void 		Inet_pton(int family, const char *strptr, void* addrptr);
const char* Inet_ntop(int family, const void *addrptr, char* strptr, size_t len);
char*		Fgets(char *, int, FILE *);



// ssize_t	readn(int fd, void *vptr, size_t n);

// ssize_t writen(int fd, const void *vptr, size_t n);

// ssize_t readline(int fd, void *vptr, size_t maxline);

// ssize_t	Readn(int fd, void *ptr, size_t nbytes);

#endif
