/* 守护进程：
 * 1.后台运行，即父进程退出，子进程继续运行
 * 2.独立于控制终端，在后台进程的基础上，脱离原来shell的进程组和session期（session是一个或多个进程组的集合，每个session独占一个终端），自立门户为新进程组的会话组长进程，与原终端脱离关系。
 * pid_t setsid();  函数setsid创建一个新的session和进程组，并以调用进程的ID号来设置新成立的进程组ID
 * 3.清楚文件创建掩码(umask)
 * 4.处理信号，为了预防父进程不等带子进程结束而导致子进程僵死。
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>

void ClearChild(int nSignal)
{
	pid_t _pid_t;
	int nState;
	while((_pid_t = waitpid(-1,&nState,WNOHANG)) > 0);
	signal(SIGCLD,ClearChild);

}

int main()
{
	pid_t pid1;
	assert((pid1 = fork()) >= 0);   //创建子进程

	if(pid1 != 0)
	{
		sleep(1);
		exit(0);
	}

	assert(setsid() >= 0);   //子进程脱离终端
	umask(0);			//清除文件创建掩码

	//忽略捕捉终端CTRL+C
	signal(SIGINT,SIG_IGN);		//忽略SIGINT信号
	signal(SIGCLD,ClearChild);   //处理SIGCLD信号，预防僵死进程
	sleep(120);
	return 0;
}


