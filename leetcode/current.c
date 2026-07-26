#include <stdio.h>
#include <stdlib.h>

int countBits(unsigned char num)
{
    // 0110 0010
    // 0000 0001
    int mask = 1;
    int count = 0;

    while (num)
    {
        count += num & mask;
        num = num >> 1;
    }

    return count;
}

static int BIT_COUNT_LUT[256];

void buildBitCountLUT(void)
{
    for (int i = 0; i < 256; i++)
    {
        BIT_COUNT_LUT[i] = countBits((unsigned char)i);
    }
}

int countBitsLUT(unsigned char num)
{
    return BIT_COUNT_LUT[num];
}

int main()
{
    buildBitCountLUT();
    printf("%d\n", countBitsLUT(0b01111110));
    return 0;
}