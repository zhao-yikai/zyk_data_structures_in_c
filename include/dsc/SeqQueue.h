/*
    SeqQueue.h
    Functions of Sequential Queues
    Created By YikaiSays on Mar 28 2025
*/

#ifndef SEQUENTIAL_QUEUES_H
#define SEQUENTIAL_QUEUES_H

#include "Common.h"  // 统一类型定义

#define SEQ_QUEUE_ERROR DSC_ERROR

// ElementType 现在由 Common.h 统一定义

typedef struct SeqQueueNode * SeqQueueNodePtr;
typedef SeqQueueNodePtr SeqQueue;

// 生成空队列， 其最大长度为 MaxSize
SeqQueue SeqQueue_Create(int MaxSize);

// 判断队列Q是否已满。 若是返回true, 否则返回false。
bool SeqQueue_IsFull(SeqQueue Q);

// 将元素X压入队列Q。 若队列已满， 返回false; 否则将元素X插入到队列Q并返回true
bool SeqQueue_Enqueue(SeqQueue Q, ElementType X);

// 判断队列Q是否为空， 若是返回true; 否则返回false
bool SeqQueue_IsEmpty(SeqQueue Q);

// 删除并返回队列头元素。 若队列为空， 返回错误信息； 否则将队列头元素数据从队列中删除并返回。
ElementType SeqQueue_Dequeue(SeqQueue Q);

// 队列销毁操作
void SeqQueue_Destroy(SeqQueue Q);

#endif //SEQUENTIAL_QUEUES_H
