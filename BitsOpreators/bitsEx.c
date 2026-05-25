#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define SUCCESS 1

int invertBits(unsigned char number, unsigned char *inverted)
{
    *inverted = ~number;

    for (int i = 7; i >= 0; i--)
    {
        printf("%d\n", (*inverted >> i) & 1);
    }

    return SUCCESS;
}

int rotateRightByN(unsigned char nunber , int N){





    
}

int main()
{

    unsigned char inverted;
    invertBits('A', &inverted);

    return 0;
}