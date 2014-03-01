/* int kill(pid_t pid,int signo);
 * int raise(int signo);
 * 函数kill参数pid取值：
 * >0  发送信号signo到进程pid中
 * 0   发送信号signo到与调用进程同组进程中
 * -1  发送信号signo到实际用户id等于调用进程的有效用户id的进程中
 * <-1 发送信号signo到进程组id等于pid绝对值的进程中
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void childfunc(int sig)   //子进程捕获信号函数
{
	fprintf(stderr,"Get Sig\n");
	exit(6);
}

int main()
{
	pid_t pid;
	int status;

	if((pid = fork()) < 0) 
		exit(1);
	else if( pid == 0) //子进程
	{
		signal(SIGTERM,childfunc);   //捕获信号SIGTERM
		sleep(30);
		exit(0);
	}

	fprintf(stderr,"Parent [%d] Fork child pid = [%d]\n",getpid(),pid);
	sleep(1);
	kill(pid,SIGTERM);   //向子进程发送SIGTERM信号
	wait(&status);    //等待子进程结束
	fprintf(stderr,"Kill child pid=[%d],exit status[%d]\n",pid,status>>8);
	return 0;
}

