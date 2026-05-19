#include <stdio.h>
#include <stdbool.h>


void factorial();
bool palindrom(int n);
bool isPrime(int number);
bool digitsAcsendingOrder(int number);
int reverseNumber (int number);


int main()
{
    
   // factorial();
   // printf("Is 1221 a palindrome? %s\n", palindrom(1221) ? "Yes" : "No");
    printf("%d\n",reverseNumber(11111234));
    return 0;
}



void factorial()
{
    int input;
    unsigned int sum = 1;
    printf("enter number to see its factorial\n");
    scanf("%d",&input);
    if (input < 0 || input > 20) { // to avoid integer overflow
        printf("Input must be between 0 and 20\n");
        return;
    }

    for (int i = 1; i <= input; i++)
    {
        sum *= i;
    }
    printf("the factorial of %d is %u\n",input,sum);
}


bool palindrom(int n)
{
    int originalNum = n;
    int reverse = 0;
    int digit;

    while (n != 0)
    {
        digit = n % 10;
        reverse = reverse * 10 + digit;
        n /= 10;
    }

    if (reverse == originalNum) {
        return true;
    }
    return false;
}


bool isPrime(int number){
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}


bool digitsAcsendingOrder(int number){
    bool flag = 1;
    int digit;
    int secondigit;

    while(number > 0){
        digit = number % 10;
        number = number / 10;
        if (digit > 0)
        {
            secondigit = number % 10;
            if (digit < secondigit) {flag = false;} 
        }
        number = number / 10;

    }
    return flag;
}

int reverseNumber(int number){

    int reverse = 0;
    int digit;

    while (number != 0)
    {
        digit = number % 10;
        reverse = reverse * 10 + digit;
        number /= 10;
    }

    return reverse;
}







