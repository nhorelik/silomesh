#include <stdio.h>

/* Function Declarations */

// functions exposed to python via SWIG
void hello(void);

/* Functions */

void hello(void)
{
  printf("Hello World!\n");
}
