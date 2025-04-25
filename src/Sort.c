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

/**
 * @brief Select the median of three elements from the array as the pivot for quicksort.
 *
 * This function takes an array and two indices, Left and Right, and selects the median of the elements
 * at the left, center, and right positions. It then rearranges these three elements so that
 * Arr[Left] <= Arr[Center] <= Arr[Right], moves the median to the position Right - 1, and returns it.
 *
 * @param Arr Pointer to the array from which to select the pivot.
 * @param Left The left index of the subarray.
 * @param Right The right index of the subarray.
 * @return ElementType The median element selected as the pivot. If the array pointer is NULL, it returns -1.
 *                     If Right is less than Left, it returns Arr[Right].
 * @note This function modifies the original array by rearranging the left, center, and right elements.
 */
ElementType Median0fThree(ElementType *Arr, const size_t Left, const size_t Right) {
    // Check if the array pointer is NULL, return -1 if true
    if (!Arr) { return -1; }
    // If Right is less than Left, return Arr[Right]
    if (Right < Left) { return Arr[Right]; }
    // Calculate the center index of the subarray
    const size_t Center = Left + (Right - Left) / 2;
    // Ensure Arr[Left] <= Arr[Center]
    if (Arr[Left] > Arr[Center]) { Swap(&Arr[Center], &Arr[Left]); }
    // Ensure Arr[Left] <= Arr[Right]
    if (Arr[Left] > Arr[Right]) { Swap(&Arr[Left], &Arr[Right]); }
    // Ensure Arr[Center] <= Arr[Right]
    if (Arr[Center] > Arr[Right]) { Swap(&Arr[Center], &Arr[Right]); }
    // Now, Arr[Left] <= Arr[Center] <= Arr[Right]
    // Move the median to the position Right - 1
    Swap(&Arr[Center], &Arr[Right - 1]);
    // Return the median element
    return Arr[Right - 1];
}


/**
 * @brief The core recursive function for the quicksort algorithm.
 *
 * This function implements the core logic of the quicksort algorithm using the divide-and-conquer strategy.
 * It selects a pivot element, partitions the array around the pivot, and then recursively sorts the two sub-arrays.
 * If the number of elements in the sub-array is less than a predefined cutoff value, it uses insertion sort instead.
 *
 * @param Arr Pointer to the array to be sorted.
 * @param Left The left index of the sub-array to be sorted.
 * @param Right The right index of the sub-array to be sorted.
 *
 * @note The time complexity of this function is O(n log n) on average, but O(n²) in the worst case.
 *       It is an in-place sorting algorithm, which means it does not require additional space proportional to the input
 *       size.
 *       The `Median0fThree` function is used to select the pivot element, which helps to reduce the probability of
 *       worst-case performance.
 *       If the array pointer is NULL or the right index is less than or equal to the left index, the function returns immediately.
 */
void QuickSortCore(ElementType *Arr, const size_t Left, const size_t Right) {
    // 核心递归函数
    if (!Arr || Right <= Left) {
        // If the array pointer is NULL or the sub-array has 0 or 1 element, return immediately
        return;
    }
    // Define the cutoff value for switching to insertion sort
    const long Cutoff = 64;
    if (Right - Left >= Cutoff) {
        // Select the pivot using the Median0fThree function
        ElementType Pivot = Median0fThree(Arr, Left, Right);
        // Initialize the low and high pointers
        size_t Low = Left;
        size_t High = Right - 1;

        // Partition the sub-array around the pivot
        while (true) {
            // In the process of selecting the pivot, the smallest element is already at the Left position,
            // so start comparing from the second element
            while (Low < Right && Arr[++Low] < Pivot) {
            }
            while (High > Left && Arr[--High] > Pivot) {
            }
            if (Low < High) {
                // Swap elements if necessary
                Swap(&Arr[Low], &Arr[High]);
            } else {
                // Break the loop when the pointers cross
                break;
            }
        }
        // Move the pivot to its correct position
        Swap(&Arr[Right - 1], &Arr[Low]);

        // Recursively sort the left and right sub-arrays
        QuickSortCore(Arr, Left, Low - 1);
        QuickSortCore(Arr, Low + 1, Right);
    } else {
        // If the number of elements is less than the cutoff, use insertion sort
        InsertionSort(Arr, Right - Left + 1);
    }
}


/**
 * @brief Perform a quicksort on the given array.
 *
 * This function serves as a wrapper for the `QuickSortCore` function, which is the core recursive implementation of the
 * quicksort algorithm.
 * It initializes the sorting process by setting the left index to 0 and the right index to `length - 1`, covering the
 * entire array.
 *
 * @param Arr Pointer to the array to be sorted. The elements in this array should be of type `ElementType`.
 * @param length The number of elements in the array. This parameter determines the range of the array to be sorted.
 *
 * @note The quicksort algorithm has an average time complexity of O(n log n), but it can degrade to O(n²) in the worst
 * case.
 *       It is an in-place sorting algorithm, meaning it does not require additional space proportional to the input
 *       size.
 *       The `Median0fThree` function is used within `QuickSortCore` to select the pivot element, which helps to reduce
 *       the probability of worst-case performance.
 *       If the array pointer is NULL or the length is 0, the `QuickSortCore` function will handle these cases
 *       appropriately.
 */
void QuickSort(ElementType *Arr, const size_t length) { QuickSortCore(Arr, 0, length - 1); }


/**
 * @brief Merge Sort - A divide-and-conquer algorithm that merges two sorted sub-sequences.
 *
 * Merge sort is a stable sorting algorithm with a time complexity of O(n log n). It is not an in-place sorting algorithm
 * and requires O(n) additional space. It is suitable for sorting linked lists and large external datasets.
 *
 * @param Arr Pointer to the array to be sorted.
 * @param length The number of elements in the array.
 *
 * @note Time complexity: O(n log n). Stable sorting, not in-place. Requires O(n) extra space.
 *       Suitable for linked list sorting and large external data sorting.
 */
void MergeSort_Merge(ElementType *Arr, ElementType *TempArr, unsigned Left, unsigned Right, unsigned RightEnd);

/**
 * @brief The core recursive function for the merge sort algorithm.
 *
 * This function recursively divides the array into two halves until each sub-array contains at most one element.
 * Then it merges these sorted sub-arrays back together.
 *
 * @param Arr Pointer to the array to be sorted.
 * @param TempArr Pointer to the temporary array used for merging.
 * @param Left The left index of the current sub-array.
 * @param Right The right index of the current sub-array.
 */
void MergeSortCore(ElementType *Arr, ElementType *TempArr, unsigned Left, unsigned Right);

/**
 * @brief Performs a merge sort on the given array.
 *
 * This function initializes the merge sort process by allocating a temporary array and calling the core recursive function.
 * It handles edge cases such as null pointers and arrays with one or two elements.
 *
 * @param Arr Pointer to the array to be sorted.
 * @param length The number of elements in the array.
 */
void MergeSort(ElementType *Arr, unsigned length) {
    // Check if the array pointer is null, return immediately if true
    if (!Arr) { return; }
    // If the array has only one element, it is already sorted
    if (length == 1) { return; }
    // If the array has two elements, use insertion sort
    if (length == 2) { InsertionSort(Arr, length); }
    // Allocate memory for the temporary array
    ElementType *TempArr = malloc(length * sizeof(ElementType));
    // Check if memory allocation failed
    if (!TempArr) {
        // Log a warning if memory allocation fails
        Warn("MergeSort: Memory Allocation Failed!");
        return;
    }
    // Call the core recursive function to perform the merge sort
    MergeSortCore(Arr, TempArr, 0, length - 1);
    // Free the allocated memory
    free(TempArr);
}

/**
 * @brief The core recursive function for the merge sort algorithm.
 *
 * This function recursively divides the array into two halves until each sub-array contains at most one element.
 * Then it merges these sorted sub-arrays back together using the `MergeSort_Merge` function.
 *
 * @param Arr Pointer to the array to be sorted.
 * @param TempArr Pointer to the temporary array used for merging.
 * @param Left The left index of the current sub-array.
 * @param Right The right index of the current sub-array.
 */
void MergeSortCore(ElementType *Arr, ElementType *TempArr, unsigned Left, unsigned Right) {
    // Base case: if the left index is greater than or equal to the right index, the sub-array is sorted
    if (Left >= Right) { return; }
    // Calculate the center index of the sub-array
    unsigned Center = (Left + Right) / 2;
    // Recursively sort the left half of the sub-array
    MergeSortCore(Arr, TempArr, Left, Center);
    // Recursively sort the right half of the sub-array
    MergeSortCore(Arr, TempArr, Center + 1, Right);
    // Merge the two sorted sub-arrays
    MergeSort_Merge(Arr, TempArr, Left, Center + 1, Right);
}

/**
 * @brief Merges two sorted sub-arrays into one sorted array.
 *
 * This function takes two sorted sub-arrays from the original array and merges them into the temporary array.
 * Then it copies the merged elements back to the original array.
 *
 * @param Arr Pointer to the original array containing the sorted sub-arrays.
 * @param TempArr Pointer to the temporary array used for merging.
 * @param Left The left index of the first sub-array.
 * @param Right The left index of the second sub-array.
 * @param RightEnd The right index of the second sub-array.
 */
void MergeSort_Merge(ElementType *Arr, ElementType *TempArr, unsigned Left, unsigned Right, unsigned RightEnd) {
    // Check if the original array pointer is null, return immediately if true
    if (!Arr) { return; }
    // Check if the temporary array pointer is null, return immediately if true
    if (!TempArr) { return; }
    // Calculate the left end index of the first sub-array
    const unsigned LeftEnd = Right - 1;
    // Calculate the number of elements to be merged
    const unsigned NumOfElements = RightEnd - Left + 1;
    // Initialize the index for the temporary array
    unsigned Index = Left;

    // Compare elements from both sub-arrays and copy the smaller one to the temporary array
    while (Left <= LeftEnd && Right <= RightEnd) {
        if (Arr[Left] <= Arr[Right]) {
            TempArr[Index++] = Arr[Left++];
        } else {
            TempArr[Index++] = Arr[Right++];
        }
    }
    // Copy any remaining elements from the first sub-array
    while (Left <= LeftEnd) { TempArr[Index++] = Arr[Left++]; }
    // Copy any remaining elements from the second sub-array
    while (Right <= RightEnd) { TempArr[Index++] = Arr[Right++]; }
    // Copy the merged elements back to the original array
    for (int i = 0; i < NumOfElements; ++i, --RightEnd) { Arr[RightEnd] = TempArr[RightEnd]; }
}

