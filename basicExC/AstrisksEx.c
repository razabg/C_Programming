#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "AstrisksEx.h"

int main(){
    //func1();
    //func2();
    //func3();
    //func4();
    //func5();
    //func6();
   
    return 0;
}


void get_input(int *rows, char *symbol){

    printf("enter number of rows\n");
    scanf("%d",rows);
    printf("enter the char you wnat\n");
    scanf(" %c",symbol);
    printf("\n--------------\n");
}



void func1(){

    char chr;
    int rows;
    get_input(&rows,&chr);

    for (size_t i = 0; i <= rows; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            printf("%c",chr);
        }
        printf("\n");
        
    }

}

void func2(){
    char chr;
    int rows;
    get_input(&rows,&chr);

    for (size_t i = rows; i > 0; i--)
    {
        for (size_t j = i; j > 0; j--)
        {
            printf("%c",chr);
        }
        printf("\n");
        
    }

}
void func3(){

    char chr;
    int rows;
    get_input(&rows,&chr);


    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            printf("%c",chr);
        }
        printf("\n");
        
    }

    for (size_t i = rows; i > 0; i--)
    {
        
        for (size_t j = i; j > 0; j--)
        {
            printf("%c",chr);
        }
        printf("\n");
        
    }

}

void func4(){

    char chr;
    int rows;
    get_input(&rows,&chr);

    for (size_t i = 0; i <= rows; i++)
    {
        printf("%*s",rows - i,"");
        for (size_t j = 0; j < i; j++)
        {
            printf("%c ",chr);
        }
        printf("\n");
        
    }




}
void func5(){

    char chr;
    int rows;
    get_input(&rows,&chr);



    for (size_t i = rows; i > 0; i--)
    {
        printf("%*s",rows - i,"");
        for (size_t j = i; j > 0; j--)
        {
            printf("%c ",chr);
        }
        printf("\n");
        
    }

}


void func6(){

     char chr;
    int rows;
    get_input(&rows,&chr);

    for (size_t i = 0; i < rows; i++)
    {
        printf("%*s",rows - i,"");
        for (size_t j = 0; j < i; j++)
        {
            printf("%c ",chr);
        }
        printf("\n");
        
    }

    for (size_t i = rows; i > 0; i--)
    {
        printf("%*s",rows - i,"");
        for (size_t j = i; j > 0; j--)
        {
            printf("%c ",chr);
        }
        printf("\n");
        
    }

}