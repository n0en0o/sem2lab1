#include "mystring.h"
#include <string.h>
#include <stdio.h>

void mystringPrint(const void* a)
{
    printf("%s ", (const void*) a);
}


int mystringSort(void* a, void* b)
{
    int flag = 0;
    char* s1 = (char*)a;
    char* s2 = (char*)b;
        if (strcmp(s1,s2)>0)
        {
            flag = 1;
            return flag;
        }
        else
        {
            return flag;
        }
}