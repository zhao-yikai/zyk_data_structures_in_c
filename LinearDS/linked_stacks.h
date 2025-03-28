/*
    linked_stacks.h
    Functions of Linked Stacks
    Created By YikaiSays on Mar 23 2025
*/

#ifndef LINKED_STACKS_H
#define LINKED_STACKS_H

#include <stdlib.h>
#include <stdbool.h>

#define LINKED_STACK_ERROR INT64_MIN

typedef int_fast64_t ElementType;

typedef struct LinkedStackNode * LinkedStackNodePtr;
typedef LinkedStackNodePtr LinkedStackHead;

// 1. 生成空堆栈
LinkedStackHead LinkedStack_Create();

// 2. 将元素X压入堆栈。 若堆栈已满， 返回false, 否则将数据元素插入到堆栈S栈顶处并返回true.
bool LinkedStack_Push(LinkedStackHead S, ElementType X);

// 3. 判断堆栈S是否为空， 若是返回true； 否则返回false.
bool LinkedStack_isEmpty(LinkedStackHead S);

// 4. 删除并返回栈顶元素。 若堆栈为空， 返回错误信息； 否则将栈顶元素从堆栈中删除并返回。
ElementType LinkedStack_Pop(LinkedStackHead S);

void LinkedStack_Delete(LinkedStackHead S);

#endif //LINKED_STACKS_H
