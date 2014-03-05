#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

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


int main()
{
	int nSock,nSock1;
	char buf[2048];
	//创建端口号为9001的侦听套接字
	VERIFY(CreateSock(&nSock,9001,9) != 0, "Create Listen SOCKET");
	//接收客户端连接申请，创建连接套接字nSock1
	VERIFY(AcceptSock(&nSock1,nSock) != 0,"Link");

	memset(buf,0,sizeof(buf));

	//接收客户端发送的TCP数据消息
	recv(nSock1,buf,sizeof(buf),0);
	fprintf(stderr,buf);
	close(nSock);   //关闭侦听套接字
	close(nSock1);  //关闭连接套接字
	return 0;
}


