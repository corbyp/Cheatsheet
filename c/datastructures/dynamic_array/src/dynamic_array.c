#include "dynamic_array.h"

#include <stdio.h>
#include <stdlib.h>

// private helper functions

void adjust(List *l, const int new_size) {
  if (new_size >= l->_cap) {
    l->_cap *= 2;
    l->_ptr = reallocarray(l->_ptr, l->_cap, sizeof(int));
    if (!l->_ptr) {
      perror("Could not realloc array on add");
      exit(1);
    }
  } else if (new_size <= l->_cap / 2) {
    l->_cap /= 2;
    if (new_size == 0)
      l->_cap = 1;
    l->_ptr = reallocarray(l->_ptr, l->_cap, sizeof(int));
    if (!l->_ptr) {
      perror("Could not realloc array on delete");
      exit(1);
    }
  }
  l->_size = new_size;
}

// public list functions

int add(List *l, const int val) {
  adjust(l, l->_size + 1);

  l->_ptr[l->_size - 1] = val;
  // Could instead call insert with l->_size as index, but
  // that would mean one unnecessary if check in while and
  // thus this implementation is more performant

  return l->_size - 1;
}

int insert(List *l, const int val, const int idx) {
  if (idx < 0 || idx > l->_size) {
    printf("Index %d out of bounds!\n", idx);
    exit(1);
  }
  adjust(l, l->_size + 1);
  int cur = l->_size;

  while (cur > idx) {
    l->_ptr[cur] = l->_ptr[cur - 1];
    --cur;
  }

  l->_ptr[idx] = val;

  return idx;
}

int pop(List *l) {
  int val = l->_ptr[l->_size - 1];
  adjust(l, l->_size - 1);

  return val;
}

int delete(List *l, const int val) {
  int idx;
  for (idx = 0; idx < l->_size && l->_ptr[idx] != val; ++idx)
    ;

  int temp = idx;

  if (idx == l->_size) {
    printf("Could not delete element %d, it does not exist!\n", val);
    exit(1);
  }

  while (idx < l->_size - 1) {
    l->_ptr[idx] = l->_ptr[idx + 1];
    ++idx;
  }

  adjust(l, l->_size - 1);

  return temp;
}

int deletei(List *l, const int idx) {
  int val = l->get(l, idx);

  int i = idx;
  while (i < l->_size - 1) {
    l->_ptr[i] = l->_ptr[i + 1];
    ++i;
  }

  adjust(l, l->_size - 1);

  return val;
}

void reverse(List *l) {
  int temp;
  for (int i = 0; i < l->_size / 2; ++i) {
    temp = l->_ptr[i];
    l->_ptr[i] = l->_ptr[l->_size - i - 1];
    l->_ptr[l->_size - i - 1] = temp;
  }
}

int get(const List *l, const int idx) {
  if (idx < 0 || idx >= l->_size) {
    printf("Index %d out of bounds!\n", idx);
    exit(1);
  }
  return l->_ptr[idx];
}

bool contains(const List *l, const int val) {
  for (int i = 0; i < l->_size; ++i) {
    if (l->_ptr[i] == val)
      return 1;
  }
  return 0;
}

void clear(List *l) { adjust(l, 0); }

void print(const List *l) {
  if (l->_size == 0) {
    printf("[]\n");
    return;
  }
  printf("[");
  for (int i = 0; i < l->_size - 1; ++i) {
    printf("%d, ", l->_ptr[i]);
  }
  printf("%d]\n", l->_ptr[l->_size - 1]);
}

void print2(const List *l) {
  printf("[");
  for (int i = 0; i < l->_cap - 1; ++i) {
    printf("%d, ", l->_ptr[i]);
  }
  printf("%d]\n", l->_ptr[l->_cap - 1]);
}

void info(const List *l) {
  printf("Capacity: %d, Size: %d\n", l->_cap, l->_size);
}

List *construct(void) {
  List *l = calloc(1, sizeof(List));
  if (!l) {
    perror("Could not alloc list");
    exit(1);
  }

  l->add = add;
  l->insert = insert;
  l->pop = pop;
  l->delete = delete;
  l->deletei = deletei;
  l->reverse = reverse;
  l->get = get;
  l->contains = contains;
  l->clear = clear;
  l->print = print;
  l->print2 = print2;
  l->info = info;

  l->_ptr = calloc(1, sizeof(int));
  if (!l->_ptr) {
    perror("Could not alloc array");
    exit(1);
  }

  l->_cap = 1;

  return l;
}

void deconstruct(List *l) {
  free(l->_ptr);
  free(l);
}
