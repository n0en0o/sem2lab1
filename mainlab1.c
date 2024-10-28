#include "array.h"
#include "menu.h"
#include "tests.h"
#include "field_Info.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Динамический массив с целыми числами и строками: сортировка, map, where, конкатенация */

int main()
{

    if (testIntArrays() == -1 || testStringArrays() == -1)
    {
        return -1;
    }

    Collection collection = {NULL, 0};

    while(1)
    {
        char input[20];
        printMenu();
        scanf("%19s", input);
        if (strncmp(input, "stop", 4) == 0)
        {
            printf("Bye!");
            break;
        }

        int action = atoi(input);
        switch (action) {
            case 1: {
                printf("All arrays: ");
                for (size_t i = 0; i < collection.size; i++) {
                    printf("%s ", collection.arrays[i].name);
                }
                break;
            }


            case 2: {
                char name[20];
                printf("Enter array's name to show: ");
                scanf("%19s", name);
                NamedArray *arr = arrayFindInCollection(&collection, name);
                if (arr) {
                    arrayPrintElements(arr);
                } else {
                    printf("Array not found.\n");
                }
                break;
            }

            case 3: {
                char name[20];
                printf("Enter array's name: ");
                scanf("%19s", name);
                arrayAddToCollection(&collection, name, getIntFieldInfo());
                printf("Array added!\n");
                break;
            }
            case 4: {
                char name[20];
                printf("Enter array's name: ");
                scanf("%19s", name);
                arrayAddToCollection(&collection, name, getStringFieldInfo());
                printf("Array added!\n");
                break;
            }

            case 5:
            {
                char name[20];
                int el;
                printf("Enter int array's name: ");
                scanf("%19s", name);
                printf("Enter int element to add: ");
                char ch;
                scanf("%d", &el);
                int flag = 0;
                while ((ch = getchar()) != '\n'){
                    printf("Wrong value!\n");
                    flag = 1;
                    break;
                }
                if (flag == 0)
                {
                    arrayAddElement(&collection, name, &el);
                }
                break;
            }

            case 6: {
                char name[20];
                char el[20];
                printf("Enter string array's name: ");
                scanf("%19s", name);
                printf("Enter string element to add: ");
                scanf("%19s", el);
                arrayAddElement(&collection, name, el);
                break;
            }

            case 7:
            {
                char name[20];
                printf("Enter array's name: ");
                scanf("%19s", name);
                arrayRemoveElement(&collection, name);
                break;
            }

            case 8:
            {
                char name[20];
                printf("Enter array's name to sort: ");
                scanf("%19s", name);
                arraySort(&collection, name);
                break;
            }

            case 9:
            {
                char name1[20], name2[20];
                printf("Enter first array's name: ");
                scanf("%19s", name1);
                printf("Enter second array's name: ");
                scanf("%19s", name2);
                arrayConcatenation(&collection, name1, name2);
                break;
            }

            case 10:
            {
                char name[20];
                printf("Enter array's name to use: ");
                scanf("%19s", name);
                arrayMap(&collection, name, func1);
                break;
            }

            case 11:
            {
                char name[20], sidename[20];
                printf("Enter array's name to use: ");
                scanf("%19s", name);
                printf("Enter side array's name: ");
                scanf("%19s", sidename);
                arrayWhere(&collection, name, sidename, func2);
                break;
            }

            default: {
                printf("Unknown command.\n");
                break;
            }
        }

    }

    return 0;
}