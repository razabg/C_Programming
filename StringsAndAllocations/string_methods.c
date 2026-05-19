#include "string_methods.h"

void ReverseRange(char *_str, int start, int end)
{
    char temp;
    while (start < end)
    {
        temp = _str[start];
        _str[start] = _str[end];
        _str[end] = temp;
        start++;
        end--;
    }
}

int main()
{
    char word[] = "";
    // int res = ReverseStr(word);
    // printf("res is %d %s\n",res,word);
    printf("%d\n", IsPalindrome(word));

    return 0;
}

int ReverseStr(char *_str)
{
    int lenstr = strlen(_str);

    if (lenstr == 0)
    {
        return 0;
    }

    int left = 0;
    int right = lenstr - 1;
    int temp;

    while (left < right)
    {
        temp = _str[left];
        _str[left] = _str[right];
        _str[right] = temp;

        left++;
        right--;
    }

    return 1;

} // 1. In place
int IsPalindrome(char *_str)
{
    int len = strlen(_str);
    char copy[len + 1];
    strcpy(copy, _str);
    ReverseStr(copy);
    if (!strcmp(copy, _str))
    {
        return 1;
    }
    else
        return 0;
}
// 2
int MyAToI(char *_str, int *_num)
{
    //"101"
    if (_str == NULL || _num == NULL || strlen(_str) == 0)
    {
        return 0; // failure
    }

    int result = 0;
    int sign = 1;
    int i = 0;

    // handle sign
    if (_str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (_str[i] == '+')
    {
        i++;
    }

    while (_str[i] != '\0')
    {
        if (_str[i] < '0' || _str[i] > '9')
        {
            return 0; // not a digit, failure
        }
        result = result * 10 + (_str[i] - '0');
        i++;
    }

    *_num = result * sign;
    return 1; // success
}

int MyIToA(int _num, char *_buffer)
{

    if (_buffer == NULL)
    {
        return 0;
    }

    int i = 0;
    int isNegative = 0;

    // handle 0
    if (_num == 0)
    {
        _buffer[0] = '0';
        _buffer[1] = '\0';
        return 1;
    }

    // handle negative
    if (_num < 0)
    {
        isNegative = 1;
        _num = -_num;
    }

    while (_num > 0)
    {
        _buffer[i] = (_num % 10) + '0';
        _num = _num / 10;
        i++;
    }

    if (isNegative)
    {
        _buffer[i] = '-';
        i++;
    }

    _buffer[i] = '\0';

    // reverse the string since digits were inserted backwards
    ReverseStr(_buffer);

    return 1;
}


int ReverseWordsInString(char *_str)
{
    if (_str == NULL)
    {
        return 0;
    }

    int len = strlen(_str);
    if (len == 0)
    {
        return 0;
    }

    // step 1: reverse entire string
    ReverseRange(_str, 0, len - 1);

    // step 2: reverse each word individually
    int start = 0;
    int i;

    for (i = 0; i <= len; i++)
    {
        if (_str[i] == ' ' || _str[i] == '\0')
        {
            ReverseRange(_str, start, i - 1);
            start = i + 1;
        }
    }

    return 1;

}



 // 5. In place
int CountWordsInString(char *_str){

     if (_str == NULL) {
        return 0;
    }

    int count = 0;
    int inWord = 0;
    int i = 0;

    while (_str[i] != '\0') {
        if (!isspace(_str[i])) {
            if (!inWord) {
                count++;      // entered a new word
                inWord = 1;
            }
        } else {
            inWord = 0;       // we're in a space
        }
        i++;
    }

    return count;


    //not in place solution using strtok
    // if (_str == NULL || strlen(_str) == 0) {
    //     return 0;
    // }

    // char copy[strlen(_str) + 1];
    // strcpy(copy, _str);

    // int count = 0;
    // char *token = strtok(copy, " \t\n\r\v\f");

    // while (token != NULL) {
    //     count++;
    //     token = strtok(NULL, " \t\n\r\v\f");
    // }

    // return count;


}
