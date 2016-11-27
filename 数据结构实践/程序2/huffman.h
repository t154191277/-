#include "stdio.h"
#include "stdlib.h"

struct HuffNode
{
	double weight;
	char c;
	int flag;
	int parent;
	int lChild;
	int rChild;
};

struct HuffCode
{
	int code[30];
	char c;
	int size;
};