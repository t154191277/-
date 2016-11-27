#include "stdio.h"
#include <stdlib.h>

typedef struct Node
{
	int num;
	struct Node* prior;
	struct Node* next;
}Node,*NodePtr;


void Init(NodePtr &L, Node a[],int size)
{
	int i =0;
	NodePtr s,temp;
	temp = L;
	for(i; i < size; i++)
	{
		s = (NodePtr)malloc(sizeof(Node));
		s->num = a[i].num;
		s->next = NULL;
		s->prior = temp;
		temp->next = s;
		temp = temp->next;
	}
	// ��һ��Ԫ�ص�ǰ��Ϊnull
	L->next->prior = NULL;
}

void MakeEmpty(NodePtr &L)
{
	L = (NodePtr)malloc(sizeof(Node));
	L->prior = NULL;
	L->next = NULL;
}

int Length(NodePtr &L)
{
	int length = 0;
	NodePtr temp;
	if(!L)
	{
		return 0;
	}
	temp = L->next;
	while(temp)
	{
		temp = temp->next;
		length++;
	}
	return length;
}

NodePtr Get(NodePtr &L,int i)
{
	NodePtr temp;
	temp = L->next;
	while(temp)
	{
		if (i == temp->num)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void GetAndPrint(NodePtr &L,Node node)
{
	NodePtr prior = Get(L, node.num);
	printf("����ǰ��:");
	while(prior->prior)
	{
		prior = prior->prior;
		printf("%d ",prior->num);
	}
	printf("\n");

	NodePtr next = Get(L, node.num);
	printf("˳����:");
	while(next->next)
	{
		next = next->next;
		printf("%d ",next->num);
	}
	printf("\n");
}



NodePtr Prior(NodePtr &L,Node node)
{
	//int length = 0;
	NodePtr temp;
	temp = L->next;
	while(temp)
	{
		//length++;
		if (node.num == temp->num)
		{
			return temp->prior;
		}
		temp = temp->next;
	}
	return NULL;
}

NodePtr Next(NodePtr &L,Node node)
{
	//int length = 0;
	NodePtr temp;
	temp = L->next;
	while(temp)
	{
	//	length++;
		if (node.num == temp->num)
		{
			return temp->next;
		}
		temp = temp->next;
	}
	return NULL;
}

int Locate(NodePtr &L,Node node)
{
	int length = 0;
	NodePtr temp;
	temp = L->next;
	while(temp)
	{
		length++;
		if (node.num == temp->num)
		{
			return length;
		}
		temp = temp->next;
	}
	return -1;
}

void Insert(NodePtr &L,int i,Node node)
{
	int length = 0;
	NodePtr temp, insert;
	temp = L;
	while(temp->next)
	{
		length++;
		if (length == i)
		{
			insert = (NodePtr)malloc(sizeof(Node));
			insert->next = temp->next;
			insert->num = node.num;
			insert->prior = temp;
			temp->next = insert;
			break;
		}
		temp = temp->next;
	}
	if(i > length)
	{
		insert = (NodePtr)malloc(sizeof(Node));
		insert->next = NULL;
		insert->num = node.num;
		insert->prior = temp;
		temp->next = insert;
	}
	if(length == 1)
	{
		L->next->prior = NULL;
	}
}

void Delete(NodePtr &L,Node node)
{
	NodePtr temp, del;
	temp = L;
	while(temp->next)
	{
		if (temp->next->num == node.num)
		{
			del = temp->next;
			if(del->next)
			{
				temp->next = del->next;
				temp->next->prior = temp;
			}
			else
			{
				temp->next = NULL;
			}
			if(!del->prior)
			{
				temp->next->prior = NULL;
			}
			free(del);
			del = NULL;
			break;
		}
		temp = temp->next;
	}
}

int IsEmpty(NodePtr &L)
{
	if(!L || L->next == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Clear(NodePtr &L)
{
	NodePtr temp;
	while(L->next)
	{
		temp = L->next;
		L->next = temp->next;
		free(temp);
		temp = NULL;
	}
	free(L);
	L = NULL;
}

void Traverse(NodePtr &L)
{
	NodePtr temp;
	temp = L->next;
	while(temp)
	{
		printf("%d ", temp->num);
		temp = temp->next;
	}
	printf("\n");
}

NodePtr Find(NodePtr &L,Node node)
{
	NodePtr temp;
	temp = L->next;
	while(temp)
	{
		if(node.num == temp->num)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}


int main()
{
	int i=0,size=15,n;
	
	Node nodeArr[15];
	for(i; i < 15; i++)
	{
		Node node;
		node.num = i;
		nodeArr[i] = node;
	}

	Node node;
	NodePtr L,s;
	printf("���������Ա�\n");
	MakeEmpty(L);
	printf("�Ƿ�Ϊ��:%d������Ϊ%d\n",IsEmpty(L),Length(L));
	system("pause");
	system("cls");

	printf("�������Ա�\n");
	Init(L, nodeArr, size);
	printf("�Ƿ�Ϊ��:%d������Ϊ%d\n",IsEmpty(L),Length(L));
	printf("�������Ա�\n");
	Traverse(L);
	system("pause");
	system("cls");

	Traverse(L);
	printf("�������Ա�������Ҫ�����λ�ã���ֵ\n");
	scanf("%d,%d",&i,&n);
	node.num = n;
	Insert(L, i, node);
	printf("�����:\n");
	Traverse(L);
	system("pause");
	system("cls");

	Traverse(L);
	printf("ɾ�����Ա�������Ҫɾ������ֵ\n");
	scanf("%d",&i);
	node.num = i;
	Delete(L, node);
	printf("ɾ����:\n");
	Traverse(L);
	system("pause");
	system("cls");

	Traverse(L);
	printf("�������Ա�������Ҫ���ҵ���ֵ\n");
	scanf("%d",&i);
	node.num = i;
	s = Find(L, node);
	if(s)
	{
		printf("���ҳɹ���\n");
	}
	else
	{
		printf("����ʧ�ܣ�\n");
	}
	system("pause");
	system("cls");

	Traverse(L);
	printf("�������Ա���ֵλ�ã�������Ҫ���ҵ���ֵ\n");
	scanf("%d",&i);
	node.num = i;
	i = Locate(L, node);
	if(i == -1)
	{
		printf("����ʧ�ܣ�\n");
	}
	else
	{
		printf("λ��Ϊ:%d\n",i);
	}
	system("pause");
	system("cls");

	Traverse(L);
	printf("��ѯ���Ա���ֵǰ����������Ҫ���ҵ���ֵ\n");
	scanf("%d",&i);
	node.num = i;
	s = Prior(L, node);
	if(s)
	{
		printf("���ҳɹ���ǰ����ֵΪ%d:\n",s->num);
	}
	else
	{
		printf("����ʧ�ܣ�:\n");
	}
	system("pause");
	system("cls");

	Traverse(L);
	printf("��ѯ���Ա���ֵ��̣�������Ҫ���ҵ���ֵ\n");
	scanf("%d",&i);
	node.num = i;
	s = Next(L, node);
	if(s)
	{
		printf("���ҳɹ��������ֵΪ%d:\n",s->num);
	}
	else
	{
		printf("����ʧ�ܣ�:\n");
	}
	system("pause");
	system("cls");
	

	Traverse(L);
	printf("��ȡ���Ա���ֵi��������Ҫ��ȡ����ֵ\n");
	scanf("%d",&i);
	node.num = i;
	GetAndPrint(L, node);
	system("pause");
	system("cls");

	Traverse(L);
	printf("ɾ�����Ա�\n");
	Clear(L);
	printf("�Ƿ�Ϊ��:%d������Ϊ%d\n",IsEmpty(L),Length(L));

	return 0;
}
