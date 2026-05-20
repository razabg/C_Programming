#include <stdio.h>
#include "vector.h"

static void print_vector(Vector *v)
{
    printf("  Array:       [ ");
    for (int i = 0; i < v->NumOfElements; i++)
        printf("%d ", v->dArray[i]);
    printf("]\n");
    printf("  Elements:    %d\n", v->NumOfElements);
    printf("  Capacity:    %d\n", v->dArrayBlockSize);
}

int main()
{
    int size, blockSize;
    printf("=== Interactive Vector Test ===\n\n");

    printf("Enter initial size and block size (e.g. 4 4): ");
    scanf("%d %d", &size, &blockSize);

    Vector *v = DynamicArrayCreate(size, blockSize);
    if (!v)
    {
        printf("ERROR: failed to create vector\n");
        return 1;
    }
    printf("Vector created.\n");
    print_vector(v);

    int choice;
    while (1)
    {
        printf("\n--- Menu ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print\n");
        printf("4. Destroy and exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int data;
            printf("Enter value to insert: ");
            scanf("%d", &data);

            int old_cap = v->dArrayBlockSize;
            int result = DynamicArrayInsert(v, data);

            if (result == OK)
            {
                printf("Inserted %d successfully.\n", data);
                if (v->dArrayBlockSize != old_cap)
                    printf("  Array was full — resized from %d to %d.\n", old_cap, v->dArrayBlockSize);
            }
            else if (result == NULLERROR)
                printf("ERROR: vector is NULL.\n");
            else if (result == RESIZEERROR)
                printf("ERROR: failed to resize array.\n");

            print_vector(v);
        }
        else if (choice == 2)
        {
            int data;
            int result = DynamicArrayDelete(v, &data);

            if (result == OK)
                printf("Deleted first element: %d\n", data);
            else if (result == UNDERFLOWERROR)
                printf("ERROR: vector is empty, nothing to delete.\n");
            else if (result == NULLERROR)
                printf("ERROR: vector is NULL.\n");

            print_vector(v);
        }
        else if (choice == 3)
        {
            print_vector(v);
        }
        else if (choice == 4)
        {
            DynamicArrayDestroy(v);
            printf("Vector destroyed. Goodbye.\n");
            break;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}