#include <stdio.h>
#include "ex2.h"


void swap (int* first , int* second);
int numberOfEven(int array[],int size);

int main(){
    // int arr[] = {12,23,43,21,34,22,1,4,100};
    // float res = avg(arr, sizeof(arr)/sizeof(arr[0]));
    // printf("Average: %.2f\n", res);
    int arr2[] = {//7 is winner
    7, 12, 7, 3, 9, 7, 22, 15, 7, 8,
    3, 7, 19, 7, 1, 14, 7, 5, 11, 7,
    30, 2, 7, 18, 7, 44, 10, 6, 3, 25,
    3, 17, 8, 12, 3, 21, 9, 4, 3, 13,
    2, 16, 20, 10, 5, 22, 1, 8, 14, 11
};

    int arr3[] = {1,1,0,0,1,0,1};
    //int res = mostOccur(arr2, sizeof(arr2)/sizeof(arr2[0]));
    //int res1 = sortOddEven(arr2, sizeof(arr2)/sizeof(arr2[0]));
    sortArray(arr2,sizeof(arr2)/sizeof(arr2[0]));
    sortBoolArray(arr3,sizeof(arr2)/sizeof(arr2[0]));
    //printf("number of even numbers %d\n", res1);
    return 0;
}

float avg(int arr[], int size){
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return (float)sum / size;

}

int mostOccur(int array[], int size) {
    if (size <= 0) return -1; 

    int maxOccur = array[0];
    int maxCount = 0;

    for (int i = 0; i < size; i++) {
        int currentVar = array[i];
        int currentCount = 0;

        
        for (int j = i; j < size; j++) {
            if (array[j] == currentVar) {
                currentCount++;
            }
        }

        if (currentCount > maxCount) {
            maxCount = currentCount;
            maxOccur = currentVar;
        }
    }

    return maxOccur;
}

// Function to rearrange the array and return the count of even numbers
int separateEvenOdd(int arr[], int size) {
    int even_idx = 0; // Pointer 1: The boundary for the next even number

    // Pointer 2: 'curr' scans through the array
    for (int curr = 0; curr < size; ++curr) {
        
        // Check if the current number is even (works perfectly for negative numbers)
        if (arr[curr] % 2 == 0) {
            
            // If the even number is not already at the correct boundary
            if (curr > even_idx) {
                int temp = arr[curr]; // Temporarily store the even number
                
                // Shift all odd elements between even_idx and curr one step to the right
                for (int i = curr; i > even_idx; --i) {
                    arr[i] = arr[i - 1];
                }
                
                // Drop the saved even number into the correct boundary position
                arr[even_idx] = temp;
            }
            
            // Increment the boundary to make room for the next even number
            even_idx++;
        }
    }
    
    // The even_idx also represents the total number of even numbers found
    return even_idx; 
}

void sortArray(int array[],int size){
    
    int i,j;

    for (i = 0; i < size - 1; i++)
    {
        for ( j = 0; j < size - 1 - i ; j++)
        {
            if (array[j] > array[j+1]){
                swap(&array[j],&array[j+1]);
            }
        }
        
    }
}

void sortBoolArray(int array[],int size){
     int i;
     int zero_index = 0;
     for ( i = 0; i < size; i++)
     {
        if (array[i] == 0)
        {
            array[i] = array[zero_index];
            array[zero_index] = 0;
            zero_index++;
        }
        
     }
     



}

void swap (int* first , int* second){
    int temp =  *first;
    *first = *second;
    *second = temp;
}


int numberOfEven(int array[],int size){
    int counter = 0;
    int i = 0;
    while (array[i] % 2 == 0 && i < size)
    {
       counter++;
       i++;
    }
    return counter;
}