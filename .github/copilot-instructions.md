# Copilot instructions for `zyk_data_structures_in_c` (C99 + CMake)

> 目标 / Goal: 让 AI 代理能立刻按本仓库的结构与习惯进行修改与扩展。
> Help AI agents become productive immediately by following this repo’s structure and conventions.

## Big picture / 总览（仓库结构）
- 这是一个 **C99** 的数据结构与算法学习仓库（课程学习记录）。
  This is a C99 data-structures/algorithms learning repo (course notes).
- 公共 API 头文件在 `include/dsc/*.h`；实现放在 `src/*.c`。
  Public APIs are in `include/dsc/*.h`; implementations are in `src/*.c`.
- CMake 按“模块”编译：**每个模块一个静态库**（见 `CMakeLists.txt` 的 `DATA_STRUCTURES` + `add_data_structure_target()`）。
  CMake builds **one static library per module** (see `DATA_STRUCTURES` + `add_data_structure_target()` in `CMakeLists.txt`).
  - 命名必须严格匹配：`src/<Name>.c` + `include/dsc/<Name>.h`。
    Names must match exactly: `src/<Name>.c` + `include/dsc/<Name>.h`.
  - `warning` 是基础工具库：`src/Warn.c` + `include/dsc/Warn.h`。
    `warning` is the shared utility lib: `src/Warn.c` + `include/dsc/Warn.h`.
- `main.c` 是唯一可执行文件 `ZYK_Data_Structures_In_C` 的测试入口（目前主要测试 `Sort`）。
  `main.c` is the single executable test harness (currently focused on `Sort`).

## Build & run / 构建与运行
- 典型 out-of-source 构建：
  Typical out-of-source build:
  - `cmake -S . -B cmake-build-debug`
  - `cmake --build cmake-build-debug`
  - `./cmake-build-debug/ZYK_Data_Structures_In_C`
- 工程会导出 `compile_commands.json`（`CMAKE_EXPORT_COMPILE_COMMANDS ON`），方便 IDE/静态分析。
  The project exports `compile_commands.json` for IDEs/static analysis.

## Code conventions / 代码约定（很重要）
- **API 写在头文件**，实现与声明保持一致（函数名、参数、返回值）。
  Keep APIs in headers and keep signatures aligned between `.h` and `.c`.
- 防御式编程：对 `NULL` 指针/非法长度尽早返回；库代码里优先用 `Warn("...")` 提示。
  Defensive checks: early-return on invalid inputs; prefer `Warn("...")` in library code.
  - 例子 / Example (see `src/Sort.c`): `if (!Arr) { Warn("...: Invalid Array!"); return; }`
- `ElementType` **通常是模块内自定义**（例如 `include/dsc/Sort.h` 里是 `typedef double ElementType`）。
  `ElementType` is usually **module-local** (e.g., `Sort.h` typedefs `double`). Don’t assume one global type.

## Editing `main.c` / 修改测试入口
- `main.c` 为了兼容不同排序函数签名，会写 wrapper 统一成 `void (*)(ElementType*, size_t)`。
  `main.c` uses wrappers to normalize sort signatures to `void (*)(ElementType*, size_t)`.
- `run_test()` 会 `assert(success)`，所以排序实现一旦出错会直接终止。
  `run_test()` asserts on correctness; broken algorithms will abort.

## Repo hygiene / 仓库维护规则（请 AI 一起遵守）
- 每次做出“可见变更”（例如：改 API、改模块文件名、改构建、加模块/算法），都要在根目录 `README.md` 的 **Change log / 变更记录** 追加一条。
  For every user-visible change (API/module/build/new algorithm), append an entry in the root `README.md` **Change log**.
