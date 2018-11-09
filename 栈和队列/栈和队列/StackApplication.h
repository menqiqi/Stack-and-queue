#pragma once

#include"Stack.h"
#include<string.h>

//括号匹配问题(MatchBrackets)
void MatchBrackets(const char* sequence, int size)
{
	Stack stack;
	int i = 0;
	char ch;
	char leftBracket;
	StackInit(&stack);
	for(i=0; i<size; i++)
	{
		ch = sequence[i];
		switch(ch){
			case '(':
			case '[':
			case '{':
				StackPush(&stack, (StackDataType)ch);
				break;
			case ')':
			case ']':
			case '}':
				if(StackEmpty(&stack))
				{
					printf("右括号多\n");
					StackDestroy(&stack);
					return;
				}
				leftBracket = (char)StackTop(&stack);
				StackPop(&stack);
				if(leftBracket=='(' && ch!=')')
				{
					printf("不匹配\n");
					return;
				}
				if(leftBracket=='[' && ch!=']')
				{
					printf("不匹配\n");
					return;
				}
				if(leftBracket=='{' && ch!='}')
				{
					printf("不匹配\n");
					return;
				}
			default:
				break;
		}
	}
	if(!StackEmpty(&stack))
	{
		printf("左括号多\n");
		return;
	}
	printf("正常匹配\n");
}

void TestBracket()
{
	int i = 0;
	const char *seqs[] = {
		"(())abc{[(])}",
		"(()))abc{[]}",
		"(()()abc{[]}",
		"(())abc{[]()}"
	};
	for(i=0; i<4; i++)
	{
		MatchBrackets(seqs[i], strlen(seqs[i]));
	}
}

//逆波兰表达式（后缀表达式）
typedef enum{
	OPERAND,//操作数类型
	OPERATOR//操作符类型
}Type;

typedef enum{
	ADD,
	SUB,
	MUL,
	DIV
}Operator;

typedef struct{
	Type type;
	int operand;  //操作数
	Operator operator;  //操作符
}Element;

int run(Operator operator, int a, int b)
{
	switch(operator){
		case ADD:
			return a+b;
		case SUB:
			return a-b;
		case MUL:
			return a*b;
		case DIV:
			return a/b;
		default:
			assert(0);
	}
}

int ReversedPolishNotation(Element expression[], int size)
{
	int op1,op2;
	int i = 0;
	int result;
	Stack stack;
	StackInit(&stack);

	for(i=0; i<size; i++)
	{
		Element e = expression[i];

		switch(e.type){
			case OPERAND:
				StackPush(&stack, e.operand);
				break;
			case OPERATOR:
				op1 = StackTop(&stack);
				StackPop(&stack);
				op2 = StackTop(&stack);
				StackPop(&stack);
				result = run(e.operator, op2, op1);//注意，后入栈的在栈顶，先被读出，所以后入栈的是op1,先入栈的是op2
				StackPush(&stack, result);
				break;
			default:
				assert(0);
		}
	}
	if(StackSize(&stack) == 1){
	result  = StackTop(&stack);
	}
	return result;
}

void TestRPN()
{
	Element expression[] = {
		{
			OPERAND,
				12,
				SUB//没有用
		},
			{
				OPERAND,
					3,
					SUB
			},
			{
				OPERAND,
					4,
					SUB
				},
				{
					OPERATOR,
						1,//没有用
						ADD
				},
				{
					OPERATOR,
						1,//没有用
						MUL
				},
				{
				OPERAND,
					6,
					SUB
			},
			{
					OPERATOR,
						1,//没有用
						SUB
				},
				{
				OPERAND,
					8,
					SUB
			},
			{
				OPERAND,
					2,
					SUB
			},
			{
					OPERATOR,
						1,//没有用
						DIV
				},
				{
					OPERATOR,
						1,//没有用
						ADD
				}
	};
	int result = ReversedPolishNotation(expression, 11);
	printf("result = %d\n",result);
}