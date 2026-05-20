#ifndef VECTOR_H
#define VECTOR_H

#define OK 0
#define NULLERROR 1
#define OVERFLOWERROR 2
#define RESIZEERROR 3
#define UNDERFLOWERROR 4

typedef struct Vector
{
    int *dArray; // pointer to the array
    int dArraySize;
    int dArrayBlockSize; // max capacity
    int NumOfElements;
} Vector;

/* Description: Creates a new dynamic array vector
 * INPUT:       size - initial number of elements to allocate
 *              blockSize - capacity chunk size used for growing
 * OUTPUT:      pointer to the created Vector
 * ERROR:       returns NULLERROR if allocation fails */
Vector *DynamicArrayCreate(unsigned size, unsigned blockSize);

/* Description: Frees all memory associated with the vector
 * INPUT:       DynaminArrayPtr - pointer to the vector to destroy
 * OUTPUT:      none
 * ERROR:       prints error if pointer is NULL */
void DynamicArrayDestroy(Vector *DynaminArrayPtr);

/* Description: Inserts an integer at the end of the vector, grows if full
 * INPUT:       DynaminArrayPtr - pointer to the vector
 *              data - integer value to insert
 * OUTPUT:      OK on success
 * ERROR:       NULLERROR if vector is NULL, RESIZEERROR if realloc fails */
int DynamicArrayInsert(Vector *DynaminArrayPtr, int data);

/* Description: Removes the first element from the vector and shifts remaining elements left
 * INPUT:       DynaminArrayPtr - pointer to the vector
 *              data - pointer to store the removed value
 * OUTPUT:      OK on success
 * ERROR:       NULLERROR if vector is NULL, UNDERFLOWERROR if vector is empty */
int DynamicArrayDelete(Vector *DynaminArrayPtr, int *data);

#endif