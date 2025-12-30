/*
    Common.h
    Common type definitions for all data structure modules
    Created By YikaiSays on Dec 30 2025

    统一类型定义，解决各模块 ElementType 冲突问题
*/

#ifndef DSC_COMMON_H
#define DSC_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>

/*
 * 统一的元素类型定义
 * 使用 double 作为通用类型，可以同时表示整数和浮点数
 * 所有模块统一使用此类型
 */
typedef double ElementType;

/*
 * 错误值定义
 * 用于函数返回错误时的标记值
 */
#define DSC_ERROR       (-DBL_MAX)
#define DSC_INT_ERROR   INT64_MIN

/*
 * 通用长度类型
 */
typedef int_fast64_t Length;

/*
 * 通用位置类型
 * 注意：各模块可能有自己的 Position 类型定义，避免直接使用此名称
 */
/* typedef int Position; */ /* 已移除，避免与模块内部类型冲突 */

#endif // DSC_COMMON_H

