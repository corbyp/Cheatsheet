#include "dynamic_array.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// private helper functions

void adjust(List *list, const int new_size) {
  if (new_size >= list->_cap) {
    list->_cap *= 2;
    list->_ptr = reallocarray(list->_ptr, list->_cap, sizeof(int));
    if (!list->_ptr) {
      perror("Could not realloc array on add");
      exit(1);
    }
  } else if (new_size <= list->_cap / 2) {
    list->_cap /= 2;
    if (new_size == 0)
      list->_cap = 1;
    list->_ptr = reallocarray(list->_ptr, list->_cap, sizeof(int));
    if (!list->_ptr) {
      perror("Could not realloc array on delete");
      exit(1);
    }
  }
  list->_size = new_size;
}

bool check_index(const List* list, int idx) {
  if (idx < 0 || idx >= list->_size) {
    errno = ERANGE;
    return 0;
  }

  return 1;
}

// public list functions

int add(List *list, const int val) {
  adjust(list, list->_size + 1);

  list->_ptr[list->_size - 1] = val;
  // Could instead call insert with l->_size as index, but
  // that would mean one unnecessary if check in while and
  // thus this implementation is more performant

  return list->_size - 1;
}

void insert(List *list, const int val, int idx) {
  if (idx < 0)
    idx = list->_size - idx;

  if (!check_index(list, idx))
    return;

  adjust(list, list->_size + 1);
  int cur = list->_size;

  while (cur > idx) {
    list->_ptr[cur] = list->_ptr[cur - 1];
    --cur;
  }

  list->_ptr[idx] = val;
}

int pop(List *list) {
  if (!list->_size) {
    errno = ERANGE;
    return -1;
  }

  int val = list->_ptr[list->_size - 1];
  adjust(list, list->_size - 1);

  return val;
}

int delete(List *list, const int val) {
  int idx = 0;
  for (idx = 0; idx < list->_size && list->_ptr[idx] != val; ++idx)
    ;

  if (idx == list->_size || !list->_size) {
    errno = ERANGE;
    return -1;
  }
  
  int temp = idx;

  while (idx < list->_size - 1) {
    list->_ptr[idx] = list->_ptr[idx + 1];
    ++idx;
  }

  adjust(list, list->_size - 1);

  return temp;
}

int deletei(List *list, int idx) {
  if (idx < 0)
    idx = list->_size - idx;

  if (!check_index(list, idx))
    return -1;

  int val = list->get(list, idx);

  int i = idx;
  while (i < list->_size - 1) {
    list->_ptr[i] = list->_ptr[i + 1];
    ++i;
  }

  adjust(list, list->_size - 1);

  return val;
}

void reverse(List *list) {
  if (list->_size < 2)
    return;

  int temp;
  for (int i = 0; i < list->_size / 2; ++i) {
    temp = list->_ptr[i];
    list->_ptr[i] = list->_ptr[list->_size - i - 1];
    list->_ptr[list->_size - i - 1] = temp;
  }
}

int get(const List *list, int idx) {
  if (idx < 0)
    idx = list->_size - idx;

  if (!check_index(list, idx))
    return -1;

  return list->_ptr[idx];
}

int find(const List *list, int val) {
  for (int i = 0; i < list->_size || list->_ptr[i] != val; ++i) {
    if (list->_ptr[i] == val)
      return i;
  }

  return -1;
}

bool contains(const List *list, const int val) {
  for (int i = 0; i < list->_size; ++i) {
    if (list->_ptr[i] == val)
      return 1;
  }
  return 0;
}

void clear(List *list) { adjust(list, 0); }

void print(const List *list) {
  if (list->_size == 0) {
    printf("[]\n");
    return;
  }
  printf("[");
  for (int i = 0; i < list->_size - 1; ++i) {
    printf("%d, ", list->_ptr[i]);
  }
  printf("%d]\n", list->_ptr[list->_size - 1]);
}

void print2(const List *list) {
  printf("[");
  for (int i = 0; i < list->_cap - 1; ++i) {
    printf("%d, ", list->_ptr[i]);
  }
  printf("%d]\n", list->_ptr[list->_cap - 1]);
}

void info(const List *list) {
  printf("Capacity: %d, Size: %d\n", list->_cap, list->_size);
}

List *construct(void) {
  List *list = calloc(1, sizeof(List));
  if (!list) {
    perror("Could not alloc list");
    exit(1);
  }

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

  list->_ptr = calloc(1, sizeof(int));
  if (!list->_ptr) {
    perror("Could not alloc array");
    exit(1);
  }

  list->_cap = 1;

  return list;
}

void deconstruct(List *list) {
  free(list->_ptr);
  free(list);
}
