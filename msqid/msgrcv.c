/* 以阻塞方式不断地从消息队列（关键字0x1234）中读取消息 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/errno.h>
#include <string.h>

struct mymsgbuf   //定义消息结构
{
	long mtype;   //消息类型
	char ctext[100];   //消息数据
};


int main()
{
	struct mymsgbuf buf;   //申请消息缓冲
	int msgid;
	int ret;

	//打开（或创建）消息队列
	if((msgid = msgget(0x1234,0666|IPC_CREAT)) < 0) 
	{
		fprintf(stderr,"open msg %X failed.\n",0x1234);
		return 0;
	}

	while(strncmp(buf.ctext,"exit",4))
	{
		//置空消息缓冲区
		memset(&buf,0,sizeof(buf));
		//接收消息
		while((ret = msgrcv(msgid,&buf,sizeof(buf.ctext),0,0)) < 0)
		{
			if(errno == EINTR) continue;  //信号中断，重新接收
			return 0;
		}
		fprintf(stderr,"Msg:Type=%d,Len=%d,Text:%s",buf.mtype,ret,buf.ctext);
	}
	return 0;
}


