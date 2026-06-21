#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

int SmallToBig(int first, int second)
{
    // if (first>second)
    return (first > second);
}

int BigToSmall(int first, int second)
{
    return (first < second);
}

int FromOddToEven(int first, int second)
{
    return (first % 2 == 0 && second % 2 == 1);
}

int FromEvenToOdd(int first, int second)
{
    return (first % 2 == 1 && second % 2 == 0);
}

void bubble_sort(int arr[], int size, bool (*compare)(int, int))
{ // function pointer can be used with typedef
    int i, j;

    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (comapre(arr[j], arr[j + 1]))
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main()
{

    int arr2[] = {// 7 is winner
                  7, 12, 7, 3, 9, 7, 22, 15, 7, 8,
                  3, 7, 19, 7, 1, 14, 7, 5, 11, 7,
                  30, 2, 7, 18, 7, 44, 10, 6, 3, 25,
                  3, 17, 8, 12, 3, 21, 9, 4, 3, 13,
                  2, 16, 20, 10, 5, 22, 1, 8, 14, 11};

    bubble_sort(arr2, sizeof(arr2) / sizeof(arr2[0]), SmallToBig);
    bubble_sort(arr2, sizeof(arr2) / sizeof(arr2[0]), BigToSmall);
    bubble_sort(arr2, sizeof(arr2) / sizeof(arr2[0]), FromOddToEven);
    bubble_sort(arr2, sizeof(arr2) / sizeof(arr2[0]), FromEvenToOdd);

    return 0;
}