/*
    LinkedStack.c
    Functions of Linked Stacks
    Created By YikaiSays on Mar 23 2025
*/

#include "LinkedStack.h"
#include "Warn.h"

// 链栈节点结构定义
struct LinkedStackNode {
    ElementType Data;        // 节点存储的数据
    LinkedStackNodePtr Next; // 指向下一个节点的指针
};

/*
 * 创建链栈头节点（哨兵节点）
 * 返回值: 成功返回头节点指针，失败返回NULL
 */
LinkedStackHead LinkedStack_Create() {
    LinkedStackHead S = malloc(sizeof(struct LinkedStackNode));
    if (S) {
        S->Next = NULL;  // 初始化空栈
    } else {
        Warn("LinkedStack_Create: MALLOC ERROR!");
    }
    return S;  // DeepSeek: 调用者需要检查返回值是否为NULL
}

/*
 * 元素压栈操作
 * 参数: S - 栈头指针，X - 入栈元素
 * 返回值: 成功返回true，失败返回false
 */
bool LinkedStack_Push(LinkedStackHead S, ElementType X) {
    bool ret = false;
    // DeepSeek: 建议添加参数校验（if (!S) { Warn... }）
    if (S) {
        LinkedStackHead tmp = malloc(sizeof(struct LinkedStackNode));
        if (!tmp) {
            Warn("LinkedStack_Push: MALLOC ERROR!");
        } else {
            // 头插法插入新节点
            tmp->Data = X;          // 存储数据
            tmp->Next = S->Next;    // 新节点指向原栈顶
            S->Next = tmp;          // 更新头节点指针
            ret = true;
        }
    } else {
        Warn("LinkedStack_Push: Invalid LinkedStackHead!");
    }
    return ret;
}

/*
 * 判断栈是否为空
 * 参数: S - 栈头指针
 * 返回值: 空栈返回true
 */
bool LinkedStack_isEmpty(LinkedStackHead S) {
    bool ret = false;
    // DeepSeek: 高危-未检查S是否为NULL（可能引发空指针崩溃）
    if (S->Next == NULL)  // 通过头节点的Next指针判断空栈
        ret = true;
    return ret;
}

/*
 * 弹出栈顶元素
 * 参数: S - 栈头指针
 * 返回值: 成功返回元素值，失败返回错误码
 */
ElementType LinkedStack_Pop(LinkedStackHead S) {
    ElementType retVal = LINKED_STACK_ERROR;
    // DeepSeek: 调用isEmpty前未检查S有效性（嵌套风险）
    if (!LinkedStack_isEmpty(S)) {
        LinkedStackNodePtr topNode = S->Next;  // 获取栈顶节点
        retVal = topNode->Data;
        S->Next = topNode->Next;  // 更新头节点指针
        free(topNode);            // 释放原栈顶节点
    }  // DeepSeek: else分支缺少空栈错误日志
    return retVal;
}

/*
 * 删除整个链栈
 * 参数: S - 栈头指针
 */
void LinkedStack_Delete(LinkedStackHead S) {
    LinkedStackNodePtr p = S;
    while (p != NULL) {
        LinkedStackNodePtr tmp = p;  // 保存当前节点
        p = p->Next;                // 移动到下一节点
        free(tmp);                  // 释放当前节点
    }
}
