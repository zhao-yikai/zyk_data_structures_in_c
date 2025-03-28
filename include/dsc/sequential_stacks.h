/*
    sequential_stacks.h
    Functions of Sequential Stacks
    Created By YikaiSays on Mar 23 2025
*/

#ifndef SEQUENTIAL_STACKS_H
#define SEQUENTIAL_STACKS_H

#include <stdlib.h>
#include <stdbool.h>

#define SEQ_STACK_ERROR INT64_MIN

typedef int_fast64_t ElementType;

typedef struct SeqStackNode * SeqStackNodePtr;
typedef SeqStackNodePtr SeqStack;

// 1. 生成空堆栈， 其最大长度为MaxSize
SeqStack SeqStack_Create(int MaxSize);

// 2. 判断堆栈S是否已满。 若堆栈已满， 返回ture, 否则返回false。
bool SeqStack_isFull(SeqStack S);

// 3. 将元素X压入堆栈。 若堆栈已满， 返回false, 否则将数据元素插入到堆栈S栈顶处并返回true.
bool SeqStack_Push(SeqStack S, ElementType X);

// 4. 判断堆栈S是否为空， 若是返回true； 否则返回false.
bool SeqStack_isEmpty(SeqStack S);

// 5. 删除并返回栈顶元素。 若堆栈为空， 返回错误信息； 否则将栈顶元素从堆栈中删除并返回。
ElementType SeqStack_Pop(SeqStack S);

#endif //SEQUENTIAL_STACKS_H
