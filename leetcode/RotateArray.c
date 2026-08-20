#include <string.h>
#include <limits.h>
#include <stdio.h>

void rotate(int *nums, int numsSize, int k)
{
    int rotateArr[numsSize];
    for (size_t i = 0; i < numsSize; i++)
    {
        rotateArr[(i + k) % numsSize] = nums[i];
    }

    memcpy(nums, rotateArr, sizeof(int) * numsSize);
}

// Example 1: there are 3 ways to solve this

// Input: nums = [1,2,3,4,5,6,7], k = 3
// Output: [5,6,7,1,2,3,4]
// Explanation:
// rotate 1 steps to the right: [7,1,2,3,4,5,6]
// rotate 2 steps to the right: [6,7,1,2,3,4,5]
// rotate 3 steps to the right: [5,6,7,1,2,3,4]
// Example 2:

// Input: nums = [-1,-100,3,99], k = 2
// Output: [3,99,-1,-100]
// Explanation:
// rotate 1 steps to the right: [99,-1,-100,3]
// rotate 2 steps to the right: [3,99,-1,-100]


static void reverse(int *nums, int start, int end)
{
    while (start < end) {
        int tmp = nums[start];
        nums[start++] = nums[end];
        nums[end--] = tmp;
    }
}

void rotate(int *nums, int numsSize, int k)
{
    k %= numsSize;
    reverse(nums, 0, numsSize - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, numsSize - 1);
}
