//
// Created by 趙熠楷 on 4/4/25.
//

#include <stdlib.h>

#include "SeqBinaryTree.h"
#include "Warn.h"

// ElementType 现在由 Common.h 统一定义

struct SeqBinaryTreeNode {
    ElementType * Data;
};

SeqBinaryTree SeqBinaryTree_Create(const int MaxSize) {
    const SeqBinaryTree SBT = malloc(sizeof (struct SeqBinaryTreeNode));
    if (!SBT) {
        Warn("SeqBinaryTree_Create: Memory Allocation Error!");
        return NULL;
    }
    SBT->Data = malloc(MaxSize * sizeof(ElementType));
    return SBT;
}

