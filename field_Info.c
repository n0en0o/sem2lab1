#include "field_Info.h"
#include "number.h"
#include "mystring.h"
#include <stdlib.h>
#include <stdio.h>

static FieldInfo *IntFieldInfo = NULL;
static FieldInfo *StringFieldInfo = NULL;

FieldInfo *getIntFieldInfo(void)
{
    if (IntFieldInfo == NULL)
    {
        IntFieldInfo = malloc(sizeof(FieldInfo));
        IntFieldInfo->elemSize = sizeof(int);
        IntFieldInfo->printElement = numberPrint;
        IntFieldInfo->sortElement = numberSort;
    }
    return IntFieldInfo;
}

FieldInfo *getStringFieldInfo(void)
{
    if (StringFieldInfo == NULL)
    {
        StringFieldInfo = malloc(sizeof(FieldInfo));
        StringFieldInfo->elemSize = 160;
        StringFieldInfo->printElement = mystringPrint;
        StringFieldInfo->sortElement = mystringSort;
    }
    return StringFieldInfo;
}