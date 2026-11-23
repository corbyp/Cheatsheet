#pragma once

#include <stdbool.h>

typedef struct Node {
  int value;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct Tree {
  struct Node *root;
} Tree;

// Adds node to tree
void bst_add(Tree *tree, int val);

// Removes given value from tree
void bst_remove(Tree *tree, int val);

// Initializes tree.
// This is just necessary to actually put tree->root as NULL
Tree bst_init();

// Prints tree in ascii directory tree style
void bst_print(Tree *tree);

// Check if value is contained in tree
bool bst_contains(Tree *tree, int val);

// Returns max value contained in tree
int bst_max(Tree *tree);

// Returns min value contained in tree
int bst_min(Tree *tree);
