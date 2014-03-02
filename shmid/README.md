共享内存：

共享内存中最重要的属性是内存大小和内存地址，进程在访问共享内存前必须先将共享内存映射到进程空间的一个虚拟地址中，然后任何对该虚拟地址的数据操作都将直接作用到物理内存上

共享内存的基本系统调用包括创建共享内存、映射共享内存和释放共享内存映射三种，分别由函数shmget、函数shmat和函数shmdt完成。

1.共享内存的创建

int shmget(key_t key,size_t size,int shmflg);

2.共享内存的映射，将共享内存映射到进程地址空间后才可以访问

void *shmat(int shmid,const void *shmaddr,int shmflg);

3.共享内存的释放

int shmdt(const void *shmaddr);

共享内存的控制：

int shmctl(int shmid,int cmd,struct shmid_ds *buf);

函数shmctl对标识号为shmid的共享内存完成信息获取与设置、共享内存的删除、锁定和解锁等多项操作，参数cmd指定操作的类型，参数buf为函数提供输入与输出数据。


