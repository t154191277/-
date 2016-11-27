
#include "stdio.h"
#include <stdlib.h>

#define DEFAULT_QUEUE_SIZE 10;

struct Node
{
	int capacity;
	int head;
	int tail;
	int size;
	int* arrQueue;
};

struct Man
{
	int n;
	int sec;
};

struct Event
{
	Man man;
	Event* next;
};

struct EventQueue
{
	Event* head;
	Event* tail;
};

typedef struct Node* Q;
typedef struct Man man;
typedef struct Event* EventPtr;

void Init(Node* &Q)
{
	Q = (Node*)malloc(sizeof(Node));

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

int IsFull(Node* Q)
{
	//假溢出
	if(Q->tail == Q->capacity)
	{
		Q->tail = 0;
	}
	
	//溢出
	if(Q->tail == Q->head && Q->size == Q->capacity)
	{
		return 1;
	}
	return 0;
}

int IsEmpty(Node* Q)
{
	if(Q->size == 0)
	{
		return 1;
	}
	return 0;
}

void EnLarge(Node* &Q)
{
	printf("队列数组已满\n");
	int* newArrQueue = (int*)malloc(sizeof(int) * Q->capacity * 2);
	if(!newArrQueue)
	{
		printf("队列数组扩容失败!\n");
		return;
	}
	//循环队列克隆
	if(Q->head >= Q->tail)
	{
		int i = Q->head;
		for(i; i < Q->capacity; i++)
		{
			newArrQueue[i - Q->head] = Q->arrQueue[i];
		}
		i = 0;
		for(i; i < Q->tail; i++)
		{
			newArrQueue[i + Q->capacity - Q->head] = Q->arrQueue[i];
		}
		newArrQueue;
		Q->head = 0;
		Q->tail = Q->size;
	}
	else
	{
		int i = 0;
		for(i; i < Q->capacity; i++)
		{
			newArrQueue[i] = Q->arrQueue[i];
		}
	}
	free(Q->arrQueue);
	Q->arrQueue = NULL;
	Q->arrQueue = newArrQueue;
	Q->capacity = Q->capacity * 2;
	printf("扩容至%d\n",Q->capacity);
}

void In(Node* &Q,int n)
{
	if(IsFull(Q))
	{
		EnLarge(Q);
	}
	Q->arrQueue[Q->tail] = n;
	Q->size++;
	Q->tail++;
}

int Out(Node* &Q)
{
	if(IsEmpty(Q))
	{
		return -1;
	}
	int i = Q->head;
	Q->head++;
	Q->size--;
	return Q->arrQueue[i];
}



void print(Node* &Q)
{
	if(Q->head >= Q->tail)
	{
		int i = Q->head;
		for(i; i < Q->size - Q->tail; i++)
		{
			int j = Out(Q);
			printf("%d ",j);
		}
		Q->head = 0;
		i = 0;
		for(i; i < Q->tail; i++)
		{
			int j = Out(Q);
			printf("%d ",j);
		}
	}
	else
	{
		int i = 0;
		while(Q->size!=0)
		{
			int j = Out(Q);
			printf("%d ",j);
		}
	}
	printf("\n");
}

int InQueue(Node* Q1,Node* Q2,man m)
{
	if(Q1->size <= Q2->size)
	{
		printf("第%d位客户进入队列1\n",m.n);
		In(Q1,m.n);
		return 1;
	}
	else
	{
		printf("第%d位客户进入队列2\n",m.n);
		In(Q2,m.n);
		return 2;
	}
}

void InEvent(EventPtr &E,man m,EventQueue &queue)
{
	EventPtr temp = E;
	
	while(temp->next)
	{
		temp = temp->next;
	}
	EventPtr insert = (EventPtr)malloc(sizeof(Event));
	insert->man = m;
	insert->next = NULL;
	temp->next = insert;

	queue.head = E->next;
	queue.tail= insert;
}

void OutEvent(EventPtr &E,EventQueue &queue)
{
	if(E->next)
	{
		EventPtr del = E->next;
		E->next = del->next;
		queue.head = E->next;
		free(del);
		del = NULL;
	}
	else
	{
		printf("EventQueue is empty!");
	}
}

Man NextEvent(EventPtr E,int n)
{
	int i = 0;
	EventPtr temp = E;
	while(temp->next)
	{
		temp = temp->next;
		if(n == i)
		{
			return temp->man;
		}
		i++;
	}
	return E->man;
}

int main()
{
	Q Q1,Q2;
	Init(Q1);
	Init(Q2);

	EventPtr evePtr = (EventPtr)malloc(sizeof(Event));
	EventQueue queue;
	evePtr->next = NULL;
	int j;
	for(j = 0; j < 100; j++)
	{
		man _m;
		_m.n = j;
		_m.sec = rand()%(60-5+1)+5;
		InEvent(evePtr,_m,queue);
	}
	
	man mm1,mm2;
	//x1,x2记录每一个顾客开始操作的时间点
	//n1,n2为填充数组的游标,m1,m2为取数组的游标
	int x1 = 0,x2 = 0,n1 = 0,n2 =0,m1 = 0,m2 = 0;
	//花费时间的数组
	int arr1[100],arr2[100];
	//取下一个顾客的游标
	int f = 0;
	for(j = 0; j< 100; j++)
	{
		int i = rand()%3;
		if((i + j) % 2 == 0)
		{
			printf("%d\n",j);
			man m = NextEvent(evePtr,f++);
			int r = InQueue(Q1,Q2,m);
			if(r==1)
			{
				mm1 = m;
				arr1[n1] = m.sec;
				n1++;
			}
			else
			{
				mm2 = m;
				arr2[n2] = m.sec;
				n2++;
			}
		}
		if(arr1[m1] == j - x1)
		{
			m1++;
			printf("%dth customer is done from %d queue and cost %d second\n",queue.head->man.n, 1, queue.head->man.sec);
			x1 = j;
			//事件出队列
			OutEvent(evePtr,queue);
			//人出队列
			Out(Q1);
		}
		if(arr2[m2] == j - x2)
		{
			m2++;
			printf("%dth customer is done from %d queue and cost %d second\n",queue.head->man.n, 2, queue.head->man.sec);
			x2 = j;
			OutEvent(evePtr,queue);
			Out(Q2);
		}
	}
	
	return 0;
}