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

  if (!list->_root) {
    list->_root = node;
    ++list->_size;
    return list->_size - 1;
  }

  Node *cur = list->_root;

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
  Node *cur = list->_root;
  if (value == cur->value) {
    if (cur->nxt) {
      cur->prv = NULL;
      list->_root = cur->nxt;
      list->_root->prv = NULL;
    } else {
      list->_root = NULL;
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

int get(const struct List* list, const int idx) {
  Node *cur = list->_root;
  int i = 0;
  while (cur != NULL && idx != i++) {
    cur = cur->nxt;
  }

  return cur->value;
}

void clear(List *list) {
  check_list(list);

  Node *cur = list->_root;
  list->_root = NULL;
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

  if (!list->_root) {
    printf("[]\n");
    return;
  }

  printf("[");
  Node *cur = list->_root;
  while (cur->nxt) {
    printf("%d, ", cur->value);
    cur = cur->nxt;
  }
  printf("%d", cur->value);
  printf("]\n");
}

void print2(const List *list) {
  check_list(list);

  if (!list->_root)
    return;

  Node *cur = list->_root;
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
  list->get = get;
  list->clear = clear;
  list->print = print;
  list->print2 = print2;

  list->_size = 0;
  list->_root = NULL;

  return list;
}

void deconstruct(List *l) {
  l->_size = 0;
}
