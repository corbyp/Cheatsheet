#include "binary_search_tree.h"

#include <stdio.h>

int main(void) {
  Tree tree = bst_init();
  int arr[] = {7, 5, 15, 3, 13, 4, 9, 12, 0, 2, 14, 1, 11, 6, 8, 10};

  for (int i = 0; i < 16; ++i) {
    bst_add(&tree, arr[i]);
  }

  bst_print(&tree);
    printf("--------------------------------------\n");

  bst_remove(&tree, 3);
  bst_print(&tree);
    printf("--------------------------------------\n");

  for (int i = 0; i < 21; ++i) {
    printf("Removing: %d\n", i);
    bst_remove(&tree, i);
    bst_print(&tree);
    printf("--------------------------------------\n");
  }

  printf("%b\n", bst_contains(&tree, 15));

  return 0;
}
