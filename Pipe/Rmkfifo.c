/* 有名管道FIFO：
 * /etc/mknod name p    创建管道文件
 * /etc/mknod name s    创建信号量
 * /etc/mknod name m    创建共享内存
 * 
 * 函数mkfifo创建管道：
 * int mkfifo(char *path,mode_t mode);
 * mkfifo -m 644 k2
 *
 */

//写有名管道

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <string.h>

extern int errno;

int main()
{
	FILE *fp;
	char buf[255];

	//创建管道，如果已存在则跳过
	if(mkfifo("myfifo",S_IFIFO|0666) < 0 && errno != EEXIST) return 0;

	while(1)
	{
		if((fp = fopen("myfifo","w")) == NULL) return 0;//打开管道
		printf("please input:");
		gets(buf);
		fputs(buf,fp);
		fputs("\n",fp);
		if(strncmp(buf,"quit",4) == 0 || strncmp(buf,"exit",4) == 0) break;
		fclose(fp);
	}
	return 0;
}

