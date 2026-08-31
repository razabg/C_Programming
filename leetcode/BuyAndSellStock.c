#include <stdio.h>

int maxProfit(int *prices, int pricesSize)
{
    int min = prices[0];

    int profit;
    int maxProfit = 0;

    
    for (size_t i = 0; i < pricesSize; i++)
    {
        if (prices[i] < min)
        {
            min = prices[i];
        }
        for (int j = i + 1; j < pricesSize; j++)
        {
            if (prices[j] > min)
            {
                profit = prices[j] - min;
                if (profit > maxProfit)
                {
                    maxProfit = profit;
                }
            }
        }
    }

    return maxProfit;
}

int maxProfitFast(int *prices, int pricesSize)
{
    int min = prices[0];
    int best = 0;

    for (int i = 1; i < pricesSize; i++)
    {
        if (prices[i] < min)
        {
            min = prices[i];
        }
        else if (prices[i] - min > best)
        {
            best = prices[i] - min;
        }
    }

    return best;
}

// index(min) < index(max) -> max - min == profit

// Example 1:
// [1,2] = 1;
// Input: prices = [7,1,5,3,6,4]
// Output: 5
// Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
// Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
// Example 2:

// Input: prices = [7,6,4,3,1]
// Output: 0
// Explanation: In this case, no transactions are done and the max profit = 0.

int main(void)
{
    int t1[] = {7, 1, 5, 3, 6, 4};
    int t2[] = {7, 6, 4, 3, 1};
    int t3[] = {1, 2};

    printf("test1 expected=5 got=%d\n", maxProfit(t1, 6));
    printf("test2 expected=0 got=%d\n", maxProfit(t2, 5));
    printf("test3 expected=1 got=%d\n", maxProfit(t3, 2));

    printf("fast test1 expected=5 got=%d\n", maxProfitFast(t1, 6));
    printf("fast test2 expected=0 got=%d\n", maxProfitFast(t2, 5));
    printf("fast test3 expected=1 got=%d\n", maxProfitFast(t3, 2));

    return 0;
}
