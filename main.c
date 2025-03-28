#include <stdio.h>

#include <SeqList.h>

int main(void) {
    SeqList l = SeqList_Create();
    Seq_InsertAt(l, 2, 2);
    printf("%lld", Seq_GetElementAt(l, 2));
    return 0;
}
