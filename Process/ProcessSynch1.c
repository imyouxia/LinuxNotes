/* pid_t wait(int * status)
 * 函数wait挂起调用它的进程，直到它的任一子进程退出或者收到一个不能忽略的信号为止，如果在父进程执行wait调用前就已经有子进程退出，则立即返回。函数成功调用后返回结束子进程的ID，否则返回-1
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t i,j;
	int status;
	if((i = fork()) == 0)  //子进程
	{	
		fprintf(stderr,"child begin. pid=[%d]\n",getpid());
		sleep(30);
		fprintf(stderr,"child end .pid=[%d]\n",getpid());
		exit(10);
	}

	j = wait(&status);
	fprintf(stderr,"child pid=[%d],exit pid[%d],status[%d]\n",i,j,status);
	return 0;
}

