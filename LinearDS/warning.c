//
// Created by 趙熠楷 on 3/27/25.
//

#include "warning.h"

#include <stdio.h>
#include <string.h>

void Warn(char * message) {
    unsigned int length = strlen(message);
    printf("\033[91m");
    for (int i = 0;  i<=length+2; ++i) {
        printf("-");
    }
    printf("\n");
    printf("%s\n", message);
    for (int i = 0;  i<=length+2; ++i) {
        printf("-");
    }
    printf("\033[0m\n");
}
