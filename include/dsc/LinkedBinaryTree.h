/*
    LinkedBinaryTree.h
    Interface of Linked Binary Trees
    Created By YikaiSays on Apr 4 2025
*/

#ifndef LINKEDBINARYTREE_H
#define LINKEDBINARYTREE_H

#include <stdbool.h>

#define NoInfo 0  /* 特殊标记值，用于表示空节点/终止输入 */

/* 二叉树节点存储元素类型（可修改为需要的数据类型） */
typedef double ElementType;

/* 前向声明二叉树节点指针类型 */
typedef struct LinkedBinaryTreeNode * LinkedBinaryTreePtr;


/* 二叉树类型定义（指向根节点的指针） */
typedef LinkedBinaryTreePtr LinkedBinaryTree;

/*━━━━━━━━━━━━━━━━━━━━━ 基础操作 ━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @brief 创建空二叉树节点
 *
 * 初始化一个左右子树均为空的二叉树节点，节点数据域未初始化。
 * 注意：创建的是单个节点而非完整树结构
 *
 * @return LinkedBinaryTree 成功返回节点指针，内存分配失败返回NULL
 */
LinkedBinaryTree LinkedBinaryTree_Create();


/**
 * @brief 判断节点是否为叶子节点
 *
 * 判断指定节点是否没有子节点（左右子树均为空）
 *
 * @param LBT 需要判断的二叉树节点
 * @return bool 输入有效且为叶子节点返回true，无效输入返回true，否则false
 */
bool LinkedBinaryTree_isEmpty(LinkedBinaryTree LBT);


/*━━━━━━━━━━━━━━━━━━━━━ 树构建操作 ━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @brief 层序构建完整二叉树
 *
 * 通过标准输入按层序方式构建完整二叉树结构，允许使用NoInfo(0)表示空节点。
 * 输入规则：
 * 1. 按层序逐个输入节点数据（包含空节点）
 * 2. 遇到NoInfo(0)时对应位置不创建节点
 * 3. 输入序列应与完全二叉树结构对应
 *
 * 示例输入序列：
 * [1,2,3,0,0,4,0] 构建结果为：
 *        1
 *      /   \
 *     2     3
 *          /
 *         4
 *
 * @return LinkedBinaryTree 成功返回根节点指针，构建失败返回NULL
 */
LinkedBinaryTree LinkedBinaryTree_LevelOrderCreate(void);


/*━━━━━━━━━━━━━━━━━━━━━ 遍历操作 ━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @brief 中序遍历（LVR）
 *
 * 递归实现中序遍历，访问顺序：左子树 -> 根节点 -> 右子树
 *
 * @param LBT   待遍历的二叉树根节点
 * @param visit 访问函数指针，格式：ElementType func(LinkedBinaryTree)
 *              接收当前节点指针，返回处理后的元素类型
 */
void LinkedBinaryTree_InOrderTraversal(const LinkedBinaryTree LBT, ElementType (*visit)(LinkedBinaryTree));


/**
 * @brief 先序遍历（VLR）
 *
 * 递归实现先序遍历，访问顺序：根节点 -> 左子树 -> 右子树
 *
 * @param LBT   待遍历的二叉树根节点
 * @param visit 访问函数指针，格式：ElementType func(LinkedBinaryTree)
 */
void LinkedBinaryTree_PreOrderTraversal(LinkedBinaryTree LBT, ElementType (*visit)(LinkedBinaryTree));


/**
 * @brief 后序遍历（LRV）
 *
 * 递归实现后序遍历，访问顺序：左子树 -> 右子树 -> 根节点
 *
 * @param LBT   待遍历的二叉树根节点
 * @param visit 访问函数指针，格式：ElementType func(LinkedBinaryTree)
 */
void LinkedBinaryTree_PostOrderTraversal(LinkedBinaryTree LBT, ElementType (*visit)(LinkedBinaryTree));


/**
 * @brief 层序遍历
 *
 * 使用队列实现的层序遍历，按层次从上到下访问节点
 *
 * @param LBT   待遍历的二叉树根节点
 * @param visit 访问函数指针，格式：ElementType func(LinkedBinaryTree)
 */
void LinkedBinaryTree_LevelOrderTraversal(LinkedBinaryTree LBT, ElementType (*visit)(LinkedBinaryTree));

#endif //LINKEDBINARYTREE_H