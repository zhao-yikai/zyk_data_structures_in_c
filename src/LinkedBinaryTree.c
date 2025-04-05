/*
    LinkedBinaryTree.c
    Functions of Linked Binary Trees
    Created By YikaiSays on Apr 4 2025
*/

#define QUEUE_ERROR NULL    /* 队列操作错误返回值定义 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LinkedBinaryTree.h"
#include "Warn.h"

/*━━━━━━━━━━━━━━━━━━━━━ 队列辅助数据结构 ━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @struct QFTNode
 * @brief 队列节点结构定义
 *
 * @var Data 存储的二叉树节点指针
 * @var Next 指向下一个队列节点的指针
 */

typedef struct QFTNode * QFTNodePtr;
struct QFTNode {
    LinkedBinaryTree Data;         // 节点存储的数据
    QFTNodePtr Next;   // 指向下一个节点的指针
};
typedef QFTNodePtr QFTNode;
typedef QFTNodePtr LinkedNode;  // DeepSeek: 类型别名冗余，建议直接使用LinkedQueueNodePtr
typedef QFTNodePtr Position;    // DeepSeek: Position与LinkedQueueNodePtr重复定义

/**
 * @struct QFTHead
 * @brief 队列头结构定义
 *
 * @var Front 指向队列首元素的指针
 * @var Rear  指向队列尾元素的指针
 */
typedef struct QFTHead * QFT;
struct QFTHead {
    Position Front;  // 队首指针
    Position Rear;   // 队尾指针
};


/*━━━━━━━━━━━━━━━━━━━━━ 队列操作实现 ━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @brief 创建并初始化空队列
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * @return QFT 成功返回队列指针，内存分配失败返回NULL
 */
QFT QFT_Create() {
    QFT Q = malloc(sizeof(struct QFTHead));
    // DeepSeek: 未检查malloc返回值，可能返回NULL指针
    Q->Front = NULL;  // 初始化空队列
    Q->Rear = NULL;
    return Q;
}

/**
 * @brief 判断队列是否为空
 *
 * 时间复杂度: O(1)
 *
 * @param Q 队列指针
 * @return bool true-队列为空或无效，false-队列非空
 */
bool QFT_IsEmpty(QFT Q) {
    if (!Q) {
        Warn("Invalid Queue!");
        return false;
    }
    if (Q->Front == NULL)  // 通过队首指针判断空队列
        return true;
    return false;
}

/**
 * @brief 元素入队操作
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)（单次分配）
 *
 * @param Q 队列指针
 * @param X 要入队的二叉树节点
 */
void QFT_Enqueue(QFT Q, LinkedBinaryTree X) {
    if (!Q) {
        Warn("Invalid Queue!");
        return;
    }
    QFTNode N = malloc(sizeof(struct QFTNode));
    if (!N) {
        Warn("MALLOC ERROR!");
        return;
    }
    N->Data = X;
    N->Next = NULL;  // 新节点作为尾节点

    // 队列为空时的处理
    if (QFT_IsEmpty(Q)) {  // DeepSeek: 嵌套调用存在空指针风险
        Q->Front = N;
        Q->Rear = N;
    }
    // 队列非空时的处理
    else {
        Q->Rear->Next = N;  // 将新节点链接到队尾
        Q->Rear = N;        // 更新尾指针
    }
}

/**
 * @brief 元素出队操作
 *
 * 时间复杂度: O(1)
 *
 * @param Q 队列指针
 * @return LinkedBinaryTree 成功返回队首元素，失败返回QUEUE_ERROR
 */
LinkedBinaryTree QFT_Dequeue(QFT Q) {
    LinkedBinaryTree Dequeue = QUEUE_ERROR;
    if (!Q) {
        Warn("Invalid Queue!");
        return QUEUE_ERROR;
    }
    // 检查队列是否为空
    if (!QFT_IsEmpty(Q)) {  // DeepSeek: 未检查Q有效性
        // 处理队列只有一个元素的情况
        if (Q->Front == Q->Rear) {
            Dequeue = Q->Front->Data;
            free(Q->Front);     // 释放唯一节点
            Q->Front = NULL;    // 重置指针
            Q->Rear = NULL;
        }
        // 处理多个元素的情况
        else {
            QFTNode tmp = Q->Front;      // 保存原队首节点
            Dequeue = tmp->Data;
            Q->Front = Q->Front->Next;      // 更新队首指针
            free(tmp);                      // 释放原队首节点
        }
    } else {
        Warn("LinkedQueue_Dequeue: EMPTY QUEUE!");
    }
    return Dequeue;
}


/*━━━━━━━━━━━━━━━━━━━━━ 二叉树操作实现 ━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @struct LinkedBinaryTreeNode
 * @brief 链表式二叉树节点结构定义
 *
 * @param Data  节点存储的数据元素
 * @param Left  左子树指针（指向左孩子节点）
 * @param Right 右子树指针（指向右孩子节点）
 */
struct LinkedBinaryTreeNode {
    ElementType Data;
    LinkedBinaryTreePtr Left;
    LinkedBinaryTreePtr Right;
};

/**
 * @brief 创建基础二叉树节点
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * @return LinkedBinaryTree 成功返回节点指针，失败返回NULL
 */
LinkedBinaryTree LinkedBinaryTree_Create() {
    LinkedBinaryTree LBT = malloc(sizeof(struct LinkedBinaryTreeNode));
    if (!LBT) {
        Warn("LinkedBinaryTree_Create: Memory Allocation Fault!");
        return NULL;
    }
    LBT->Left = LBT->Right = NULL;
    return LBT;
}

/**
 * @brief 层序构建完整二叉树
 *
 * 输入规范:
 * 1. 输入序列应当遵循完全二叉树层序格式
 * 2. 使用NoInfo(0)表示空节点
 * 3. 输入结束需要额外输入EOF标志
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
 *
 * @return LinkedBinaryTree 成功返回根节点指针，失败返回NULL
 */
LinkedBinaryTree LinkedBinaryTree_LevelOrderCreate(void) {
    ElementType Data;
    QFT Q = QFT_Create();

    scanf("%lf", &Data);
    if (Data == NoInfo) {
        return NULL;
    }
    LinkedBinaryTree LBT = LinkedBinaryTree_Create();
    if (!LBT) // 这里不需要写错误日志了， 调用的LinkedBinaryTree_CreateEmpty()会输出错误日志
        return NULL;
    LBT->Data = Data;
    QFT_Enqueue(Q, LBT);

    while (!QFT_IsEmpty(Q)) {
        LinkedBinaryTree T = QFT_Dequeue(Q);

        // 读入左孩子
        scanf("%lf", &Data);
        if (Data == NoInfo)
            T->Left = NULL;
        else {
            T->Left = LinkedBinaryTree_Create();
            if (!T->Left)
                return NULL;
            T->Left->Data = Data;
            QFT_Enqueue(Q, T->Left);
        }

        // 读入右孩子
        scanf("%lf", &Data);
        if (Data == NoInfo)
            T->Right = NULL;
        else {
            T->Right = LinkedBinaryTree_Create();
            if (!T->Right)
                return NULL;
            T->Right->Data = Data;
            QFT_Enqueue(Q, T->Right);
        }
    }
    return LBT;
}

bool LinkedBinaryTree_isEmpty(LinkedBinaryTree LBT) {
    if (!LBT) {
        Warn("LinkedBinaryTree_isEmpty: Invalid LinkedBinaryTree!");
        return true;
    }
    if (LBT->Left == NULL && LBT->Right == NULL)
        return true;
    return false;
}


/*━━━━━━━━━━━━━━━━━━━━━ 遍历算法实现 ━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @brief 递归中序遍历实现
 *
 * 算法特性:
 * - 时间复杂度: O(n)
 * - 空间复杂度: O(h) h为树高
 *
 * @param LBT   要遍历的二叉树根节点
 * @param visit 访问回调函数，原型：ElementType func(LinkedBinaryTree)
 */
void LinkedBinaryTree_InOrderTraversal(const LinkedBinaryTree LBT, ElementType (*visit)(LinkedBinaryTree)) {
    if (!LBT) {
        Warn("LinkedBinaryTree_InOrderTraversal: Invalid LinkedBinaryTree!");
        return;
    }
    if (!visit) {
        Warn("LinkedBinaryTree_InOrderTraversal: Invalid Function Call!");
        return;
    }
    if (LBT->Left) LinkedBinaryTree_InOrderTraversal(LBT->Left, visit); // 中序遍历其左子树
    visit(LBT); // 访问根节点
    if (LBT->Right) LinkedBinaryTree_InOrderTraversal(LBT->Right, visit);   // 中序遍历其右子树
}


/**
 * @brief 递归先序遍历实现
 *
 * 注意：当树深度较大时可能引发栈溢出
 */
void LinkedBinaryTree_PreOrderTraversal(LinkedBinaryTree LBT, ElementType (*visit)(LinkedBinaryTree)) {
    if (!LBT) {
        Warn("LinkedBinaryTree_InOrderTraversal: Invalid LinkedBinaryTree!");
        return;
    }
    if (!visit) {
        Warn("LinkedBinaryTree_InOrderTraversal: Invalid Function Call!");
        return;
    }
    visit(LBT); // 访问根节点
    if (LBT->Left) LinkedBinaryTree_PreOrderTraversal(LBT->Left, visit); // 中序遍历其左子树
    if (LBT->Right) LinkedBinaryTree_PreOrderTraversal(LBT->Right, visit);   // 中序遍历其右子树
}

/**
 * @brief 递归后序遍历实现
 *
 * 典型应用场景：表达式树求值
 */
void LinkedBinaryTree_PostOrderTraversal(LinkedBinaryTree LBT, ElementType (*visit)(LinkedBinaryTree)) {
    if (!LBT) {
        Warn("LinkedBinaryTree_InOrderTraversal: Invalid LinkedBinaryTree!");
        return;
    }
    if (!visit) {
        Warn("LinkedBinaryTree_InOrderTraversal: Invalid Function Call!");
        return;
    }
    if (LBT->Left) LinkedBinaryTree_PostOrderTraversal(LBT->Left, visit); // 中序遍历其左子树
    if (LBT->Right) LinkedBinaryTree_PostOrderTraversal(LBT->Right, visit);   // 中序遍历其右子树
    visit(LBT); // 访问根节点
}

/**
 * @brief 层序遍历实现
 *
 * 特殊说明:
 * - 使用辅助队列实现广度优先搜索
 * - 适用于按层次处理节点的场景
 *
 */
void LinkedBinaryTree_LevelOrderTraversal(LinkedBinaryTree LBT, ElementType (*visit)(LinkedBinaryTree)) {
    if (!LBT) {
        Warn("LinkedBinaryTree_LevelOrderTraversal: Invalid LinkedBinaryTree!");
        return;
    }
    QFT queue = QFT_Create();
    QFT_Enqueue(queue, LBT);
    while (!QFT_IsEmpty(queue)) {
        LinkedBinaryTree treeNode = QFT_Dequeue(queue);
        visit(treeNode);
        if (treeNode->Left) QFT_Enqueue(queue, treeNode->Left);
        if (treeNode->Right) QFT_Enqueue(queue, treeNode->Right);
    }
}

