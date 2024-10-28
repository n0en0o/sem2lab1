#include "tests.h"
#include <stdlib.h>
#include "field_Info.h"
void func1(void* a)
{
    int * b = (int*)a;
    *b = *b * 2;
}

int func2(void* a)
{
    if (*(int*)a % 2 == 0)
    {
        return 1;
    }
    else return 0;
}

int testIntArrays()
{
    int result = 0;
    Collection collection = {NULL, 0};

    arrayAddToCollection(&collection, "abc", getIntFieldInfo());
    if (collection.size != 1)
    {
        printf("arrayAddToCollection does not work!");
        result = -1;
    }

    NamedArray *arr = arrayFindInCollection(&collection, "abc");
    if (!arr)
    {
        printf("arrayFindInCollection does not work!");
        result = -1;
    }

    int *p1 = (int*)1;
    arrayAddElement(&collection, "abc", &p1);
    if (arr->size != 1)
    {
        printf("arrayAddElement does not work!");
        result = -1;
    }

    arrayRemoveElement(&collection, "abc");
    if (collection.arrays->size != 0)
    {
        printf("arrayRemoveElement does not work!");
        result = -1;
    }

    int *p2 = (int*)2;
    arrayAddElement(&collection, "abc", &p2);
    arrayAddElement(&collection, "abc", &p1);
    arraySort(&collection, "abc");
    if (*(int*)arr->element > *(int*)arr->element + arr->fieldInfo.elemSize)
    {
        printf("arraySort does not work!");
        result = -1;
    }

    //?
    int *p3 = (int*)3;
    arrayAddToCollection(&collection, "cba", getIntFieldInfo());
    arrayAddElement(&collection, "cba", &p3);
    arrayConcatenation(&collection, "abc", "cba");
    if (arr->size != 2)
    {
        printf("arrayConcatenation does not work!");
        result = -1;
    }

    arrayMap(&collection, "abc", func1);
    if (*((int*)arr->element + arr->fieldInfo.elemSize) % 2 != 0)
    {
        printf("arrayMap does not work!");
        result = -1;
    }

    arrayWhere(&collection, "abc", "q", func2);
    NamedArray *b = arrayFindInCollection(&collection, "q");
    if (!b)
    {
        printf("arrayWhere does not work!");
        result = -1;
    }

    for (size_t i = 0; i < collection.size; i++)
    {
        arrayFree(&collection.arrays[i]);
    }
    free(collection.arrays);
    return result;
}

int testStringArrays()
{
    int result = 0;
    Collection collection = {NULL, 0};

    arrayAddToCollection(&collection, "abc", getStringFieldInfo());
    if (collection.size != 1)
    {
        printf("arrayAddToCollection does not work!");
        result = -1;
    }

    NamedArray *arr = arrayFindInCollection(&collection, "abc");
    if (!arr)
    {
        printf("arrayFindInCollection does not work!");
        result = -1;
    }

    arrayAddElement(&collection, "abc", "1");
    if (collection.arrays->size != 1)
    {
        printf("arrayAddElement does not work!");
        result = -1;
    }

    arrayRemoveElement(&collection, "abc");
    if (collection.arrays->size != 0)
    {
        printf("arrayAddElement does not work!");
        result = -1;
    }

    arrayAddElement(&collection, "abc", "t");
    arrayAddElement(&collection, "abc", "a");
    arraySort(&collection, "abc");
    char* s1 = (char*)arr->element + 0 * arr->fieldInfo.elemSize;
    char* s2 = (char*)arr->element + 1 * arr->fieldInfo.elemSize;
    if (strcmp(s1,s2)>0)
    {
        printf("arraySort does not work!");
        result = -1;
    }

    arrayAddToCollection(&collection, "cba", getStringFieldInfo());
    arrayAddElement(&collection, "cba", "c");
    arrayConcatenation(&collection, "abc", "cba");
    if (collection.arrays->size != 3)
    {
        printf("arrayConcatenation does not work!");
        result = -1;
    }

    for (size_t i = 0; i < collection.size; i++)
    {
        arrayFree(&collection.arrays[i]);
    }
    free(collection.arrays);
    return result;
}
