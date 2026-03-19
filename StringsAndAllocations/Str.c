#include <stdio.h>

int myStrLen(char str[]){
    int length = 0;
    int i = 0;
    
    while (str[i] != '\0')
    {
       length++;
       i++;
    }
    
    return length;
}

int myStrCopy(char strDest[],char strSource[]){
    int lenSource = myStrLen(strSource);
    int i;

    for (i = 0; i < lenSource; i++)
        {
            strDest[i] = strSource[i];
        }
    for (;i < lenSource; i++)
        {
            strDest[i] = '\0';
        }

        return strDest;

    }
          
               


int main() {
    int len = myStrLen("hello world");
    printf("the len is %d\n",len);
	return 0;
}
