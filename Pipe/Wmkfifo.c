/* 读有名管道i，与Rmkfifo一起使用
 * 无名管道只能在共同血缘进程中使用，有名管道，可以在整个系统中使用
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	FILE *fp;
	char buf[255];
	while(1)
	{
		if((fp = fopen("myfifo","r")) == NULL) return 0;
		fgets(buf,sizeof(buf),fp);
		printf("gets:[%s]",buf);
		if(strncmp(buf,"quit",4) == 0 || strncmp(buf,"exit",4) == 0)  break;
		fclose(fp);
	}

	return 0;
}

