/*
 * int semop(int semid,struct sembuf *sops,unsigned nsops);
 *
 * 结构sembuf成员sem_op含义：
 *
 * 正整数（>0）    V操作，信号量数值增加sem_op
 * 0			   Z操作，判断信号量数值是否等于0
 * 负整（<0）      P操作，信号量数值增加sem_op，由于sem_op此时为负，故操作等价于信号量数值减去|sem_op|
 *
 * 例1：以阻塞方式对标识号为semid的信号量集合中序号为3的信号量执行P操作。
 * 答：
 * //准备信号量操作结构sembuf
 * struct sembuf sb;
 * sb.sem_op = 3;    //信号量序号
 * sb.sem_op = -1;   //信号量值减1
 * sb.sem_flg = sb.sem & ~IPC_NOWAIT;   //阻塞操作
 *
 * //调用函数semop执行P操作
 * semop(nSid,&sb,1);
 *
 * 例2：以阻塞方式对标识号为semid的信号量集合中序号为0的信号量执行V操作
 * 答：
 * //准备信号量操作结构sembuf
 * struct sembuf sb;
 * sb.sem_num = 0;      //信号量序号
 * sb.sem_op = 1;       //信号量值加1
 * sb.sem_flg = sb.sem_flg & ~IPC_NOWAIT;    //阻塞操作
 * //调用函数semop执行V操作
 * semop(nSid,&sb,1)
 */


