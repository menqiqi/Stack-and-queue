#pragma once

#include"Stack.h"
#include<string.h>

//����ƥ������(MatchBrackets)
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
					printf("�����Ŷ�\n");
					StackDestroy(&stack);
					return;
				}
				leftBracket = (char)StackTop(&stack);
				StackPop(&stack);
				if(leftBracket=='(' && ch!=')')
				{
					printf("��ƥ��\n");
					return;
				}
				if(leftBracket=='[' && ch!=']')
				{
					printf("��ƥ��\n");
					return;
				}
				if(leftBracket=='{' && ch!='}')
				{
					printf("��ƥ��\n");
					return;
				}
			default:
				break;
		}
	}
	if(!StackEmpty(&stack))
	{
		printf("�����Ŷ�\n");
		return;
	}
	printf("����ƥ��\n");
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

//�沨�����ʽ����׺���ʽ��
typedef enum{
	OPERAND,//����������
	OPERATOR//����������
}Type;

typedef enum{
	ADD,
	SUB,
	MUL,
	DIV
}Operator;

typedef struct{
	Type type;
	int operand;  //������
	Operator operator;  //������
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
				result = run(e.operator, op2, op1);//ע�⣬����ջ����ջ�����ȱ����������Ժ���ջ����op1,����ջ����op2
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
				SUB//û����
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
						1,//û����
						ADD
				},
				{
					OPERATOR,
						1,//û����
						MUL
				},
				{
				OPERAND,
					6,
					SUB
			},
			{
					OPERATOR,
						1,//û����
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
						1,//û����
						DIV
				},
				{
					OPERATOR,
						1,//û����
						ADD
				}
	};
	int result = ReversedPolishNotation(expression, 11);
	printf("result = %d\n",result);
}