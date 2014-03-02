/* 读共享内存 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>

#define VERIFYERR(a,b) \
	if(a) \
	{\
		fprintf(stderr,"%s failed.\n",b); \
		return 0; \
	}\
	else \
		fprintf(stderr,"%s success.\n",b);

int main()
{
	int shmid,no;
	char *pmat = NULL,buf[1024];
	
	//打开共享内存
	VERIFYERR((shmid = shmget(0x1234,10*1024,0666|IPC_CREAT)) == -1,"Open(Create) Shm");
	//映射共享内存，地址存储在pmat处
	VERIFYERR((pmat = (char *)shmat(shmid,0,0)) == 0, "Link Shm");
	//输入读取的内存块号
	printf("Please Input No.(0-9):");
	scanf("%d",&no);
	VERIFYERR(no < 0 || no > 9, "Input No.");
	//读取共享内存的数据
	memcpy(buf,pmat+no*1024,1024);
	printf("Data:[%s]\n",buf);
	//释放共享内存映射
	shmdt(pmat);
	return 0;
}


