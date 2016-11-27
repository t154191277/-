#include "stdio.h"
#include "stdlib.h"

struct OPND
{
	int* top;
	int* base;
	int size;
};

struct OPTR
{
	char* top;
	char* base;
	int size;
};

void init(OPND* &stack,int n)
{
	stack = (OPND*) malloc(sizeof(OPND));
	stack->base = (int*)malloc(sizeof(int) * n);
	stack->top = stack->base;
	stack->size = n;
}

int push(OPND* stack,int n)
{
	if(!stack)
	{
		return 0;
	}
	if(stack->top - stack->base == stack->size)
	{
		//����
		return 0;
	}
	return *++stack->top = n;
}

int pop(OPND* stack)
{
	if(stack->top == stack->base)
	{
		//����
		return -1;
	}
	return *stack->top--;
}

int empty(OPND* stack)
{
	return stack->base == stack->top;
}

int top(OPND* stack)
{
	return *stack->top;
}

void init(OPTR* &stack,int n)
{
	stack = (OPTR*)malloc(sizeof(OPTR));
	stack->base = (char*)malloc(sizeof(char) * n);
	stack->top = stack->base;
	stack->size = n;
}

int push(OPTR* stack,char n)
{
	if(!stack)
	{
		return 0;
	}
	if(stack->top - stack->base == stack->size)
	{
		//����
		return 0;
	}
	return *++stack->top = n;
}

char pop(OPTR* stack)
{
	if(stack->top == stack->base)
	{
		//����
		return ' ';
	}
	return *stack->top--;
}

int empty(OPTR* stack)
{
	return stack->base == stack->top;
}

char top(OPTR* stack)
{
	return *stack->top;
}

int rRate(char c)
{
	switch(c)
	{
	case '+':
		return 2;
		break;
	case '-':
		return 2;
		break;
	case '*':
		return 4;
		break;
	case '/':
		return 4;
		break;
	case '(':
		return 6;
		break;
	case ')':
		return 1;
		break;
	case '#':
		return 0;
		break;
	}
}

int lRate(char c)
{
	switch(c)
	{
	case '+':
		return 3;
		break;
	case '-':
		return 3;
		break;
	case '*':
		return 5;
		break;
	case '/':
		return 5;
		break;
	case '(':
		return 1;
		break;
	case ')':
		return 6;
		break;
	case '#':
		return 0;
		break;
	}
}

int calu(int a,int b,char c)
{
	switch(c)
	{
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		return a / b;
		break;
	}
}

int main()
{
	OPND* opnd;
	OPTR* optr;
	int q;
	for(q = 0; q< 3; q++)
	{
	init(opnd,5);
	init(optr,5);
	push(optr,'#');
//	printf("%c", top(optr));

	//in��������,express��ʽ����,
	//opndArr�����λ��������
	char in[50],express[20];
	int i,size = 0,s = 0,opndArr[5];
	for(i =0;i<50;i++)
	{
		in[i] = '`';
	}
	gets(in);
	for(i =0;i<50;i++)
	{
		if(in[i] != '`' && in[i] != '\0')
		{
			express[size++] = in[i];
		}
	}

	for(i = 0;i<size;i++)
	{
		//printf("%c",express[i]);
		int goon = 1;

		char c = express[i];
		//�жϲ�����
		if( 47 < c && c <= 57)
		{
			int a=atoi(&c);
			opndArr[s++] = a;
		}
		//�жϲ�����
		else if('#' == c || '+' == c || '-' == c || '*' == c || '/' == c || '(' == c ||')' == c)
		{
			//��λ�������ϲ�
			if(s > 0)
			{
				int m = s - 1,num = 0;
				for(m; m >= 0; m--)
				{
					if(m == s - 1)
					{
						num += opndArr[m];
						continue;
					}
					num += opndArr[m] * (s - m - 1) *10;
				}
				s = 0;
				push(opnd, num);
			}

			while(!empty(optr) && goon)
			{
				char temp = top(optr);

				//ջ���ȵ�ǰ�����Ȩ�ظ������
				if (lRate(temp) > rRate(c))
				{
					int b = pop(opnd);
					int a = pop(opnd);
					temp = pop(optr);
					int res = calu(a,b,temp);
					push(opnd,res);

					//��ֹ���˵�+,-
					if(c == '+' || c == '-')
					{
						push(optr, c);
					}
				}
				temp = top(optr);
				//���ų�ջ����tempΪ#��ʱ�򣬴�ӡ����������opndջ��
				if (lRate(temp) == rRate(c))
				{
					if(temp == '#')
					{
						printf("=%d\n",top(opnd));
						break;
					}
					pop(optr);
				}
				temp = top(optr);
				//�¼������ջ��Ȩ�ظߣ���ջ
				if (lRate(temp) <= rRate(c) && c != 'c' && c!= ')')
				{
					push(optr, c);
				}


				goon = 0;

				if(i == size -1)
				{
					goon = 1;
				}
			}
		}
	}	
	}
	return 0;
}