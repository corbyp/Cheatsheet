#pragma once

typedef struct Node {
  int value;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct Tree {
  struct Node *root;
} Tree;

/*
Adds node to tree
*/
void bt_add(Tree *tree, Node* node);

void bt_init(Tree *tree);

void bt_print(Tree *tree);

void rec_bt_print(Tree *tree);

Node lmao();
