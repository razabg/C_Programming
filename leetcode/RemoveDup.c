#include <string.h>
#include <limits.h>
#include <stdio.h>

int removeDuplicates(int *nums, int numsSize)
{

    if (numsSize == 0)
    {
        return 0;
    }

    int curr = nums[0];
    int insertNext = 1;
    int i = 0;

    for (i = 0; i < numsSize; i++)
    {
        if (nums[i] == curr)
        {
            continue;
        }
        else
        {
            nums[insertNext] = nums[i];
            insertNext++;
            curr = nums[i];
        }
    }
    return insertNext;
}

int main()
{
    // int nums[] = {0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 7, 8, 8, 8, 9, 9, 9};
    int nums[] = {0, 1, 2, 6, 7, 8, 9};

    printf("%d\n", removeDuplicates(nums, sizeof(nums) / sizeof(nums[0])));
    return 0;
}

// Example 1:

// Input: nums = [1,1,2]
// Output: 2, nums = [1,2,_]
// Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
// It does not matter what you leave beyond the returned k (hence they are underscores).
// Example 2:

// Input: nums = [0,0,1,1,1,2,2,3,3,4]
// Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
// Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
// It does not matter what you leave beyond the returned k (hence they are underscores).
