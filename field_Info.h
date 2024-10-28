#ifndef UNTITLED_FIELD_INFO_H
#define UNTITLED_FIELD_INFO_H
#include "number.h"
#include "mystring.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef void (*PrintArrayElement)(const void* el);
typedef int (*SortArrayElement)(void* el1, void* el2);

typedef struct {
    size_t elemSize;
    PrintArrayElement printElement;
    SortArrayElement sortElement;
} FieldInfo;

FieldInfo *getIntFieldInfo(void);

FieldInfo *getStringFieldInfo(void);

#endif
