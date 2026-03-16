#include "list.h"
#include <stdio.h>

int main(void) {
  List* list = ll_init();

  for (int i = 0; i < 100; ++i) {
    ll_add(list, i);
  }

  ll_reverse(list);
  ll_print(list);
  ll_insert(list, 10, 5);

  printf("%d\n", ll_get(list, 10));
  
  return 0;
}
