#include "unp.h"

/**
 * @param family 协议域
 * @param type 套接字类型
 * @param protocol 某个协议类型常值 0为指定family和type的系统默认值
 */
int Socket(int family, int type, int protocol)
{
	int n;

	//若成功则返回非负描述符，若出错则为-1
	if( (n = socket(family, type, protocol) ) < 0 )
	{
		err_sys("socket error");
	}

	return n;
}


/**
 * @description 状态转换 CLOSED->SYS_SEND 若成功则->ESTABLISHED,若失败则必须关闭该套接字，不能对其再次调用connect函数
 */
void Connect(int fd, const struct sockaddr* sa, socklen_t salen)
{
	//若成功则为0，若出错则为-1
	if(connect(fd, sa, salen) < 0)
	{
		err_sys("connect error");
	}
}

void Bind(int fd, struct sockaddr* sa, socklen_t salen)
{
	//若成功则为0，若出错则为-1
	if(bind(fd, sa, salen) < 0)
	{
		err_sys("bind error");
	}
}

/**
 * @description 把一个未连接的套接字转换成被动套接字，指示内核应接受指向该套接字的请求	状态转换：CLOSED->LISTEN
 * @param fd 由socket()函数返回的套接字描述符
 * @param backlog 未完成连接队列和已完成连接队列之和
 */
void Listen(int fd, int backlog)
{
	char	*ptr;

		/*4can override 2nd argument with environment variable */
	if ( (ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	//若成功则返回0 若出错则为-1
	if (listen(fd, backlog) < 0)
		err_sys("listen error");
}

/**
 * @description 由服务器调用 用于从已完成连接队列的对头返回一个已完成连接 ，如果已完成队列为空，则进程进入睡眠 （假定套接字为默认的阻塞模式）
 * @param fd 监听套接字 由socket()函数返回的套接字描述符
 * @param sa : 用来返回已连接的对端进程（客户）的协议地址
 * @param salenptr : 由内核存放在该套接字地址结构内的确切字节数
 * @return 已连接套接字 若成则由内核生成的一个全新的描述符（非负值），代表与所返回客户的tcp连接，若出错则返回-1
 */
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int		n;

again:
	if ( (n = accept(fd, sa, salenptr)) < 0) {
#ifdef	EPROTO
		if (errno == EPROTO || errno == ECONNABORTED)
#else
		if (errno == ECONNABORTED)
#endif
			goto again;
		else
			err_sys("accept error");
	}
	return(n);
}
