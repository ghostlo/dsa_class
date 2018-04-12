#pragma once

#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0

typedef int QElemType;
typedef int Status;

typedef struct QNode {
	QElemType datax;
	QElemType datay;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct {       //定义链队列
	QueuePtr front;   //队头指针
	QueuePtr rear;	  //队尾指针
}LinkQueue;

Status InitQueue(LinkQueue &Q)
{
	Q.front = (QNode *)malloc(sizeof(QNode));
	if (!Q.front)
		return ERROR;
	Q.front->next = NULL;
	Q.rear = Q.front;
	return OK;
}

Status DestroyQueue(LinkQueue &Q)
{
	while (Q.front) {
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

int QueueLength(LinkQueue Q)
{
	QueuePtr p;
	int len = 0;
	p = Q.front->next;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

Status EnQueue(LinkQueue &Q, QElemType x, QElemType y)
{
	QueuePtr p;
	p = (QNode *)malloc(sizeof(QNode));   //生成新的结点
	if (!p)
		return ERROR;
	p->datax = x;
	p->datay = y;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

Status DeQueue(LinkQueue &Q)
{
	QueuePtr p;
	p = Q.front->next;
	Q.front->next = p->next;
	free(p);
	p = NULL;
	return OK;
}