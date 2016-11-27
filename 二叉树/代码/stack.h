#include "stdio.h"
#include "stdlib.h"

struct Node
{
	int i;
	struct Node* lChild;
	struct Node* rChild;
};

typedef struct Node* NodePtr;

struct stack
{
	Node** top;
	Node** base;
	int size;
};

void init(stack* &s)
{
	s = (stack*) malloc(sizeof(stack));
	s->base = (NodePtr*)malloc(sizeof(Node*) * 20);
	s->top = s->base;
	s->size = 20;
}

void push(stack* s,NodePtr n)
{
	if(!s)
	{
		return;
	}
	if(s->top - s->base == s->size)
	{
		//ÉÏÒç
		return;
	}
	*++s->top = n;
}

NodePtr pop(stack* s)
{
	if(s->top == s->base)
	{
		//ÏÂÒç
		return NULL;
	}
	return *s->top--;
}

int empty(stack* s)
{
	return s->base == s->top;
}

NodePtr top(stack* s)
{
	return *s->top;
}