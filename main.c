#include <stdio.h>

#include "Sort.h"

int main() {
    ElementType A[3] = {3, 2, 1};
    for (int i = 0; i<3; ++i) printf("%.2f ", A[i]);
    BubbleSort(A, 3);
    for (int i = 0; i<3; ++i) printf("%.2f ", A[i]);
    return 0;
}
