#include "unp.h"

/**
 * @descr 转换strptr指向的表达格式地址，并通过addrptr存放二进制结果
 * @param family: 协议域
 * @param strptr: 输入地址的表达格式	
 * @param addrptr: 存放地址的数值格式
 */
void Inet_pton(int family, const char *strptr, void* addrptr)
{
	int n;

	//若成功则为1, 若输入的不是有效的表达格式地址，则返回0，若出错则返回-1
	if( (n = inet_pton(family, strptr, addrptr)) < 0)
	{
		err_sys("inet_pton error for %s\n", strptr);
	}else if(n == 0)
	{
		err_quit("inet_pton error for %s\n", strptr);
	}
}

/**
 * @descr 转换addrptr指向的数值格式地址，并通过strptr存放结果
 * @param family: 协议域
 * @param addrptr: 输入地址的数值格式
 * @param strptr: 存放地址的表达格式(不能为空指针 调用者必须为其申请空间 并指定大小)
 * @param len: strptr的大小
 * @return 若成功则返回用于存放指向结果的指针，若出错则为NULL
 */
const char* Inet_ntop(int family, const void* addrptr, char* strptr, size_t len)
{
	const char* ptr;

	if(strptr == NULL)
	{
		err_quit("NULL 3rd argement to inet_ntop");
	}

	if( (ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
	{
		err_sys("inet_ntop error");
	}
	return ptr;
}