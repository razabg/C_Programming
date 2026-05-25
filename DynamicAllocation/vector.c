#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

Vector *DynamicArrayCreate(unsigned size, unsigned blockSize)
{
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    if (!vector)
    {
        return NULLERROR;
    }

    vector->dArray = (int *)malloc(size * sizeof(int));

    if (!vector->dArray)
    {
        free(vector);
        return NULLERROR;
    }

    vector->dArraySize = size;
    vector->NumOfElements = 0;
    vector->dArrayBlockSize = blockSize;

    return vector;
}

void DynamicArrayDestroy(Vector *DynaminArrayPtr)
{

    if (!DynaminArrayPtr)
    {
        perror("the vector is not exist!");
        return;
    }
    free(DynaminArrayPtr->dArray);
    free(DynaminArrayPtr);
}

int DynamicArrayInsert(Vector *DynaminArrayPtr, int data)
{
    if (!DynaminArrayPtr)
    {
        return NULLERROR;
    }

    if (DynaminArrayPtr->NumOfElements == DynaminArrayPtr->dArrayBlockSize) // we need to extend the array
    {
        int new_block_size = DynaminArrayPtr->dArrayBlockSize * 2;
        int *temp = (int *)realloc(DynaminArrayPtr->dArray, new_block_size * sizeof(int));

        if (!temp)
        {
            return RESIZEERROR;
        }
        DynaminArrayPtr->dArray = temp;
        DynaminArrayPtr->dArrayBlockSize = new_block_size;
    }

    DynaminArrayPtr->dArray[DynaminArrayPtr->NumOfElements] = data;
    DynaminArrayPtr->NumOfElements += 1;

    return OK;
}

int DynamicArrayDelete(Vector *DynaminArrayPtr, int *data)
{
    if (!DynaminArrayPtr)
    {
        return NULLERROR;
    }

    if (DynaminArrayPtr->NumOfElements == 0)
    {
        return UNDERFLOWERROR;
    }

    *data = DynaminArrayPtr->dArray[0];

    for (size_t i = 0; i < DynaminArrayPtr->NumOfElements - 1; i++)
    {
        DynaminArrayPtr->dArray[i] = DynaminArrayPtr->dArray[i + 1];
    }

    DynaminArrayPtr->NumOfElements--;

    return OK;
}
