/*
    LinkedQueue.c
    Functions of Linked Queues
    Created By YikaiSays on Mar 28 2025
*/

#ifndef LINKED_QUEUES_H
#define LINKED_QUEUES_H

#include "Common.h"  // 统一类型定义

#define LINKED_QUEUE_ERROR DSC_ERROR

// ElementType 现在由 Common.h 统一定义

typedef struct LinkedQueueHead * LinkedQueue;

// 生成空队列
LinkedQueue LinkedQueue_Create(void);

// 将元素X插入到队列Q
void LinkedQueue_Enqueue(LinkedQueue Q, ElementType X);

// 判断队列Q是否为空， 若是返回true; 否则返回false
bool LinkedQueue_IsEmpty(LinkedQueue Q);

// 删除并返回队列头元素。 若队列为空， 返回错误信息； 否则将队列头元素数据从队列中删除并返回。
ElementType LinkedQueue_Dequeue(LinkedQueue Q);

#endif //LINKED_QUEUES_H
