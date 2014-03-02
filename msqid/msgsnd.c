/* 设计一个消息发送的例子，它循环读取键盘输入，并将输入的字符串信息写入到消息队列（关键字0x1234）中 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/errno.h>
#include <string.h>
#include <unistd.h>

extern int errno;

struct mymsgbuf  //定义消息结构
{
	long mtype;	//消息类型
	char ctext[100];   //消息数据
};

int main()
{
	struct mymsgbuf buf;   //申请消息缓冲
	int msgid;
	
	//打开（或创建）消息队列
	if((msgid = msgget(0x1234,0666|IPC_CREAT)) < 0)
	{
		fprintf(stderr,"open msg %X failed.\n",0x1234);
		return 0;
	}

	while(strncmp(buf.ctext,"exit",4))
	{
		memset(&buf,0,sizeof(buf));
		//从键盘输入消息数据内容
		fgets(buf.ctext,sizeof(buf.ctext),stdin);
		//设置消息类型为进程ID
		buf.mtype = getpid();
		//发送消息
		while((msgsnd(msgid,&buf,strlen(buf.ctext),0)) < 0)
		{
			if(errno == EINTR) continue;   //信号中断，重新发送
			return 0;
		}
	}

	return 0;
}

