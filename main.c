#include <stdio.h>

#include "SeqQueue.h"

int main() {
    SeqQueue q1 = SeqQueue_Create(5);
    SeqQueue_Enqueue(q1, 1);
    SeqQueue_Enqueue(q1, 2);
    SeqQueue_Enqueue(q1, 3);
    SeqQueue_Enqueue(q1, 4);
    SeqQueue_Enqueue(q1, 5);

    ElementType d = SeqQueue_Dequeue(q1);
    printf("Dequeued: %lf \n", d);

    d = SeqQueue_Dequeue(q1);
    printf("Dequeued: %lf \n", d);

    d = SeqQueue_Dequeue(q1);
    printf("Dequeued: %lf \n", d);

    d = SeqQueue_Dequeue(q1);
    printf("Dequeued: %lf \n", d);

    d = SeqQueue_Dequeue(q1);
    printf("Dequeued: %lf \n", d);

    // getchar();

    return 0;
}
