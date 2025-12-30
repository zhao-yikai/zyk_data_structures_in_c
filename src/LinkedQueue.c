/*
    LinkedQueue.c
    Functions of Linked Queues
    Created By YikaiSays on Mar 28 2025
*/

#include <LinkedQueue.h>
#include <Warn.h>
#include <stdio.h>
#include <stdlib.h>

// 队列节点结构定义
typedef struct LinkedQueueNode * LinkedQueueNodePtr;
struct LinkedQueueNode {
    ElementType Data;         // 节点存储的数据
    LinkedQueueNodePtr Next;   // 指向下一个节点的指针
};

// 类型别名定义（建议使用更清晰的命名）
typedef LinkedQueueNodePtr LinkedNode;  // DeepSeek: 类型别名冗余，建议直接使用LinkedQueueNodePtr
typedef LinkedQueueNodePtr Position;    // DeepSeek: Position与LinkedQueueNodePtr重复定义

// 队列头结构定义
struct LinkedQueueHead {
    Position Front;  // 队首指针
    Position Rear;   // 队尾指针
};

/*
 * 创建空队列
 * 返回值: 队列头指针
 */
LinkedQueue LinkedQueue_Create(void) {
    LinkedQueue Q = malloc(sizeof(struct LinkedQueueHead));
    // DeepSeek: 未检查malloc返回值，可能返回NULL指针
    Q->Front = NULL;  // 初始化空队列
    Q->Rear = NULL;
    return Q;
}

/*
 * 判断队列是否为空
 * 参数: Q - 队列指针
 * 返回值: 空队列返回true，否则false
 */
bool LinkedQueue_IsEmpty(LinkedQueue Q) {
    bool IsEmpty = false;
    // DeepSeek: 未检查Q是否为NULL，可能导致空指针解引用
    if (Q->Front == NULL)  // 通过队首指针判断空队列
        IsEmpty = true;
    return IsEmpty;
}

/*
 * 元素入队操作
 * 参数: Q - 队列指针，X - 入队元素
 * 时间复杂度: O(1) （通过尾指针直接插入）
 */
void LinkedQueue_Enqueue(LinkedQueue Q, ElementType X) {
    LinkedNode N = malloc(sizeof(struct LinkedQueueNode));
    if (!N) {
        Warn("LinkedQueue_Enqueue: MALLOC ERROR!");
        return;
    }
    N->Data = X;
    N->Next = NULL;  // 新节点作为尾节点

    // 队列为空时的处理
    if (LinkedQueue_IsEmpty(Q)) {  // DeepSeek: 嵌套调用存在空指针风险
        Q->Front = N;
        Q->Rear = N;
    }
    // 队列非空时的处理
    else {
        Q->Rear->Next = N;  // 将新节点链接到队尾
        Q->Rear = N;        // 更新尾指针
    }
}

/*
 * 元素出队操作
 * 参数: Q - 队列指针
 * 返回值: 成功返回队首元素，失败返回错误码
 */
ElementType LinkedQueue_Dequeue(LinkedQueue Q) {
    ElementType Dequeue = LINKED_QUEUE_ERROR;

    // 检查队列是否为空
    if (!LinkedQueue_IsEmpty(Q)) {  // DeepSeek: 未检查Q有效性
        // 处理队列只有一个元素的情况
        if (Q->Front == Q->Rear) {
            Dequeue = Q->Front->Data;
            free(Q->Front);     // 释放唯一节点
            Q->Front = NULL;    // 重置指针
            Q->Rear = NULL;
        }
        // 处理多个元素的情况
        else {
            LinkedNode tmp = Q->Front;      // 保存原队首节点
            Dequeue = tmp->Data;
            Q->Front = Q->Front->Next;      // 更新队首指针
            free(tmp);                      // 释放原队首节点
        }
    } else {
        Warn("LinkedQueue_Dequeue: EMPTY QUEUE!");
    }
    return Dequeue;
}

// DeepSeek: 缺少队列销毁函数，会导致内存泄漏
/*
void LinkedQueue_Destroy(LinkedQueue Q) {
    while (!LinkedQueue_IsEmpty(Q)) {
        LinkedQueue_Dequeue(Q);
    }
    free(Q);
}
*/

// DeepSeek: 建议添加遍历函数
/*
void LinkedQueue_Traverse(LinkedQueue Q) {
    Position p = Q->Front;
    while (p) {
        printf("%d ", p->Data);
        p = p->Next;
    }
}
*/

// DeepSeek: 建议添加队列长度统计函数
/*
int LinkedQueue_Length(LinkedQueue Q) {
    if (!Q) return -1;
    int count = 0;
    Position p = Q->Front;
    while (p) {
        count++;
        p = p->Next;
    }
    return count;
}
*/
