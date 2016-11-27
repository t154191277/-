#include "stdio.h"
#include <stdlib.h>

#define DEFAULT_QUEUE_SIZE 20;

struct Node
{
	int capacity;
	int head;
	int tail;
	int size;
	int* arrQueue;
};

typedef struct Node* Queue;

void Init(Queue &Q)
{
	Q = (Queue)malloc(sizeof(Node));

	if(!Q)
	{
		printf("队列内存分配失败!");
		return;
	}

	int i = DEFAULT_QUEUE_SIZE;
	Q->arrQueue = (int*)malloc(sizeof(int) * i);
	if(!Q->arrQueue)
	{
		printf("队列数组内存分配失败!");
		return;
	}

	Q->capacity = DEFAULT_QUEUE_SIZE;
	Q->size = 0;
	Q->head = 0;
	Q->tail = 0;
}

int IsEmpty(Queue Q)
{
	if(Q->size == 0)
	{
		return 1;
	}
	return 0;
}

void In(Queue &Q,int n)
{

	Q->arrQueue[Q->tail] = n;
	Q->size++;
	Q->tail++;
}

int Out(Queue &Q)
{
	int i = Q->head;
	Q->head++;
	Q->size--;
	return Q->arrQueue[i];
}





