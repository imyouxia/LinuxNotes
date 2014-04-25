#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "tpool.h"

void *func(void *arg)
{
	printf("thread %d\n",(int)arg);
	return NULL;
}

int main()
{
	if(tpool_create(5) != 0)
	{
		printf("tpool_create failed\n");
		exit(1);
	}

	int i;
	for(i = 0; i < 10; i++)
	{
		tpool_add_work(func,(void *)i);
	}

	sleep(2);
	tpool_destroy();
	return 0;
}

