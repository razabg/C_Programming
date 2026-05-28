#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// add lds when compile a program

#define SUCCESS 1
#define CHAR_SIZE 8

void print_num_bin(unsigned char number){
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (number >> i) & 1);
    }

}

int invertBits(unsigned char number, unsigned char *inverted)
{
    *inverted = ~number;

    for (int i = 7; i >= 0; i--)
    {
        printf("%d\n", (*inverted >> i) & 1);
    }
    printf("\n");
    return SUCCESS;
}

int rotateRightByN(unsigned char number, int N)//relevent for 8 bits
{
    N = N % 8;// to avoid number bigger than 8 or negative numbers
    number = (number >> N) | (number << (8 - N));

    print_num_bin(number);
    
    return SUCCESS;
}

void setbit(unsigned char x ,int p,int n, unsigned char y){

    print_num_bin(x);
    print_num_bin(y);

    unsigned char substring = y << (CHAR_SIZE - n);
    substring >>= (CHAR_SIZE - p);
    unsigned char rightString = x << (CHAR_SIZE - (p - n));
    rightString >>= (CHAR_SIZE - (p - n));
    unsigned char leftString = x >> p;
    leftString <<= p;

    x = substring | rightString | leftString;
    printf("setbits n=%d, p=%d, gives x = ", n, p);


}
//mask method
// unsigned char setbits(unsigned char x, int p, int n, unsigned char y) {
//     // Step 1: extract the rightmost n bits from y
//     //   (1 << n) - 1 creates a mask of n ones
//     //   e.g. n=3: (1<<3)-1 = 0b111
//     unsigned char y_bits = y & ((1 << n) - 1);

//     // Step 2: shift them to the correct position
//     //   p=6, n=3 → shift left by 3 to land at indices 5,4,3
//     int shift = p - n;
//     unsigned char y_shifted = y_bits << shift;

//     // Step 3: create a mask to clear those bits in x
//     //   e.g. 0b111 << 3 = 0b00111000
//     unsigned char mask = ((1 << n) - 1) << shift;

//     // Step 4: clear the bits in x, then paste y's bits in
//     //   x & ~mask = 10000010  (hole)
//     //   | y_shifted = 00111000  (paste)
//     //   result     = 10111010
//     return (x & ~mask) | y_shifted;
// }

void reverseBits(unsigned char number) {
    unsigned char res = 0;

    for (int i = 0; i < 8; i++) {
        // grab the rightmost bit of number
        int bit = number & 1;

        // shift result left to make room
        res = (res << 1) | bit;

        // shift number right to get next bit
        number >>= 1;
    }

    print_num_bin(res);
}

int main()
{
    
    unsigned char inverted;
    // invertBits('A', &inverted);
   // rotateRightByN('A', 2);
   reverseBits(65);

    return 0;
}