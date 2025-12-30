#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>

// 包含您要测试的排序函数的头文件
#include "Sort.h"

// --- 辅助函数声明 ---

// 生成各种测试数组
ElementType* generate_random_array(size_t size, double min_val, double max_val);
ElementType* generate_sorted_array(size_t size);
ElementType* generate_reverse_sorted_array(size_t size);
ElementType* generate_array_with_duplicates(size_t size, int num_distinct);

// 数组操作
void print_array(const char* title, const ElementType* arr, size_t size);
bool is_sorted(const ElementType* arr, size_t size);
ElementType* copy_array(const ElementType* arr, size_t size);

// --- 排序函数包装器 ---
// 由于原始函数签名不统一，使用包装器统一为 void(ElementType*, size_t)

void SelectionSort_wrapper(ElementType* arr, size_t length) {
    SelectionSort(arr, (int)length);
}

void BubbleSort_wrapper(ElementType* arr, size_t length) {
    BubbleSort(arr, (int)length);
}

void MergeSort_wrapper(ElementType* arr, size_t length) {
    MergeSort(arr, (unsigned)length);
}

// --- 测试框架 ---

// 定义一个结构体来存储排序算法的名称和函数指针
typedef struct {
    const char* name;
    void (*func)(ElementType*, size_t);
} SortAlgorithm;

// 运行单个测试用例
void run_test(SortAlgorithm algorithm, const char* test_case_name, ElementType* arr, size_t size);


int main() {
    // 设置随机数种子
    srand((unsigned int)time(NULL));

    // 定义要测试的排序算法数组
    SortAlgorithm algorithms[] = {
        {"SelectionSort", SelectionSort_wrapper},
        {"InsertionSort", InsertionSort},
        {"BubbleSort",    BubbleSort_wrapper},
        {"QuickSort",     QuickSort},
        {"MergeSort",     MergeSort_wrapper}
        // 注意: HeapSort, ShellSort 等在 Sort.c 中未实现，故不在此测试
    };
    int num_algorithms = sizeof(algorithms) / sizeof(algorithms[0]);

    printf("====================================================\n");
    printf("           SORTING ALGORITHM TEST SUITE\n");
    printf("====================================================\n\n");

    // --- 1. 正确性测试 (小规模数组) ---
    printf("--- 1. Correctness Test (Small Array) ---\n");
    size_t small_size = 15;
    ElementType* original_small = generate_random_array(small_size, 0.0, 100.0);
    print_array("Original Small Array", original_small, small_size);
    for (int i = 0; i < num_algorithms; ++i) {
        ElementType* arr_copy = copy_array(original_small, small_size);
        printf("\nTesting %s...\n", algorithms[i].name);
        algorithms[i].func(arr_copy, small_size);
        print_array("Sorted Array", arr_copy, small_size);
        printf("Verification: %s\n", is_sorted(arr_copy, small_size) ? "PASSED" : "FAILED");
        free(arr_copy);
    }
    free(original_small);
    printf("\n--------------------------------------------\n\n");


    // --- 2. 边缘情况测试 ---
    printf("--- 2. Edge Case Tests ---\n");
    for (int i = 0; i < num_algorithms; ++i) {
        printf("\nTesting %s with edge cases...\n", algorithms[i].name);

        // a) NULL 数组 (部分算法内部未必做保护；测试框架这里保证不崩溃)
        printf("  - NULL array: ");
        // QuickSort 等实现可能没有对 NULL 做防御式检查；这里仅验证 wrapper 层不崩溃。
        if (algorithms[i].func == QuickSort) {
            printf("SKIPPED (QuickSort implementation may not accept NULL)\n");
        } else {
            algorithms[i].func(NULL, 10);
            printf("PASSED (no crash)\n");
        }

        // b) 长度为 0 的数组
        printf("  - Size 0 array: ");
        ElementType* arr_zero = malloc(0);
        algorithms[i].func(arr_zero, 0);
        printf("%s\n", is_sorted(arr_zero, 0) ? "PASSED" : "FAILED");
        free(arr_zero);

        // c) 长度为 1 的数组
        printf("  - Size 1 array: ");
        ElementType arr_one[] = { 123.45 };
        algorithms[i].func(arr_one, 1);
        printf("%s\n", is_sorted(arr_one, 1) ? "PASSED" : "FAILED");
    }
    printf("\n--------------------------------------------\n\n");


    // --- 3. 性能和鲁棒性测试 (不同数据模式和规模) ---
    printf("--- 3. Performance and Robustness Tests ---\n");
    size_t test_sizes[] = {100, 2000, 10000}; // O(n^2) 算法在 10000 时会很慢
    int num_sizes = sizeof(test_sizes) / sizeof(test_sizes[0]);

    for (int i = 0; i < num_sizes; ++i) {
        size_t current_size = test_sizes[i];
        printf("\n================== Testing with array size: %zu ==================\n", current_size);

        // a) 随机数据
        ElementType* random_arr = generate_random_array(current_size, -1000.0, 1000.0);
        for (int j = 0; j < num_algorithms; ++j) {
            // 对于 O(n^2) 算法，当数据量太大时跳过测试以节省时间
            if ((strcmp(algorithms[j].name, "SelectionSort") == 0
                 || strcmp(algorithms[j].name, "InsertionSort") == 0
                 || strcmp(algorithms[j].name, "BubbleSort") == 0) && current_size > 5000) {
                printf("[SKIPPED] %-15s  Case: Random Data         Size: %-7zu (too slow)\n", algorithms[j].name, current_size);
                continue;
            }
            run_test(algorithms[j], "Random Data", random_arr, current_size);
        }
        free(random_arr);

        // b) 已排序数据
        ElementType* sorted_arr = generate_sorted_array(current_size);
        for (int j = 0; j < num_algorithms; ++j) {
            run_test(algorithms[j], "Sorted Data", sorted_arr, current_size);
        }
        free(sorted_arr);

        // c) 逆序数据
        ElementType* reverse_arr = generate_reverse_sorted_array(current_size);
        for (int j = 0; j < num_algorithms; ++j) {
            if ((strcmp(algorithms[j].name, "BubbleSort") == 0) && current_size > 5000) {
                 printf("[SKIPPED] %-15s | Case: Reverse Sorted Data| Size: %-7zu (too slow)\n", algorithms[j].name, current_size);
                 continue;
            }
            run_test(algorithms[j], "Reverse Sorted Data", reverse_arr, current_size);
        }
        free(reverse_arr);

        // d) 大量重复数据
        ElementType* duplicate_arr = generate_array_with_duplicates(current_size, 10); // 只有10个不同的值
        for (int j = 0; j < num_algorithms; ++j) {
            run_test(algorithms[j], "Many Duplicates", duplicate_arr, current_size);
        }
        free(duplicate_arr);
    }

    printf("\n====================================================\n");
    printf("                 TESTING COMPLETE\n");
    printf("====================================================\n");

    return 0;
}


// --- 辅助函数实现 ---

void run_test(SortAlgorithm algorithm, const char* test_case_name, ElementType* arr, size_t size) {
    ElementType* arr_copy = copy_array(arr, size);
    if (!arr_copy && size > 0) {
        printf("Failed to allocate memory for test.\n");
        return;
    }

    clock_t start = clock();
    algorithm.func(arr_copy, size);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    bool success = is_sorted(arr_copy, size);

    printf("%-15s | Case: %-20s | Size: %-7zu | Time: %-10.5f s | Verification: %s\n",
           algorithm.name, test_case_name, size, time_spent, success ? "PASSED" : "FAILED");

    assert(success); // 如果排序失败，程序将终止
    free(arr_copy);
}

ElementType* generate_random_array(size_t size, double min_val, double max_val) {
    if (size == 0) return malloc(0);
    ElementType* arr = (ElementType*)malloc(size * sizeof(ElementType));
    if (!arr) return NULL;
    for (size_t i = 0; i < size; ++i) {
        arr[i] = min_val + ((double)rand() / RAND_MAX) * (max_val - min_val);
    }
    return arr;
}

ElementType* generate_sorted_array(size_t size) {
    if (size == 0) return malloc(0);
    ElementType* arr = (ElementType*)malloc(size * sizeof(ElementType));
    if (!arr) return NULL;
    for (size_t i = 0; i < size; ++i) {
        arr[i] = (ElementType)i;
    }
    return arr;
}

ElementType* generate_reverse_sorted_array(size_t size) {
    if (size == 0) return malloc(0);
    ElementType* arr = (ElementType*)malloc(size * sizeof(ElementType));
    if (!arr) return NULL;
    for (size_t i = 0; i < size; ++i) {
        arr[i] = (ElementType)(size - 1 - i);
    }
    return arr;
}

ElementType* generate_array_with_duplicates(size_t size, int num_distinct) {
    if (size == 0) return malloc(0);
    ElementType* arr = (ElementType*)malloc(size * sizeof(ElementType));
    if (!arr) return NULL;
    for (size_t i = 0; i < size; ++i) {
        arr[i] = (ElementType)(rand() % num_distinct);
    }
    return arr;
}

void print_array(const char* title, const ElementType* arr, size_t size) {
    printf("%s (%zu elements):\n", title, size);
    if (size == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (size_t i = 0; i < size; ++i) {
        printf("%.2f", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

bool is_sorted(const ElementType* arr, size_t size) {
    if (size <= 1) {
        return true;
    }
    for (size_t i = 0; i < size - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

ElementType* copy_array(const ElementType* arr, size_t size) {
    if (size == 0) return malloc(0);
    ElementType* new_arr = (ElementType*)malloc(size * sizeof(ElementType));
    if (!new_arr) return NULL;
    memcpy(new_arr, arr, size * sizeof(ElementType));
    return new_arr;
}