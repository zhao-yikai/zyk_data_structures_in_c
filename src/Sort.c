//
// Created by 趙熠楷 on 4/12/25.
//
#include "Sort.h"
#include "Warn.h"

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
void InsertionSort(ElementType *Arr, const int length) {
    if (!Arr) {
        Warn("InsertionSort: Invalid Array!");
        return;
    }
    if (length <= 0) {
        Warn("InsertionSort: Invalid Length!");
        return;
    }
    for (int i = 1; i < length; ++i) {
        ElementType temp = Arr[i];
        int j;
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
