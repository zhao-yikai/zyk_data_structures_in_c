/*
    LinkedList.c
    Functions of Linked Linear Lists
    Created By YikaiSays on Mar 23 2025
*/

#include <stdio.h>
#include <stdlib.h>  // 添加标准库头文件
#include "LinkedList.h"
#include "Warn.h"

// 链表节点结构定义
struct LinkedListNode {
    ElementType Data;             // 节点数据
    LinkedListNodePtr Next;       // 指向下一个节点的指针
};

/*
 * 创建链表头节点
 * 返回值: 成功返回头节点指针，失败返回NULL
 */
LinkedListHead Linked_Create(void) {
    LinkedList_Position p = malloc(sizeof(struct LinkedListNode));
    if (!p) {
        Warn("Linked_Create: Memory Allocation Error!");
        return NULL;
    }
    // DeepSeek: 头节点数据域建议初始化为特殊值（根据ElementType定义）
    p->Data = LINKED_ERROR;      // 修改建议：使用定义好的错误值初始化
    p->Next = NULL;              // 空链表初始化
    return p;
}

/*
 * 获取链表长度（不含头节点）
 * L: 链表头节点
 * 返回值: 成功返回实际长度，失败返回LINKED_ERROR
 */
Length Linked_GetLength(LinkedListHead L) {
    if (!L) {
        Warn("Linked_GetLength: INVALID LIST!");
        return LINKED_ERROR;
    }
    Length l = 0;
    // DeepSeek: 建议从第一个有效节点开始计数（头节点不计入长度）
    for (LinkedList_Position p = L->Next; p != NULL; p = p->Next, ++l) {}
    return l;
}

/*
 * 在指定位置插入节点（从1开始计数）
 * L: 链表头节点
 * X: 插入元素值
 * i: 插入位置
 * 返回值: 成功返回true，失败返回false
 */
bool Linked_InsertAtNodePosition(LinkedListHead L, ElementType X, int i) {
    if (!L || i < 1) {  // 位置从1开始计数
        Warn("Linked_InsertAtNodePosition: INVALID PARAMETERS!");
        return false;
    }

    LinkedList_Position pre = L;
    int cnt = 0;
    // 寻找第i-1个节点
    while (pre && cnt < i - 1) {
        pre = pre->Next;
        ++cnt;
    }

    if (!pre || cnt != i - 1) {
        Warn("Linked_InsertAtNodePosition: INVALID POSITION!");
        return false;
    }

    // DeepSeek: 直接创建新节点，避免使用Linked_Create（可能包含不必要初始化）
    LinkedList_Position tmp = malloc(sizeof(struct LinkedListNode));
    if (!tmp) {
        Warn("Linked_InsertAtNodePosition: MALLOC ERROR!");
        return false;
    }

    tmp->Data = X;
    tmp->Next = pre->Next;
    pre->Next = tmp;
    return true;
}

/*
 * 在指定节点前插入新节点
 * L: 链表头节点
 * X: 插入元素值
 * P: 目标节点指针
 * 返回值: 成功返回true，失败返回false
 */
bool Linked_InsertAtNodePtr(LinkedListHead L, ElementType X, LinkedList_Position P) {
    if (!L || !P) {
        Warn("Linked_InsertAtNodePtr: INVALID PARAMETERS!");
        return false;
    }

    LinkedList_Position pre = L;
    // 查找目标节点的前驱节点
    while (pre && pre->Next != P) {
        pre = pre->Next;
    }

    if (!pre) {
        Warn("Linked_InsertAtNodePtr: NODE NOT FOUND!");
        return false;
    }

    LinkedList_Position tmp = malloc(sizeof(struct LinkedListNode));
    if (!tmp) {
        Warn("Linked_InsertAtNodePtr: MALLOC ERROR!");
        return false;
    }

    tmp->Data = X;
    tmp->Next = P;
    pre->Next = tmp;
    return true;
}

/*
 * 获取指定位置的元素值
 * L: 链表头节点
 * k: 元素位置（从0开始计数）
 * 返回值: 成功返回元素值，失败返回LINKED_ERROR
 */
ElementType Linked_GetElementAtPosition(LinkedListHead L, int k) {
    if (!L || k < 0) {
        Warn("Linked_GetElementAtPosition: INVALID PARAMETERS!");
        return LINKED_ERROR;
    }

    LinkedList_Position p = L->Next;  // 跳过头节点
    int cnt = 0;
    while (p && cnt < k) {
        p = p->Next;
        ++cnt;
    }
    return p ? p->Data : LINKED_ERROR;
}

/*
 * 获取指定节点的元素值
 * L: 链表头节点（参数未使用，建议移除）
 * p: 目标节点指针
 * 返回值: 成功返回元素值，失败返回LINKED_ERROR
 */
ElementType Linked_GetElementAtNodePtr(LinkedList_Position p) {
    return p ? p->Data : LINKED_ERROR;
}

/*
 * 查找元素首次出现的位置
 * L: 链表头节点
 * X: 目标元素值
 * 返回值: 成功返回节点指针，失败返回NULL
 */
LinkedList_Position Linked_Find(LinkedListHead L, ElementType X) {
    if (!L) return NULL;

    // DeepSeek: 应该从第一个有效节点开始查找
    LinkedList_Position p = L->Next;
    while (p && p->Data != X) {
        p = p->Next;
    }
    return p;
}

/*
 * 删除指定位置的节点
 * L: 链表头节点
 * i: 删除位置（从1开始计数）
 * 返回值: 成功返回true，失败返回false
 */
bool Linked_DeleteAtNodePosition(LinkedListHead L, int i) {
    if (!L || i < 1) {
        Warn("Linked_DeleteAtNodePosition: INVALID PARAMETERS!");
        return false;
    }

    LinkedList_Position pre = L;
    int cnt = 0;
    while (pre && cnt < i - 1) {
        pre = pre->Next;
        ++cnt;
    }

    if (!pre || !pre->Next || cnt != i - 1) {
        Warn("Linked_DeleteAtNodePosition: INVALID POSITION!");
        return false;
    }

    LinkedList_Position toDel = pre->Next;
    pre->Next = toDel->Next;
    free(toDel);
    return true;
}

/*
 * 删除指定节点
 * L: 链表头节点
 * P: 要删除的节点指针
 * 返回值: 成功返回true，失败返回false
 */
bool Linked_DeleteAtNodePtr(LinkedListHead L, LinkedList_Position P) {
    if (!L || !P) {
        Warn("Linked_DeleteAtNodePtr: INVALID PARAMETERS!");
        return false;
    }

    LinkedList_Position pre = L;
    while (pre && pre->Next != P) {
        pre = pre->Next;
    }

    if (!pre) {
        Warn("Linked_DeleteAtNodePtr: NODE NOT FOUND!");
        return false;
    }

    pre->Next = P->Next;
    free(P);
    return true;
}

// DeepSeek: 建议添加的销毁链表函数
/*
bool Linked_Destroy(LinkedListHead L) {
    if (!L) return false;

    LinkedList_Position p = L;
    while (p) {
        LinkedList_Position tmp = p;
        p = p->Next;
        free(tmp);
    }
    return true;
}
*/
