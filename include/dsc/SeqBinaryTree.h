//
// Created by 趙熠楷 on 4/4/25.
//

#ifndef SEQBINARYTREE_H
#define SEQBINARYTREE_H

#include "Common.h"  // 统一类型定义

// ElementType 现在由 Common.h 统一定义

typedef struct SeqBinaryTreeNode * SeqBinaryTreePtr;
typedef SeqBinaryTreePtr SeqBinaryTree;

bool SeqBinaryTree_isEmpty(SeqBinaryTree SBT);

// LVR
void SeqBinaryTree_InOrderTraversal(SeqBinaryTree SBT);

// VLR
void SeqBinaryTree_PreOrderTraversal(SeqBinaryTree SBT);

// LRV
void SeqBinaryTree_PostOrderTraversal (SeqBinaryTree SBT);

void SeqBinaryTree_LevelOrderTraversal (SeqBinaryTree SBT);

SeqBinaryTree SeqBinaryTree_Create(int MaxSize);

#endif //SEQBINARYTREE_H
