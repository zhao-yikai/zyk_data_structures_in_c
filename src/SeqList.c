/*
    SeqList.c
    Functions of Sequential Lists
    Created By YikaiSays on Mar 18 2025
*/

#include "SeqList.h"
#include "Warn.h"

#include <stdio.h>

#define SEQ_LIST_ERROR INT64_MIN

// 顺序表结构体定义
// Data: 存储元素的数组，Last: 最后一个元素的索引（-1表示空表）
struct SeqList {
    ElementType Data[MAXSIZE]; // DeepSeek: 需要确保MAXSIZE已在头文件中定义
    SeqPosition Last;
};

/*
 * 创建并初始化顺序表
 * 返回值: 成功返回顺序表指针，失败返回NULL
 */
SeqList SeqList_Create(void) {
    SeqList L = (SeqList) malloc(sizeof(struct SeqList));
    // DeepSeek: 建议添加空指针检查
    if (!L) {
        Warn("SeqList_Create: Memory Allocation Error!");
    } else {
        L->Last = -1;
    }
    return L;
}

bool SeqList_IsEmpty(SeqList L) {
    if (!L) {
        Warn("SeqList_IsEmpty: Invalid SeqList L!");
        return false;
    }
    if (L->Last == -1) {
        return true;
    }
    return false;
}

/*
 * 获取指定位置的元素
 * L: 顺序表指针
 * p: 要获取元素的位置
 * 返回值: 成功返回元素值，失败返回SEQ_LIST_ERROR
 */
// Mar 29 重写
ElementType SeqList_GetElementAt(SeqList L, SeqPosition p) {
    if (!L) {
        Warn("SeqList_GetElementAt: Invalid SeqList!");
        return SEQ_LIST_ERROR;
    }
    if (SeqList_IsEmpty(L)) {
        Warn("SeqList_GetElementAt: Empty SeqList!");
        return false;
    }
    if ( p<0 || p > L->Last) {
        Warn("SeqList_GetElementAt: Invalid SeqPosition!");
        return SEQ_LIST_ERROR;
    }
    return L->Data[p];
}

/*
 * 查找元素第一次出现的位置
 * L: 顺序表指针
 * X: 要查找的元素
 * 返回值: 成功返回位置索引，失败返回-1
 */
SeqPosition SeqList_Find(SeqList L, ElementType X) {
    SeqPosition p = -1;
    // DeepSeek: 循环条件错误，应包含最后一个元素
    for (int i = 0; i <= L->Last; ++i) {
        // 修改建议：调整循环终止条件
        if (L->Data[i] == X) {
            p = i;
            break;
        }
    }
    return p;
}

/*
 * 在指定位置插入元素
 * L: 顺序表指针
 * X: 要插入的元素
 * p: 插入位置
 * 返回值: 成功返回true，失败返回false
 */

// Mar 29 重写 -> 重写的过程中咖啡洒在了电脑上， 此处标记为 The Coffee Crisis
bool SeqList_InsertAt(SeqList L, ElementType X, SeqPosition p) {
    // 判断顺序表指针L是否有效
    if (!L) {
        Warn("SeqList_InsertAt: Invalid SeqList!");
        return false;
    }
    // 判断位置下标p是否有效
    if (p < 0) {
        Warn("Seq_Insert: Invalid Position, Negative SeqPosition p");
        return false;
    }
    if (p >=L->Last + 2) {   // Apr 2: 需要修改， 上次这里没写完， 电脑撒上咖啡了
        Warn("Seq_Insert: Invalid Position!");
        return false;
    }
    // 判断顺序表L是否已满
    if (!SeqList_IsFull(L)) {
        // 顺序表L未满
        // 从后向前把每一个元素向后移动一个单元
        for (int i = L->Last; i>=p; --i)
            L->Data[i+1] = L->Data[i];
        L->Data[p] = X;
        ++L->Last;
        return true;
    }
    return false;
}

/*
 * 删除指定位置元素
 * L: 顺序表指针
 * p: 要删除的位置
 * 返回值: 成功返回true，失败返回false
 */
bool SeqList_DeleteAt(SeqList L, SeqPosition p) {
    bool ret = false;
    // 检查位置合法性
    if (p < 0 || p > L->Last) {
        Warn("Delete: INVALID POSITION!");
    } else {
        // 检查表是否为空
        if (SeqList_IsEmpty(L)) {
            Warn("Delete: EMPTY LIST!");
        } else {
            // 从目标位置开始向前移动元素
            for (int i = p; i < L->Last; ++i)
                L->Data[i] = L->Data[i + 1];
            --L->Last;
            ret = true;
        }
    }
    return ret;
}

/*
 * 获取顺序表长度
 * L: 顺序表指针
 * 返回值: 当前元素个数
 */
int SeqList_GetLength(SeqList L) {
    if (!L) {
        Warn("SeqList_GetLength: Invalid SeqList!");
        return -1;
    }
    return L->Last + 1;
}

/*
 * 打印顺序表内容（测试用）
 * L: 顺序表指针
 */
void Seq_Print(SeqList L) {
    Warn("LIST OUT:");
    printf("\033[31m"); // 红色文本
    printf("L->Last = %d.\n\n", L->Last);
    printf("\033[0m"); // 重置颜色

    for (int i = 0; i <= L->Last; ++i) {
        printf("Data[%d] = %lld\t", i, L->Data[i]);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

bool SeqList_IsFull(SeqList L) {
    if (!L) {
        Warn("SeqList_IsFull: Invalid SeqList L!");
        return true;
    }
    if (L->Last == MAXSIZE-1) {
        return true;
    }
    return false;
}

// DeepSeek: 建议添加销毁函数释放内存
/*
void SeqList_Destroy(SeqList L) {
    free(L);
}
*/
