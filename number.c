#include "number.h"
#include <stdio.h>
#include <stdlib.h>

int numberSort(void* a, void* b)
{
    int flag = 0;
    if (*(int*) a > *(int*) b)
    {
        flag = 1;
        return flag;
    }
    return flag;
}

void numberPrint(const void* el) {
    printf("%d ", *(const int*)el);
}
