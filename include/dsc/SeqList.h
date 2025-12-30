/*
    SeqList.h
    Functions of Sequential Lists
    Created By YikaiSays on Mar 18 2025
*/

#ifndef SEQUENTIAL_LINEAR_LIST_H  // Include Guard 开始
#define SEQUENTIAL_LINEAR_LIST_H

#include "Common.h"  // 统一类型定义

/*  Considering that operations on linear lists include insertion, deletion, etc.
    and the length of the list is dynamically variable, the capacity of the array 
    needs to be designed large enough.
*/
#define MAXSIZE 1000 // MAXSIZE is an integer sufficiently large as defined based on practical issues.

// ElementType 现在由 Common.h 统一定义

/*
    The Position here refers to the integer index of the array, starting from 0. 
    The ordinal position refers to the nth element, starting from 1.
*/
typedef int SeqPosition;

/*
    To reflect the integrity of data organization, the array Data and the variable 
    Last are typically encapsulated into a structure as the type of the sequential list.
*/
typedef struct SeqList * SeqListPtr;

/*
    Since LNode is a structure containing an array, directly passing this structure as 
    a function parameter is clearly not a good approach when implementing various operations 
    for sequential lists. Using a structure pointer for passing is more efficient, so we 
    define List as a structure pointer. This allows us to use List to define a linear list L: List L, 
    through which we can access the contents of the corresponding linear list. 
    For example, L->Data[i], and the length of the linear list can be obtained by L->Last + 1.
*/
typedef SeqListPtr SeqList;

// Linear List Operations:

// Initialize a New List
SeqList SeqList_Create(void);

bool SeqList_IsEmpty(SeqList L);

// Return the element a_i in L at the specified position p
ElementType SeqList_GetElementAt(SeqList L, SeqPosition p);

// Return the position of the first occurrence of X in L. Returns an error if X is not found.
SeqPosition SeqList_Find(SeqList L, ElementType X);

bool SeqList_IsFull(SeqList L);

// Insert X into L before position p. Returns true on success, false otherwise.
bool SeqList_InsertAt(SeqList L, ElementType X, SeqPosition p);

// Delete the element at position p in L. Returns true on success, false otherwise.
bool SeqList_DeleteAt(SeqList L, SeqPosition p);

// Return the number of elements in L.
int SeqList_GetLength(SeqList L);

// Print the value of L->Last and every element in the list
void Seq_Print(SeqList L);

#endif // SEQUENTIAL_LINEAR_LIST_H  // Include Guard 结束
