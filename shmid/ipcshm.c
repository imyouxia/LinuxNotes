/* 设计一个类似于命令ipcs和命令ipcrm的程序ipcshm，它从命令行参数中获取要执行的操作，包括创建共享内存、读取共享内存信息和删除共享内存 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <string.h>

#define VERIFYERR(a,b) \
	if(a) fprintf(stderr,"%s failed.\n",b);  \
	else fprintf(stderr,"%s success.\n",b);

int StatShm(int shmid)
{
	char resp[20];
	struct shmid_ds buf;
	memset(&buf,0,sizeof(buf));    //置空消息队列数据缓冲区
	shmctl(shmid,IPC_STAT,&buf);

	//转化共享内存结构并打印
	fprintf(stderr,"T    ID    KEY    MODE    OWNER    GROUP    NATTCH    SEGSZ    CPID    LPID\n");
	fprintf(stderr,"m %6d %10s %10d  %10d %10d %10d %10d\n",shmid,//标识号
							//buf.shm_perm.key, //关键字
							buf.shm_perm.mode,  //访问权限
							buf.shm_perm.uid,   //有限用户ID
							buf.shm_perm.gid,   //有限组ID
							//buf.shm_natch,     //共享内存链接数
							buf.shm_segsz,		//共享内存字节数
							buf.shm_cpid,   //创建共享内存的用户的ID数
							buf.shm_lpid		//最近一次操作共享内存的用户ID
			);	
}

int main(int argc,char *argv[])
{
	int shmid,size;
	if(argc != 3) return 0;

	shmid = atoi(argv[1]);

	if(strcmp(argv[2],"v") == 0)  //查询共享内存
	{
		StatShm(shmid);
	}

	else if(strcmp(argv[2],"d") == 0)  //删除共享内存
	{
		VERIFYERR(shmctl(shmid,IPC_RMID,NULL) < 0, "Delete Shm");
	}

	else  //创建共享内存
	{
		size = atoi(argv[2]);
		VERIFYERR(shmget(shmid,size,0666|IPC_CREAT|IPC_EXCL) < 0,"Create Shm");
	}
	
	return 0;
}

