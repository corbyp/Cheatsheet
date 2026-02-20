#include "binary_tree.h"

#include <stdio.h>

int main(void) {
  Tree tree;
  bt_init(&tree);

  Node node = lmao();
  bt_add(&tree, &node);
  rec_bt_print(&tree);
  
  return 0;
}
