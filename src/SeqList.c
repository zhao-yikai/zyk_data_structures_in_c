/*
    SeqList.c
    Functions of Sequential Lists
    Created By YikaiSays on Mar 18 2025
*/

#include <SeqList.h>
#include <Warn.h>
#include <stdio.h>

#define SEQ_LIST_ERROR INT64_MIN

// 顺序表结构体定义
// Data: 存储元素的数组，Last: 最后一个元素的索引（-1表示空表）
struct SeqList {
    ElementType Data[MAXSIZE];  // DeepSeek: 需要确保MAXSIZE已在头文件中定义
    SeqPosition Last;
};

/*
 * 创建并初始化顺序表
 * 返回值: 成功返回顺序表指针，失败返回NULL
 */
SeqList SeqList_Create(void){
    SeqList L = (SeqList)malloc(sizeof(struct SeqList));
    // DeepSeek: 建议添加空指针检查
    if (L != NULL) {
        L->Last = -1;
    }
    return L;
}

/*
 * 获取指定位置的元素
 * L: 顺序表指针
 * p: 要获取元素的位置
 * 返回值: 成功返回元素值，失败返回SEQ_LIST_ERROR
 */
ElementType Seq_GetElementAt(SeqList L, SeqPosition p) {
    ElementType ret_v = SEQ_LIST_ERROR;
    // DeepSeek: 位置判断条件错误，应允许p=0的位置
    if (p >= 0 && p <= L->Last) {  // 修改建议：调整条件判断
        ret_v = L->Data[p];
    } else {
        Warn("Seq_GetElementAt: INVALID POSITION!");
    }
    return ret_v;
}

/*
 * 查找元素第一次出现的位置
 * L: 顺序表指针
 * X: 要查找的元素
 * 返回值: 成功返回位置索引，失败返回-1
 */
SeqPosition Seq_Find(SeqList L, ElementType X) {
    SeqPosition p = -1;
    // DeepSeek: 循环条件错误，应包含最后一个元素
    for (int i = 0; i <= L->Last; ++i) {  // 修改建议：调整循环终止条件
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
bool Seq_InsertAt(SeqList L, ElementType X, SeqPosition p) {
    bool ret = false;
    // 检查位置合法性（允许插入到最后一个元素之后的位置）
    if (p < 0 || p > L->Last+1) {
        Warn("Insert: INVALID POSITION!");
    } else {
        // 检查表是否已满
        if (L->Last + 1 == MAXSIZE) {
            Warn("Insert: FULL LIST!");
        } else {
            // 从最后一个元素开始向后移动元素
            for (int i = L->Last; i >= p; --i)
                L->Data[i+1] = L->Data[i];
            L->Data[p] = X;
            ++L->Last;
            ret = true;
        }
    }
    return ret;
}

/*
 * 删除指定位置元素
 * L: 顺序表指针
 * p: 要删除的位置
 * 返回值: 成功返回true，失败返回false
 */
bool Seq_DeleteAt(SeqList L, SeqPosition p) {
    bool ret = false;
    // 检查位置合法性
    if (p < 0 || p > L->Last) {
        Warn("Delete: INVALID POSITION!");
    } else {
        // 检查表是否为空
        if (L->Last == -1) {
            Warn("Delete: EMPTY LIST!");
        } else {
            // 从目标位置开始向前移动元素
            for (int i = p; i < L->Last; ++i)
                L->Data[i] = L->Data[i+1];
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
int Seq_GetLength(SeqList L) {
    return L->Last + 1;
}

/*
 * 打印顺序表内容（测试用）
 * L: 顺序表指针
 */
void Seq_Print(SeqList L) {
    Warn("LIST OUT:");
    printf("\033[31m");  // 红色文本
    printf("L->Last = %d.\n\n", L->Last);
    printf("\033[0m");   // 重置颜色

    for (int i = 0; i <= L->Last; ++i) {
        printf("Data[%d] = %lld\t", i, L->Data[i]);
        if ((i+1)%5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// DeepSeek: 建议添加销毁函数释放内存
/*
void SeqList_Destroy(SeqList L) {
    free(L);
}
*/