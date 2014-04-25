/* 利用select和阻塞（Blocking）Socket实现数据转发 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

int main()
{
	if(argc < 5)
	{
		printf("Usage:%s local_ip local_port remote_ip remote_port.\n",argv[0]);

	}	
	
	char* local_ip = argv[1];
	int local_port = atoi(argv[2]);
	char* remote_ip = argv[3];
	int remote_port = atoi(argv[4]);

	struct sockaddr_in l_addr;
	bzero(&l_addr,sizeof(l_addr));
	l_addr.sin_family = AF_INET;
	l_addr.sin_port = htons(local_port);
	//inet_pton(AF_INET,local_ip,&addr.sin_addr);  //点分十进制-->整数，可以处理ipv6
	l_addr.sin_addr.s_addr = inet_addr(local_ip); //将网络地址转成二进制的数字
	
	struct sockaddr_in r_addr;
   	bzero(&r_addr,sizeof(r_addr));
	r_addr.sin_family = AF_INET;
	r_addr.sin_port = htons(remote_port);
	r_addr.sin_addr.s_addr = inet_addr(remote_ip);


	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("create socket error\n");
		exit(1);
	}

	if(bind(sockfd,&l_addr,sizeof(l_addr)) < 0)
	{
		close(sockfd);
		perror("bind error!\n");
		exit(1);
	}

	if(listen(sockfd,3) < 0)
	{
		close(sockfd);
		perror("listen error\n");
		exit(1);
	}

	printf("The Server is listening!\n");

	fd_set readfds,writefds;
	char buf[4096];
	FD_ZERO(&sockfd);	
	while(1)
	{
		
	}
}

