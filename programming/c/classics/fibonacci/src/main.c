#include <stdio.h>

void fib(void) {
  int a = 0;
  int b = 1;
  int temp;

  while (a < 100000) {
    printf("%d\n", a);
    temp = a + b;
    a = b;
    b = temp;
  }
}

int main(void) {
  fib();
  return 0;
}

