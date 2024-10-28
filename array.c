#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void arrayCreate(Collection *collection, const char *name, FieldInfo *getFieldInfo)
{
    NamedArray *newArr = malloc(sizeof(NamedArray));
    strncpy(newArr->name, name, sizeof(newArr->name));
    newArr->size = 0;
    newArr->fieldInfo = *getFieldInfo;
    newArr->element = malloc(newArr->fieldInfo.elemSize);
    collection->arrays[collection->size] = *newArr;
}

void arrayFree(NamedArray* a)
{
    free(a->element);
    a->element = NULL;
    a->size = 0;
    a->fieldInfo.elemSize = 0;
}

void arrayAddToCollection(Collection *collection, const char *name, FieldInfo *getFieldInfo)
{
    collection->arrays = realloc(collection->arrays, (collection->size + 1) * sizeof(NamedArray));
    //NamedArray *newArr = &collection->arrays[collection->size];
    NamedArray* newArr = malloc(sizeof(NamedArray));
    collection->arrays[collection->size] = *newArr;
    strncpy(newArr->name, name, sizeof(name));
    arrayCreate(collection, newArr->name, getFieldInfo);
    collection->size++;
}

NamedArray *arrayFindInCollection(Collection *collection, const char *name)
{
    for (size_t i = 0; i < collection->size; i++)
    {
        if (strcmp(collection->arrays[i].name, name) == 0)
        {
            return &collection->arrays[i];
        }
    }
    return NULL;
}

void arrayPrintElements(const NamedArray *a)
{
    for (size_t i = 0; i < a->size; i++)
    {
        a->fieldInfo.printElement((void *)a->element + i * a->fieldInfo.elemSize);
    }
}

void arrayAddElement(Collection *collection, const char *name, const void *el)
{
    NamedArray *a = arrayFindInCollection(collection, name);
    if (a)
    {
        a->element = realloc(a->element, (a->size + 1) * a->fieldInfo.elemSize);
        memcpy((char*)a->element + a->size * a->fieldInfo.elemSize, el, a->fieldInfo.elemSize);
        a->size++;
    }
    else printf("Array not found.\n");
}

void arraySort(Collection *collection, const char *name)
{
    NamedArray *a = arrayFindInCollection(collection, name);
    if (a)
    {
        SortArrayElement sort = a->fieldInfo.sortElement;
        for(size_t i = 0; i != a->size-1; i++)
            for(size_t j = 0; j != a->size - i - 1; j++)
                if(sort(a->element + j * a->fieldInfo.elemSize, a->element + (j+1) * a->fieldInfo.elemSize))
                {
                    void *tmpElement = malloc(a->fieldInfo.elemSize);
                    strncpy(tmpElement, a->element + j * a->fieldInfo.elemSize, a->fieldInfo.elemSize);
                    strncpy(a->element + j * a->fieldInfo.elemSize, a->element + (j + 1) * a->fieldInfo.elemSize, a->fieldInfo.elemSize);
                    strncpy(a->element + (j + 1) * a->fieldInfo.elemSize, tmpElement, a->fieldInfo.elemSize);
                    free(tmpElement);
                }

    }
    else printf("Array not found.\n");
}

void arrayRemoveElement(Collection *collection, const char *name)
{
    NamedArray *a = arrayFindInCollection(collection, name);
    if (a)
    {
        void* tmp = malloc(a->fieldInfo.elemSize);
        memcpy(tmp, a->element + (a->size - 1) * a->fieldInfo.elemSize, a->fieldInfo.elemSize);
        memset(a->element + (a->size - 1) * a->fieldInfo.elemSize, 0, a->fieldInfo.elemSize);
        free(tmp);
        a->size--;
    }
    else printf("Array not found.\n");


}


void arrayConcatenation(Collection *collection, const char *name1, const char *name2)
{
    NamedArray *a = arrayFindInCollection(collection, name1);
    if (a)
    {
        NamedArray *b = arrayFindInCollection(collection, name2);
        if (b)
        {
            if ((int*)a->fieldInfo.elemSize == (int*)b->fieldInfo.elemSize)
            {
                int tmp = a->size;
                for (int i = 0; i < b->size; i++)
                {
                    a->element = realloc(a->element, (a->size + 1) * a->fieldInfo.elemSize);
                    a->size++;
                    strncpy(a->element + tmp * a->fieldInfo.elemSize, b->element + i * b->fieldInfo.elemSize,b->fieldInfo.elemSize);
                    tmp++;
                }
                //printf("Arrays have concatenated, show again the first one to see!");
            }
            else printf("Arrays can't be concatenated.\n");
        }
        else printf("Second array not found.\n");
    }
    else printf("First array not found.\n");
}

void arrayMap(Collection *collection, const char *name, void (*func1)(void*))
{
    NamedArray *a = arrayFindInCollection(collection, name);
    if (a)
    {
        for (int i = 0; i < a->size; i++)
        {
            func1((char *)a->element + i * a->fieldInfo.elemSize);
        }
    }
    else printf("Array not found!");
}

void arrayWhere(Collection *collection, const char *name, const char *sidename, int (*func2)(void*))
{
    NamedArray *a = arrayFindInCollection(collection, name);
    if (a)
    {
        arrayAddToCollection(collection, sidename, getIntFieldInfo());
        for (size_t i = 0; i < a->size; i++)
        {
            void *elem = malloc(sizeof(int));
            strncpy(elem, a->element + i * a->fieldInfo.elemSize, sizeof(int));
            if (func2(elem))
            {
                arrayAddElement(collection, sidename, elem);
                free(elem);
            }
        }
    }
    else printf("Array not found!");
}
