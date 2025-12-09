/*
    LinkedStack.c
    Functions of Linked Stacks
    Created By YikaiSays on Mar 23 2025
*/

#include "LinkedStack.h"
#include "Warn.h"

/**
 * @struct LinkedStackNode
 * @brief Defines the structure of a node in a linked stack.
 *
 * This structure represents a single node in a linked stack. Each node contains
 * a data element and a pointer to the next node in the stack.
 *
 * @var LinkedStackNode::Data
 * The data element stored in the node. The type of this data is defined by `ElementType`.
 *
 * @var LinkedStackNode::Next
 * A pointer to the next node in the linked stack. If this is `NULL`, it indicates
 * the end of the stack.
 */
struct LinkedStackNode {
    ElementType Data;        // 节点存储的数据
    LinkedStackNodePtr Next; // 指向下一个节点的指针
};

/**
 * @brief Creates a new head node (sentinel node) for a linked stack.
 *
 * This function allocates memory for a new head node of a linked stack.
 * If the memory allocation is successful, it initializes the `Next` pointer
 * of the head node to `NULL`, indicating an empty stack. If the allocation fails,
 * it logs a warning message using the `Warn` function.
 *
 * @return LinkedStackHead A pointer to the newly created head node if successful,
 *                         or `NULL` if memory allocation fails.
 *
 * @note The caller should check the return value to ensure that the head node
 *       was created successfully. If the return value is `NULL`, the operation failed.
 */
LinkedStackHead LinkedStack_Create() {
    // Allocate memory for the head node of the linked stack
    LinkedStackHead S = malloc(sizeof(struct LinkedStackNode));
    if (S) {
        // Initialize the Next pointer to NULL, indicating an empty stack
        S->Next = NULL;
    } else {
        // Log a warning message if memory allocation fails
        Warn("LinkedStack_Create: MALLOC ERROR!");
    }
    // Return the pointer to the head node, which may be NULL if allocation failed
    return S;
}


/*
 * 元素压栈操作
 * 参数: S - 栈头指针，X - 入栈元素
 * 返回值: 成功返回true，失败返回false
 */
/**
 * @brief Pushes an element onto the top of the linked stack.
 *
 * This function attempts to add a new element to the top of the specified linked stack.
 * It first checks if the provided stack head pointer is valid. If not, it logs a warning message.
 * Then it allocates memory for a new node. If the memory allocation fails, it logs a warning message.
 * If the allocation is successful, it inserts the new node at the top of the stack using the head insertion method.
 *
 * @param S A pointer to the head of the linked stack.
 * @param X The element to be pushed onto the stack.
 *
 * @return bool Returns `true` if the element is successfully pushed onto the stack, `false` otherwise.
 *
 * @note The caller should check the return value to ensure that the operation was successful.
 *       If the stack head pointer is invalid or memory allocation fails, the operation will fail.
 */
bool LinkedStack_Push(LinkedStackHead S, ElementType X) {
    bool ret = false;
    // Check if the stack head pointer is valid
    if (S) {
        // Allocate memory for a new node
        LinkedStackHead tmp = malloc(sizeof(struct LinkedStackNode));
        if (!tmp) {
            // Log a warning message if memory allocation fails
            Warn("LinkedStack_Push: MALLOC ERROR!");
        } else {
            // Insert the new node at the top of the stack using the head insertion method
            tmp->Data = X;          // Store the data
            tmp->Next = S->Next;    // The new node points to the original top of the stack
            S->Next = tmp;          // Update the head node pointer
            ret = true;
        }
    } else {
        // Log a warning message if the stack head pointer is invalid
        Warn("LinkedStack_Push: Invalid LinkedStackHead!");
    }
    return ret;
}

/**
 * @brief Checks if the linked stack is empty.
 *
 * This function determines whether the specified linked stack is empty.
 * It first validates the provided stack head pointer. If the pointer is `NULL`,
 * it implies an invalid stack, and the function returns `false` to indicate that
 * the stack is not considered empty in this invalid state. If the pointer is valid,
 * it checks the `Next` pointer of the head node. If the `Next` pointer is `NULL`,
 * it means there are no elements in the stack, and the function returns `true`.
 *
 * @param S A pointer to the head of the linked stack.
 *
 * @return bool Returns `true` if the stack is valid and empty, `false` if the stack
 *              is either invalid (head pointer is `NULL`) or contains elements.
 *
 * @note The caller should ensure that the provided stack head pointer is valid
 *       to avoid unexpected behavior. Passing a `NULL` pointer will result in
 *       the function returning `false`, which may not be the expected result.
 */
bool LinkedStack_isEmpty(LinkedStackHead S) {
    if (!S) {return false;}
    if (S->Next == NULL) { return true; }
    return false;
}

/**
 * @brief Removes and returns the top element from the linked stack.
 *
 * This function attempts to pop the top element from the stack. It first validates
 * the stack head pointer, then checks if the stack is empty. If successful,
 * it removes the top node, retrieves its data, and properly updates the stack pointers.
 *
 * @param S Pointer to the head of the linked stack. Must be a valid stack head
 *          created by LinkedStack_Create().
 *
 * @return ElementType The value of the popped element if successful. Returns
 *         LINKED_STACK_ERROR if:
 *         - The stack head pointer is invalid (NULL)
 *         - The stack is empty
 *
 * @note The caller should:
 *       1. Always check the validity of the stack head pointer before calling
 *       2. Handle the LINKED_STACK_ERROR return value appropriately
 *       3. Be aware that this function will free the memory of the popped node
 *       4. The function does NOT log warnings for empty stack conditions (caller
 *          should check isEmpty() first if this is important)
 */
ElementType LinkedStack_Pop(LinkedStackHead S) {
    if (!S) { return LINKED_STACK_ERROR; }
    ElementType retVal = LINKED_STACK_ERROR;
    if (!LinkedStack_isEmpty(S)) {
        LinkedStackNodePtr topNode = S->Next;  // 获取栈顶节点
        retVal = topNode->Data;
        S->Next = topNode->Next;  // 更新头节点指针
        free(topNode);            // 释放原栈顶节点
    }  // DeepSeek: else分支缺少空栈错误日志
    return retVal;
}


/**
 * @brief Deletes the entire linked stack and frees all allocated memory.
 *
 * This function iterates through the linked stack starting from the head node.
 * It deletes each node in the stack one by one, freeing the memory allocated for each node.
 * After the function execution, the entire linked stack is removed from memory,
 * and the stack head pointer becomes invalid.
 *
        LinkedStackNodePtr tmp = p;  // Save the current node
        p = p->Next;                // Move to the next node
        free(tmp);                  // Free the current node
    // Iterate through the stack and free each node
 * @param S A pointer to the head of the linked stack.
 *
 * @note The function does not check if the input pointer is `NULL`.
 *       If a `NULL` pointer is passed, the function will terminate immediately
 *       without performing any operations.
 * @note After calling this function, the caller should not use the original stack head pointer
 *       as the memory has been freed.
 */
void LinkedStack_Delete(LinkedStackHead S) {
    LinkedStackNodePtr p = S;
    while (p) {
        LinkedStackNodePtr tmp = p;  // 保存当前节点
        p = p->Next;                // 移动到下一节点
        free(tmp);                  // 释放当前节点
    }
}
