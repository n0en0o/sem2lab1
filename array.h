#ifndef UNTITLED_ARRAY_H
#define UNTITLED_ARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include "field_Info.h"
#include "number.h"
#include "mystring.h"

typedef void (*PrintArrayElement)(const void* el);
typedef int (*SortArrayElement)(void* el1, void* el2);

typedef struct {
    char name[20];
    size_t size;
    FieldInfo fieldInfo;
    void* element;
} NamedArray;

typedef struct {
    NamedArray *arrays;
    size_t size;
} Collection;


void arrayFree(NamedArray* a);

void arrayAddToCollection(Collection *collection, const char *name, FieldInfo *getFieldInfo);

NamedArray *arrayFindInCollection(Collection *collection, const char *name);

void arrayPrintElements(const NamedArray *a);

void arrayAddElement(Collection *collection, const char *name, const void *elem);

void arrayRemoveElement(Collection *collection, const char *name);

void arraySort(Collection *collection, const char *name);

void arrayConcatenation(Collection *collection, const char *name1, const char *name2);

void arrayCreate(Collection *collection, const char *name, FieldInfo *getFieldInfo);

void arrayMap(Collection *collection, const char *name, void(*func1)(void*));

void arrayWhere(Collection *collection, const char *name, const char *sidename, int(*func2)(void*));

#endif //UNTITLED_ARRAY_H
