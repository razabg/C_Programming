
#include <stdio.h>
#include <string.h>

int mapLetters(char letter);

int romanToInt(char *s)
{
    int len = strlen(s);
    int number = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (i + 1 <= len)
        {
            if ((s[i] == 'I' && ((s[i + 1] == 'V') || (s[i + 1] == 'X'))) ||
                (s[i] == 'X' && ((s[i + 1] == 'L') || (s[i + 1] == 'C'))) ||
                (s[i] == 'C' && ((s[i + 1] == 'D') || (s[i + 1] == 'M'))))
            {
                number += (mapLetters(s[i + 1]) - mapLetters(s[i]));
                if (i + 2 <= len)
                {
                    i += 1;
                    continue;
                }
            }
        }

        number += mapLetters(s[i]);
    }

    return number;
}

// best solution
int romanToInt(char *s)
{
    int len = strlen(s);
    int total = 0;

    for (int i = 0; i < len; i++)
    {
        int cur = mapLetters(s[i]);
        int next = (i + 1 < len) ? mapLetters(s[i + 1]) : 0;

        if (cur < next)
            total -= cur;
        else
            total += cur;
    }

    return total;
}

// M C M X C I V
// 0 1 2 3 4 5 6
// I can be placed before V (5) and X (10) to make 4 and 9.
// X can be placed before L (50) and C (100) to make 40 and 90.
// C can be placed before D (500) and M (1000) to make 400 and 900.

int mapLetters(char letter)
{

    switch (letter)
    {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;

    case 'L':
        return 50;

    case 'C':
        return 100;

    case 'D':
        return 500;

    case 'M':
        return 1000;

    default:
        return 0;
    }
}

// I can be placed before V (5) and X (10) to make 4 and 9.
// X can be placed before L (50) and C (100) to make 40 and 90.
// C can be placed before D (500) and M (1000) to make 400 and 900.
//     Symbol       Value
// I             1
// V             5
// X             10
// L             50
// C             100
// D             500
// M             1000

int main(void)
{
    printf("III expected=3 got=%d\n", romanToInt("III"));
    printf("LVIII expected=58 got=%d\n", romanToInt("LVIII"));
    printf("MCMXCIV expected=1994 got=%d\n", romanToInt("MCMXCIV"));

    return 0;
}
