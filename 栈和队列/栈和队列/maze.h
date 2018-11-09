#pragma once

#include<string.h>
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

//ȫ�ֱ���
#define ROWS (6)
#define COLS (6)

//���������Թ��е����꣬x���£�y����
typedef struct{
	int x;
	int y;
}Position;

//ջ����

typedef Position StackDataType;//��ס���������Ҫ�任��Position
#define MAX_SIZE (100)

typedef struct Stack{
	StackDataType array[MAX_SIZE];
	int top;//��ʾ��ǰ����
}Stack;

//��ʼ��/����
//����ֻ�ܴ�ջ����/ɾ��ֻ�ܴ�ջ����/�飨ֻ�ܴ�ջ����
//����/�Ƿ��/�Ƿ���
//��----˳����β��
//ɾ----˳����βɾ

void StackInit(Stack *pStack)
{
	pStack->top = 0;                                                                                  
}

void StackDestroy(Stack *pStack)
{
	pStack->top = 0;
}

void StackPush(Stack *pStack, StackDataType data)
{
	assert(pStack->top < MAX_SIZE);
	pStack->array[pStack->top++] = data;
}

void StackPop(Stack *pStack)
{
	assert(pStack->top > 0);
	pStack->top--;
}

StackDataType StackTop(const Stack *pStack)
{
	assert(pStack->top > 0);
	return pStack->array[pStack->top-1];
}

int StackSize(const Stack* pStack)
{
	return pStack->top;
}

int StackFull(const Stack* pStack)
{
	return pStack->top >= MAX_SIZE;
}

int StackEmpty(const Stack* pStack)
{
	return pStack->top <= 0;
}

//ջ����
void StackCopy(Stack *pDest, Stack *pSrc)
{
	memcpy(pDest->array, pSrc->array, sizeof(StackDataType)* pSrc->top);
	pDest->top = pSrc->top;
}

//ջ�������

//�Թ�
int gMaze[ROWS][COLS] = {
	{0,0,0,0,0,0},
	{0,0,1,0,0,0},
	{0,0,1,0,0,0},
	{0,0,1,1,1,0},
	{0,0,1,0,1,1},
	{0,0,1,0,0,0}
};
//int gMaze[ROWS][COLS] = {
//	{0,0,0,0,0,0},
//	{0,1,1,1,1,1},
//	{0,1,0,0,0,0},
//	{0,1,0,0,0,0},
//	{0,1,1,1,1,1},
//	{0,1,0,0,0,0}
//};
//int gMaze[ROWS][COLS] = {
//	{0,0,0,0,0,0},
//	{0,1,1,1,0,0},
//	{0,1,0,1,0,0},
//	{0,1,0,1,0,0},
//	{0,1,1,1,1,1},
//	{0,1,0,0,0,0}
//};

//��ڵ�
Position gEntry = {5,2};

//�ж��Ƿ��ߵ����ڣ����һ�ж��ǳ���
int IsExit(Position pos)
{
	if(pos.y == COLS-1){
		return 1;
	}
	else{
		return 0;
	}
}

//�ж��Ƿ�����ߣ�û��Խ�� && ֵ��1��
int CanPass(Position pos)
{
	if(pos.x >= ROWS){
		return 0;
	}
	if(pos.y >= COLS){
		return 0;
	}
	return gMaze[pos.x][pos.y] == 1;
}

void PrintPath(Stack *pStack)
{
	Position at;
	int i = 0;
	for(i=0; i<pStack->top; i++)
	{
		at = pStack->array[i];
		printf("x = %d, y = %d\n",at.x,at.y);
	}
}

Stack path;
Stack min;

void PrintMaze()
{
	int i = 0;
	int j = 0;
	for(i=0; i<ROWS; i++)
	{
		for(j=0; j<COLS; j++)
		{
		if(gMaze[i][j] == 0)
		{
			printf("@");
		}
		else if(gMaze[i][j] == 1){
			printf(" ");
		}
		else if(gMaze[i][j] == 2){//2��ʾ�߹���·
			printf("*");
		}
		}
		printf("\n");
	}
	printf("\n\n");
}



//�ݹ�����Թ���·
void RunMazeRec(Position at)
{
	Position next;
	StackPush(&path, at);

	//һ�������������߹���
	gMaze[at.x][at.y] = 2;
	PrintMaze();

	//Ϊʲô����Ҫ��ջ���¼��ֱ�����õ���ջ����
	if(IsExit(at)){
		//�����ǰ·����path��С��֮ǰ����С·����min��,��ǰ·��Ϊ���
		if(StackEmpty(&min) || StackSize(&path)<StackSize(&min)){
			StackCopy(&min, &path);
		}
		PrintPath(&path);
		printf("===========================================\n");

		//������Ϊ1
		gMaze[at.x][at.y] = 1;
		StackPop(&path);
		return;//�ᷢ������
	}
	//������-->��-->��-->�� ������
	next.x = at.x;
	next.y = at.y-1;
	if(CanPass(next)){
		RunMazeRec(next);
		PrintMaze();
	}
	next.x = at.x-1;
	next.y = at.y;
	if(CanPass(next)){
		RunMazeRec(next);
		PrintMaze();
	}
	next.x = at.x;
	next.y = at.y+1;
	if(CanPass(next)){
		RunMazeRec(next);
		PrintMaze();
	}
	next.x = at.x+1;
	next.y = at.y;
	if(CanPass(next)){
		RunMazeRec(next);
		PrintMaze();
	}
	//������Ϊ1
	gMaze[at.x][at.y] = 1;
	StackPop(&path);
	return;//����
}


#if 0
//ջ+ѭ�������Թ���·
//�ݹ���Լ�����ջ���ݵ�������ǣ��ݹ鳢�Թ��÷��򲻻����ߣ�Ŀǰѭ������
void RunMaze()
{
	//��Ҫһ��ջ��ʵ�ֻ���
	Stack stack;
	Position at;
	Position next;
	StackInit(&stack);
	at.x = gEntry.x;
	at.y = gEntry.y;
	
	while(1){
		//��ǵ�ǰ��λ�����Ѿ��߹���
		gMaze[at.x][at.y] = 2;
		//��ջ���¼��ǰλ�ã�Ϊ�Ժ�Ļ�����׼��
		StackPush(&stack, at);

		if(IsExit(at))
		{
			PrintPath(&stack);
			return;
		}
		//������-->��-->��-->�� ������
	next.x = at.x;
	next.y = at.y-1;
	if(CanPass(next)){
		at.x = next.x;
		at.y = next.y;
		continue;
	}
	next.x = at.x-1;
	next.y = at.y;
	if(CanPass(next)){
		at.x = next.x;
		at.y = next.y;
		continue;
	}
	next.x = at.x;
	next.y = at.y+1;
	if(CanPass(next)){
		at.x = next.x;
		at.y = next.y;
		continue;
	}
	next.x = at.x+1;
	next.y = at.y;
	if(CanPass(next)){
		at.x = next.x;
		at.y = next.y;
		continue;
	}
	//������裬����
	StackPop(&stack);//����pop�ľ��ǵ�ǰ��at
	if(StackEmpty(&stack)){
		printf("û�г���\n");
		return;
	}
	at = StackTop(&stack);
	}
}
#endif


void TestRunMaze1()
{
	StackInit(&path);
	StackInit(&min);
	RunMazeRec(gEntry);
	printf("���·�������� %d\n",StackSize(&min));
	//RunMaze(gEntry);
}