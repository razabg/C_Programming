
#include <string.h>

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n)
{

    int merged[n + m];
    int mergedCounter = 0;
    int num1 = 0;
    int num2 = 0;

    while (num1 != m && num2 != n)
    {

        if (nums1[num1] < nums2[num2])
        {
            merged[mergedCounter] = nums1[num1];
            num1++;
            mergedCounter++;
        }
        else if (nums1[num1] > nums2[num2])
        {
            merged[mergedCounter] = nums2[num2];
            num2++;
            mergedCounter++;
        }
        else
        {
            merged[mergedCounter] = nums1[num1];
            num1++;
            mergedCounter++;

            merged[mergedCounter] = nums2[num2];
            num2++;
            mergedCounter++;
        }
    }

    if (num1 < m)
    {
        while (num1 < m)
        {
            merged[mergedCounter] = nums1[num1];
            num1++;
            mergedCounter++;
        }
    }

    if (num2 < n)
    {
        while (num2 < n)
        {
            merged[mergedCounter] = nums2[num2];
            num2++;
            mergedCounter++;
        }
    }

    memcpy(nums1, merged, (n + m) * sizeof(int));
}

// inplace num1 solution;
//  void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n)
//  {
//      int i = m - 1;       // last real element in nums1
//      int j = n - 1;       // last element in nums2
//      int k = m + n - 1;   // last slot in nums1

//     while (i >= 0 && j >= 0)
//     {
//         if (nums1[i] > nums2[j])
//             nums1[k--] = nums1[i--];
//         else
//             nums1[k--] = nums2[j--];
//     }

//     while (j >= 0)        // leftover nums2 elements
//         nums1[k--] = nums2[j--];
//     // leftover nums1[0..i] are already in place — nothing to do
// }

// Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
// Output: [1,2,2,3,5,6]
// Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
// The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.
// Example 2:

// Input: nums1 = [1], m = 1, nums2 = [], n = 0
// Output: [1]
// Explanation: The arrays we are merging are [1] and [].
// The result of the merge is [1].
// Example 3:

// Input: nums1 = [0], m = 0, nums2 = [1], n = 1
// Output: [1]
// Explanation: The arrays we are merging are [] and [1].
// The result of the merge is [1].
// Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.