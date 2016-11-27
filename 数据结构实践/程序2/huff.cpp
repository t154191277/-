#include "stdio.h"
#include "stdlib.h"
#include "huffman.h"

typedef struct Node* NodePtr;

void getInput(double * &d,char * &c,int* n)
{
	char in[40];
	int size = 0, i =0;
	printf("how many codes do you want?\n");
	scanf("%d",&size);
	c = (char*)malloc(sizeof(char) * size);
	d = (double*)malloc(sizeof(double) * size);
	printf("please input %d codes:\n", size);
	*n = size;

	for(i; i < 40; i++)
	{
		in[i] = '`';
	}

	fflush(stdin);
	gets(in);

	int f = 0;
	for(i = 0; i < 40; i++)
	{
		char s = in[i];
		if(s != '`' && s != '\0' && s != ',')
		{	
			c[f++] = s; 
		}
	}

	printf("please input %d weights:\n", size);

	for(i = 0; i < 40; i++)
	{
		in[i] = '`';
	}

	fflush(stdin);
	gets(in);

	char *temp = (char*)malloc(sizeof(char) * 5);
	char *tempbase;
    tempbase = temp;
	if(!temp)
	{
		printf("null");
	}
	f = 0;
	for(i = 0; i < 40; i++)
	{
		char s = in[i];
		if(s != '`' && s != '\0' )
		{	
			*temp++ = s;
			if((s == ',' && size != 1) || in[i + 1] == '\0')
			{
				double a = atof(tempbase);
				temp = tempbase;
				d[f++] = a; 
			}
		}
	}

	for(i = 0; i < size; i++)
	{
		printf("%c",c[i]);
	}

	for(i = 0; i < size; i++)
	{
		printf("%5.2lf",d[i]);
	}
}

void initHuff(char* c,double *d, int* size, HuffNode hufftree[])
{
	//拥有n个叶子节点的满二叉树有2n-1个节点
	//初始化深林
	int i,n = *size;
	for(i = 0; i < 2 * n - 1; i++)
	{	
		HuffNode node;

		if(i < n)
		{
			node.weight = *d;
			node.c = *c;
		}
		else
		{
			node.weight = 0;
			node.c = '`';
		}
		node.parent = 0;
		node.lChild = -1;
		node.rChild = -1;
		*d++;
		*c++;

		hufftree[i] = node;
		
	}
	//非叶子节点, n - 1 个
	for(i = 0; i < n - 1; i++)
	{
		//printf("%c",*dbase++);
		int x1,x2;
		double m1 = 1000,m2 = 1000;
		int j;

		for(j = 0; j < n + i; j++)
		{
			if(hufftree[j].weight < m1 && hufftree[j].parent == 0)
			{
				x1 = j;
				m1 = hufftree[j].weight;
			}
			else if(hufftree[j].weight < m2 && hufftree[j].parent == 0)
			{
				x2 = j;
				m2 = hufftree[j].weight;
			}
		}

		hufftree[x1].parent = n + i;
		hufftree[x2].parent = n + i;
		hufftree[n + i].weight = hufftree[x1].weight + hufftree[x2].weight;
		hufftree[n + i].lChild = x1;
		hufftree[n + i].rChild = x2;
	}
}

void HuffManCode(HuffNode hufftree[], int* n)
{
	HuffCode huffcode[10];
	int i,parent,child;
	for(i =0; i < *n; i++)
	{
		int j = 0,size = 0;
		HuffCode codetemp;
		//字符
		codetemp.c = hufftree[i].c;
		child = i;
		parent = hufftree[i].parent;
		while(parent != 0)
		{
			if(hufftree[parent].lChild == child)
			{
				codetemp.code[j++] = 0;
			}
			else if(hufftree[parent].rChild == child)
			{				
				codetemp.code[j++] = 1;				
			}
			size++;
			child = parent;
			parent = hufftree[child].parent;
		}
		huffcode[i] = codetemp;
		huffcode[i].size = size;
	}

	printf("\n");
	for(i = 0; i < *n; i++)
	{
		printf("%c: ",huffcode[i].c);
		int j;
		for(j = huffcode[i].size - 1; j >= 0; j--)
		{
			printf("%d ",huffcode[i].code[j]);
		}
		printf("\n");
	}
}


void huffdecode(HuffNode hufftree[],int* i)
{
	int root = 2 * *i -1 -1;
	int n = root,f = 0;
	char c[100];
	printf("please input huff code:\n");
	fflush(stdin);
	gets(c);
	while(c[f] != '`')
	{
		if(c[f] == '0')
		{
			n = hufftree[n].lChild;
		}
		else if(c[f] == '1')
		{
			n = hufftree[n].rChild;
		}
		if(hufftree[n].lChild == -1)
		{
			printf("%c", hufftree[n].c);
			n = root;
		}
		c[f++];
	}
	printf("\n");

	if(hufftree[n].lChild == -1 && c[f] == '`')
	{
		printf("报文有错！\n");
	}
}

int main()
{

	double* d;
	char* c;
	int n;
	getInput(d, c, &n);
	HuffNode hufftree[100];
	initHuff(c, d, &n, hufftree);
	HuffManCode(hufftree, &n);
	huffdecode(hufftree, &n);
	return 0;
}