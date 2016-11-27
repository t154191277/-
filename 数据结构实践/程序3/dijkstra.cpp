#include "stdio.h"
#include "stdlib.h"
#include <sstream>
#include <string>
#include<iostream>
using namespace std;

int visit[100];

//�ߣ����ӵ��Ľڵ�i,�Լ����Ƚڵ����ӵ���һ����ָ�롣
struct EdgeNode 
{
	int i;
	int right;
	EdgeNode* next;
};

//�ڵ� 
struct VertexNode
{	
	VertexNode()
	{
		firstedge = NULL;
	}
	// �ڵ���Ϣ
	char i[2];
	string info;
	//�ڽӱ�ͷָ��
	EdgeNode* firstedge;
};

//ͼ
struct Graph
{
	//������
	VertexNode list[50];
	//�ڵ�ͱߵ�����
	int n,e;
};

void dijkstra(Graph* graph, int from, int to)
{
	//vΪѡ��������С����ĵ�,p[][]Ϊ��·��������
	int n,w,minDisNode,S[20],D[20],p[20][20];
	for(n = 0; n < graph->n; n++)
	{
		D[n] = 10000;
		S[n] = 0;
		for(w = 0; w < graph->n; w++) p[n][w] = 0;


	}
	
	EdgeNode* temp = graph->list[from].firstedge;
	while(temp)
	{
		D[temp->i] = temp->right;
		p[temp->i][from] = 1;
		p[temp->i][temp->i] = 1;
		temp = temp->next;
	}
	
	//DΪ��֪�����·��Ȩ��
	//SΪ�Ѿ�ѡ�������·���ĵ�ļ���
	D[from] = 0; S[from] = 1;

	for(n = 1; n < graph->n; n++)
	{
		int min = 10000;

		for(w = 0; w < graph->n; w++)
		{
			if(!S[w])
			{
				if(D[w] < min)
				{
					minDisNode = w;
					min = D[minDisNode];
				}
			}
		}

		//��minDisNode����S�� 
		S[minDisNode] = 1;
		temp = graph->list[minDisNode].firstedge;
		while(temp)
		{
			if(!S[temp->i] && (min + temp->right) < D[temp->i])
			{
				D[temp->i] = min + temp->right;
				for(int x=0;x < 17; x++) p[temp->i][x] = p[minDisNode][x];
				p[temp->i][temp->i] = 1;
			}
			temp = temp->next;
		}
		
	}

	//�������·��Ȩ��
//	for (int x = 0; x < n; x++) printf("D[%d] = %d\n",x,D[x]);

	//ģ��������һ��·��������p[to][v]�ľ������·��
	int j = from, v;
	cout << graph->list[j].info;
	for(w = 1; w < 17; w++)
	{
		for(v = 0; v < 17; v++)
		{
			temp = graph->list[j].firstedge;
			while(temp)
			{
				if(p[to][v] && v == temp->i)
				{
					//��p[to][v]�Ƴ�
					p[to][v] = 0;
					j = v;
					cout << "->" << graph->list[j].info;
					break;
				}
				temp = temp->next;
			}
		}
	}
}


void initSchollGraph(Graph* &graph)
{
	//graph = (Graph*)malloc(sizeof(Graph));
	graph = new Graph();
	graph->n = 17;
	graph->e = 17;
	string n[17];
	int e[17][17];
	n[0] = "����";
	n[1] = "ͼ���";
	n[2] = "���ʽ���ѧԺ";
	n[3] = "����";
	n[4] = "ˮ��";
	n[5] = "ѧһ";
	n[6] = "ѧ��";
	n[7] = "ѧ��";
	n[8] = "У԰����";
	n[9] = "УҽԺ";
	n[10] = "����";
	n[11] = "ѧ��";
	n[12] = "�ﾶ��";
	n[13] = "��һ";
	n[14] = "�̶�";
	n[15] = "����";
	n[16] = "����";

	int i;
	for(i = 0; i < 17; i++)
	{
		graph->list[i].info = "ab";
		graph->list[i].info = n[i];
		char str[2];
		sprintf(str,"%d",i);
		graph->list[i].i[0] = str[0];
		graph->list[i].i[1] = str[1];
		cout<< i << "----" << n[i] << endl;
	}

	for(i = 0; i < 17; i++)
	{
		int j;
		for(j = 0; j < 17; j++)
		{
			e[i][j] = 0;
		}
	}

	e[0][1] = 2;
	e[0][14] = 4;
	e[1][3] = 3;
	e[1][2] = 2;
	e[2][3] = 2;
	e[2][13] = 1;
	e[3][4] = 2;
	e[4][5] = 1;
	e[4][16] = 2;
	e[5][6] = 4;
	e[6][7] = 1;
	e[6][8] = 5;
	e[6][9] = 5;
	e[7][10] = 4;
	e[7][13] = 7;
	e[7][11] = 12;
	e[8][9] = 4;
	e[10][11] = 15;
	e[11][12] = 2;
	e[12][15] = 1;
	e[13][14] = 1;
	e[14][15] = 1;

	for(i = 0; i < 17; i++)
	{
		int j;
		for(j = 0; j < 17; j++)
		{
			if(e[i][j] != 0)
			{	
				//���߲��뵽�ڵ���ڽӱ���
				//˫���
				EdgeNode* enode = (EdgeNode*)malloc(sizeof(EdgeNode));
				enode->i = i;
				enode->right = e[i][j];
				enode->next = graph->list[j].firstedge;
				graph->list[j].firstedge = enode;

				enode = (EdgeNode*)malloc(sizeof(EdgeNode));
				enode->i = j;
				enode->right = e[i][j];
				enode->next = graph->list[i].firstedge;
				graph->list[i].firstedge = enode;
			}
		}
	}
}

int main()
{
	Graph* graph2;

	initSchollGraph(graph2);
	printf("from where to where?\n");
	int f,t;
	scanf("%d,%d",&f,&t);
	dijkstra(graph2,f,t);
	return 0;
}