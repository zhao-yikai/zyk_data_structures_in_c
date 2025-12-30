/*
SeqStack.c
    Functions of Sequential Stacks
    Created By YikaiSays on Mar 23 2025
*/

#include "SeqStack.h"

// 定义栈顶指针类型（建议使用无符号类型避免负数）
typedef int Position;  // DeepSeek: 建议改为 size_t 以提高可移植性

// 顺序栈结构体定义
struct SeqStackNode {
    ElementType* Data;   // 存储元素的动态数组指针
    Position     Top;     // 栈顶指针（-1表示空栈）
    int          MaxSize; // 栈的最大容量
};

/*
 * 创建顺序栈
 * 参数: MaxSize - 栈的最大容量
 * 返回值: 初始化后的栈指针
 */
SeqStack SeqStack_Create(int MaxSize) {
    // 分配栈结构体内存
    SeqStack S = malloc(sizeof(struct SeqStackNode));
    // DeepSeek: 缺少malloc失败检查，可能导致后续操作崩溃

    // 分配存储空间
    S->Data = malloc(MaxSize * sizeof(ElementType));
    // DeepSeek: 1.未检查MaxSize有效性（应>0）
    // DeepSeek: 2.未处理malloc失败情况

    // 初始化栈状态
    S->Top = -1;          // 空栈标记
    S->MaxSize = MaxSize; // 设置容量上限
    return S;
}

/*
 * 判断栈是否已满
 * 参数: S - 栈指针
 * 返回值: 栈满返回true，否则false
 */
bool SeqStack_isFull(SeqStack S) {
    bool ret = false;
    // DeepSeek: 未进行空指针校验，S==NULL时会进入else分支
    if (S)
        // 检查栈顶位置是否达到最大下标
            if (S->Top == S->MaxSize - 1)
                ret = true;
    return ret;
}

/*
 * 元素入栈操作
 * 参数: S - 栈指针，X - 入栈元素
 * 返回值: 成功返回true，失败返回false
 */
bool SeqStack_Push(SeqStack S, ElementType X) {
    bool ret = false;
    // 先检查栈是否已满
    if (!SeqStack_isFull(S)) {
        // 先移动栈顶指针再存储数据
        S->Data[++S->Top] = X;  // DeepSeek: 当S为NULL时会产生未定义行为
        ret = true;
    }
    // DeepSeek: 失败时缺少错误日志，建议添加Warn输出
    return ret;
}

/*
 * 判断栈是否为空
 * 参数: S - 栈指针
 * 返回值: 空栈返回true，否则false
 */
bool SeqStack_isEmpty(SeqStack S) {
    bool ret = false;
    // DeepSeek: 直接访问S->Top存在空指针解引用风险
    if (S->Top == -1)  // 若S为NULL会在此处崩溃
        ret = true;
    return ret;
}

/*
 * 弹出栈顶元素
 * 参数: S - 栈指针
 * 返回值: 成功返回元素值，失败返回错误码
 */
ElementType SeqStack_Pop(SeqStack S) {
    ElementType Pop = SEQ_STACK_ERROR;
    // 检查栈是否为空
    if (!SeqStack_isEmpty(S))  // DeepSeek: 嵌套调用会放大空指针风险
        // 先取数据再移动栈顶指针
            Pop = S->Data[S->Top--];
    // DeepSeek: 无法区分"空栈"和"无效栈"两种错误情况
    return Pop;
}
