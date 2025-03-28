/*
    SeqQueue.c
    Functions of Sequential Queues
    Created By YikaiSays on Mar 28 2025
*/

#include "SeqQueue.h"

#include <stdio.h>
#include <stdlib.h>

typedef int Position;

struct SeqQueueNode {
    ElementType *Data;
    Position Front, Rear;
    int MaxSize;
};

// 生成空队列， 其最大长度为 MaxSize
SeqQueue SeqQueue_Create(int MaxSize) {
    SeqQueue Q = malloc(sizeof (struct SeqQueueNode));
    Q->Data = malloc(MaxSize * sizeof (ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

bool SeqQueue_IsFull(SeqQueue Q) {
    bool isfull = false;
    if ((Q->Rear + 1) % Q->MaxSize == Q->Front)
        isfull = true;
    return isfull;
}

// 将元素X压入队列Q。 若队列已满， 返回false; 否则将元素X插入到队列Q并返回true
bool SeqQueue_Enqueue(SeqQueue Q, ElementType X) {
    bool ret = false;
    if (!SeqQueue_IsFull(Q)) {
        Q->Rear = (Q->Rear + 1) % Q->MaxSize;
        Q->Data[Q->Rear] = X;
        ret = true;
    }
    return ret;
}

// 判断队列Q是否为空， 若是返回true; 否则返回false
bool SeqQueue_IsEmpty(SeqQueue Q) {
    bool ret = false;
    if (Q->Rear == Q->Front)
        ret = true;
    return ret;
}

// 删除并返回队列头元素。 若队列为空， 返回错误信息； 否则将队列头元素数据从队列中删除并返回。
ElementType SeqQueue_Dequeue(SeqQueue Q) {
    ElementType Dequeued = SEQ_QUEUE_ERROR;
    if (!SeqQueue_IsEmpty(Q)) {
        Q->Front = (Q->Front + 1) % Q->MaxSize;
        Dequeued = Q->Data[Q->Front];
    }
    return Dequeued;
}

