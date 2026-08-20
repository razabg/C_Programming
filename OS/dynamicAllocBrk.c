#include <stdio.h>
#include <stdlib.h>

// brk/sbrk vs mmap (both used internally by malloc/free):
//   brk(addr)   -> sets the program break (end of heap) to an absolute address
//   sbrk(incr)  -> moves the program break by `incr` bytes, returns old break;
//                  sbrk(0) just returns the current break with no change
//   mmap(...)   -> asks the kernel for a new, independent virtual memory
//                  mapping (not tied to the heap), used by malloc for large
//                  allocations (commonly > 128KB, threshold configurable)
//
// Difference: brk/sbrk grow/shrink one contiguous heap region, so freed
// memory in the middle can't be returned to the OS until the break shrinks
// past it. mmap allocations are separate regions that can be unmapped
// (munmap) and returned to the OS individually as soon as they're freed.

#define BUF_LEN 1000
#define NUM_OF_BUF 1000

int main()
{
    char *bufArr[NUM_OF_BUF];
    int i;

    for (i = 0; i < NUM_OF_BUF; i++)
    {
        bufArr[i] = (char *)malloc(BUF_LEN);
    }
    for (i = 0; i < NUM_OF_BUF; i++)
    {
        free(bufArr[i]);
    }
    return 0;
}


//examine it using strace linux command.