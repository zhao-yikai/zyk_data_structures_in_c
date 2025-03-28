/*
    SeqList.c
    Functions of Sequential Lists
    Created By YikaiSays on Mar 18 2025
*/

#include <SeqList.h>
#include <Warn.h>
#include <stdio.h>

#define SEQ_LIST_ERROR INT64_MIN

struct SeqList {
    ElementType Data[MAXSIZE];
    SeqPosition Last;
};

// Specific implementation:
SeqList SeqList_Create(void){
    SeqList L = (SeqList)malloc(sizeof(struct SeqList));
    L -> Last = -1;
    return L;
}

ElementType Seq_GetElementAt(SeqList L, SeqPosition p) {
    ElementType ret_v = SEQ_LIST_ERROR;
    // 需要判断位置 p 是否合法， 若不合法， 给予相应的提示
    if (p > 0 && p <= L->Last) {
        ret_v = L->Data[p];
    } else {
        Warn("Seq_GetElementAt: INVALID POSITION!");
    }
    return ret_v;
}

SeqPosition Seq_Find(SeqList L, ElementType X) {
    SeqPosition p = -1;
    for (int i = 0; i < L->Last; ++i) {
        if (L->Data[i] == X) {
            p = i;
            break;
        }
    }
    return p;
}

bool Seq_InsertAt(SeqList L, ElementType X, SeqPosition p) {
    bool ret = false;
    if (p < 0 || p > L->Last+1) {
        // printf("Insert: INVALID POSITION!\n");
        Warn("Insert: INVALID POSITION!");
    } else {
        if (L->Last + 1 == MAXSIZE) {
            // printf("Insert: FULL LIST!\n");
            Warn("Insert: FULL LIST!");
        } else {
            // 从后开始向后平移每一个元素
            for (int i = L->Last; i >= p; --i)
                L->Data[i+1] = L->Data[i];
            L->Data[p] = X;
            ++ L->Last;
            ret = true;
        }
    }
    return ret;
}

bool Seq_DeleteAt(SeqList L, SeqPosition p) {
    bool ret = false;
    if (p < 0 || p > L->Last) {
        // printf("\nDelete: INVALID POSITION!\n");
        Warn("Delete: INVALID POSITION!");
    } else {
        if (L->Last == -1) {
            // printf("\nDelete: EMPTY LIST!\n");
            Warn("Delete: EMPTY LIST!");
        } else {
            for (int i = p; i < L->Last; ++i)
                L->Data[i] = L->Data[i+1];
            -- L->Last;
            ret = true;
        }
    }
    return ret;
}

int Seq_GetLength(SeqList L) {
    return L->Last + 1;
}

// 以下函数为测试使用
void Seq_Print(SeqList L) {
    Warn("LIST OUT:");
    printf("\033[31m");
    printf("L->Last = %d.\n\n", L->Last);
    printf("\033[0m");
    for (int i = 0; i <= L->Last; ++i) {
        printf ("Data[%d] = %lld\t",i,  L->Data[i]);
        if ((i+1)%5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

