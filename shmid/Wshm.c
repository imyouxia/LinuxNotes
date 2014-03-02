/* 写共享内存:
 * 向共享内存中指定位置写入数据
 */

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
	VERIFYERR((pmat = (char *)shmat(shmid,0,0)) == 0,"Link Shm");

	//输入更新的内存块号
	printf("Please Input No.(0-9):");
	scanf("%d",&no);

	VERIFYERR(no < 0 || no > 9,"Input No.");
	//输入更新的数据
	printf("Please Input Data:");
	memset(buf,0,sizeof(buf));
	scanf("%s",buf);

	//更新共享内存数据
	memcpy(pmat+no*1024,buf,1024);

	//释放共享内存
	shmdt(pmat);
	return 0;
}


