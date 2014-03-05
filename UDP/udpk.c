#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int CreateUdpSock(int *pnSock,int nPort)
{
	struct sockaddr_in addrin;
	struct sockaddr *paddr = (struct sockaddr *)&addrin;
	assert(pnSock != NULL && nPort > 0);
	memset(&addrin,0,sizeof(addrin));

	//协议地址组包
	addrin.sin_family = AF_INET;  //协议名
	addrin.sin_addr.s_addr = htonl(INADDR_ANY);   //自动分配地址
	addrin.sin_port = htons(nPort);   //端口号

	assert((*pnSock = socket(AF_INET,SOCK_DGRAM,0)) > 0);

	if(bind(*pnSock,paddr,sizeof(addrin)) >= 0)
		return 0;
	else
	{
		close(*pnSock);
		return 1;
	}	
}

int SendMsgByUdp(void *pMsg,int nSize,char *szAddr,int nPort)
{
	int nSock;
	struct sockaddr_in addrin;
	
	//创建UDP套接字描述符
	assert((nSock = socket(AF_INET,SOCK_DGRAM,0)) > 0);
	memset(&addrin,0,sizeof(struct sockaddr));
	
	//接收发的地址协议地址组包
	addrin.sin_family = AF_INET;   //协议名
	addrin.sin_addr.s_addr = inet_addr(szAddr);   //接收方的地址
	addrin.sin_port = htons(nPort);   //接收方的服务端口号

	assert(sendto(nSock,pMsg,nSize,0,(struct sockaddr *)&addrin,sizeof(addrin)));
	close(nSock);
	return 0;
}

int RecvMsgByUdp(int nFile,void *pData,int *pnSize)
{
	int nSize;
	//接收数据，并不关心发送方协议地址
	assert((*pnSize = recvfrom(nFile,pData,*pnSize,0,NULL,NULL)) > 0);
	return 0;
}	

int main()
{
	int ret,i = 0;
	char szBuf[100];
	while(1)
	{
		sprintf(szBuf,"第%d次发送",i);
		ret = SendMsgByUdp(szBuf,strlen(szBuf),"127.0.0.1",9999);  //发送
		if(ret == 0)
			printf("Send UDP Success:%s\n",szBuf);
		else
			printf("Send UDP Failed:%s\n",szBuf);
		sleep(1);
		i++;   //i代表发送的次数
	}

}

