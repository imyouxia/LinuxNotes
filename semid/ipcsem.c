/* 本处设计一个类似于命令"ipcs"和命令"ipcrm"的程序ipcsem，它从命令行参数中获取要执行的操作，包括创建信号量、读取信号量信息、读取信号量取值和删除信号量等等。
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define VERIFYERR(a,b) \
	if(a) fprintf(stderr,"%s failed.\n",b);\
	else fprintf(stderr,"%s success.\n",b);

int main(int argc,char *argv[])
{
	int semid,index,i;
	unsigned short array[100];
	struct semid_ds ds;  //管理信号量
	
	if(argc != 4)
		return 0;

	semid = atoi(argv[1]);
	index = atoi(argv[2]);  //index指定了信号量中信号量的个数

	if(argv[3][0] == 'c')   //创建信号量
	{
		VERIFYERR(semget(semid,index,0666|IPC_CREAT|IPC_EXCL) < 0,"Create sem");
	}

	else if (argv[3][0] == 'd')   //删除消息队列
	{
		VERIFYERR(semctl(semid,0,IPC_RMID,NULL) < 0,"Delete sem");
	}
	
	else if (argv[3][0] == 'v')  //查询信号量消息
	{
		fprintf(stderr,"T    ID    INDEX    SEMVAL    SEMPID   SEMNCNT    SEMZCNT\n");
		fprintf(stderr,"s %6d %6d %10d %10d %10d %10d\n",
						semid,   						//标识号
						index,   						//信号量序号
						semctl(semid,index,GETVAL),     //信号量值
						semctl(semid,index,GETPID),		//最近访问进程ID
						semctl(semid,index,GETNCNT),	//P阻塞进程数
						semctl(semid,index,GETZCNT)     //Z阻塞进程数
						);
	}

	else if (argv[3][0] == 'a')   //查询全体信号量取值
	{
		ds.sem_nsems = 0;
		VERIFYERR(semctl(semid,0,IPC_STAT,&ds) != 0,"Get Sem Stat");
		VERIFYERR(semctl(semid,0,GETALL,array) != 0,"Get Sem All");

		for(i=0; i < ds.sem_nsems; i++)
		{
			fprintf(stderr,"Sem no [%d][%d]\n",i,array[i]);
		}
	}

	else
	{
		VERIFYERR(semctl(semid,index,SETVAL,atoi(argv[3])) != 0,"set Sem Val");
	}

	return 0;
}

	
