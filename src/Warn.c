/*
    Warn.c
    Created By YikaiSays on Mar 23 2025
    Modified with safety enhancements and output optimization
*/

#include "Warn.h"  // 使用双引号包含自定义头文件
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // 添加malloc/free支持

// 定义颜色代码常量
#define RED_COLOR    "\033[31m"
#define RESET_COLOR  "\033[0m"
#define BORDER_CHAR  '-'

void Warn(const char *message) {
    // 空指针保护
    if (!message) {
        fprintf(stderr, "%sWarning: Received NULL message pointer%s\n",
                RED_COLOR, RESET_COLOR);
        return;
    }

    const size_t msg_len = strlen(message);

    // 计算边框长度（消息长度 + 左右各一个空格）
    const size_t border_len = msg_len + 2;

    // 创建边框字符串（自动添加空终止符）
    char *border = (char*)malloc(border_len + 1);
    if (!border) {
        fprintf(stderr, "%sWarning: Memory allocation failed%s\n",
                RED_COLOR, RESET_COLOR);
        return;
    }
    memset(border, BORDER_CHAR, border_len);
    border[border_len] = '\0';

    // 输出带格式的警告信息
    printf("%s%s\n", RED_COLOR, border);      // 顶部边框
    printf(" %s \n", message);                // 带缩进的消息
    printf("%s%s%s\n\n", RED_COLOR, border, RESET_COLOR);

    free(border);
}

/* 示例输出（message = "Hello"）：
-------------
 Hello
-------------
*/
