//
// Created by 趙熠楷 on 4/12/25.
//
#include <stdbool.h>

#include "Warn.h"
#include "Sort.h"

#include <stdlib.h>
#include <string.h>

// 交换两个元素
void Swap(ElementType *a, ElementType *b) {
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}


/**
 * @brief 选择排序 - 每次选择最小元素放到已排序序列末尾
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n²) 不稳定排序 原地排序
 *       适用场景：小规模数据或交换成本高的场景
 */
void SelectionSort(ElementType *Arr, const int length) {
    if (!Arr) {
        Warn("SelectionSort: Invalid Array!");
        return;
    }
    if (length <= 0) {
        Warn("SelectionSort: Invalid Length!");
        return;
    }
    for (int i = 0; i < length; ++i) {
        for (int j = i + 1; j < length; ++j) {
            if (Arr[j] < Arr[i]) { Swap(Arr + i, Arr + j); }
        }
    }
}

/**
 * @brief 插入排序 - 将元素插入到已排序序列的合适位置
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n²) 稳定排序 原地排序
 *       最佳情况O(n)，适合基本有序的小规模数据集
 */
void InsertionSort(ElementType *Arr, const size_t length) {
    if (!Arr) {
        Warn("InsertionSort: Invalid Array!");
        return;
    }
    if (length <= 0) {
        Warn("InsertionSort: Invalid Length!");
        return;
    }
    for (size_t i = 1; i < length; ++i) {
        ElementType temp = Arr[i];
        size_t j;
        for (j = i; j > 0 && temp < Arr[j - 1]; --j) { Arr[j] = Arr[j - 1]; }
        Arr[j] = temp;
    }
}

/**
 * @brief 冒泡排序 - 通过相邻元素比较交换进行排序
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n²) 稳定排序 原地排序
 *       优化后可添加提前终止标志，适合教学演示用途
 */
void BubbleSort(ElementType *Arr, int length) {
    if (!Arr) {
        Warn("BubbleSort: Invalid Array!");
        return;
    }
    if (length <= 0) {
        Warn("BubbleSort: Invalid Length!");
        return;
    }
    for (int i = length; i > 0; --i) {
        for (int j = 0; j < i - 1; ++j) {
            if (Arr[j] > Arr[j + 1]) { Swap(Arr + j, Arr + j + 1); }
        }
    }
}

/**
 * @brief 快速排序 - 分治法，选择基准元素进行分区排序
 *        原理： 将未排序的元素根据一个作为基准的“主元”(pivot)分为两个子序列，
 *              其中一个子序列的记录均大于主元， 而另一个子序列均小于主元，
 *              然后递归地对这两个子序列用类似的方法进行排序。
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 平均时间复杂度：O(n log n) 不稳定排序 原地排序
 *       实际中最快的通用排序算法，注意递归深度优化
 */
ElementType Median0fThree(ElementType *Arr, const size_t Left, const size_t Right) {
    if (!Arr) { return -1; }
    if (Right < Left) { return Arr[Right]; }
    const size_t Center = Left + (Right - Left) / 2;
    if (Arr[Left] > Arr[Center]) { Swap(&Arr[Center], &Arr[Left]); }
    if (Arr[Left] > Arr[Right]) { Swap(&Arr[Left], &Arr[Right]); }
    if (Arr[Center] > Arr[Right]) { Swap(&Arr[Center], &Arr[Right]); }
    // Now, Arr[Left] <= Arr[Center] <= Arr[Right]
    Swap(&Arr[Center], &Arr[Right - 1]);
    return Arr[Right - 1];
}

void QuickSortCore(ElementType *Arr, const size_t Left, const size_t Right) {
    // 核心递归函数
    if (!Arr || Right <= Left) { return; }
    const long Cutoff = 64;
    if (Right - Left >= Cutoff) {
        ElementType Pivot = Median0fThree(Arr, Left, Right);
        size_t Low = Left;
        size_t High = Right - 1;

        // 进行子集划分
        while (true) {
            // 在选择Pivot的过程中， 已经保证最小的元素在Left的位置上， 此处直接开始比较第二个值
            while (Low < Right && Arr[++Low] < Pivot) { }
            while (High > Left && Arr[--High] > Pivot) { }
            if (Low < High) { Swap(&Arr[Low], &Arr[High]); } else { break; }
        }
        Swap(&Arr[Right - 1], &Arr[Low]); // 将基准换到正确的位置

        // 递归进行排序
        QuickSortCore(Arr, Left, Low - 1);
        QuickSortCore(Arr, Low + 1, Right);
    } else {
        // 若元素数量过少， 直接调用插入排序进行解决
        InsertionSort(Arr, Right - Left + 1);
    }
}

void QuickSort(ElementType *Arr, const size_t length) { QuickSortCore(Arr, 0, length - 1); }


/**
 * @brief 归并排序 - 分治法，合并两个有序子序列
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n log n) 稳定排序 非原地排序
 *       需要O(n)额外空间，适合链表排序和大数据外部排序
 */
void MergeSort_Merge(ElementType *Arr, ElementType *TempArr, unsigned Left, unsigned Right, unsigned RightEnd);

void MergeSortCore(ElementType *Arr, ElementType *TempArr, unsigned Left, unsigned Right);

void MergeSort(ElementType *Arr, unsigned length) {
    if (!Arr) { return; }
    if (length == 1) { return; }
    if (length == 2) { InsertionSort(Arr, length); }
    ElementType *TempArr = malloc(length * sizeof(ElementType));
    if (!TempArr) {
        Warn("MergeSort: Memory Allocation Failed!");
        return;
    }
    MergeSortCore(Arr, TempArr, 0, length - 1);
    free(TempArr);
}

void MergeSortCore(ElementType *Arr, ElementType *TempArr, unsigned Left, unsigned Right) {
    // 核心递归排序函数
    if (Left >= Right) { return; }
    unsigned Center = (Left + Right) / 2;
    MergeSortCore(Arr, TempArr, Left, Center);
    MergeSortCore(Arr, TempArr, Center + 1, Right);
    MergeSort_Merge(Arr, TempArr, Left, Center + 1, Right);
}

void MergeSort_Merge(ElementType *Arr, ElementType *TempArr, unsigned Left, unsigned Right, unsigned RightEnd) {
    if (!Arr) { return; }
    if (!TempArr) { return; }
    const unsigned LeftEnd = Right - 1; // 左边终点位置
    const unsigned NumOfElements = RightEnd - Left + 1;
    unsigned Index = Left; // 有序数列起始位置

    while (Left <= LeftEnd && Right <= RightEnd) {
        if (Arr[Left] <= Arr[Right]) { TempArr[Index++] = Arr[Left++]; }
        else { TempArr[Index++] = Arr[Right++]; }
    }
    while (Left <= LeftEnd) { TempArr[Index++] = Arr[Left++]; }
    while (Right <= RightEnd) { TempArr[Index++] = Arr[Right++]; }
    for (int i = 0; i < NumOfElements; ++i, --RightEnd) { Arr[RightEnd] = TempArr[RightEnd]; }
}

