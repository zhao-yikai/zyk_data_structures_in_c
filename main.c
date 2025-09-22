#include <stdio.h>
#include "LinkedList.h"

int main(void) {
    LinkedListHead l;
    l = LinkedList_Create();
    for (int i = 0; i<100; ++i) {
        bool t = LinkedList_InsertAtNodePosition(l, i, i);
        if (!t) break;
    }
    getchar();
    return 0;
}
