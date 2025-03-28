/*
    linked_linear_list.h
    Functions of Linked Linear List
    Created By YikaiSays on Mar 23 2025
*/

#ifndef LINKED_LINEAR_LIST_H
#define LINKED_LINEAR_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#define LINKED_ERROR INT64_MIN

typedef int_fast64_t ElementType;

typedef struct LinkedListNode *LinkedListNodePtr;

typedef LinkedListNodePtr LinkedList_Position;
typedef LinkedListNodePtr LinkedListHead;
typedef int_fast64_t Length;

LinkedListHead Linked_Create(void);

// 1. 求表长 GetLength
Length Linked_GetLength(LinkedListHead L);

// 2. 按序号查找 FindKth, 根据指定的位序K， 返回L中相应的元素
ElementType Linked_GetElementAtPosition(LinkedListHead L, int k);

ElementType Linked_GetElementAtNodePtr(LinkedListHead L, LinkedList_Position p);

// 3. 按值查找， 既定位 Find
LinkedList_Position Linked_Find(LinkedListHead L, ElementType X);

// 4. 带头结点的插入(按位序插入)
bool Linked_InsertAtNodePosition(LinkedListHead L, ElementType X, int i);

// 5. 带头结点的插入（按指针插入）
bool Linked_InsertAtNodePtr(LinkedListHead L, ElementType X, LinkedList_Position P);

// 6. 带头结点的删除 （按位序删除）
bool Linked_DeleteAtNodePosition(LinkedListHead L, int i);

// 7. 带头结点的删除（按指针删除）
bool Linked_DeleteAtNodePtr(LinkedListHead L, LinkedList_Position P);


#endif //LINKED_LINEAR_LIST_H
