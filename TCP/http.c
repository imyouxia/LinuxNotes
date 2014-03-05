#include "head.h"

//char html1[] = "<html>\n<head>\n<title>HTTP</title>\n</head>\n<body>\n<b>Hello World.</b><br><b>你的IP是";
//char html2[] = "\n<b>\n</body>\n</html>\n";

int main()
{
	int nSock,nSock1;
	pid_t nChild;
	char buf[2048],szAddr[30];
	memset(buf,0,sizeof(buf));
	assert(CreateSock(&nSock,9001,9) == 0);   //创建端口号9001的侦听套接字
	
	while(1)
	{
		assert(AcceptSock(&nSock1,nSock) == 0);   //创建连接套接字
		nChild = fork();  //创建子进程
		if(nChild == 0)
		{
			break;
		}
		close(nSock1);   //父进程关闭连接套接字
	}

	//子进程
	close(nSock);   //子进程关闭侦听套接字
	memset(szAddr,0,sizeof(szAddr));   
	//LocateRemoteAddr(nSock1,szAddr);  //获取远程IP地址
	recv(nSock1,buf,sizeof(buf),0);   //获取HTTP协议报文
	fprintf(stderr,buf);

	//组建应答包
//	sprintf(buf,"HTTP/1.1 200 OK\n%s%s\n",html1,html2);
	send(nSock1,buf,strlen(buf),0);    //发送HTTP应答报文
	fprintf(stderr,buf);
	close(nSock1);   //中断套接字连接
	return 0;
}


