# 数据结构与算法库

## 项目概述
本项目为C语言实现的基础数据结构与算法库，包含线性结构、树形结构、排序算法及辅助工具模块。代码遵循模块化设计原则，部分功能仍在开发完善中。

## 功能特性
### 数据结构
- **线性结构**
  - 链表（单向链表）
  - 顺序表
  - 链式队列
  - 顺序队列
  - 链式栈
  - 顺序栈

- **树形结构**
  - 链式二叉树（支持层序构建）
  - 顺序二叉树（开发中）

### 算法
- 排序算法
  - 选择排序
  - 插入排序
  - 冒泡排序
  - 快速排序（优化基准选择）
  - 归并排序（未完成）

### 工具模块
- 带颜色输出的警告系统（Warn.h）

## 文件结构
```
src/
├── LinkedBinaryTree.c    # 链式二叉树实现（含队列辅助）
├── LinkedList.c          # 单向链表实现
├── LinkedQueue.c         # 链式队列实现
├── LinkedStack.c         # 链式栈实现
├── SeqBinaryTree.c       # 顺序二叉树框架
├── SeqList.c             # 顺序表实现
├── SeqQueue.c            # 顺序队列实现
├── SeqStack.c            # 顺序栈实现
├── Sort.c                # 排序算法集
└── Warn.c                # 警告处理模块
```

## 依赖项
- 标准C库（stdio.h, stdlib.h, stdbool.h）
- 自定义头文件：Warn.h（需与源码同级目录）

## 构建说明
建议分模块编译后链接使用：
```bash
gcc -c *.c -Wall -Wextra  # 分别编译所有源文件
gcc *.o -o datastruct      # 链接生成可执行文件
```

## 使用示例
### 链式二叉树创建与遍历
```c
LinkedBinaryTree tree = LinkedBinaryTree_LevelOrderCreate();
LinkedBinaryTree_InOrderTraversal(tree, printFunc);
```

### 链式队列操作
```c
LinkedQueue q = LinkedQueue_Create();
LinkedQueue_Enqueue(q, 10.5);
ElementType val = LinkedQueue_Dequeue(q);
```

## 注意事项
1. 部分函数存在空指针风险（需调用前检查指针有效性）
2. 队列/栈实现缺少销毁函数，长期运行可能导致内存泄漏
3. 顺序二叉树模块仅完成基础结构定义
4. 归并排序暂未实现核心逻辑
5. 部分函数参数校验需完善

## 待办事项
- [ ] 完成归并排序算法实现
- [ ] 添加各数据结构的销毁函数
- [ ] 实现顺序二叉树完整功能
- [ ] 补充单元测试用例
- [ ] 增加内存分配失败处理
- [ ] 完善文档注释（Doxygen格式）
- [ ] 实现迭代器模式遍历

## 贡献指南
1. Fork本项目仓库
2. 创建特性分支（feat/xxx 或 fix/xxx）
3. 提交代码变更（遵循现有代码风格）
4. 创建Pull Request并描述修改内容

## 许可证
[MIT License](LICENSE) © 2025 YikaiSays
```

> 提示：建议开发者在使用时注意以下DeepSeek注释标记的问题：
> ```c
> // DeepSeek: 未检查malloc返回值
> // DeepSeek: 内存泄漏风险
> // DeepSeek: 未完成功能
> ```
> 这些标记指出了代码中需要特别注意和改进的关键位置。