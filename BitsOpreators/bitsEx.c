#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// add lds when compile a program

#define SUCCESS 1
#define CHAR_SIZE 8
#define MAX_CHAR 256

void print_num_bin(unsigned char number)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (number >> i) & 1);
    }
    printf("\n");
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

int rotateRightByN(unsigned char number, int N) // relevent for 8 bits
{
    N = N % 8; // to avoid number bigger than 8 or negative numbers
    number = (number >> N) | (number << (8 - N));

    print_num_bin(number);

    return SUCCESS;
}

void setbit(unsigned char x, int p, int n, unsigned char y)
{

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
// mask method
//  unsigned char setbits(unsigned char x, int p, int n, unsigned char y) {
//      // Step 1: extract the rightmost n bits from y
//      //   (1 << n) - 1 creates a mask of n ones
//      //   e.g. n=3: (1<<3)-1 = 0b111
//      unsigned char y_bits = y & ((1 << n) - 1);

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
// 1110011
//
// 0000001
// 0000001
// res =

void reverseBits(unsigned char number)
{
    unsigned char res = 0;

    for (int i = 0; i < 8; i++)
    {
        // grab the rightmost bit of number
        int bit = number & 1;

        // shift result left to make room
        res = (res << 1) | bit;

        // shift number right to get next bit
        number >>= 1;
    }

    print_num_bin(res);
}

void reverse_bit_lut(unsigned char number)
{
    print_num_bin(number);
    unsigned char look_up_table[MAX_CHAR] = {0};
    static bool first_time_run = 1;
    unsigned char res = 0;
    if (first_time_run)
    {
        for (int i = 0; i < MAX_CHAR; i++)
        {
            res = 0;
            int temp = i;

            for (int j = 0; j < 8; j++)
            {
                // grab the rightmost bit of number
                int bit = temp & 1;

                // shift result left to make room
                res = (res << 1) | bit;

                // shift number right to get next bit
                temp >>= 1;
            }
            look_up_table[i] = res;
        }
        first_time_run = 0;
    }

    print_num_bin(look_up_table[number]);
}

//"abcd" //every letter == 4 bits and we have 15 letters a-o
// to get the 4 bit value letter - 'a' + 1 // letter + 'a' + 1 to bring back to one byte size
void pack_letters(unsigned char *string)
{
    char temp;
    int i;
    int len = strlen(string);
    char letterfirst;
    char twoLetters;
    int write_pointer = 0;

    if (len == 0)
    {
        perror("empty string");
    }

    for (i = 0; i < len - 1; i += 2) //"abc"
    {
        temp = string[i] - 'a' + 1;
        letterfirst = temp << 4;
        temp = string[i + 1] - 'a' + 1;
        twoLetters = letterfirst | temp;
        string[write_pointer++] = twoLetters;
    }
    if ((len % 2) != 0)
    {
        temp = string[i] - 'a' + 1;
        temp <<= 4;
        string[write_pointer++] = temp;
    }

    string[write_pointer] = '\0';

    for (int i = 0; i < strlen(string); i++)
    {
        print_num_bin(string[i]);
    }
}

typedef struct two_letters
{
    int msb : 4; // high 4 bits
    int lsb : 4; // low 4 bits
} two_letters;

union packed_byte
{
    struct two_letters letters;
    unsigned char raw;
};

void pack_letters_bit_fields(unsigned char *string)
{
    union packed_byte b;
    int len = strlen(string);
    int i;
    int writepointer = 0;

    for (i = 0; i < len - 1; i += 2)
    {
        b.letters.msb = string[i] - 'a' + 1;
        b.letters.lsb = string[i + 1] - 'a' + 1;
        string[writepointer++] = b.raw;
    }

    if (len % 2 != 0)
    {
        b.letters.msb = string[i] - 'a' + 1;
        b.letters.lsb = 0;
        string[writepointer++] = b.raw;
    }

    string[writepointer] = '\0';
}



int main()
{

    // unsigned char inverted;
    //  invertBits('A', &inverted);
    //  rotateRightByN('A', 2);
    // reverseBits(65);
    // reverse_bit_lut(91);
    unsigned char str[] = "";
    pack_letters(str);

    return 0;
}