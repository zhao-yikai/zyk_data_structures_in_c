#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "Sort.h"

/* 函数声明 */
double* generate_random_double_array(size_t size);
void print_array_samples(const double* arr, size_t size);
void print_array(const double* arr, size_t size);

double* generate_random_double_array(size_t size) {
    const double RANGE = 1000000;

    // 使用calloc防止乘法溢出
    double* arr = (double*)calloc(size, sizeof(double));
    if (!arr) {
        perror("数组内存分配失败");
        return NULL;
    }

    // 使用更精确的随机数生成方式
    for (size_t i = 0; i < size; i++) {
        double normalized = (double)rand() / (RAND_MAX + 1.0);
        arr[i] = normalized * RANGE - RANGE/2;
    }

    return arr;
}

void print_array_samples(const double* arr, size_t size) {
    printf("数组样本数据 (前%zu个):\n", (size > 10) ? 10 : size);
    for (size_t i = 0; i < size && i < 10; i++) {
        printf("[%06zu] %+10.4f\n", i, arr[i]);
    }
}

void print_array(const double* arr, size_t size) {
    printf("完整数组数据 (%zu 元素):\n", size);
    for (size_t i = 0; i < size; i++) {
        printf("[%06zu] %+10.4f\n", i, arr[i]);
    }
}

int main() {
    // uint64_t element_count = 0;
    // printf("请输入数组长度: ");
    //
    // // 使用无符号64位整数输入
    // if (scanf("%llu", &element_count) != 1 || element_count == 0) {
    //     fprintf(stderr, "错误：请输入有效的正整数\n");
    //     return EXIT_FAILURE;
    // }

    for (uint64_t element_count = 1; element_count<2^32; element_count*=2) {
        printf("-----------------\n");
        printf("元素个数: %llu\n", element_count);
        // 检查实际可分配的内存大小
        const size_t max_safe_size = SIZE_MAX / sizeof(double);
        if (element_count > max_safe_size) {
            fprintf(stderr, "错误：请求的数组大小超过系统限制 (%zu)\n", max_safe_size);
            return EXIT_FAILURE;
        }

        srand((unsigned int)time(NULL));
        double* my_array = generate_random_double_array((size_t)element_count);

        if (!my_array) {
            return EXIT_FAILURE;
        }

        // 添加内存分配成功后的检查
        printf("已成功分配 %.2f MB 内存\n",
              (double)element_count * sizeof(double) / (1024 * 1024));



        /* 使用安全排序函数接口 */
        if (element_count > INT_MAX) {
            fprintf(stderr, "警告：元素数量超过INT_MAX，请确保排序函数支持size_t类型\n");
        }


        // 调用排序算法（需确保Sort.h中的函数参数类型为size_t）
        clock_t t1 = clock();
        // QuickSort(my_array, (size_t)element_count);
        // InsertionSort(my_array, (size_t)element_count);
        MergeSort(my_array, element_count);
        clock_t t2 = clock();

        // 打印部分结果防止溢出
        print_array_samples(my_array, (size_t)element_count);


        printf("耗时: %.6f 秒\n", (double)(t2-t1)/CLOCKS_PER_SEC);
        printf("排序速度: %.2f 万元素/秒\n",
              element_count / ((double)(t2-t1)/CLOCKS_PER_SEC) / 10000);

        free(my_array);
    }


    return EXIT_SUCCESS;
}
