/*
    LinkedList.c
    Functions of Linked Linear Lists
    Created By YikaiSays on Mar 23 2025
*/

#ifndef LINKED_LINEAR_LIST_H
#define LINKED_LINEAR_LIST_H

#include "Common.h"  // 统一类型定义

#define LINKED_ERROR DSC_ERROR

// ElementType 现在由 Common.h 统一定义

typedef struct LinkedListNode *LinkedListNodePtr;

typedef LinkedListNodePtr LinkedList_Position;
typedef LinkedListNodePtr LinkedListHead;
// Length 现在由 Common.h 统一定义

/*
 * 创建链表头节点
 * 返回值: 成功返回头节点指针，失败返回NULL
 */
LinkedListHead LinkedList_Create(void);

/*
 * 获取链表长度（不含头节点）
 * L: 链表头节点
 * 返回值: 成功返回实际长度，失败返回LINKED_ERROR
 */
Length LinkedList_GetLength(LinkedListHead L);

// 2. 按序号查找 FindKth, 根据指定的位序K， 返回L中相应的元素
ElementType LinkedList_GetElementAtPosition(LinkedListHead L, int k);

ElementType LinkedList_GetElementAtNodePtr(LinkedList_Position p);

// 3. 按值查找， 既定位 Find
LinkedList_Position LinkedList_Find(LinkedListHead L, ElementType X);

// 4. 带头结点的插入(按位序插入)
bool LinkedList_InsertAtNodePosition(LinkedListHead L, ElementType X, int i);

// 5. 带头结点的插入（按指针插入）
bool LinkedList_InsertAtNodePtr(LinkedListHead L, ElementType X, LinkedList_Position P);

// 6. 带头结点的删除 （按位序删除）
bool LinkedList_DeleteAtNodePosition(LinkedListHead L, int i);

// 7. 带头结点的删除（按指针删除）
bool LinkedList_DeleteAtNodePtr(LinkedListHead L, LinkedList_Position P);

// 销毁链表
bool LinkedList_Destroy(LinkedListHead L);

#endif //LINKED_LINEAR_LIST_H
