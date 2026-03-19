#ifndef EX2_H
#define EX2_H

/* -------------------------------------------------------------------------- */

/**
 * DESCRIPTION: Calculates the mathematical average (mean) of all integers in an array.
 * INPUT:       int arr[] - The source array; int size - Number of elements.
 * OUTPUT:      float - The calculated average.
 * ERRORS:      
 */
float avg(int arr[], int size);

/**
 * DESCRIPTION: Identifies the number that appears most frequently in the array (the Mode).
 * INPUT:       int array[] - The source array; int size - Number of elements.
 * OUTPUT:      int - The value of the most frequent element.
 * ERRORS:      If size <= 0, returns -1. If multiple numbers have the same count, 
 * returns the first one encountered.
 */
int mostOccur(int array[], int size);

/**
 * DESCRIPTION: Reorders the array in-place so all even numbers are shifted to the left 
 * and all odd numbers are shifted to the right.
 * INPUT:       int array[] - The array to reorder; int size - Number of elements.
 * OUTPUT:      number of even numbers
 * ERRORS:      If the array pointer is NULL, returns NULL.
 */
int sortOddEven(int array[], int size);

/**
 * DESCRIPTION: Sorts the entire array in ascending numerical order (lowest to highest).
 * INPUT:       int array[] - The array to sort; int size - Number of elements.
 * OUTPUT:      void - The array is modified directly in memory.
 * ERRORS:      If size < 2, the function exits without making changes.
 */
void sortArray(int array[], int size);

/**
 * DESCRIPTION: An optimized sort specifically for arrays containing only 0s and 1s.
 * INPUT:       int array[] - The boolean-style array; int size - Number of elements.
 * OUTPUT:      void - The array is modified directly in memory.
 * ERRORS:      If the array contains values other than 0 or 1, those values are 
 * treated as 1s (True) and moved to the end.
 */
void sortBoolArray(int array[], int size);



#endif