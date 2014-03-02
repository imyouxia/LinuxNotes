/*
 * FILE *popen(const char *command,char *type) 
 * popen 参数type取值情况表：
 * r：创建与子进程的标准输出连接的管道（管道数据由子进程流向父进程）
 * w：创建与子进程的标准输入连接的管道（管道数据由父进程流向子进程）
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *out,*in;
	char buf[255];

	if((out = popen("grep init","w")) == NULL)  //创建写管道流
	{
		fprintf(stderr,"error!\n");
		return 0;
	}

	if((in = popen("ps -ef","r")) == NULL)  //创建读管道流
	{
		fprintf(stderr,"error!\n");
		return 0;
	}

	while(fgets(buf,sizeof(buf),in))  //读取ps -ef 结果
		fputs(buf,out);   //转发到grep init

	pclose(out);
	pclose(in);
	return 0;
}

