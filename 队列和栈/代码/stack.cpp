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
		//上溢
		return 0;
	}
	return *++stack->top = n;
}

int pop(OPND* stack)
{
	if(stack->top == stack->base)
	{
		//下溢
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
		//上溢
		return 0;
	}
	return *++stack->top = n;
}

char pop(OPTR* stack)
{
	if(stack->top == stack->base)
	{
		//下溢
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

	//in输入数组,express算式数组,
	//opndArr储存多位数字输入
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
		//判断操作数
		if( 47 < c && c <= 57)
		{
			int a=atoi(&c);
			opndArr[s++] = a;
		}
		//判断操作符
		else if('#' == c || '+' == c || '-' == c || '*' == c || '/' == c || '(' == c ||')' == c)
		{
			//高位操作数合并
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

				//栈顶比当前计算符权重高则计算
				if (lRate(temp) > rRate(c))
				{
					int b = pop(opnd);
					int a = pop(opnd);
					temp = pop(optr);
					int res = calu(a,b,temp);
					push(opnd,res);

					//防止过滤掉+,-
					if(c == '+' || c == '-')
					{
						push(optr, c);
					}
				}
				temp = top(optr);
				//括号出栈，当temp为#号时候，打印结果，结果在opnd栈顶
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
				//新计算符比栈顶权重高，入栈
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