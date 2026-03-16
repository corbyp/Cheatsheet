#include "double_linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// private helper functions

void check_list(List *list) {
  if (!list) {
    perror("Trying to perform operation on empty list\n");
    exit(1);
  }
}

// public functions

List *dll_create(void) {
  List *list = malloc(sizeof(List));

  if (!list) {
    perror("Could not malloc for list\n");
    exit(1);
  }

  list->size = 0;
  list->root = NULL;

  return list;
}

void dll_add(List *list, int value) {
  check_list(list);

  Node *node = malloc(sizeof(Node));
  if (!node) {
    perror("Could not malloc node\n");
    exit(1);
  }
  node->value = value;

  if (!list->root) {
    list->root = node;
    ++list->size;
    return;
  }

  Node *cur = list->root;

  while (true) {
    if (!cur->nxt) {
      break;
    }
    cur = cur->nxt;
  }

  ++list->size;
  cur->nxt = node;
  cur->nxt->prv = cur;
}

void dll_remove(List *list, int value) {
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
    return;
  }
  Node *tmp;

  while (cur->nxt) {
    if (cur->nxt->value == value) {
      tmp = cur->nxt;
      cur->nxt = cur->nxt->nxt;
      cur->nxt->prv = cur;
      free(tmp);
      return;
    }
    cur = cur->nxt;
  }
}

void dll_clear(List *list) {
  check_list(list);

  Node *cur = list->root;
  list->root = NULL;
  list->size = 0;
  Node *temp;

  while (cur->nxt) {
    temp = cur;
    cur = cur->nxt;
    free(temp);
  }
}

void dll_print(List *list) {
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

void dll_print2(List *list) {
  check_list(list);

  if (!list->root)
    return;

  Node *cur = list->root;
  while (cur) {
    printf("%p->%p(%d)->%p\n", cur->prv, cur, cur->value, cur->nxt);
    cur = cur->nxt;
  }
}
