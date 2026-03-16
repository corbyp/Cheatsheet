#include "dynamic_array.h"

#include <stdio.h>
#include <stdlib.h>

void add(List *l, int val) {
  if (l->size + 1 >= l->cap) {
    int *ptr = reallocarray(l->ptr, l->cap * 2, sizeof(int));
    if (!ptr) {
      perror("Could not realloc array!\n");
      exit(1);
    }
    l->ptr = ptr;
    l->cap *= 2;
  }

  l->ptr[l->size++] = val;
}

void delete(List *l, int val) {
  int index;
  for (index = 0; (l->ptr[index] == val || index < l->size); index++) {}

  printf("%d\n", index);
}

void print(List *l) {
  printf("[");
  for (int i = 0; i < l->size - 1; ++i) {
    printf("%d, ", l->ptr[i]);
  }
  printf("%d], c: %d, s: %d\n", l->ptr[l->size - 1], l->cap, l->size);
}

List *list(void) {
  List *l = calloc(1, sizeof(List));
  if (!l) {
    perror("Could not alloc list!\n");
    exit(1);
  }

  l->add = add;
  l->delete = delete;
  l->print = print;

  int *ptr = calloc(1, sizeof(int));
  if (!ptr) {
    perror("Could not malloc array!\n");
    exit(1);
  }

  l->ptr = ptr;
  l->cap = 1;

  return l;
}
