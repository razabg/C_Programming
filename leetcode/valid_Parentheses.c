#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../RAZ_DS/Stack/stack.h"

// input: s = "[{()}]"
// Output: true
// Explanation:  All the brackets are well-formed.
// Input:  s = "([{]})"
// Output: false
// Explanation: The expression is not balanced because there is a closing ']' before the closing '}'.

bool valid(char *str)
{
    Stack *stack = StackCreate(10, 2);
    int pointer = 0;
    int len = strlen(str);
    void *val;

    if (len == 0)
        return true;

    while (pointer < len)
    {
        if (str[pointer] != ')' && str[pointer] != ']' && str[pointer] != '}')
        {
            StackPush(stack, &str[pointer]);
            pointer++;
        }
        else
        {
            if (StackIsEmpty(stack))
                return false;

            StackPop(stack, &val);
            char ch = *(char *)val;
            if (!((ch == '(' && str[pointer] == ')') || (ch == '{' && str[pointer] == '}') || (ch == '[' && str[pointer] == ']')))
                return false;

            pointer++;
        }
    }
    return StackIsEmpty(stack);
}

int main()
{
    // bool res = valid("{[(]}");
    // bool res = valid("(()");
    // bool res = valid("({({})})");
    // bool res = valid("");
    // printf("%d\n", res);

    void *var;
    char one = 'A';
    var = &one;
    printf("%c\n", *(char *)var);

    return 0;
}