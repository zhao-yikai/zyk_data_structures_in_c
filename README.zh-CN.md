# zyk_data_structures_in_c

[![Language](https://img.shields.io/badge/language-C99-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build System](https://img.shields.io/badge/build-CMake-informational.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](https://opensource.org/licenses/MIT)

> 数据结构课程学习记录：用 C（C99）实现常见数据结构与算法。

本仓库是我在学习《数据结构》（陈越、何钦明）课程/教材过程中编写的练习与笔记式实现。
目标是通过 **手写实现 + 小型测试** 来理解数据结构的核心操作、边界条件和复杂度。

## 目录
- [模块概览](#模块概览)
- [项目结构](#项目结构)
- [构建与运行](#构建与运行)
- [使用示例](#使用示例)
- [变更记录](#变更记录)

## 模块概览
> 以 `CMakeLists.txt` 中的模块列表为准（每个模块单独编译成静态库）。

- 线性结构：`SeqList`、`LinkedList`、`SeqStack`、`LinkedStack`、`SeqQueue`、`LinkedQueue`
- 树结构：`SeqBinaryTree`（开发中）、`LinkedBinaryTree`
- 算法：`Sort`（排序算法集合）
- 工具：`Warn`（彩色警告输出，供库代码防御式检查用）

## 项目结构
- `include/dsc/*.h`：公共 API 头文件（模块对外接口）
- `src/*.c`：模块实现
- `main.c`：唯一可执行文件 `ZYK_Data_Structures_In_C` 的测试入口（目前主要测试 `Sort`）
- `CMakeLists.txt`：CMake 构建脚本（每个模块一个静态库 + `warning` 工具库）

## 构建与运行
本项目推荐使用 out-of-source 构建：

```sh
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
./cmake-build-debug/ZYK_Data_Structures_In_C
```

说明：工程开启了 `CMAKE_EXPORT_COMPILE_COMMANDS ON`，便于 CLion/clangd 使用。

## 使用示例
> 头文件直接从 `include/dsc` 引入（CMake 已添加 include 路径）。

```c
#include "Sort.h"

int main(void) {
    ElementType arr[] = {3.14, 1.59, 2.65};
    QuickSort(arr, sizeof(arr) / sizeof(arr[0]));
    return 0;
}
```

## 变更记录
> 规则：每次对 **代码结构 / API / 构建方式 / 新增模块或算法** 做出可见变更，都需要在此追加一条记录。

### 2025-12-30
- 修复模块文件名不匹配：`src/SeqBInaryTree.c` → `src/SeqBinaryTree.c`（与 `CMakeLists.txt` 对齐）。
- 修复 `include/dsc/SeqBinaryTree.h` 的 typedef 拼写问题，并调整 `SeqBinaryTree_isEmpty` 的函数签名。
- 新增 `.github/copilot-instructions.md`：为 AI 代理提供仓库结构与编码约定。
