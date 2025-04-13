# 数据结构与算法库

C语言实现的通用数据结构与算法库，包含链式/顺序结构实现及经典排序算法

## 📚 功能特性

- **数据结构实现**
  - 链式结构: 二叉树/链表/队列/栈
  - 顺序结构: 线性表/队列/栈/二叉树
- **排序算法**
  - 基础排序: 选择/插入/冒泡
  - 高效排序: 快速/归并/堆排序
  - 特殊排序: 希尔/桶/基数/TimSort
- **完整遍历支持**
  - 二叉树: 前序/中序/后序/层序遍历
  - 线性结构: 迭代器模式访问

## 🧩 模块说明

### 链式结构
| 模块                 | 核心功能                                                                         |
|----------------------|----------------------------------------------------------------------------------|
| LinkedBinaryTree.h   | 二叉树创建、空节点判断、层序构建、四种遍历方式                                   |
| LinkedList.h         | 链表基础操作、元素查找、位置插入/删除、长度获取                                  |
| LinkedQueue.h        | 链式队列的创建、入队/出队、空队判断                                             |
| LinkedStack.h        | 链式栈的初始化、压栈/弹栈、栈空判断                                             |

### 顺序结构
| 模块                 | 核心特性                                                                         |
|----------------------|----------------------------------------------------------------------------------|
| SeqBinaryTree.h      | 顺序存储二叉树结构、四种遍历方法实现                                             |
| SeqList.h            | 顺序表基础操作（MAXSIZE=1000）、元素访问、插入删除、容量判断                    |
| SeqQueue.h           | 定长顺序队列、入队/出队操作、队列销毁                                            |
| SeqStack.h           | 顺序栈的创建（指定MaxSize）、栈满判断、压栈/弹栈                                 |

### 排序算法 (Sort.h)
| 算法         | 时间复杂度        | 空间复杂度 | 稳定性 | 特点                                                                 |
|--------------|-------------------|------------|--------|----------------------------------------------------------------------|
| 选择排序     | O(n²)            | O(1)       | ❌      | 适合小规模数据，交换次数最少                                        |
| 堆排序       | O(n log n)       | O(1)       | ❌      | 原地排序，适合大数据量                                              |
| 插入排序     | O(n²)            | O(1)       | ✅      | 最佳情况O(n)，基本有序时高效                                        |
| 希尔排序     | O(n log n)       | O(1)       | ❌      | 改进插入排序，Sedgewick增量序列                                      |
| 冒泡排序     | O(n²)            | O(1)       | ✅      | 教学演示常用，可优化提前终止                                        |
| 快速排序     | O(n log n) 平均  | O(log n)   | ❌      | 实际最快通用排序，递归实现                                          |
| 归并排序     | O(n log n)       | O(n)       | ✅      | 稳定排序，适合外部排序                                              |
| 桶排序       | O(n + k)         | O(n + k)   | ✅      | 数据需均匀分布                                                      |
| 基数排序     | O(nk)            | O(n + k)   | ✅      | 适合整数排序，LSD/MSD实现                                           |
| TimSort      | O(n log n)       | O(n)       | ✅      | Python/Java内置，利用自然有序片段                                   |

## 🛠️ 使用示例

```c
// 创建链式二叉树并进行层序遍历
LinkedBinaryTree tree = LinkedBinaryTree_LevelOrderCreate();
LinkedBinaryTree_LevelOrderTraversal(tree, LinkedBinaryTree_GetNodeData);

// 使用快速排序
double arr[] = {3.14, 1.59, 2.65, 3.58, 9.79};
QuickSort(arr, sizeof(arr)/sizeof(arr[0]));
```

## 🔨 构建说明

1. 克隆仓库：
```bash
git clone [repository_url]
```

2. 包含头文件：
```c
#include "LinkedBinaryTree.h"
#include "Sort.h"
// 其他所需头文件...
```

3. 编译时链接所有实现文件：
```bash
gcc -std=c99 your_program.c LinkedList.c LinkedQueue.c Sort.c -o program
```

## 🤝 贡献指南
欢迎提交Pull Request或Issue
1. Fork项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交修改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 发起Pull Request

## 📄 许可证
[MIT License](LICENSE) © YikaiSays
``` 

关键亮点说明：
1. 模块化组织：清晰区分链式/顺序结构，突出排序算法特性
2. 算法特性矩阵：直观对比不同排序算法的性能指标
3. 即用型示例：提供核心模块的典型使用代码片段
4. 贡献流程引导：标准化协作路径，鼓励社区参与
5. 兼容性提示：包含C99标准编译指令，确保跨平台可用性