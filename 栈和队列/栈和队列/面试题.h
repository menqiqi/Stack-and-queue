#pragma once

#include "Stack.h"

//1.实现一个栈，要求实现Push,Pop,Min的时间复杂度为O（1）
typedef struct MinStack
{
	Stack stackNormal;//普通栈
	Stack stackMin; //保存当前最小数
}MinStack;

//初始化
void MinStackInit(MinStack* pMS)
{
	StackInit(&(pMS->stackNormal));
	StackInit(&(pMS->stackMin));
}

//入栈
void MinStackPush(MinStack* pMS, StackDataType data)
{
	StackPush(&(pMS->stackNormal), data);
	if(StackEmpty(&(pMS->stackMin)))
	{
		StackPush(&(pMS->stackMin), data);
		return;
	}
	if(data < StackTop(&(pMS->stackMin)))
	{
		StackPush(&(pMS->stackMin), data);
	}
}

//出栈
void MinStackPop(MinStack* pMS)
{
	if(StackTop(&(pMS->stackMin)) == StackTop(&(pMS->stackNormal)))
	{                                                
		StackPop(&(pMS->stackMin));
	}
	StackPop(&(pMS->stackNormal));
}

StackDataType MinStackTop(const MinStack* pMS)
{
	return StackTop(&(pMS->stackNormal));
}

StackDataType MinStackMin(const MinStack* pMS)
{
	return StackTop(&(pMS->stackMin));
}

void TestMinStack()
{
	int i = 0;

	StackDataType number[] = {5,7,4,3,1,6,2};
	MinStack stack;

	MinStackInit(&stack);
	for(i=0; i<7; i++)
	{
		MinStackPush(&stack, number[i]);
		printf("Top = %d, Min = %d\n",MinStackTop(&stack), MinStackMin(&stack));
	}
	printf("\n");
	
	for(i=0; i<6; i++)
	{
		MinStackPop(&stack);
		printf("Top = %d, Min = %d\n",MinStackTop(&stack), MinStackMin(&stack));
	}
}


//2.使用两个栈实现一个队列
typedef struct Queues
{
	Stack stack1;
	Stack stack2;
}Queues;

//初始化
void QInit(Queues *pQS)
{
	StackInit(&(pQS->stack1));
	StackInit(&(pQS->stack2));
}

//入队列
void QPush(Queues *pQS, StackDataType data)
{
	StackPush(&(pQS->stack1), data);
}

//出队列(将栈1的数据移到栈2，栈1只管进，栈2只管出)
void QPop(Queues *pQS)
{
	StackDataType data;
	if(StackEmpty(&(pQS->stack2)))
	{
		while(! StackEmpty(&(pQS->stack1))){
	data = StackTop(&(pQS->stack1));
	StackPush(&(pQS->stack2), data);
	StackPop(&(pQS->stack1));
		}
	}
	StackPop(&(pQS->stack2));
}

StackDataType QSFront(Queues *pQS)
{
	//如果栈2为空，把栈1的数据倒过去
	StackDataType data;
	if(StackEmpty(&(pQS->stack2)))
	{
		while(! StackEmpty(&(pQS->stack1))){
	data = StackTop(&(pQS->stack1));
	StackPush(&(pQS->stack2), data);
	StackPop(&(pQS->stack1));
		}
	}
	return StackTop(&(pQS->stack2));
}

void TestQS()
{ 
	int i = 0;
	Queues qs;
	QInit(&qs);

	for(i=0; i<10; i++)
	{
		QPush(&qs, i);
	}
	for(i=0; i<10; i++)
	{
		printf("%d\n",QSFront(&qs));
		QPop(&qs);
	}
}

//3.使用两个队列实现一个栈
#include "Queue.h"

typedef struct QStack{
	Queue q1;
	Queue q2;
}QStack;

//初始化
void QStackInit(QStack *pQS)
{
	QueueInit(&(pQS->q1));
	QueueInit(&(pQS->q2));
}

//销毁
void QStackDestroy(QStack *pQS)
{
	QueueDestroy(&(pQS->q1));
	QueueDestroy(&(pQS->q2));
}

//增
void QStackPush(QStack *pQS, QDataType data)
{
	//往非空队列里插入，若两个都为空，则往第一个插入
	Queue* qEmpty = &(pQS->q1);
	Queue* qNoEmpty = &(pQS->q2);
	if(!IsEmpty(&(pQS->q1))){
		qEmpty = &(pQS->q2);
		qNoEmpty = &(pQS->q1);
	}
	QueuePush(qNoEmpty, data);
}

//删
void QStackPop(QStack *pQS)
{
	QDataType data;
	//从非空队列中move size-1 个数到空队列中，Pop剩下的一个
	Queue* qEmpty = &(pQS->q1);
	Queue* qNoEmpty = &(pQS->q2);
	if(!IsEmpty(&(pQS->q1))){
		qEmpty = &(pQS->q2);
		qNoEmpty = &(pQS->q1);
	}
	while(QueueSize(qNoEmpty) > 1){
	data = QueueTop(qNoEmpty);
	QueuePush(qEmpty, data);
	QueuePop(qNoEmpty);
	}
	QueuePop(qNoEmpty);
}

//查
QDataType QStackTop(QStack* pQS)
{
	QDataType data;
	QDataType ret;
	//从非空队列中move size-1 个数到空队列中，返回剩下的一个值，
	//把剩下的一个值也放到另一个队列中
	Queue* qEmpty = &(pQS->q1);
	Queue* qNoEmpty = &(pQS->q2);
	if(!IsEmpty(&(pQS->q1))){
		qEmpty = &(pQS->q2);
		qNoEmpty = &(pQS->q1);
	}
	while(QueueSize(qNoEmpty) > 1){
	data = QueueTop(qNoEmpty);
	QueuePush(qEmpty, data);
	QueuePop(qNoEmpty);
	}
	//只剩一个数据
	ret = QueueTop(qNoEmpty);
	QueuePop(qNoEmpty);
	QueuePush(qEmpty,ret);
	return ret;
}

void TestQStack()
{
	int i = 0;
	QStack stack;
	QStackInit(&stack);

	for(i=0; i<5; i++)
	{
		QStackPush(&stack,i);
		printf("压入了%d,Top = %d\n",i,QStackTop(&stack));
	}

	for(i=0; i<3; i++)
	{
		QStackPop(&stack);
		printf("Top = %d\n",QStackTop(&stack));
	}

	for(i=0; i<2; i++){
		QStackPush(&stack,i+10);
		printf("压入了%d, Top = %d\n",i+10,QStackTop(&stack));
	}
}

//4.元素出栈，入栈顺序的合法性
#include "Stack.h"

int IsValid(char in[], char out[], int size)
{
	int ii = 0;
	int io = 0;//分别为in,out的数组的下标
	Stack stack;
	StackInit(&stack);
	while(ii < size)
	{
		if(in[ii] != out[io]){
			if(!StackEmpty(&stack) && (StackTop(&stack)==out[io])){
				StackPop(&stack);
				io++;
			}
			else{
				StackPush(&stack,in[ii]);
				ii++;
			}
		}
		if(in[ii] == out[io])
		{
			ii++;
			io++;
		}
	}
	while(!StackEmpty(&stack))
	{
		if(StackTop(&stack) != out[io])
		{
			return 0;
		}
		io++;
		StackPop(&stack);
	}
	return 1;
}

void TestIsValid()
{
	char *in = "abcdefg";
	char *out1 = "decfbga";
	char *out2 = "fegdacb";
	char *out3 = "efdgbca";
	char *out4 = "cdbefag";

	printf("%s\n",IsValid(in,out1,strlen(in))?"合法":"不合法");
	printf("%s\n",IsValid(in,out2,strlen(in))?"合法":"不合法");
	printf("%s\n",IsValid(in,out3,strlen(in))?"合法":"不合法");
	printf("%s\n",IsValid(in,out4,strlen(in))?"合法":"不合法");
}

//5.一个数组实现两个栈（共享栈）
//两边往中间生长的方式
//typedef struct{
//	int *array;
//	int top1;
//	int top2;
//	int capacity;
//}TStack;
//
////初始化
//void TStackInit(TStack *pTS)
//{
//	pTS->capacity = 10;
//	pTS->array = (int*)malloc(sizeof(int)*pTS->capacity);
//	pTS->top1 = 0;
//	pTS->top2 = pTS->capacity-1;//不要越界
//}
//
//void TStackDestroy(TStack *pTS)
//{
//	free(pTS->array);
//}
//
//void ExpandIfRequired(TStack *pTS)//扩容
//{
//	int newCapacity;
//	int* newArray;
//	int i = 0;
//	int j = 0;
//	int k = 0;
//	if(pTS->top1 <= pTS->top2)
//	{
//		return;
//	}
//	newCapacity = pTS->capacity*2;
//	newArray = (int*)malloc(sizeof(int)*newCapacity);
//	assert(newArray);
//	//搬移数据
//
//	//搬移栈1的数据
//	for(i=0; i<pTS->top1; i++)
//	{
//		newArray[i] = pTS->array[i];
//	}
//
//	//搬移栈2的数据
//	//j [top1,capacity)栈2在老数组中的下标区间
//	for(j=pTS->top1; j<pTS->capacity; j++)
//	{
//		k = j + pTS->capacity;
//		newArray[k] = pTS->array[j];
//	}
//	pTS->top2 += pTS->capacity;
//	pTS->capacity = newCapacity;
//
//	//空间，下面两句的顺序不能交换
//	free(pTS->array);
//	pTS->array = newArray;
//}
//
////增
//void Push_1(TStack *pTS,int data)
//{
//	ExpandIfRequired(pTS);
//
//	pTS->array[pTS->top1] = data;
//	pTS->top1++;
//}
//
//void Push_2(TStack *pTS, int data)
//{
//	ExpandIfRequired(pTS);
//
//	pTS->array[pTS->top2] = data;
//	pTS->top2--;
//}
//
////删
//void Pop_1(TStack *pTS)
//{
//	pTS->top1--;
//}
//
//void Pop_2(TStack *pTS)
//{
//	pTS->top2++;
//}
//
////查
//int Top_1(TStack *pTS)
//{
//	return pTS->array[pTS->top1-1];
//}
//
//int Top_2(TStack *pTS)
//{
//	return pTS->array[pTS->top2+1];
//}
//
////返回数据的个数
//int size_1(TStack *pTS)
//{
//	return pTS->top1;
//}
//
//int size_2(TStack *pTS)
//{
//	return pTS->capacity-pTS->top2-1;//结合图
//}
//
//void TestTStack()
//{
//	TStack stack;
//	TStackInit(&stack);
//
//	Push_1(&stack,1);
//	Push_1(&stack,2);
//	Push_1(&stack,3);
//	Push_1(&stack,4);
//	Push_1(&stack,5);
//	Push_1(&stack,6);
//	Push_1(&stack,7);
//
//	Push_2(&stack,101);
//	Push_2(&stack,102);
//	Push_2(&stack,103);
//
//	//触发扩容
//	Push_2(&stack,104);
//	Push_2(&stack,105);
//
//}

//奇偶间隔的方式
typedef struct{
	int *array;
	int top1;
	int top2;
	int capacity;
}TStack;

//初始化
void TStackInit(TStack *pTS)
{
	pTS->capacity = 10;
	pTS->array = (int*)malloc(sizeof(int)*pTS->capacity);
	pTS->top1 = 0;
	pTS->top2 = 1;
}

//销毁
void TStackDestroy(TStack *pTS)
{
	free(pTS->array);
}

//扩容
void ExpandIfRequired(TStack *pTS)
{
	int newCapacity;
	int *newArray;
	int i = 0;
	int j = 0;
	//不需要扩容的条件
	if((pTS->top1<pTS->capacity) || (pTS->top2<pTS->capacity))
	{
		return;
	}
	//扩容过程
	newCapacity = pTS->capacity*2;
	newArray = (int*)malloc(sizeof(int)*newCapacity);
	assert(newCapacity);
	//搬移数据

	//搬移栈1的数据
	for(i=0; i<pTS->top1; i=i+2)
	{
		newArray[i] = pTS->array[i];
	}
	//搬移栈2的数据
	for(j=1; j<pTS->top2; j=j+2)
	{
		newArray[j] = pTS->array[j];
	}
	pTS->capacity = newCapacity;
	//空间，下面两句不能调换
	free(pTS->array);
	pTS->array = newArray;
}

//增
void Push_1(TStack *pTS, int data)
{
	ExpandIfRequired(pTS);

	pTS->array[pTS->top1] = data;
	pTS->top1 = pTS->top1+2;
}

void Push_2(TStack *pTS, int data)
{
	ExpandIfRequired(pTS);

	pTS->array[pTS->top2] = data;
	pTS->top2 = pTS->top2+2;
}

//删
void Pop_1(TStack *pTS, int data)
{
	pTS->top1 = pTS->top1-2;
}

void Pop_2(TStack *pTS, int data)
{
	pTS->top2 = pTS->top2-2;
}

//查
int Top_1(TStack *pTS)
{
	return pTS->array[pTS->top1-2];
}

int Top_2(TStack *pTS)
{
	return pTS->array[pTS->top1-2];
} 

//返回数据个数
int size_1(TStack *pTS)
{
	return (pTS->top1)/2;
}

int size_2(TStack *pTS)
{
	return (pTS->top2)/2;
}

void TestTStack()
{
	TStack stack;
	TStackInit(&stack);

	Push_1(&stack,1);
	Push_1(&stack,2);
	Push_1(&stack,3);
	Push_1(&stack,4);
	Push_1(&stack,5);
	Push_1(&stack,6);
	Push_1(&stack,7);

	Push_2(&stack,101);
	Push_2(&stack,102);
	Push_2(&stack,103);

	//触发扩容
	Push_2(&stack,104);
	Push_2(&stack,105);

}