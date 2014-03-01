/* int pipe(int fides[2])
 * 父进程向管道写入一行字符，子进程读取数据并打印到屏幕上
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fildes[2];
	pid_t pid;
	int i,j;
	char buf[256];
	if(pipe(fildes) < 0)   //创建管道
	{
		fprintf(stderr,"pipe error!\n");
		return 0;
	}

	if((pid = fork()) < 0)   //创建子进程
	{
		fprintf(stderr,"fork error!\n");
		return 0;
	}

	if(pid == 0)   //子进程
	{
		close(fildes[1]);   //子进程关闭管道输入
		memset(buf,0,sizeof(buf));
		j = read(fildes[0],buf,sizeof(buf));  //读管道
		
		fprintf(stderr,"[child] buf=[%s] len [%d]\n",buf,j);
		return 0;
	}

	close(fildes[0]);   //父进程 关闭管道输入
	write(fildes[1],"hello!",strlen("hello!"));  //写管道
	write(fildes[1],"world!",strlen("world!"));  //写管道
	return 0;
}

