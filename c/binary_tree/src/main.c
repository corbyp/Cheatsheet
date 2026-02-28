#include "binary_tree.h"

#include <stdio.h>

int main(void) {
  Tree tree = bt_init();
  int arr[] = {7, 5, 15, 3, 13, 4, 9, 12, 0, 2, 14, 1, 11, 6, 8, 10};

  for (int i = 0; i < 16; ++i) {
    bt_add(&tree, arr[i]);
  }

  bt_print(&tree);
    printf("--------------------------------------\n");

  bt_remove(&tree, 3);
  bt_print(&tree);
    printf("--------------------------------------\n");

  for (int i = 0; i < 21; ++i) {
    printf("Removing: %d\n", i);
    bt_remove(&tree, i);
    bt_print(&tree);
    printf("--------------------------------------\n");
  }

  printf("%b\n", bt_contains(&tree, 15));

  return 0;
}
