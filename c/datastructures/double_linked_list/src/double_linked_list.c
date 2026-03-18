#include "double_linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// private helper functions

typedef struct Node {
  struct Node *prv;
  struct Node *nxt;
  int value;
} Node;


void check_list(const List *list) {
  if (!list) {
    perror("Trying to perform operation on empty list\n");
    exit(1);
  }
}

// public functions

int add(List *list, const int value) {
  check_list(list);

  Node *node = malloc(sizeof(Node));
  if (!node) {
    perror("Could not malloc node\n");
    exit(1);
  }
  node->value = value;

  if (!list->root) {
    list->root = node;
    ++list->_size;
    return list->_size - 1;
  }

  Node *cur = list->root;

  while (true) {
    if (!cur->nxt) {
      break;
    }
    cur = cur->nxt;
  }

  ++list->_size;
  cur->nxt = node;
  cur->nxt->prv = cur;
  return list->_size - 1;
}

int delete(List *list, const int value) {
  Node *cur = list->root;
  if (value == cur->value) {
    if (cur->nxt) {
      cur->prv = NULL;
      list->root = cur->nxt;
      list->root->prv = NULL;
    } else {
      list->root = NULL;
    }

    free(cur);
    return 0;
  }
  Node *tmp;

  while (cur->nxt) {
    if (cur->nxt->value == value) {
      tmp = cur->nxt;
      cur->nxt = cur->nxt->nxt;
      cur->nxt->prv = cur;
      free(tmp);
      return 0;
    }
    cur = cur->nxt;
  }

  return 0;
}

void clear(List *list) {
  check_list(list);

  Node *cur = list->root;
  list->root = NULL;
  list->_size = 0;
  Node *temp;

  while (cur->nxt) {
    temp = cur;
    cur = cur->nxt;
    free(temp);
  }
}

void print(const List *list) {
  check_list(list);

  if (!list->root) {
    printf("[]\n");
    return;
  }

  printf("[");
  Node *cur = list->root;
  while (cur->nxt) {
    printf("%d, ", cur->value);
    cur = cur->nxt;
  }
  printf("%d", cur->value);
  printf("]\n");
}

void print2(const List *list) {
  check_list(list);

  if (!list->root)
    return;

  Node *cur = list->root;
  while (cur) {
    printf("%p->%p(%d)->%p\n", cur->prv, cur, cur->value, cur->nxt);
    cur = cur->nxt;
  }
}

List *construct(void) {
  List *list = malloc(sizeof(List));

  if (!list) {
    perror("Could not malloc for list\n");
    exit(1);
  }

  list->add = add;
  list->delete = delete;
  list->clear = clear;
  list->print = print;
  list->print2 = print2;

  list->_size = 0;
  list->root = NULL;

  return list;
}

void deconstruct(List *l) {
  
}
