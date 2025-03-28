/*
    SeqStack.c
    Functions of Sequential Stacks
    Created By YikaiSays on Mar 23 2025
*/

#include "SeqStack.h"

typedef int Position;

struct SeqStackNode {
    ElementType * Data;
    Position Top;
    int MaxSize;
};

SeqStack SeqStack_Create(int MaxSize) {
    SeqStack S = malloc(sizeof(struct SeqStackNode));
    S->Data = malloc(MaxSize * sizeof(ElementType));
    S->Top = -1;
    S->MaxSize = MaxSize;
    return S;
}

// 2. 判断堆栈S是否已满。 若堆栈已满， 返回ture, 否则返回false
bool SeqStack_isFull(SeqStack S) {
    bool ret = false;
    if (S)
        if (S->Top == S->MaxSize - 1)
            ret = true;
    return ret;
}

// 3. 将元素X压入堆栈。 若堆栈已满， 返回false, 否则将数据元素插入到堆栈S栈顶处并返回true
bool SeqStack_Push(SeqStack S, ElementType X) {
    bool ret = false;
    if (!SeqStack_isFull(S)) {
        S->Data[++S->Top] = X;
        ret = true;
    }
    return ret;
}

// 4. 判断堆栈S是否为空， 若是返回true； 否则返回false
bool SeqStack_isEmpty(SeqStack S) {
    bool ret = false;
    if (S->Top == -1)
        ret = true;
    return ret;
}

// 5. 删除并返回栈顶元素。 若堆栈为空， 返回错误信息； 否则将栈顶元素从堆栈中删除并返回。
ElementType SeqStack_Pop(SeqStack S) {
    ElementType Pop = SEQ_STACK_ERROR;
    if (!SeqStack_isEmpty(S))
        Pop = S->Data[S->Top--];
    return Pop;
}
