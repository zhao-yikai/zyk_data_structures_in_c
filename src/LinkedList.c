/*
    LinkedList.c
    Functions of Linked Linear Lists
    Created By YikaiSays on Mar 23 2025
*/

#include <stdio.h>
#include <stdlib.h>  // Add standard library header file
#include "LinkedList.h"
#include "Warn.h"

/**
 * @struct LinkedListNode
 * @brief Represents a node in a linked list.
 *
 * This structure defines the basic building block of a linked list.
 * Each node contains a data element and a pointer to the next node in the list.
 */
// Linked list node structure definition
struct LinkedListNode {
    /**
     * @brief The data stored in the node.
     *
     * The type of this data is defined by `ElementType`, which should be
     * specified elsewhere in the codebase.
     */
    ElementType Data;             // Node data
    /**
     * @brief A pointer to the next node in the linked list.
     *
     * If this pointer is `NULL`, it indicates that this node is the last node in the list.
     */
    LinkedListNodePtr Next;       // Pointer to the next node
};


/**
 * @brief Creates a new head node for a linked list.
 *
 * This function allocates memory for a new linked list head node. If the memory allocation is successful,
 * it initializes the data field of the head node with a special error value (`LINKED_ERROR`) and sets
 * the `Next` pointer to `NULL`, indicating an empty linked list. If the memory allocation fails, it logs
 * a warning message and returns `NULL`.
 *
 * @return LinkedListHead A pointer to the newly created head node if successful, or `NULL` if memory allocation fails.
 *
 * @note The data field of the head node is initialized with `LINKED_ERROR`, which should be defined elsewhere
 *       in the codebase to represent a special value.
 */
LinkedListHead LinkedList_Create(void) {
    // Allocate memory for a new linked list node
    LinkedList_Position p = malloc(sizeof(struct LinkedListNode));
    // Check if memory allocation was successful
    if (!p) {
        // Log a warning if memory allocation fails
        Warn("LinkedList_Create: Memory Allocation Error!");
        return NULL;
    }
    // Initialize the data field of the head node with a special error value
    p->Data = LINKED_ERROR;      // Modification suggestion: Initialize with the defined error value
    // Initialize the Next pointer to NULL, indicating an empty linked list
    p->Next = NULL;
    return p;
}

/*
 * Shall We Meet Again ?
 * 28 May 2025
 */

/**
 * @brief Gets the length of the linked list (excluding the head node).
 *
 * @param L The head node of the linked list.
 * @return The actual length if successful, or `LINKED_ERROR` if failed.
 */
Length LinkedList_GetLength(LinkedListHead L) {
    if (!L) {
        Warn("LinkedList_GetLength: INVALID LIST!");
        return LINKED_ERROR;
    }
    Length l = 0;
    // DeepSeek: Suggest starting counting from the first valid node (the head node is not included in the length)
    for (LinkedList_Position p = L->Next; p != NULL; p = p->Next, ++l) {}
    return l;
}

/**
 * @brief Inserts a node at the specified position (counting from 1).
 *
 * @param L The head node of the linked list.
 * @param X The value of the element to be inserted.
 * @param i The insertion position.
 * @return `true` if successful, `false` if failed.
 */
bool LinkedList_InsertAtNodePosition(LinkedListHead L, ElementType X, int i) {
    if (!L || i < 1) {  // Position starts counting from 1
        Warn("LinkedList_InsertAtNodePosition: INVALID PARAMETERS!");
        return false;
    }

    LinkedList_Position pre = L;
    int cnt = 0;
    // Find the (i-1)th node
    while (pre && cnt < i - 1) {
        pre = pre->Next;
        ++cnt;
    }

    if (!pre || cnt != i - 1) {
        Warn("LinkedList_InsertAtNodePosition: INVALID POSITION!");
        return false;
    }

    LinkedList_Position tmp = malloc(sizeof(struct LinkedListNode));
    if (!tmp) {
        Warn("LinkedList_InsertAtNodePosition: MALLOC ERROR!");
        return false;
    }

    tmp->Data = X;
    tmp->Next = pre->Next;
    pre->Next = tmp;
    return true;
}

/**
 * @brief Inserts a new node before the specified node.
 *
 * @param L The head node of the linked list.
 * @param X The value of the element to be inserted.
 * @param P The pointer to the target node.
 * @return `true` if successful, `false` if failed.
 */
bool LinkedList_InsertAtNodePtr(LinkedListHead L, ElementType X, LinkedList_Position P) {
    if (!L || !P) {
        Warn("LinkedList_InsertAtNodePtr: INVALID PARAMETERS!");
        return false;
    }

    LinkedList_Position pre = L;
    // Find the predecessor node of the target node
    while (pre && pre->Next != P) {
        pre = pre->Next;
    }

    if (!pre) {
        Warn("LinkedList_InsertAtNodePtr: NODE NOT FOUND!");
        return false;
    }

    LinkedList_Position tmp = malloc(sizeof(struct LinkedListNode));
    if (!tmp) {
        Warn("LinkedList_InsertAtNodePtr: MALLOC ERROR!");
        return false;
    }

    tmp->Data = X;
    tmp->Next = P;
    pre->Next = tmp;
    return true;
}

/**
 * @brief Gets the element value at the specified position.
 *
 * @param L The head node of the linked list.
 * @param k The position of the element (counting from 0).
 * @return The element value if successful, or `LINKED_ERROR` if failed.
 */
ElementType LinkedList_GetElementAtPosition(LinkedListHead L, int k) {
    if (!L || k < 0) {
        Warn("LinkedList_GetElementAtPosition: INVALID PARAMETERS!");
        return LINKED_ERROR;
    }

    LinkedList_Position p = L->Next;  // Skip the head node
    int cnt = 0;
    while (p && cnt < k) {
        p = p->Next;
        ++cnt;
    }
    return p ? p->Data : LINKED_ERROR;
}

/**
 * @brief Gets the element value of the specified node.
 *
 * @param p The pointer to the target node.
 * @return The element value if successful, or `LINKED_ERROR` if failed.
 */
ElementType LinkedList_GetElementAtNodePtr(LinkedList_Position p) {
    return p ? p->Data : LINKED_ERROR;
}

/**
 * @brief Finds the first occurrence position of an element.
 *
 * @param L The head node of the linked list.
 * @param X The target element value.
 * @return The pointer to the node if successful, or `NULL` if failed.
 */
LinkedList_Position LinkedList_Find(LinkedListHead L, ElementType X) {
    if (!L) return NULL;

    // Start searching from the first valid node
    LinkedList_Position p = L->Next;
    while (p && p->Data != X) {
        p = p->Next;
    }
    return p;
}

/**
 * @brief Deletes the node at the specified position.
 *
 * @param L The head node of the linked list.
 * @param i The deletion position (counting from 1).
 * @return `true` if successful, `false` if failed.
 */
bool LinkedList_DeleteAtNodePosition(LinkedListHead L, int i) {
    if (!L || i < 1) {
        Warn("LinkedList_DeleteAtNodePosition: INVALID PARAMETERS!");
        return false;
    }

    LinkedList_Position pre = L;
    int cnt = 0;
    while (pre && cnt < i - 1) {
        pre = pre->Next;
        ++cnt;
    }

    if (!pre || !pre->Next || cnt != i - 1) {
        Warn("LinkedList_DeleteAtNodePosition: INVALID POSITION!");
        return false;
    }

    LinkedList_Position toDel = pre->Next;
    pre->Next = toDel->Next;
    free(toDel);
    return true;
}

/**
 * @brief Deletes the specified node.
 *
 * @param L The head node of the linked list.
 * @param P The pointer to the node to be deleted.
 * @return `true` if successful, `false` if failed.
 */
bool LinkedList_DeleteAtNodePtr(LinkedListHead L, LinkedList_Position P) {
    if (!L || !P) {
        Warn("LinkedList_DeleteAtNodePtr: INVALID PARAMETERS!");
        return false;
    }

    LinkedList_Position pre = L;
    while (pre && pre->Next != P) {
        pre = pre->Next;
    }

    if (!pre) {
        Warn("LinkedList_DeleteAtNodePtr: NODE NOT FOUND!");
        return false;
    }

    pre->Next = P->Next;
    free(P);
    return true;
}

/**
 * @brief Destroys the linked list and frees all allocated memory.
 *
 * @param L The head node of the linked list.
 * @return `true` if successful, `false` if the input is `NULL`.
 */
bool LinkedList_Destroy(LinkedListHead L) {
    if (!L) return false;

    LinkedListNodePtr p = L;
    while (p) {
        LinkedListNodePtr tmp = p;
        p = p->Next;
        free(tmp);
    }
    return true;
}
