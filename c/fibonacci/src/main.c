#include <stdio.h>

unsigned long fib_it(int n) {
  unsigned long a = 0;
  unsigned long b = 1;
  unsigned long temp;

  for (int i = 0; i < n; ++i) {
    temp = a + b;
    a = b;
    b = temp;
  }

  return a;
}

unsigned long fib_rec_helper(int n, unsigned long a, unsigned long b) {
  if (n == 0) {
    return a;
  }
  return fib_rec_helper(n - 1, a + b, a);
}

unsigned long fib_rec(int n) { return fib_rec_helper(n, 0, 1); }

int main(void) {
  printf("%lu\n", fib_it(50));
  printf("%lu\n", fib_rec(50));
  return 0;
}
