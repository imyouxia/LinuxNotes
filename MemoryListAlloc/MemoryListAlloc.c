/* 循环链表的内存分配释放 */

#include <stdio.h>
#include <stdlib.h>

struct clist    //循环链表结构声明
{
	int data;   //结点数据
	struct clist *next;   //指向前一结点的指针
};

typedef struct clist cnode;  //循环链表新类型
typedef cnode *clink;   //循环链表指针新类型


/* 链表的结点内存分配 */

clink nodealloc(clink *memory)
{
	clink new_node;   //新结点的指针
	clink ptr;   

	if((*memory) != NULL)  //链表是否是空
	{
		ptr = (*memory);
		*memory = (*memory)->next;   //指向下一个结点
		ptr->next = NULL;   //设置指针初值
		return ptr;   //返回新结点指针
	}

	else
	{
		//创建新结点分配结点内存
		new_node = (clink)malloc(sizeof(cnode));
		if(!new_node)  //检查内存指针
		{
			return NULL;
		}
		new_node->next = NULL;  //设置指针初值
		return new_node;   //返回新结点指针
	}

}


/* 链表的结点内存释放 */
int freenode(clink *memory,clink ptr)
{
	ptr->next = (*memory);   //插入链表开始
	(*memory) = ptr;         //设置链表指针
	return 0;
}

/* 循环链表的输出 */
int printclist(clink head)
{
	clink ptr;
	printf("循环链表的内存：");
	ptr = head;    //指向链表的开始
	do
	{
		printf("[%d]",ptr->data);   //输出结点数据
		ptr = ptr->next;   //指向下一个结点
	}while(head != ptr);
	printf("\n");  //换行
	return 0;
}

/* 列出内存链表内容 */
int printmemory(clink memory)
{
	clink ptr;
	printf("内存链表内容：");
	ptr = memory;   //指向链表开始
	while(ptr != NULL)  //链表遍历循环
	{
		printf("[%d]",ptr->data);   //输出结点数据
		ptr = ptr->next;   //指向下一个结点
	}
	printf("\n");
	return 0;

}

/* 使用数组值创建链表 */
clink createclist(int *array,clink *memory,int len)
{
	clink head = NULL;  //循环链表的指针
	clink before;   //前一结点的指针
	clink new_node;   //新结点的指针
	int i;  

	//创建第一个结点
	head = nodealloc(memory);   //分配结点内存
	head->data = array[0];    //创建结点内容
	before = head;    //指向第一个结点

	for(i = 1; i < len; i++)   //用循环创建其他结点
	{
		new_node = nodealloc(memory);   //分配结点内存
		new_node->data = array[i];    //创建结点内容
		before->next = new_node;   //将前结点指向新结点
		before = new_node;    //新结点成为前结点
	}
	new_node->next = head;  //创建环状链接

	return head;   //返回链表起始指针
}

/* 释放整个循环链表 */
int freeclist(clink head,clink *memory)
{
	clink ptr;    //下一个结点的指针
	if(head != NULL)   //链表是否是空
	{
		ptr = head->next;    //指向下一结点
		head->next = *memory;      //head 指向memory
		*memory = ptr;   //新的内存链表开始
	}
	return 0;
}

/* 主程序：使用内存管理方式来创建链表和作内存释放 */

int main()
{
	clink head = NULL;    //循环链表指针
	clink memory = NULL;   //内存管理指针
	clink ptr;

	int list[6] = {1,2,3,4,5,6};   //数组内容
	int i;

	//用循环创建内存链表，总共7个结点
	for(i = 0; i < 7; i++)
	{
		//分配一个结点内存
		ptr = (clink)malloc(sizeof(cnode));
		if(!ptr)  //检查内存指针
		{
			exit(1);
		}

		ptr->next = NULL;  
		ptr->data = 100 + i;  //创建结点内存
		freenode(&memory,ptr);   //释放一个结点内存
	}
	printmemory(memory);   //输出内存链表

	head = createclist(list,&memory,6);    //创建循环链表
	printclist(head);   //输出循环链表

	//循环链表的内存释放
	freeclist(head,&memory);
	printmemory(memory);   //输出内存链表
	
	return 0;
	
}




