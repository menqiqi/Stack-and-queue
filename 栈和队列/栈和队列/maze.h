#pragma once

#include<string.h>
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

//全局变量
#define ROWS (6)
#define COLS (6)

//用来保存迷宫中的坐标，x向下，y向右
typedef struct{
	int x;
	int y;
}Position;

//栈代码

typedef Position StackDataType;//记住，这个类型要变换成Position
#define MAX_SIZE (100)

typedef struct Stack{
	StackDataType array[MAX_SIZE];
	int top;//表示当前个数
}Stack;

//初始化/销毁
//增（只能从栈顶）/删（只能从栈顶）/查（只能从栈顶）
//个数/是否空/是否满
//增----顺序表的尾插
//删----顺序表的尾删

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

//栈拷贝
void StackCopy(Stack *pDest, Stack *pSrc)
{
	memcpy(pDest->array, pSrc->array, sizeof(StackDataType)* pSrc->top);
	pDest->top = pSrc->top;
}

//栈代码结束

//迷宫
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

//入口点
Position gEntry = {5,2};

//判断是否走到出口，最后一列都是出口
int IsExit(Position pos)
{
	if(pos.y == COLS-1){
		return 1;
	}
	else{
		return 0;
	}
}

//判定是否可以走（没有越界 && 值是1）
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
		else if(gMaze[i][j] == 2){//2表示走过的路
			printf("*");
		}
		}
		printf("\n");
	}
	printf("\n\n");
}



//递归计算迷宫的路
void RunMazeRec(Position at)
{
	Position next;
	StackPush(&path, at);

	//一进来标记这个我走过了
	gMaze[at.x][at.y] = 2;
	PrintMaze();

	//为什么不需要在栈里记录，直接利用调用栈回溯
	if(IsExit(at)){
		//如果当前路径（path）小于之前的最小路径（min）,则当前路径为最短
		if(StackEmpty(&min) || StackSize(&path)<StackSize(&min)){
			StackCopy(&min, &path);
		}
		PrintPath(&path);
		printf("===========================================\n");

		//重新置为1
		gMaze[at.x][at.y] = 1;
		StackPop(&path);
		return;//会发生回溯
	}
	//根据左-->上-->右-->下 来尝试
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
	//重新置为1
	gMaze[at.x][at.y] = 1;
	StackPop(&path);
	return;//回溯
}


#if 0
//栈+循环计算迷宫的路
//递归和自己利用栈回溯的区别就是：递归尝试过得方向不会再走，目前循环不行
void RunMaze()
{
	//需要一个栈，实现回溯
	Stack stack;
	Position at;
	Position next;
	StackInit(&stack);
	at.x = gEntry.x;
	at.y = gEntry.y;
	
	while(1){
		//标记当前的位置我已经走过了
		gMaze[at.x][at.y] = 2;
		//在栈里记录当前位置，为以后的回溯做准备
		StackPush(&stack, at);

		if(IsExit(at))
		{
			PrintPath(&stack);
			return;
		}
		//根据左-->上-->右-->下 来尝试
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
	//四面楚歌，回溯
	StackPop(&stack);//这里pop的就是当前的at
	if(StackEmpty(&stack)){
		printf("没有出口\n");
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
	printf("最短路径长度是 %d\n",StackSize(&min));
	//RunMaze(gEntry);
}