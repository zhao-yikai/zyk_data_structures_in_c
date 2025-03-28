/*
    linked_linear_list.c
    Functions of Linked Linear List
    Created By YikaiSays on Mar 23 2025
*/

#include <stdio.h>
#include "linked_linear_list.h"

#include "warning.h"

struct LinkedListNode {
    ElementType Data;
    LinkedListNodePtr Next;
};

LinkedListHead Linked_Create(void) {
    LinkedList_Position p = malloc(sizeof(struct LinkedListNode));
    if (!p) {
        Warn("Linked_Create: MALLOC ERROR!");
    } else {
        p->Data = 0;
        p->Next = NULL;
    }
    return p;
}

Length Linked_GetLength(LinkedListHead L) {
    Length ret = LINKED_ERROR;
    if (L) {
        Length l = 0;
        for (LinkedList_Position p = L; p->Next; p = p->Next, ++l){}
        ret = l;
    } else {
        printf("INVALID LIST!\n");
    }
    return ret;
}

// 需要修改
bool Linked_InsertAtNodePosition(LinkedListHead L, ElementType X, int i) {
    bool ret = false;
    LinkedList_Position pre = L;
    int cnt = 0;
    while (pre && cnt < i - 1) {
        pre = pre->Next;
        ++cnt;
    }
    if (pre == NULL || cnt != i - 1) {
        printf("INVALID POSITION!\n");
    } else {
        LinkedList_Position tmp = Linked_Create();
        tmp->Next = pre->Next;
        tmp->Data = X;
        pre->Next = tmp;
        ret = true;
    }
    return ret;
}

bool Linked_InsertAtNodePtr(LinkedListHead L, ElementType X, LinkedList_Position P) {
    bool ret = false;
    LinkedList_Position pre = L;
    if (P) {
        while (pre && pre->Next != P)
            pre = pre->Next;
        if (!pre) {
            Warn("Linked_InsertAtNodePtr: INVALID POSITION!");
        } else {
            LinkedListHead tmp = malloc(sizeof (struct LinkedListNode));
            if (!tmp) {
                Warn("Linked_InsertAtNodePtr: MALLOC ERROR!");
            } else {
                tmp->Data = X;
                tmp->Next = P;
                pre->Next = tmp;
                ret = true;
            }
        }
    } else {
        Warn("Linked_InsertAtNodePtr: INVALID POSITION!");
    }
    return ret;
}

ElementType Linked_GetElementAtPosition(LinkedListHead L, int k) {
    ElementType RET = LINKED_ERROR;
    LinkedList_Position p = L;
    int cnt;
    for (cnt = 0; p && cnt < k; p = p->Next, ++cnt){}
    if (cnt == k && p)
        RET = p->Data;
    return RET;
}

ElementType Linked_GetElementAtNodePtr(LinkedListHead L, LinkedList_Position p) {
    ElementType RET = LINKED_ERROR;
    if (p)
        RET = p->Data;
    return RET;
}

LinkedList_Position Linked_Find(LinkedListHead L, ElementType X) {
    LinkedList_Position p = L;
    while (p && p->Data != X)
        p = p->Next;
    return p;
}


bool Linked_DeleteAtNodePosition(LinkedListHead L, int i) {
    bool ret = false;
    LinkedList_Position pre = L;
    int cnt = 0;
    while (cnt < i - 1 && pre) {
        pre = pre->Next;
        ++cnt;
    }
    if (cnt != i - 1 || pre == NULL) {
        printf("INVALID POSITION!\n");
    } else {
        LinkedList_Position p = pre->Next;
        pre->Next = pre->Next->Next;
        free(p);
        ret = true;
    }
    return ret;
}

bool Linked_DeleteAtNodePtr(LinkedListHead L, LinkedList_Position P) {
    bool ret = false;
    LinkedList_Position pre = L;
    if (P == NULL) {
        printf("INVALID POSITION!\n");
    } else {
        while (pre && pre->Next != P) {
            pre = pre->Next;
        }
        if (pre == NULL) {
            printf("INVALID POSITION!\n");
        } else {
            pre->Next = P->Next;
            free(P);
            ret = true;
        }
    }
    return ret;
}

