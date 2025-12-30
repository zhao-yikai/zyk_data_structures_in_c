# zyk_data_structures_in_c

[![Language](https://img.shields.io/badge/language-C99-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build System](https://img.shields.io/badge/build-Make-informational.svg)](https://www.gnu.org/software/make/)
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
> The list of modules is defined in `Makefile` (`DS_MODULES`). Each module compiles to `.o` and links into the final executable.

- Linear structures: `SeqList`, `LinkedList`, `SeqStack`, `LinkedStack`, `SeqQueue`, `LinkedQueue`
- Trees: `SeqBinaryTree` (in progress), `LinkedBinaryTree`
- Algorithms: `Sort` (sorting algorithms)
- Utility: `Warn` (colored warning output used by modules for defensive checks)

## Project layout
- `include/dsc/*.h`: public module headers (APIs)
- `src/*.c`: module implementations
- `main.c`: the single executable test harness (`ZYK_Data_Structures_In_C`, currently focused on `Sort`)
- `Makefile`: simple Make build (no CMake required!)

## Build & run
This project uses a simple **Makefile** — no CMake required! Just run:

```sh
make          # Build the project
make run      # Build and run
make clean    # Remove build artifacts
make rebuild  # Full rebuild
make help     # Show all commands
```

Build output goes to `build/`. The executable is `build/ZYK_Data_Structures_In_C`.

## Example
Headers are included directly from `include/dsc`:

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

### 2025-12-31 (UI Alignment Optimization)
- **FIX**: Fixed visual alignment issues in Matrix demo program
  - Binary tree visualization: unified all leaf node box widths for perfect alignment
  - Traversal order box: fixed Level-order row alignment
  - Breach simulation stats: fixed "BREACH SIMULATION COMPLETE" box alignment
  - All border lines and text now perfectly symmetrical

### 2025-12-31 (VSCode Configuration & Warning Fixes)
- **NEW**: Added VSCode C/C++ IntelliSense configuration
  - `.vscode/c_cpp_properties.json` - Include path configuration
  - `.vscode/settings.json` - Editor settings
  - `compile_commands.json` - Compilation command database
- **FIX**: Fixed all compilation warnings
  - Fixed function prototypes: `Create()` → `Create(void)` (C99 strict mode)
  - Added newlines at end of files

### 2025-12-31 (Build System Simplification)
- **CHANGE**: Replaced CMake with a simple Makefile
  - No need to install CMake — `make` is built into macOS/Linux
  - Simple commands: `make`, `make run`, `make clean`, `make rebuild`
  - Build output in `build/` directory
  - Removed `CMakeLists.txt`, `cmake-build-debug/`, `.idea/`

### 2025-12-31
- **FIX**: Removed global `Position` typedef from `Common.h` to resolve conflicts with module-local `Position` types in `LinkedQueue.c` and `LinkedBinaryTree.c`
- **NEW**: Complete overhaul of `main.c` - "THE MATRIX: Data Structure Edition"
  - Matrix-style digital rain animation using `SeqQueue` for frame history
  - System initialization demo using `SeqList` for module loading simulation
  - Network trace demo using `LinkedList` for IP node tracking
  - Call stack demo using both `SeqStack` and `LinkedStack`
  - Message queue demo using `SeqQueue` and `LinkedQueue`
  - Decision tree visualization using `SeqBinaryTree`
  - Sorting benchmark demo testing 5 algorithms: Selection, Bubble, Quick, Merge, Insertion
  - Comprehensive "hack simulation" using all data structures simultaneously
  - Full ANSI color support with Matrix-green color scheme

### 2025-12-30 (Evening)
- **NEW**: Complete rewrite of `main.c` with a "Matrix"-themed interactive demo program:
  - Showcases ALL data structures: `SeqList`, `LinkedList`, `SeqStack`, `LinkedStack`, `SeqQueue`, `LinkedQueue`
  - Demonstrates 5 sorting algorithms: `InsertionSort`, `QuickSort`, `BubbleSort`, `SelectionSort`, `MergeSort`
  - Features cyberpunk aesthetics: ANSI color codes, Matrix-style code rain, typing animations
  - Includes 5 themed modules: Neural Network Sim, Memory Chain Analysis, Call Stack Trace, Packet Stream, Decryption
  - Resolved `ElementType` typedef conflicts between modules using extern declarations

### 2025-12-30
- Fixed module filename mismatch: renamed `src/SeqBInaryTree.c` -> `src/SeqBinaryTree.c`.
- Updated `include/dsc/SeqBinaryTree.h` typedef typo (`SeqBinayTreePtr` -> `SeqBinaryTreePtr`) and adjusted `SeqBinaryTree_isEmpty` signature to accept `SeqBinaryTree`.
- Added `.github/copilot-instructions.md` to guide AI coding agents working in this repo.
