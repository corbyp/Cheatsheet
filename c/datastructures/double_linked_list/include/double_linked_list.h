#pragma once

typedef struct Node {
  struct Node *prv;
  struct Node *nxt;
  int value;
} Node;

typedef struct List {
  struct Node *root;
  int size;
} List;

List* dll_create(void);
void dll_add(List *list, int value);
void dll_remove(List *list, int value);
void dll_clear(List *list);

void dll_print(List *list);
void dll_print2(List *list);
