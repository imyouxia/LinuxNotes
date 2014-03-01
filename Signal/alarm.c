/* 由于在部分UNIX版本中，信号的捕获只响应一次，故函数中需要增加信号捕获设置。
 * 同理，函数alarm设置的定时器也只能定时一次，故函数中需要重新定时。
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int n = 0;

void timefunc(int sig)   //定时事件代码
{
	fprintf(stderr,"Alarm %d\n",n++);
	signal(SIGALRM,timefunc);   //捕获定时信号
	alarm(1);   //定时开始
}

int main()
{
	signal(SIGALRM,timefunc);   //捕获定时信号
	alarm(1);   //定时开始
	while(1);
}


