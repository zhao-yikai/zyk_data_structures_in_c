/*
    linked_stacks.c
    Functions of Linked Stacks
    Created By YikaiSays on Mar 23 2025
*/

#include "linked_stacks.h"

#include "warning.h"

struct LinkedStackNode {
    ElementType Data;
    LinkedStackNodePtr Next;
};

// 1. 生成堆栈头结点
LinkedStackHead LinkedStack_Create() {
    LinkedStackHead S= malloc(sizeof(struct LinkedStackNode));
    if (S) {
        S->Next = NULL;
    } else {
        Warn("LinkedStack_Create: MALLOC ERROR!");
    }
    return S;
}

// 2. 将元素X压入堆栈。 若空间不足， 返回false, 否则将数据元素插入到堆栈S栈顶处并返回true.
bool LinkedStack_Push(LinkedStackHead S, ElementType X) {
    bool ret = false;
    if (S) {
        LinkedStackHead tmp = malloc(sizeof (struct LinkedStackNode));
        if (!tmp) {
            Warn("LinkedStack_Push: MALLOC ERROR!");
        } else {
            tmp->Data = X;
            tmp->Next = S->Next;
            S->Next = tmp;
            ret = true;
        }
    }
    return ret;
}

// 3. 判断堆栈S是否为空， 若是返回true； 否则返回false.
bool LinkedStack_isEmpty(LinkedStackHead S) {
    bool ret = false;
    if (S->Next == NULL)
        ret = true;
    return ret;
}

// 4. 删除并返回栈顶元素。 若堆栈为空， 返回错误信息； 否则将栈顶元素从堆栈中删除并返回。
ElementType LinkedStack_Pop(LinkedStackHead S) {
    ElementType retVal = LINKED_STACK_ERROR;
    if (!LinkedStack_isEmpty(S)) {
        LinkedStackNodePtr topNode = S->Next;
        retVal = topNode->Data;
        S->Next = topNode->Next;
        free(topNode);
    }
    return retVal;
}

// 删除一个堆栈
void LinkedStack_Delete(const LinkedStackHead S) {
    LinkedStackNodePtr p = S;
    while (p!=NULL) {
        LinkedStackNodePtr tmp = p;
        p = p->Next;
        free(tmp);
    }
}

