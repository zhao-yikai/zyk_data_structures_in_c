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
 * @brief TimSort - 混合排序算法（归并+插入），Python内置算法
 * @param Arr 待排序数组指针
 * @param length 待排数组长度
 * @note 时间复杂度：O(n log n) 稳定排序 需要O(n)空间
 *       特点：利用数据现有有序性（自然游程），适合真实世界数据
 *       实现要点：
 *       1. 定义最小游程长度（通常32-64）
 *       2. 查找自然游程并进行插入排序扩展
 *       3. 使用归并排序合并游程
 */
/* 预分配合并缓冲区 */
static ElementType* g_merge_buffer = NULL;
static size_t g_buffer_size = 0;

/* 最小合并分段大小 */
#define MIN_MERGE 64

/* 运行栈结构体 */
typedef struct {
    size_t start;
    size_t length;
} Run;

/* 初始化TimSort环境 */
void TimSort_Init(size_t max_elements) {
    g_buffer_size = max_elements / 2;
    g_merge_buffer = malloc(g_buffer_size * sizeof(ElementType));
}

/* 清理TimSort环境 */
void TimSort_Cleanup() {
    free(g_merge_buffer);
    g_merge_buffer = NULL;
    g_buffer_size = 0;
}

/* 计算最小run长度 */
static size_t ComputeMinrun(size_t n) {
    size_t r = 0;
    while (n >= MIN_MERGE) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

/* 反转数组区间 */
static void Reverse(ElementType* arr, size_t start, size_t end) {
    while (start < end) {
        ElementType tmp = arr[start];
        arr[start++] = arr[end];
        arr[end--] = tmp;
    }
}

/* 二分插入排序 */
static void BinaryInsertionSort(ElementType* arr, size_t len) {
    for (size_t i = 1; i < len; ++i) {
        ElementType key = arr[i];
        size_t left = 0;
        size_t right = i;

        while (left < right) {
            size_t mid = left + (right - left)/2;
            if (key < arr[mid]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        size_t shift_pos = i;
        while (shift_pos > left) {
            arr[shift_pos] = arr[shift_pos-1];
            --shift_pos;
        }
        arr[left] = key;
    }
}

/* 扩展并排序短run */
static void ExtendAndSort(ElementType* arr, size_t start, size_t minrun, size_t max_pos) {
    size_t end = start + minrun;
    if (end > max_pos) end = max_pos;

    BinaryInsertionSort(arr + start, end - start);
}

/* 智能合并实现 */
static void SmartMerge(ElementType* arr, Run* left, Run* right) {
    const size_t l_start = left->start;
    const size_t l_len = left->length;
    const size_t r_len = right->length;

    // 使用预分配缓冲区合并
    if (l_len <= r_len && l_len <= g_buffer_size) {
        memcpy(g_merge_buffer, arr + l_start, l_len * sizeof(ElementType));

        size_t i = 0, j = 0, k = l_start;
        const size_t r_start = left->start + left->length;

        while (i < l_len && j < r_len) {
            arr[k++] = (g_merge_buffer[i] <= arr[r_start + j]) ?
                g_merge_buffer[i++] : arr[r_start + j++];
        }

        while (i < l_len) arr[k++] = g_merge_buffer[i++];
    }
    else {
        // 回退到原地合并
        size_t i = l_start + l_len - 1;
        size_t j = r_len - 1;
        size_t k = l_start + l_len + r_len - 1;

        while (j != SIZE_MAX) {
            if (i != SIZE_MAX && arr[i] > arr[left->start + l_len + j]) {
                arr[k--] = arr[i--];
            } else {
                arr[k--] = arr[left->start + l_len + j--];
            }
        }
    }

    left->length += right->length;
}

/* 合并栈平衡 */
static void MergeCollapse(ElementType* arr, Run* stack, size_t* stack_top) {
    while (*stack_top > 1) {
        size_t n = *stack_top - 1;

        if (*stack_top >= 3 && stack[n-2].length <= stack[n-1].length + stack[n].length) {
            if (stack[n-2].length < stack[n].length) {
                SmartMerge(arr, &stack[n-2], &stack[n-1]);
                stack[n-2].length += stack[n-1].length;
                stack[n-1] = stack[n];
                (*stack_top)--;
            } else {
                SmartMerge(arr, &stack[n-1], &stack[n]);
                (*stack_top)--;
            }
        }
        else if (stack[n-1].length <= stack[n].length) {
            SmartMerge(arr, &stack[n-1], &stack[n]);
            (*stack_top)--;
        }
        else {
            break;
        }
    }
}

/* TimSort主函数 */
void Sort(ElementType* arr, size_t length) {
    if (length < 2) return;

    const size_t minrun = ComputeMinrun(length);
    Run stack[48] = {0};
    size_t stack_top = 0;
    size_t pos = 0;

    while (pos < length) {
        size_t run_start = pos;

        // 寻找自然run
        size_t run_end = pos + 1;
        while (run_end < length && arr[run_end-1] <= arr[run_end]) {
            ++run_end;
        }

        // 处理递减序列
        if (arr[run_end-1] < arr[run_start]) {
            Reverse(arr, run_start, run_end-1);
        }

        size_t current_run_len = run_end - run_start;

        // 扩展短run
        if (current_run_len < minrun) {
            const size_t remain = length - pos;
            ExtendAndSort(arr, run_start, minrun, pos + remain);
            current_run_len = (remain > minrun) ? minrun : remain;
            run_end = run_start + current_run_len;
        }

        // 压入运行栈
        stack[stack_top++] = (Run){run_start, current_run_len};
        pos = run_end;

        // 执行合并平衡
        MergeCollapse(arr, stack, &stack_top);
    }

    // 强制合并剩余run
    while (stack_top > 1) {
        SmartMerge(arr, &stack[stack_top-2], &stack[stack_top-1]);
        stack_top--;
    }
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

