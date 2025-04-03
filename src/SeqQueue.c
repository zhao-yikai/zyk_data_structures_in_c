/*
    SeqQueue.c
    Functions of Sequential Queues
    Created By YikaiSays on Mar 28 2025
*/

#include <SeqQueue.h>
#include <stdlib.h>

#include "Warn.h"

typedef int Position; // DeepSeek: 建议使用无符号类型（如size_t）避免负数

// 顺序队列结构体定义
struct SeqQueueNode {
    ElementType *Data; // 存储元素的动态数组
    Position Front; // 队首指针（指向队首元素的前一个位置）
    Position Rear; // 队尾指针（指向最后一个元素）
    int MaxSize; // 队列最大容量
};


// SeqQueue SeqQueue_Create(int MaxSize) {
//     SeqQueue Q = malloc(sizeof(struct SeqQueueNode));
//     // DeepSeek: 高危-未检查malloc返回值（可能返回NULL）
//     // DeepSeek: 未校验MaxSize有效性（应>0）
//
//     Q->Data = malloc(MaxSize * sizeof(ElementType));
//     // DeepSeek: 高危-未检查malloc返回值
//     // DeepSeek: 实际可用容量为MaxSize-1（循环队列特性）
//
//     Q->Front = Q->Rear = 0;  // 初始化空队列
//     Q->MaxSize = MaxSize;
//     return Q;  // DeepSeek: 当malloc失败时返回部分初始化的结构体
// }

// Apr 3 重写

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


// ElementType SeqQueue_Dequeue(SeqQueue Q) {
//     ElementType Dequeued = SEQ_QUEUE_ERROR;
//     // DeepSeek: 未检查Q有效性（嵌套调用风险）
//     if (!SeqQueue_IsEmpty(Q)) {
//         Q->Front = (Q->Front + 1) % Q->MaxSize; // 移动队首指针
//         Dequeued = Q->Data[Q->Front]; // 取出新队首元素
//     }
//     // DeepSeek: 1.无法区分"空队列"和"无效队列指针"
//     // DeepSeek: 2.建议添加错误日志输出
//     return Dequeued;
// }

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
