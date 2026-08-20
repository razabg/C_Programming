
#include <string.h>
#include <limits.h>

#define INT_NULL INT_MIN

int removeElement(int *nums, int numsSize, int val)
{

    int lastElememt = numsSize - 1;
    int i = 0;
    int k = 0;

    while (i < lastElememt)
    {
        while (nums[lastElememt] == val && lastElememt > i) // still o(n) complex
        {
            --lastElememt;
        }

        if (nums[i] == val)
        {

            int temp = nums[i];
            nums[i] = nums[lastElememt];
            nums[lastElememt] = temp;
            lastElememt--;
        }
        i++;
    }

    for (size_t j = 0; j < numsSize; j++)
    {
        if (nums[j] != val)
        {
            k++;
        }
    }

    return k;
}

int removeElement(int *nums, int numsSize, int val) // the best elegant solution!
{
    int n = numsSize;
    int i = 0;

    while (i < n)
    {
        if (nums[i] == val)
        {
            nums[i] = nums[--n];
        }
        else
        {
            i++;
        }
    }

    return n;
}

int main()
{
    int nums[8] = {0, 1, 2, 2, 3, 0, 4, 2};
    removeElement(nums, 8, 2);
    return 0;
}

// Input: nums = [0,1,2,2,3,0,4,2], val = 2
// Output: 5, nums = [0,1,4,0,3,_,_,_]

// 1 - i = 0 , last = 7 0,1,4,2,3,0,2,2
// 2 - i = 3 last = 5   0,1,4,0,3,2,2,2
// 3 - i = 4 last = 4 done  = k = 5
