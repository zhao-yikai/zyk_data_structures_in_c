#include <stdio.h>
#include <assert.h>
#include "SeqList.h"

void test_creation_and_basics() {
    SeqList L = SeqList_Create();
    assert(L != NULL);
    assert(SeqList_IsEmpty(L) == true);
    assert(SeqList_GetLength(L) == 0);
    printf("创建和基础测试通过 ✅\n");
}

void test_insertion_deletion() {
    SeqList L = SeqList_Create();

    // 基础插入
    assert(SeqList_InsertAt(L, 100, 0) == true);
    assert(SeqList_GetElementAt(L, 0) == 100);
    assert(SeqList_GetLength(L) == 1);

    // 头部插入
    assert(SeqList_InsertAt(L, 200, 0) == true);
    assert(SeqList_GetElementAt(L, 0) == 200);
    assert(SeqList_GetElementAt(L, 1) == 100);

    // 中间插入
    assert(SeqList_InsertAt(L, 300, 1) == true);
    assert(SeqList_GetElementAt(L, 1) == 300);

    // 尾部插入
    assert(SeqList_InsertAt(L, 400, 3) == true);
    assert(SeqList_GetElementAt(L, 3) == 400);
    assert(SeqList_GetLength(L) == 4);

    // 非法插入
    assert(SeqList_InsertAt(L, 500, -1) == false);   // 负位置
    assert(SeqList_InsertAt(L, 500, 5) == false);     // 超过当前长度+1
    assert(SeqList_InsertAt(L, 500, 1000) == false); // 超过MAXSIZE

    // 删除测试
    assert(SeqList_DeleteAt(L, 0) == true);        // 删除头部
    assert(SeqList_GetElementAt(L, 0) == 300);
    assert(SeqList_DeleteAt(L, 2) == true);        // 删除尾部
    assert(SeqList_GetLength(L) == 2);
    assert(SeqList_DeleteAt(L, 1) == true);        // 删除中间
    assert(SeqList_GetElementAt(L, 0) == 300);

    // 非法删除
    assert(SeqList_DeleteAt(L, -1) == false);      // 负位置
    assert(SeqList_DeleteAt(L, 1) == false);       // 超出现有长度
    printf("插入删除测试通过 ✅\n");
}

void test_search_and_edge_cases() {
    SeqList L = SeqList_Create();

    // 空表测试
    assert(SeqList_Find(L, 100) == -1);
    assert(SeqList_IsEmpty(L) == true);

    // 填充测试数据
    SeqList_InsertAt(L, 10, 0);
    SeqList_InsertAt(L, 20, 1);
    SeqList_InsertAt(L, 30, 2);

    // 查找测试
    assert(SeqList_Find(L, 10) == 0);
    assert(SeqList_Find(L, 30) == 2);
    assert(SeqList_Find(L, 99) == -1);

    // 边界值测试
    assert(SeqList_GetElementAt(L, 0) == 10);
    assert(SeqList_GetElementAt(L, 2) == 30);
    printf("搜索和边界测试通过 ✅\n");
}

void test_full_condition() {
    SeqList L = SeqList_Create();

    // 填满整个表
    for (SeqPosition i = 0; i < MAXSIZE; i++) {
        assert(SeqList_InsertAt(L, i, i) == true);
    }

    assert(SeqList_IsFull(L) == true);
    assert(SeqList_InsertAt(L, 100, MAXSIZE) == false); // 满表插入失败
    assert(SeqList_GetLength(L) == MAXSIZE);
    printf("满表测试通过 ✅\n");
}

void test_print_function() {
    SeqList L = SeqList_Create();
    printf("\n打印功能测试：");
    SeqList_InsertAt(L, 10, 0);
    SeqList_InsertAt(L, 20, 1);
    Seq_Print(L);  // 应显示 Last:1 和元素 [10,20]
    printf("请人工验证打印输出 📄\n");
}

int main() {
    test_creation_and_basics();
    test_insertion_deletion();
    test_search_and_edge_cases();
    test_full_condition();
    test_print_function();

    printf("\n所有测试通过！🎉\n");
    return 0;
}