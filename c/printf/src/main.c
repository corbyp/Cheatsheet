#include "cprintf.h"
#include <stdlib.h>

int main(void) {
  int x = 1;
  cprintf("% is a % guy!\n",
          (const void *[]){"corby", &x, "nice", NULL});
  return 0;
}
