#include <stdio.h>

#include <sequential_linear_list.h>

int main(void) {
    SeqList l = SeqList_Create();
    Seq_InsertAt(l, 2, 2);
    printf("%ld", Seq_GetElementAt(l, 2));
    return 0;
}
