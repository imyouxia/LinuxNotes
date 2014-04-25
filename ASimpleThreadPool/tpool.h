#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>

//要执行的任务链表
typedef struct tpool_work
{
	void *(*routine)(void *);   //任务函数
  	void *arg;   	//传入任务函数的参数
	struct tpool_work *next;	
}tpool_work_t;

typedef struct tpool
{
	int shutdown;
	int max_thr_num;
	pthread_t *thr_id;
	tpool_work_t *queue_head;
	pthread_mutex_t queue_lock;
	pthread_cond_t queue_ready;

}tpool_t;

//创建线程池，max_thr_num 最大线程数
int tpool_create(int max_thr_num);

//销毁线程池
void tpool_destroy();

//向线程池中添加任务 ，routine任务函数指针，arg任务函数参数
int tpool_add_work(void*(*routine)(void*),void *arg);

#endif


