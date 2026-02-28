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
void bt_add(Tree *tree, int val);

// Removes given value from tree
void bt_remove(Tree *tree, int val);

// Initializes tree.
// This is just necessary to actually put tree->root as NULL
Tree bt_init();

// Prints tree in ascii directory tree style
void bt_print(Tree *tree);

// Check if value is contained in tree
bool bt_contains(Tree *tree, int val);

// Returns max value contained in tree
int bt_max(Tree *tree);

// Returns min value contained in tree
int bt_min(Tree *tree);
