# Copilot instructions for `zyk_data_structures_in_c` (C99 + Make)

> 目标: 让 AI 代理能立刻按本仓库的结构与习惯进行修改与扩展。

## 仓库总览
- 这是一个 **C99** 的数据结构与算法学习仓库（课程学习记录）。
- 公共 API 头文件在 `include/dsc/*.h`；实现放在 `src/*.c`。
- 使用 **Makefile** 构建，模块列表定义在 `DS_MODULES` 变量中。
  - 命名必须严格匹配：`src/<Name>.c` + `include/dsc/<Name>.h`。
  - `warning` 是基础工具库：`src/Warn.c` + `include/dsc/Warn.h`。
- `main.c` 是唯一可执行文件 `ZYK_Data_Structures_In_C` 的测试入口。

## 构建与运行
使用 Makefile（macOS/Linux 自带 `make`，无需额外安装）：

```sh
make          # 构建项目
make run      # 构建并运行
make clean    # 清理构建产物
make rebuild  # 完全重建
make help     # 查看所有命令
```

构建产物在 `build/` 目录下。

## 代码约定（很重要）
- **API 写在头文件**，实现与声明保持一致（函数名、参数、返回值）。
- 防御式编程：对 `NULL` 指针/非法长度尽早返回；库代码里优先用 `Warn("...")` 提示。
  - 例子 (见 `src/Sort.c`): `if (!Arr) { Warn("...: Invalid Array!"); return; }`
- `ElementType` **通常是模块内自定义**（例如 `include/dsc/Sort.h` 里是 `typedef double ElementType`）。

## 修改测试入口 (`main.c`)
- `main.c` 为了兼容不同排序函数签名，会写 wrapper 统一成 `void (*)(ElementType*, size_t)`。
- `run_test()` 会 `assert(success)`，所以排序实现一旦出错会直接终止。

## 仓库维护规则（请 AI 一起遵守）

### README 文档规则 ⚠️ 重要
本仓库有两个 README 文件：
- `README.zh-CN.md` — **中文主文档**（主要维护）
- `README.md` — 英文文档

**每次修改文档时，必须同时更新两个文件**：
1. 先修改 `README.zh-CN.md`（中文为主）
2. 然后同步修改 `README.md`（翻译为英文）
3. 保持两个文件的结构和内容一致

### Change log 规则
每次做出"可见变更"（例如：改 API、改模块文件名、改构建、加模块/算法），都要在 **两个 README** 的 **Change log / 变更记录** 追加一条。
