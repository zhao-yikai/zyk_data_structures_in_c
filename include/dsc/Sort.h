//
// Created by 趙熠楷 on 4/12/25.
//

#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <float.h>
#define SORT_ERROR (-DBL_MAX)

typedef double ElementType;

/**
 * @brief 选择排序 - 每次选择最小元素放到已排序序列末尾
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n²) 不稳定排序 原地排序
 *       适用场景：小规模数据或交换成本高的场景
 */
void SelectionSort(ElementType *Arr, int length);


/**
 * @brief 堆排序 - 通过构建最大堆实现排序
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n log n) 不稳定排序 原地排序
 *       优势：适合大数据量，且最坏情况仍保持O(n log n)
 */
void HeapSort(ElementType* Arr, int length);


/**
 * @brief 插入排序 - 将元素插入到已排序序列的合适位置
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n²) 稳定排序 原地排序
 *       最佳情况O(n)，适合基本有序的小规模数据集
 */
void InsertionSort(ElementType *Arr, size_t length);


/**
 * @brief 希尔排序 - 改进的插入排序，使用Sedgewick增量序列
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n^(3/2)) 不稳定排序 原地排序
 *       Sedgewick增量序列公式：9 * 4^i - 9 * 2^i + 1 和 4^i - 3 * 2^i + 1
 *       适合中等规模数据，实际性能优于简单插入排序
 */
void ShellSort(ElementType* Arr, int length);


/**
 * @brief 冒泡排序 - 通过相邻元素比较交换进行排序
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n²) 稳定排序 原地排序
 *       优化后可添加提前终止标志，适合教学演示用途
 */
void BubbleSort(ElementType* Arr, int length);


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
void QuickSort(ElementType *Arr, size_t length);


/**
 * @brief 归并排序 - 分治法，合并两个有序子序列
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n log n) 稳定排序 非原地排序
 *       需要O(n)额外空间，适合链表排序和大数据外部排序
 */
void MergeSort(ElementType* Arr, unsigned length);


/**
 * @brief 桶排序 - 将数据分布到有限数量的桶中，各自排序后合并
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(n + k) 稳定排序 非原地排序
 *       要求数据均匀分布，适合知道数据范围的场景（如0-1小数）
 */
void BucketSort(ElementType* Arr, unsigned length);


/**
 * @brief 基数排序 - 按位数从低位到高位进行稳定排序
 * @param Arr 待排序数组指针
 * @param length 数组元素个数
 * @note 时间复杂度：O(d*(n+k)) 稳定排序 非原地排序
 *       适合整数或定长字符串排序，d为最大位数
 */
void RadixSort(ElementType* Arr, unsigned length);

#endif //SORT_H
