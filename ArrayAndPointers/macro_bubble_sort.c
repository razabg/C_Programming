#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARRAYSIZE 60000

#define BUBBLESORT(arr)                             \
    int temp;                                       \
    for (int i = 0; i < ARRAYSIZE - 1; i++)         \
    {                                               \
        for (int j = 0; j < ARRAYSIZE - i - 1; j++) \
        {                                           \
            if (arr[j] > arr[j + 1])                \
            {                                       \
                temp = arr[j + 1];                  \
                arr[j + 1] = arr[j];                \
                arr[j] = temp;                      \
            }                                       \
        }                                           \
    }

void BubbleSort(int *arr)
{
    int temp;
    for (int i = 0; i < ARRAYSIZE - 1; i++)
    {
        for (int j = 0; j < ARRAYSIZE - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main()
{
    clock_t start, end;
    double time1, time2;
    int arr[ARRAYSIZE];

    for (int i = 0; i < ARRAYSIZE; i++)
    {
        arr[i] = rand() % 80000;
    }
    start = clock();
    BubbleSort(arr);
    end = clock();
    time1 = (double)(end - start) / CLOCKS_PER_SEC;
    // printf("%d", RAND_MAX);
    start = clock();
    BUBBLESORT(arr)
    end = clock();
    time2 = (double)(end - start) / CLOCKS_PER_SEC;

    printf("the BubbleSort Func takes: %f [s] and the BubbleSort macro takes:%f [s]\n the time difference: %f", time1, time2, time1 - time2);
}