#pragma once

#include "Stack.h"

//1.ʵ��һ��ջ��Ҫ��ʵ��Push,Pop,Min��ʱ�临�Ӷ�ΪO��1��
typedef struct MinStack
{
	Stack stackNormal;//��ͨջ
	Stack stackMin; //���浱ǰ��С��
}MinStack;

//��ʼ��
void MinStackInit(MinStack* pMS)
{
	StackInit(&(pMS->stackNormal));
	StackInit(&(pMS->stackMin));
}

//��ջ
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

//��ջ
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


//2.ʹ������ջʵ��һ������
typedef struct Queues
{
	Stack stack1;
	Stack stack2;
}Queues;

//��ʼ��
void QInit(Queues *pQS)
{
	StackInit(&(pQS->stack1));
	StackInit(&(pQS->stack2));
}

//�����
void QPush(Queues *pQS, StackDataType data)
{
	StackPush(&(pQS->stack1), data);
}

//������(��ջ1�������Ƶ�ջ2��ջ1ֻ�ܽ���ջ2ֻ�ܳ�)
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
	//���ջ2Ϊ�գ���ջ1�����ݵ���ȥ
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

//3.ʹ����������ʵ��һ��ջ
#include "Queue.h"

typedef struct QStack{
	Queue q1;
	Queue q2;
}QStack;

//��ʼ��
void QStackInit(QStack *pQS)
{
	QueueInit(&(pQS->q1));
	QueueInit(&(pQS->q2));
}

//����
void QStackDestroy(QStack *pQS)
{
	QueueDestroy(&(pQS->q1));
	QueueDestroy(&(pQS->q2));
}

//��
void QStackPush(QStack *pQS, QDataType data)
{
	//���ǿն�������룬��������Ϊ�գ�������һ������
	Queue* qEmpty = &(pQS->q1);
	Queue* qNoEmpty = &(pQS->q2);
	if(!IsEmpty(&(pQS->q1))){
		qEmpty = &(pQS->q2);
		qNoEmpty = &(pQS->q1);
	}
	QueuePush(qNoEmpty, data);
}

//ɾ
void QStackPop(QStack *pQS)
{
	QDataType data;
	//�ӷǿն�����move size-1 �������ն����У�Popʣ�µ�һ��
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

//��
QDataType QStackTop(QStack* pQS)
{
	QDataType data;
	QDataType ret;
	//�ӷǿն�����move size-1 �������ն����У�����ʣ�µ�һ��ֵ��
	//��ʣ�µ�һ��ֵҲ�ŵ���һ��������
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
	//ֻʣһ������
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
		printf("ѹ����%d,Top = %d\n",i,QStackTop(&stack));
	}

	for(i=0; i<3; i++)
	{
		QStackPop(&stack);
		printf("Top = %d\n",QStackTop(&stack));
	}

	for(i=0; i<2; i++){
		QStackPush(&stack,i+10);
		printf("ѹ����%d, Top = %d\n",i+10,QStackTop(&stack));
	}
}

//4.Ԫ�س�ջ����ջ˳��ĺϷ���
#include "Stack.h"

int IsValid(char in[], char out[], int size)
{
	int ii = 0;
	int io = 0;//�ֱ�Ϊin,out��������±�
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

	printf("%s\n",IsValid(in,out1,strlen(in))?"�Ϸ�":"���Ϸ�");
	printf("%s\n",IsValid(in,out2,strlen(in))?"�Ϸ�":"���Ϸ�");
	printf("%s\n",IsValid(in,out3,strlen(in))?"�Ϸ�":"���Ϸ�");
	printf("%s\n",IsValid(in,out4,strlen(in))?"�Ϸ�":"���Ϸ�");
}

//5.һ������ʵ������ջ������ջ��
//�������м������ķ�ʽ
//typedef struct{
//	int *array;
//	int top1;
//	int top2;
//	int capacity;
//}TStack;
//
////��ʼ��
//void TStackInit(TStack *pTS)
//{
//	pTS->capacity = 10;
//	pTS->array = (int*)malloc(sizeof(int)*pTS->capacity);
//	pTS->top1 = 0;
//	pTS->top2 = pTS->capacity-1;//��ҪԽ��
//}
//
//void TStackDestroy(TStack *pTS)
//{
//	free(pTS->array);
//}
//
//void ExpandIfRequired(TStack *pTS)//����
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
//	//��������
//
//	//����ջ1������
//	for(i=0; i<pTS->top1; i++)
//	{
//		newArray[i] = pTS->array[i];
//	}
//
//	//����ջ2������
//	//j [top1,capacity)ջ2���������е��±�����
//	for(j=pTS->top1; j<pTS->capacity; j++)
//	{
//		k = j + pTS->capacity;
//		newArray[k] = pTS->array[j];
//	}
//	pTS->top2 += pTS->capacity;
//	pTS->capacity = newCapacity;
//
//	//�ռ䣬���������˳���ܽ���
//	free(pTS->array);
//	pTS->array = newArray;
//}
//
////��
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
////ɾ
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
////��
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
////�������ݵĸ���
//int size_1(TStack *pTS)
//{
//	return pTS->top1;
//}
//
//int size_2(TStack *pTS)
//{
//	return pTS->capacity-pTS->top2-1;//���ͼ
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
//	//��������
//	Push_2(&stack,104);
//	Push_2(&stack,105);
//
//}

//��ż����ķ�ʽ
typedef struct{
	int *array;
	int top1;
	int top2;
	int capacity;
}TStack;

//��ʼ��
void TStackInit(TStack *pTS)
{
	pTS->capacity = 10;
	pTS->array = (int*)malloc(sizeof(int)*pTS->capacity);
	pTS->top1 = 0;
	pTS->top2 = 1;
}

//����
void TStackDestroy(TStack *pTS)
{
	free(pTS->array);
}

//����
void ExpandIfRequired(TStack *pTS)
{
	int newCapacity;
	int *newArray;
	int i = 0;
	int j = 0;
	//����Ҫ���ݵ�����
	if((pTS->top1<pTS->capacity) || (pTS->top2<pTS->capacity))
	{
		return;
	}
	//���ݹ���
	newCapacity = pTS->capacity*2;
	newArray = (int*)malloc(sizeof(int)*newCapacity);
	assert(newCapacity);
	//��������

	//����ջ1������
	for(i=0; i<pTS->top1; i=i+2)
	{
		newArray[i] = pTS->array[i];
	}
	//����ջ2������
	for(j=1; j<pTS->top2; j=j+2)
	{
		newArray[j] = pTS->array[j];
	}
	pTS->capacity = newCapacity;
	//�ռ䣬�������䲻�ܵ���
	free(pTS->array);
	pTS->array = newArray;
}

//��
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

//ɾ
void Pop_1(TStack *pTS, int data)
{
	pTS->top1 = pTS->top1-2;
}

void Pop_2(TStack *pTS, int data)
{
	pTS->top2 = pTS->top2-2;
}

//��
int Top_1(TStack *pTS)
{
	return pTS->array[pTS->top1-2];
}

int Top_2(TStack *pTS)
{
	return pTS->array[pTS->top1-2];
} 

//�������ݸ���
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

	//��������
	Push_2(&stack,104);
	Push_2(&stack,105);

}