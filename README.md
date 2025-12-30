# zyk_data_structures_in_c

[![Language](https://img.shields.io/badge/language-C99-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build System](https://img.shields.io/badge/build-CMake-informational.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](https://opensource.org/licenses/MIT)

> Data Structures course study notes: common data structures and algorithms implemented in C (C99).

This repository is my hands-on implementation notebook while studying **Data Structures** using the textbook/course
**《数据结构》 (Chen Yue / 陈越, He Qinming / 何钦明)**.
The goal is to internalize the core operations, edge cases, and complexity trade-offs by writing the code from scratch
and validating it with a small local test harness.

- 中文版 README: see [`README.zh-CN.md`](./README.zh-CN.md)

## Contents
- [Modules](#modules)
- [Project layout](#project-layout)
- [Build & run](#build--run)
- [Example](#example)
- [Change log](#change-log)

## Modules
> The authoritative list is in `CMakeLists.txt` (`DATA_STRUCTURES`). Each module is built as a separate static library.

- Linear structures: `SeqList`, `LinkedList`, `SeqStack`, `LinkedStack`, `SeqQueue`, `LinkedQueue`
- Trees: `SeqBinaryTree` (in progress), `LinkedBinaryTree`
- Algorithms: `Sort` (sorting algorithms)
- Utility: `Warn` (colored warning output used by modules for defensive checks)

## Project layout
- `include/dsc/*.h`: public module headers (APIs)
- `src/*.c`: module implementations
- `main.c`: the single executable test harness (`ZYK_Data_Structures_In_C`, currently focused on `Sort`)
- `CMakeLists.txt`: CMake build (one static library per module + `warning` utility lib)

## Build & run
This project is intended to be built out-of-source with CMake:

```sh
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
./cmake-build-debug/ZYK_Data_Structures_In_C
```

Note: `CMAKE_EXPORT_COMPILE_COMMANDS` is enabled to generate `compile_commands.json` for IDEs/clangd.

## Example
Headers are included directly from `include/dsc` (CMake already configures the include path):

```c
#include "Sort.h"

int main(void) {
    ElementType arr[] = {3.14, 1.59, 2.65};
    QuickSort(arr, sizeof(arr) / sizeof(arr[0]));
    return 0;
}
```

## Change log
> Rule: for any user-visible change (API/module/build/new algorithm), append an entry here.

### 2025-12-30
- Fixed module filename mismatch: renamed `src/SeqBInaryTree.c` -> `src/SeqBinaryTree.c` to match `CMakeLists.txt`.
- Updated `include/dsc/SeqBinaryTree.h` typedef typo (`SeqBinayTreePtr` -> `SeqBinaryTreePtr`) and adjusted `SeqBinaryTree_isEmpty` signature to accept `SeqBinaryTree`.
- Added `.github/copilot-instructions.md` to guide AI coding agents working in this repo.
