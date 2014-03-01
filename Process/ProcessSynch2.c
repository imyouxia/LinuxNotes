/* pid_t waitpid(pid_t pid,int *status,int options)
 * pid > 0  等待进程标识号为pid的子进程结束
 * pid = 0  等待进程组标识等于父进程进程组标识的子进程结束
 * pid = -1 等待任意子进程结束
 * pid < -1 等待进程组表示等于pid的绝对值的子进程结束
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid1;
	if((pid1 = fork()) == 0)  //第一次fork
	{
		printf("child[%d]\n",getpid());
		if((pid1 = fork()) == 0) //第二次fork
		{
			printf("child[%d]\n",getpid());
			sleep(20);
			exit(0);   //第二次创建的子进程退出
		}
		exit(0);	 //第一次创建的子进程退出
	}
	
	waitpid(pid1,0,0);
	printf("parent[%d]\n",getpid());
	sleep(60);
	return 0;
}

