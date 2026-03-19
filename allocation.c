#include <stdlib.h>
#include <stdio.h>

typedef struct Person
{
    int id;
    char name[20];
    int age;
} Person;



int main() {

    Person person = {314,"raz abergel",31};
    Person *pPerson = &person;

    // printf("the id is %d\n,the name is %s\n,and the age is %d\n"
    //     ,person.id,person.name,person.age);

    // printf("the id is %d\n,the name is %s\n,and the age is %d\n"
    //     ,pPerson->id,pPerson->name,pPerson->age);    

    Person arrPerson[3] = {{55,"raz abergel",43},{1,"addie Golde",31},{2,"David azula",12}};

    for (int i = 0; i < 3; i++)
    {
         printf("the id is %d\n,the name is %s\n,and the age is %d\n"
        ,arrPerson[i].id,arrPerson[i].name,arrPerson[i].age);  
    }
    












    // int *ptr;
    
    // // Allocate memory for 100 integers
    // ptr = (int*)malloc(sizeof(int) * 100);
    
    // // Check if allocation was successful
    // if (ptr != NULL) {
    //     // Use the allocated memory
    //     for (int i = 0; i < 100; i++) {
    //         ptr[i] = i * 2;
    //     }
        
    //     // Print some values
    //     printf("First 5 values:\n");
    //     for (int i = 0; i < 5; i++) {
    //         printf("ptr[%d] = %d\n", i, ptr[i]);
    //     }
        
    //     // Free the allocated memory
    //     free(ptr);
    //     ptr = NULL; // Good practice to set pointer to NULL after freeing
    // } else {
    //     printf("Memory allocation failed!\n");
    //     return 1;
    // }
    
    return 0;
}