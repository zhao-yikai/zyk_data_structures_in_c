//
// Created by 趙熠楷 on 3/27/25.
//

#ifndef LINKED_QUEUES_H
#define LINKED_QUEUES_H

#include <stdbool.h>
#include <float.h>

#define LINKED_QUEUE_ERROR (-DBL_MAX)

typedef struct LinkedQueueHead * LinkedQueue;
typedef double ElementType;

// 生成空队列
LinkedQueue LinkedQueue_Create(void);

// 将元素X插入到队列Q
void LinkedQueue_Enqueue(LinkedQueue Q, ElementType X);

// 判断队列Q是否为空， 若是返回true; 否则返回false
bool LinkedQueue_IsEmpty(LinkedQueue Q);

// 删除并返回队列头元素。 若队列为空， 返回错误信息； 否则将队列头元素数据从队列中删除并返回。
ElementType LinkedQueue_Dequeue(LinkedQueue Q);

#endif //LINKED_QUEUES_H
