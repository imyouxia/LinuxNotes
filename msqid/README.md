IPC就是进程间通信（Interprocess Communication），狭义上讲IPC特指消息队列、信号量和共享内存三种方法。

其中：

消息队列应用于不同进程之间少量数据的顺序共享。

信号量应用于进程之间的同步与互斥的控制。

共享内存则应用于进程之间大批量数据的随机共享访问。

ipcs 命令查看IPC对象信息

int msgget(key_t key, int msgflg);   //采用msgget创建消息队列

msgflg指定了消息队列的创建方式：

IPC_CREATE  创建消息队列，如果队列已经存在，就打开消息队列
IPC_EXCL  与宏IPC_CREATE 一齐使用，单独使用无意义。创建一个不存在的消息队列，如果队列已存在，函数调用失败

msgsnd(int msqid,void *msgp,int msgsz,int msgflg); //消息队列的发送

int msgrcv(int msqid,void *msgp,int msgsz,long msgtyp,int msgflg);  //从消息队列接收消息

int msgctl(int msgid,int cmd,struct msqid_ds *buf);  

对消息队列执行各种控制，包括消息队列数据结构，改变消息队列访问权限，改变消息队列属主信息和删除消息队列。




