#define BITS_IN_BYTE 8

int CountBit(unsigned char _num)
{
    int count = 0;
    int i;
    unsigned char mask = 1;

    for (i = 0; i < BITS_IN_BYTE; ++i)
    {
        if (_num & mask)
        {
            ++count;
        }
        mask <<= 1;
    }

    return count;
}

// option 2 little bit better runtime wise
// int CountBit(unsigned char _num)
// {
//     int count = 0;

//     while (_num)
//     {
//         if (_num & 1)
//         {
//             ++count;
//         }
//         _num >>= 1;
//     }

//     return count;
// }