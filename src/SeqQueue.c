/*
    SeqQueue.c
    Functions of Sequential Queues
    Created By YikaiSays on Apr 3 2025
*/

#include <SeqQueue.h>
#include <stdlib.h>

#include "Warn.h"

typedef size_t Position;

// 顺序队列结构体定义
struct SeqQueueNode {
    ElementType *Data; // 存储元素的动态数组
    Position Front; // 队首指针（指向队首元素的前一个位置）
    Position Rear; // 队尾指针（指向最后一个元素）
    int MaxSize; // 队列最大容量
};


/*
 * 创建空队列
 * 参数: MaxSize - 队列容量
 * 返回值: 队列指针
 */
SeqQueue SeqQueue_Create(int MaxSize) {
    if (MaxSize <= 0) {
        Warn("SeqQueue_Create: Invalid MaxSize!");
        return NULL;
    }
    SeqQueue Q = malloc(sizeof(struct SeqQueueNode));
    if (!Q) {
        Warn("SeqQueue_Create: Memory Allocation Fault!");
        return NULL;
    }
    Q->Data = malloc(MaxSize * sizeof(ElementType));
    Q->MaxSize = MaxSize;
    Q->Front = Q->Rear = 0;
    return Q;
}


/*
 * 判断队列是否已满
 * 参数: Q - 队列指针
 * 返回值: 队列满返回true
 * Apr 3 重构
 */
bool SeqQueue_IsFull(SeqQueue Q) {
    if (!Q) {
        // 避免空指针问题
        Warn("SeqQueue_isFull: Invalid SeqQueue!");
        return true;
    }
    if ((Q->Rear + 1) % Q->MaxSize == Q->Front)
        return true;
    return false;
}


/*
 * 元素入队操作
 * 参数: Q - 队列指针，X - 入队元素
 * 返回值: 成功返回true
 * Apr 3 重构
 */
bool SeqQueue_Enqueue(SeqQueue Q, ElementType X) {
    if (!Q) {
        // 判断队列指针是否为空
        Warn("SeqQueue_Enqueue: Invalid SeqQueue!");
        return false;
    }
    if (SeqQueue_IsFull(Q)) {
        // 判断队列是否已满
        Warn("SeqQueue_Enqueue: Full Queue!");
        return false;
    }
    Q->Rear = (Q->Rear + 1) % Q->MaxSize; // 先移动队尾指针
    Q->Data[Q->Rear] = X; // 存储数据到新的队尾位置
    return true;
}


/*
 * 判断队列是否为空
 * 参数: Q - 队列指针
 * 返回值: 空队列返回true
 * Apr 3 重构
 */
bool SeqQueue_IsEmpty(SeqQueue Q) {
    if (!Q) {
        // 判断队列指针是否为空
        Warn("SeqQueue_IsEmpty: Invalid SeqQueue!");
        return true;
    }
    if (Q->Front == Q->Rear) // 判断队列是否为空
        return true;

    return false;
}


/*
 * 元素出队操作
 * 参数: Q - 队列指针
 * 返回值: 队首元素或错误码
 * Ape 3 重构
 */
ElementType SeqQueue_Dequeue(SeqQueue Q) {
    if (!Q) {
        Warn("SeqQueue_Dequeue: Invalid SeqQueue!");
        return SEQ_QUEUE_ERROR;
    }
    if (SeqQueue_IsEmpty(Q)) {
        Warn("SeqQueue_Dequeue: Empty SeqQueue!");
        return SEQ_QUEUE_ERROR;
    }
    return Q->Data[Q->Front = (Q->Front + 1) % Q->MaxSize];
}


/*
 * 队列销毁操作
 * 参数: Q - 队列指针
 * 返回值: 无
 */
void SeqQueue_Destroy(SeqQueue Q) {
    if (Q) {
        free(Q->Data);
        free(Q);
    }
}
