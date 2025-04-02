#include <stdio.h>
#include "SeqList.h"
#include <assert.h>

#define STRESS_TEST_SIZE 1000  // 远超过MAXSIZE的测试量

// 异常测试宏
#define TEST_EXCEPTION(expr, expected) \
    do { \
        bool res = (expr); \
        printf("[%s] %s -> %s (Expected: %s)\n", \
              res ? "FAIL" : "PASS", #expr, res ? "true" : "false", expected ? "true" : "false"); \
    } while(0)

void test_basic_operations() {
    printf("\n=== 基础功能测试 ===\n");
    SeqList L = SeqList_Create();

    // 空表测试
    assert(SeqList_GetLength(L) == 0);
    Seq_Print(L);

    // 边界插入测试
    TEST_EXCEPTION(SeqList_InsertAt(L, 100, 1), false);  // 空表插入越界[1](@ref)
    TEST_EXCEPTION(SeqList_InsertAt(L, 0, 0), true);     // 首元素插入
    TEST_EXCEPTION(SeqList_InsertAt(L, 1, 1), true);     // 连续插入
    TEST_EXCEPTION(SeqList_InsertAt(L, 3, 2), false);    // 跳跃插入

    // 数据验证
    assert(SeqList_GetElementAt(L, 0) == 0);
    assert(SeqList_GetElementAt(L, 1) == 1);
    assert(SeqList_Find(L, 1) == 1);
    Seq_Print(L);
}

void test_boundary_conditions() {
    printf("\n=== 边界条件测试 ===\n");
    SeqList L = SeqList_Create();

    // 满容量测试
    for (SeqPosition i=0; i<MAXSIZE; i++) {
        assert(SeqList_InsertAt(L, i, i));
    }
    TEST_EXCEPTION(SeqList_InsertAt(L, MAXSIZE, MAXSIZE), false);  // 超出MAXSIZE[1](@ref)
    assert(SeqList_GetLength(L) == MAXSIZE);

    // 边界删除测试
    TEST_EXCEPTION(SeqList_DeleteAt(L, MAXSIZE), false);  // 越界删除
    assert(SeqList_DeleteAt(L, MAXSIZE-1));              // 删除末尾
    assert(SeqList_GetLength(L) == MAXSIZE-1);

    // 循环插入删除
    for (int i=0; i<10; i++) {
        assert(SeqList_InsertAt(L, 0, i));    // 头部插入
        assert(SeqList_DeleteAt(L, 0));       // 头部删除
    }
    Seq_Print(L);
}

void test_error_handling() {
    printf("\n=== 异常处理测试 ===\n");
    SeqList L = SeqList_Create();

    // 非法位置访问
    TEST_EXCEPTION(SeqList_GetElementAt(L, 0), false);  // 空表访问
    TEST_EXCEPTION(SeqList_DeleteAt(L, 0), false);       // 空表删除

    // 特殊值测试
    SeqList_InsertAt(L, -1, 0);        // 插入负值
    SeqList_InsertAt(L, 0xDEAD, 1);    // 插入非常规数值
    assert(SeqList_Find(L, 0xDEAD) == 1);
}

void stress_test() {
    printf("\n=== 压力测试 ===\n");
    SeqList L = SeqList_Create();

    // 顺序插入
    for (int i=0; i<MAXSIZE; i++) {
        assert(SeqList_InsertAt(L, i, i%100));
    }

    // 随机删除
    for (int i=MAXSIZE-1; i>=0; i-=2) {
        assert(SeqList_DeleteAt(L, i));
    }
    assert(SeqList_GetLength(L) == MAXSIZE/2);

    // 交替操作
    for (int i=0; i<100; i++) {
        assert(SeqList_InsertAt(L, i%5, i));
        assert(SeqList_DeleteAt(L, (i+3)%SeqList_GetLength(L)));
    }
}

int main() {
    // 基础功能验证
    test_basic_operations();

    // 边界条件测试
    test_boundary_conditions();

    // 异常处理测试
    test_error_handling();

    // 压力测试
    stress_test();

    printf("\n所有测试用例执行完成！\n");
    return 0;
}