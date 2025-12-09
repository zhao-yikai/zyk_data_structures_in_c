//
// Created by 趙熠楷 on 4/4/25.
//

#include <stdlib.h>

#include "SeqBinaryTree.h"
#include "Warn.h"

typedef double ElementType;

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

