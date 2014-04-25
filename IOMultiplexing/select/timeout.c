/* select多路复用方式超时处理：
 * 函数select将返回文件描述符集合中已准备好的文件总个数，
 * 如果在任意文件描述符准备好之前，定时到达，函数返回0；如果出错，返回-1。
 * 函数select返回就绪文件描述符数量后，必需执行read等输入函数，否则函数将继续返回就绪文件数。
 */

#include <stdio.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/select.h>
#include <unistd.h>

int main()
{
	struct timeval timeout;
	fd_set readfds;
	int i;
	char c;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;

	FD_ZERO(&readfds);
	FD_SET(0,&readfds);     //监控文件0

	i = select(1,&readfds,NULL,NULL,&timeout); 

	if(i > 0)   //文件0就绪
	{
		read(0,&c,1);
		printf("%d\n",c);
	}
	else
	{
		if(i == 0)
		{
			printf("timeout\n");   //超时处理
		}
		else
		{
			printf("error\n");
		}
	
	}
	return 0;
}

