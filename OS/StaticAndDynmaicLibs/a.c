#include <stdio.h>

int k_glob_init = 7;              /* .data                       */
int k_glob_zero;                  /* .bss                        */
static int k_priv = 3;            /* .data, but a *local* symbol */
const char *msg = "hello from a"; /* pointer in .data, string in .rodata */

void a(void) { printf("a() -> %s, k_priv=%d\n", msg, k_priv); }
