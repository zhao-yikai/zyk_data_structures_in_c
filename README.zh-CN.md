# zyk_data_structures_in_c

[![Language](https://img.shields.io/badge/language-C99-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build System](https://img.shields.io/badge/build-Make-informational.svg)](https://www.gnu.org/software/make/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](https://opensource.org/licenses/MIT)

> 数据结构课程学习记录：用 C（C99）实现常见数据结构与算法。

本仓库是我在学习《数据结构》（Chen Yue / 陈越, He Qinming / 何钦明）课程/教材过程中编写的练习与笔记式实现。
目标是通过 **手写实现 + 小型测试** 来理解数据结构的核心操作、边界条件和复杂度取舍。

- 英文版 README：见 [`README.md`](./README.md)

## 目录
- [模块概览](#模块概览)
- [项目结构](#项目结构)
- [构建与运行](#构建与运行)
- [使用示例](#使用示例)
- [变更记录](#变更记录)

## 模块概览
> 模块列表定义在 `Makefile` 的 `DS_MODULES` 变量中。

- 线性结构：`SeqList`、`LinkedList`、`SeqStack`、`LinkedStack`、`SeqQueue`、`LinkedQueue`
- 树结构：`SeqBinaryTree`（开发中）、`LinkedBinaryTree`
- 算法：`Sort`（排序算法集合）
- 工具：`Warn`（彩色警告输出，供库代码防御式检查用）

## 项目结构
- `include/dsc/*.h`：公共 API 头文件（模块对外接口）
- `src/*.c`：模块实现
- `main.c`：唯一可执行文件 `ZYK_Data_Structures_In_C` 的测试入口
- `Makefile`：构建脚本（无需 CMake！）

## 构建与运行
本项目使用 **Makefile** 构建（macOS/Linux 自带 `make`，无需安装任何东西）：

```sh
make          # 构建项目
make run      # 构建并运行
make clean    # 清理构建产物
make rebuild  # 完全重建
make help     # 查看所有命令
```

构建产物在 `build/` 目录下，可执行文件为 `build/ZYK_Data_Structures_In_C`。

## 使用示例
> 头文件直接从 `include/dsc` 引入。

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

### 2025-12-31 (VSCode 配置与编译警告修复)
- **NEW**: 添加 VSCode C/C++ IntelliSense 配置
  - `.vscode/c_cpp_properties.json` - 头文件路径配置
  - `.vscode/settings.json` - 编辑器设置
  - `compile_commands.json` - 编译命令数据库
- **FIX**: 修复所有编译警告
  - 修复函数原型：`Create()` → `Create(void)` (C99 严格模式)
  - 添加文件末尾换行符

### 2025-12-31 (构建系统简化)
- **CHANGE**: 移除 CMake，改用简单的 Makefile
  - macOS/Linux 自带 `make`，无需安装任何工具
  - 简单命令：`make`、`make run`、`make clean`、`make rebuild`
  - 构建产物在 `build/` 目录
  - 删除了 `CMakeLists.txt`、`cmake-build-debug/`、`.idea/`

### 2025-12-31
- **FIX**: 移除 `Common.h` 中全局的 `Position` typedef，解决其与 `LinkedQueue.c`、`LinkedBinaryTree.c` 中模块内 `Position` 类型的冲突
- **NEW**: 完整重构 `main.c` - "THE MATRIX: Data Structure Edition"
  - Matrix 风格数字雨动画：使用 `SeqQueue` 保存帧历史
  - 系统初始化演示：使用 `SeqList` 模拟模块加载
  - 网络追踪演示：使用 `LinkedList` 追踪 IP 节点
  - 调用栈演示：同时使用 `SeqStack` 与 `LinkedStack`
  - 消息队列演示：使用 `SeqQueue` 与 `LinkedQueue`
  - 决策树可视化：使用 `SeqBinaryTree`
  - 排序基准测试：测试 5 种算法（Selection、Bubble、Quick、Merge、Insertion）
  - 综合 "hack simulation"：同时使用所有数据结构
  - 完整 ANSI 颜色支持（Matrix 绿色主题）

### 2025-12-30 (Evening)
- **NEW**: 以 "Matrix" 主题重写 `main.c` 交互式演示程序：
  - 展示所有数据结构：`SeqList`、`LinkedList`、`SeqStack`、`LinkedStack`、`SeqQueue`、`LinkedQueue`
  - 演示 5 种排序算法：`InsertionSort`、`QuickSort`、`BubbleSort`、`SelectionSort`、`MergeSort`
  - 赛博朋克风格：ANSI 颜色、Matrix 风格代码雨、打字机动画
  - 包含 5 个主题模块：Neural Network Sim、Memory Chain Analysis、Call Stack Trace、Packet Stream、Decryption
  - 通过 extern 声明解决模块间 `ElementType` typedef 冲突

### 2025-12-30
- 修复模块文件名不匹配：`src/SeqBInaryTree.c` → `src/SeqBinaryTree.c`（与 `CMakeLists.txt` 对齐）。
- 修复 `include/dsc/SeqBinaryTree.h` 的 typedef 拼写问题，并调整 `SeqBinaryTree_isEmpty` 的函数签名。
- 新增 `.github/copilot-instructions.md`：为 AI 代理提供仓库结构与编码约定。
