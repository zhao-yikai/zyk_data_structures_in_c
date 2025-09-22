//
// Created by 趙熠楷 on 4/12/25.
//
#include <stdbool.h>

#include "Warn.h"
#include "Sort.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Swap two elements of type ElementType.
 *
 * This function takes two pointers to ElementType variables and exchanges their values.
 * It uses a temporary variable to hold the value of one of the elements during the swap process.
 *
 * @param a Pointer to the first ElementType variable.
 * @param b Pointer to the second ElementType variable.
 *
 * @note This function modifies the original variables pointed to by `a` and `b`.
 *       It assumes that `a` and `b` are valid pointers to ElementType variables.
 */
void Swap(ElementType *a, ElementType *b) {
    // Store the value of the first element in a temporary variable
    ElementType temp = *a;
    // Assign the value of the second element to the first element
    *a = *b;
    // Assign the value of the temporary variable to the second element
    *b = temp;
}



/**
 * @brief Selection Sort - Select the smallest element in each iteration and place it at the end of the sorted sequence.
 *
 * This function implements the selection sort algorithm. Selection sort divides the input array into two parts:
 * a sorted subarray at the beginning and an unsorted subarray at the end. In each iteration, it finds the minimum
 * element from the unsorted subarray and swaps it with the first element of the unsorted subarray, effectively
 * expanding the sorted subarray by one element.
 *
 * @param Arr Pointer to the array to be sorted. The elements in this array should be of type `ElementType`.
 * @param length The number of elements in the array. It determines the range of the array to be sorted.
 *
 * @note Time complexity: O(n²), where n is the number of elements in the array. This algorithm is not stable,
 *       meaning that the relative order of equal elements may not be preserved. It is an in-place sorting algorithm,
 *       which means it does not require additional space proportional to the input size. It is suitable for
 *       small-scale data or scenarios where the cost of swapping elements is high.
 *
 * @warning If the input array pointer `Arr` is `NULL`, a warning message will be logged, and the function will return
 *          immediately.
 * @warning If the input `length` is less than or equal to 0, a warning message will be logged, and the function will
 *          return immediately.
 */
void SelectionSort(ElementType *Arr, const int length) {
    // Check if the input array pointer is NULL
    if (!Arr) {
        // Log a warning if the array pointer is invalid
        Warn("SelectionSort: Invalid Array!");
        return;
    }
    // Check if the input length is less than or equal to 0
    if (length <= 0) {
        // Log a warning if the length is invalid
        Warn("SelectionSort: Invalid Length!");
        return;
    }
    // Outer loop: Iterate through the array to expand the sorted subarray
    for (int i = 0; i < length; ++i) {
        // Inner loop: Find the minimum element from the unsorted subarray
        for (int j = i + 1; j < length; ++j) {
            // If a smaller element is found, swap it with the current element
            if (Arr[j] < Arr[i]) {
                Swap(Arr + i, Arr + j);
            }
        }
    }
}


/**
 * @brief Insertion Sort - Insert an element into the appropriate position in the sorted sequence.
 *
 * This function implements the insertion sort algorithm. Insertion sort builds the final sorted array one item at
 * a time.
 * It iterates through the array, taking each element and inserting it into its correct position in the already sorted
 * part of the array.
 *
 * @param Arr Pointer to the array to be sorted. The elements in this array should be of type `ElementType`.
 * @param length The number of elements in the array. It determines the range of the array to be sorted.
 *
 * @note Time complexity: O(n²) in the average and worst cases, but O(n) in the best case (when the array is already
 * sorted).
 *       It is a stable sorting algorithm, meaning that the relative order of equal elements is preserved.
 *       It is an in-place sorting algorithm, which means it does not require additional space proportional to the input
 *       size.
 *       It is suitable for small-scale datasets or datasets that are nearly sorted.
 *
 * @warning If the input array pointer `Arr` is `NULL`, a warning message will be logged, and the function will return
 *          immediately.
 * @warning If the input `length` is less than or equal to 0, a warning message will be logged, and the function will
 *          return immediately.
 */
void InsertionSort(ElementType *Arr, const size_t length) {
    // Check if the input array pointer is NULL
    if (!Arr) {
        // Log a warning if the array pointer is invalid
        Warn("InsertionSort: Invalid Array!");
        return;
    }
    // Check if the input length is less than or equal to 0
    if (length <= 0) {
        // Log a warning if the length is invalid
        Warn("InsertionSort: Invalid Length!");
        return;
    }
    // Iterate through the array starting from the second element
    for (size_t i = 1; i < length; ++i) {
        // Store the current element in a temporary variable
        ElementType temp = Arr[i];
        // Declare a variable to track the position to insert the element
        size_t j;
        // Shift elements greater than the current element to the right
        for (j = i; j > 0 && temp < Arr[j - 1]; --j) {
            Arr[j] = Arr[j - 1];
        }
        // Insert the current element into its correct position
        Arr[j] = temp;
    }
}


/**
 * @brief Implements the bubble sort algorithm to sort an array.
 *
 * Bubble sort is a simple sorting algorithm that repeatedly steps through the list to be sorted,
 * compares each pair of adjacent items and swaps them if they are in the wrong order.
 * The pass through the list is repeated until the list is sorted.
 *
 * @param Arr Pointer to the array to be sorted. The elements in this array should be of type `ElementType`.
 * @param length The number of elements in the array. It determines the range of the array to be sorted.
 *
 * @note The time complexity of this algorithm is O(n²), where n is the number of elements in the array.
 *       It is a stable sorting algorithm, meaning that the relative order of equal elements is preserved.
 *       It is an in - place sorting algorithm, which means it does not require additional space proportional to the
 *       input size.
 *       This algorithm can be optimized by adding an early termination flag. It is mainly used for teaching
 *       demonstration purposes.
 *
 * @warning If the input array pointer `Arr` is `NULL`, a warning message will be logged, and the function will return
 *          immediately.
 * @warning If the input `length` is less than or equal to 0, a warning message will be logged, and the function will
 *          return immediately.
 */
void BubbleSort(ElementType *Arr, const int length) {
    // Check if the input array pointer is NULL
    if (!Arr) {
        // Log a warning if the array pointer is invalid
        Warn("BubbleSort: Invalid Array!");
        return;
    }
    // Check if the input length is less than or equal to 0
    if (length <= 0) {
        // Log a warning if the length is invalid
        Warn("BubbleSort: Invalid Length!");
        return;
    }
    // Outer loop controls the number of passes
    for (int i = length; i > 0; --i) {
        // Inner loop compares adjacent elements
        for (int j = 0; j < i - 1; ++j) {
            // Swap adjacent elements if they are in the wrong order
            if (Arr[j] > Arr[j + 1]) { Swap(Arr + j, Arr + j + 1); }
        }
    }
}


/**
 * @brief Quick Sort - A divide-and-conquer algorithm that partitions the array around a pivot element.
 *        Principle: Divide the unsorted elements into two sub-sequences based on a "pivot" element.
 *                   One sub-sequence contains elements greater than the pivot, and the other contains elements smaller
 *                   than the pivot.
 *                   Then recursively sort these two sub-sequences using a similar method.
 * @param Arr Pointer to the array to be sorted.
 * @param Left
 * @param Right
 * @param length The number of elements in the array.
 * @note Average time complexity: O(n log n). Unstable sorting. In-place sorting.
 *       It is the fastest general-purpose sorting algorithm in practice. Pay attention to recursive depth optimization.
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
 *       If the array pointer is NULL or the right index is less than or equal to the left index, the function returns
 *       immediately.
 */
void QuickSortCore(ElementType *Arr, const size_t Left, const size_t Right) {
    // Core recursive function
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
 * @param TempArr
 * @param Left
 * @param Right
 * @param RightEnd
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

