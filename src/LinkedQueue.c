//
// Created by 趙熠楷 on 3/27/25.
//

#include "LinkedQueue.h"
#include "Warn.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct LinkedQueueNode * LinkedQueueNodePtr;
struct LinkedQueueNode {
    ElementType Data;
    LinkedQueueNodePtr Next;
};
typedef LinkedQueueNodePtr LinkedNode;

typedef LinkedQueueNodePtr Position;
struct LinkedQueueHead {
    Position Front, Rear;
};

// 生成空队列
LinkedQueue LinkedQueue_Create() {
    LinkedQueue Q = malloc(sizeof(struct LinkedQueueHead));
    Q->Front = NULL;
    Q->Rear = NULL;
    return Q;
}

// 判断队列Q是否为空， 若是返回true; 否则返回false
bool LinkedQueue_IsEmpty(LinkedQueue Q) {
    bool IsEmpty = false;
    if (Q->Front == NULL)
        IsEmpty = true;
    return IsEmpty;
}

// 将元素X插入到队列Q
// Mar 28 修改解决上一版本中存在的当队列不为空时导致的遍历队列的时间复杂度过高的问题， 改为使用Rear指针直接插入
void LinkedQueue_Enqueue(LinkedQueue Q, ElementType X) {
    LinkedNode N = malloc(sizeof(struct LinkedQueueNode));
    if (!N) {
        Warn("LinkedQueue_Enqueue: MALLOC ERROR!");
        return;
    }
    N->Data = X;
    N->Next = NULL;
    if (LinkedQueue_IsEmpty(Q)) {
        Q->Front = N;
        Q->Rear = N;
    } else {
        Q->Rear->Next = N;
        Q->Rear = N;
    }
}

// 删除并返回队列头元素。 若队列为空， 返回错误信息； 否则将队列头元素数据从队列中删除并返回。
ElementType LinkedQueue_Dequeue(LinkedQueue Q) {
    ElementType Dequeue = LINKED_QUEUE_ERROR;
    if (!LinkedQueue_IsEmpty(Q)) {
        if (Q->Front == Q->Rear) {
            Dequeue = Q->Front->Data;
            free(Q->Front);
            Q->Rear = Q->Front = NULL;
        } else {
            LinkedNode tmp = Q->Front;
            Dequeue = tmp->Data;
            Q->Front = Q->Front->Next;
            free(tmp);
        }
    } else {
        Warn("LinkedQueue_Dequeue: EMPTY QUEUE!");
    }
    return Dequeue;
}

