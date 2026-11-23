#include "linked_list.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool error_handling(const List *list, int *index) {
  if (!list || !list->root) {
    errno = EINVAL;
    return 0;
  }

  if (index) {
    if (*index < 0)
      *index = list->_size - *index;

    if (*index < 0 || *index >= list->_size) {
      errno = ERANGE;
      return 0;
    }
  }

  return 1;
}

int size(const List *list) { return 0; }

int cap(const List *list) { return 0; }

int add(List *list, int val) {
  Node *root = list->root;

  if (root == NULL) {
    root = (Node *)malloc(sizeof(Node));

    if (root == NULL) {
      goto error_handling;
    }

    root->value = val;

    list->root = root;
    list->_size++;
    return 0;
  } else {
    Node *curr = root;

    while (curr->next != NULL) {
      curr = curr->next;
    }

    curr->next = (Node *)malloc(sizeof(Node));

    if (curr->next == NULL) {
      goto error_handling;
    }

    curr->next->value = val;
    list->_size++;
    return 0;
  }

error_handling:
  fprintf(stderr, "Could not malloc for %d\n", val);
  exit(1);
}

void insert(List *list, int index, int val) {
  if (index >= list->_size || index < 0) {
    fprintf(stderr,
            "Tried inserting into position %d but list only has length %d\n",
            index, list->_size);
    return;
  } else {
    Node *curr = list->root;
    index--;

    while (index-- > 0) {
      curr = curr->next;
    }

    printf("%d\n", curr->value);
  }
}

int pop(List *list) { return 0; }

int delete(List *list, const int val) {
  Node *root = list->root;

  if (root == NULL) {
    fprintf(stderr, "Tried to remove from empty list!\n");
  } else if (root->value == val) {
    Node *temp = list->root;
    list->root = root->next;
    free(temp);
    list->_size--;
  } else {
    Node *curr;
    Node *parent = root;

    for (curr = root->next; curr != NULL; curr = curr->next) {
      if (curr->value == val) {
        parent->next = curr->next;
        list->_size--;
        free(curr);
        return 0;
      }

      parent = curr;
    }

    fprintf(stderr, "Item %d not found!\n", val);
  }
  return 0;
}

int deletei(List *list, int index) { return 0; }

void reverse(List *list) {
  Node *root = list->root;

  if (root == NULL) {
    fprintf(stderr, "Tried reversing an empty list!\n");
  } else {
    Node *temp;
    Node *parent = NULL;
    Node *curr = root;

    for (curr = root; curr != NULL; curr = temp) {
      temp = curr->next;
      curr->next = parent;
      parent = curr;
      curr = temp;
    }

    list->root = parent;
  }
}

int get(const List *list, int index) {
  if (index >= list->_size || index < 0) {
    errno = ERANGE;
    return -1;
  }

  int i = 0;

  Node *curr;

  for (curr = list->root; curr != NULL; curr = curr->next) {
    if (i++ == index) {
      return curr->value;
    }
  }

  errno = EACCES;
  return -1;
}

int find(const List *list, const int val) { return 0; }

bool contains(const List *list, int val) {
  Node *curr;

  for (curr = list->root; curr != NULL; curr = curr->next) {
    if (curr->value == val) {
      return 1;
    }
  }

  return 0;
}

void clear(List *list) {}

void print(const List *list) {
  Node *curr = list->root;

  int str_len = 3; // 2 for "[" and "]\0" at the end

  for (curr = list->root; curr != NULL; curr = curr->next) {
    str_len += snprintf(NULL, 0, "%d", curr->value); // len of number

    if (curr->next != NULL) {
      str_len += 2; // 2 more len for ", "
    }
  }

  char str[str_len];
  str[0] = '[';

  int ctr = 1;
  char temp[12]; // 12 because of max int size: "-2147483648\0"

  for (curr = list->root; curr != NULL; curr = curr->next) {
    int len = snprintf(temp, 11 + 1, "%d", curr->value);

    for (int i = 0; i < len; ++i) {
      str[ctr + i] = temp[i];
    }

    ctr += len;

    if (curr->next != NULL) {
      str[ctr] = ',';
      str[ctr + 1] = ' ';
      ctr += 2;
    }
  }

  str[str_len - 2] = ']';
  str[str_len - 1] = '\0';

  printf("%s\n", str);
}

void print2(const List *list) {}

void info(const List *list) {}

List *construct(void) {
  List *list = (List *)malloc(sizeof(List));

  if (!list) {
    perror("Could not alloc list");
    exit(1);
  }

  // bind all functions to its struct pointer
  list->size = size;
  list->cap = cap;
  list->add = add;
  list->insert = insert;
  list->pop = pop;
  list->delete = delete;
  list->deletei = deletei;
  list->reverse = reverse;
  list->get = get;
  list->find = find;
  list->contains = contains;
  list->clear = clear;
  list->print = print;
  list->print2 = print2;
  list->info = info;

  list->root = calloc(1, sizeof(Node));
  if (!list->root) {
    perror("Could not alloc array");
    exit(1);
  }

  return list;
}

void deconstruct(List *list) {
  if (!error_handling(list, NULL))
    return;
  free(list);
}
