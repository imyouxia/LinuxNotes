/*
 * void (*signal (int sig,void(*f)(int))) (int);
 *
 * typedef void (*func)(int);
 * func signal(int sig,func f);
 *
 * 函数signal参数f取值：
 * SIG_DFL   恢复信号默认处理机制
 * SIG_IGN	 忽略信号处理
 * 函数地址  调用信号捕获函数执行处理
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int usr1 = 0,usr2 = 0;

void func(int);

int main()
{
	signal(SIGUSR1,func);
	signal(SIGUSR2,func);
	for(;;) sleep(1);
	
}

void func(int sig)
{
	//SIGUSR1 SIGUSR2 为预留信号，终止进程
	if(sig == SIGUSR1) usr1++;
	if(sig == SIGUSR2) usr2++;
	
	fprintf(stderr,"SIGUSR1[%d];SIGUSR2[%d]\n",usr1,usr2);
	signal(SIGUSR1,func);
	signal(SIGUSR2,func);

}

