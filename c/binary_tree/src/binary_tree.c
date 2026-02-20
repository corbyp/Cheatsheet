#include "binary_tree.h"
#include <stdio.h>
#define true 1
#define false 0

Node lmao() {
  Node node;
  node.value = 1;
  return node;
}

void bt_init(Tree *tree) {
  tree->root = NULL;
}

void bt_add(Tree *tree, Node *node) {
  if (tree->root == NULL) {
    tree->root = node;
    return;
  }

  Node *curr = tree->root;

  while (true) {
    if (node->value == curr->value) {
      return;
    } else if (node->value < curr->value) {
      if (curr->left == NULL) {
        curr->left = node;
        return;
      } else {
        curr = curr->left;
      }
    } else {
      if (curr->right == NULL) {
        curr->right = node;
        return;
      } else {
        curr = curr->right;
      }
    }
  }
}

void rec_bt_print_helper(Node * node) {
  printf("%d", node->value);

  if (node->left) rec_bt_print_helper(node->left);
  if (node->right) rec_bt_print_helper(node->right);
}

void rec_bt_print(Tree *tree) {
  if (!tree || !tree->root) return;

  rec_bt_print_helper(tree->root);
}
