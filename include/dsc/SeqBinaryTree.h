//
// Created by 趙熠楷 on 4/4/25.
//

#ifndef SEQBINARYTREE_H
#define SEQBINARYTREE_H

#include <stdbool.h>

typedef struct SeqBinaryTreeNode * SeqBinayTreePtr;
typedef SeqBinayTreePtr SeqBinaryTree;

bool SeqBinaryTree_isEmpty();

// LVR
void SeqBinaryTree_InOrderTraversal(SeqBinaryTree SBT);

// VLR
void SeqBinaryTree_PreOrderTraversal(SeqBinaryTree SBT);

// LRV
void SeqBinaryTree_PostOrderTraversal (SeqBinaryTree SBT);

void SeqBinaryTree_LevelOrderTraversal (SeqBinaryTree SBT);

SeqBinaryTree SeqBinaryTree_Create(int MaxSize);

#endif //SEQBINARYTREE_H
