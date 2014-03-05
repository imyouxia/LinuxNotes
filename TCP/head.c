#include "head.h"

/*
 * #include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

*/

#define VERIFY(a,b) \
	if(a) \
	{\
		fprintf(stderr,"%s failed.\n",b); \
		return 0;\
	}\
	else fprintf(stderr,"%s success.\n",b);


int CreateSock(int *pSock,int nPort,int nMax)
{
	struct sockaddr_in addrin;
	struct sockaddr *paddr = (struct sockaddr *)&addrin;
	assert(pSock != NULL && nPort > 0 && nMax > 0);
	memset(&addrin,0,sizeof(addrin));
	
	addrin.sin_family = AF_INET;   //协议名   
	addrin.sin_addr.s_addr = htonl(INADDR_ANY);   //自动分配地址
	addrin.sin_port = htons(nPort);   //端口号
	
	//创建TCP套接字描述符
	if((*pSock = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		printf("socket error\n");
		close(*pSock);
		return -1;
	}

	if(bind(*pSock,paddr,sizeof(addrin)) < 0)
	{
		printf("bind error\n");
		close(*pSock);
		return -1;
	}

	if(listen(*pSock,nMax) < 0)   //套接字进入侦听状态
	{
		printf("listen error\n");
		close(*pSock);
		return -1;
	}

	return 0;
}

int AcceptSock(int *pSock,int nSock)
{
	struct sockaddr_in addrin;
	int lSize;
	assert(pSock != NULL && nSock > 0);
	while(1)
	{
		lSize = sizeof(addrin);
		memset(&addrin,0,sizeof(addrin));
		//阻塞接收客户端连接请求，并创建新的套接字描述符
		if((*pSock = accept(nSock,(struct sockaddr *)&addrin,&lSize)) > 0)
			return 0;
		//调用accept过程中接收到信号，调用中断
		else if(errno == EINTR) continue;
	
	}

}

int LocateRemoteAddr(int nSock,char *pAddr)
{
	struct sockaddr_in addrin;
	int lSize;
	assert(nSock > 0 && pAddr != NULL);
	memset(&addrin,0,sizeof(addrin));
	lSize = sizeof(addrin);
	//获取对方套接字协议地址信息
	assert(getpeername(nSock,(struct sockaddr*)&addrin,&lSize) > 0);
	//装换套接字地址信息为以点分割的字符串形式
	strcpy(pAddr,inet_ntoa(addrin.sin_addr));
	return 0;
}

