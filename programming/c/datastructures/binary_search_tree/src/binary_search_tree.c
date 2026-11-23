#include "binary_search_tree.h"
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

// Private helper functions

void check_tree(Tree *tree) {
  if (!tree) {
    perror("Tried to do operation on not initialized tree\n");
    exit(1);
  }
}

// Gets parent node of requested value
// Returns NULL if tree does not contain value
Node *bst_get_parent(Tree *tree, int val) {
  check_tree(tree);

  Node *cur = tree->root;
  if (!cur)
    return NULL;

  while (true) {
    if (val < cur->value) {
      if (!cur->left)
        return NULL;
      else if (cur->left->value == val)
        return cur;
      else
        cur = cur->left;
    } else if (val > cur->value) {
      if (!cur->right)
        return NULL;
      else if (cur->right->value == val)
        return cur;
      else
        cur = cur->right;
    } else {
      return NULL;
    }
  }
}

// Returns node of requested value
// or NULL if tree does not contain value
Node *bst_get_node(Tree *tree, int val) {
  check_tree(tree);

  Node *cur = bst_get_parent(tree, val);

  if (!cur)
    return NULL;

  if (val < cur->value) {
    return cur->left;
  } else {
    return cur->right;
  }
}

Node *bst_get_max_helper(Node *node) {
  if (!node) {
    perror("Tried to get max of non existent node");
    exit(1);
  }

  Node *cur = node;
  while (cur->right)
    cur = cur->right;

  return cur;
}

Node *bst_get_min_helper(Node *node) {
  if (!node) {
    perror("Tried to get min of non existent node");
    exit(1);
  }

  Node *cur = node;
  while (cur->left)
    cur = cur->left;

  return cur;
}

Node *bst_remove_helper(Node *node) {
  Node *curr = node;

  while (true) {
  }
}

void bst_print_helper(Node *node, int level) {
  if (!node)
    return;

  bst_print_helper(node->right, level + 1);

  for (int i = 0; i < level; i++)
    printf("|  ");
  printf("|- %d\n", node->value);

  bst_print_helper(node->left, level + 1);
}

// Public use functions

Tree bst_init() {
  Tree tree;
  tree.root = NULL;
  return tree;
}

int bst_max(Tree *tree) {
  check_tree(tree);
  return bst_get_max_helper(tree->root)->value;
}

int bst_min(Tree *tree) {
  check_tree(tree);
  return bst_get_min_helper(tree->root)->value;
}

bool bst_contains(Tree *tree, int val) {
  check_tree(tree);
  return bst_get_parent(tree, val) ? true : false;
}

// Adds value to tree.
// Does not add duplicates.
void bst_add(Tree *tree, int val) {
  check_tree(tree);

  Node *node = malloc(sizeof(Node));
  if (!node) {
    fprintf(stderr, "Could not allocate memory for %d\n", val);
    exit(1);
  }

  node->value = val;

  if (!tree->root) {
    tree->root = node;
    return;
  }

  Node *cur = tree->root;

  while (true) {
    if (cur->value == val) {
      free(node); // If val already in tree, remove allocated node
      return;
    } else if (val < cur->value) {
      if (cur->left == NULL) {
        cur->left = node;
        node->parent = cur;
        return;
      }
      cur = cur->left;
    } else {
      if (cur->right == NULL) {
        cur->right = node;
        node->parent = cur;
        return;
      }
      cur = cur->right;
    }
  }
}

void bst_remove(Tree *tree, int val) {
  check_tree(tree);

  if (!tree->root)
    return;

  Node *cur;
  Node **parent_pointer = NULL;

  if (val == tree->root->value) {
    // Node in question is root thus does not have a parent
    cur = tree->root;
  } else {
    cur = bst_get_node(tree, val);

    if (!cur) // Values is not in tree
      return;

    if (val < cur->parent->value) {
      // The node in question is the left child of its parent
      parent_pointer = &(cur->parent->left);
    } else {
      parent_pointer = &(cur->parent->right);
    }
  }

  if (!cur->left && !cur->right) {
    // Node in question has no children
    // Node can be removed by removing pointer and freeing cur
    if (parent_pointer)
      // It has a parent, so it's not the root
      (*parent_pointer) = NULL;
    else
      // It is the root
      tree->root = NULL;

    free(cur);
  } else if (cur->left && cur->right) {
    // Node in question has two children
    // Find the successor, swap values and remove successor
    // Successor is the left most node from the current one
    Node *suc = cur->right;

    while (suc->left) {
      suc = suc->left;
    }

    if (suc->parent->left->value == suc->value) {
      suc->parent->left = NULL;
    } else {
      suc->parent->right = NULL;
    }
    cur->value = suc->value;
    free(suc);
  } else if (cur->left) {
    // Node in question only has left child
    // Parent pointer to the left child
    if (parent_pointer) {
      (*parent_pointer) = cur->left;
      cur->left->parent = cur->parent;
    }
    else
      tree->root = tree->root->left;
    free(cur);
  } else {
    // Node in question only has right child
    if (parent_pointer) {
      (*parent_pointer) = cur->right;
      cur->right->parent = cur->parent;
    }
    else
      tree->root = tree->root->right;
    free(cur);
  }
}

void bst_print(Tree *tree) {
  check_tree(tree);
  bst_print_helper(tree->root, 0);
}
