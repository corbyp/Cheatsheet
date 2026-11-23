#include "dynamic_array.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// private helper functions

void adjust(List *list, const int new_size) {
  if (new_size >= list->_cap) {
    list->_cap *= 2;
    list->_ptr = reallocarray(list->_ptr, list->_cap, sizeof(int));
    memset(list->_ptr + list->_size, 0,
           (list->_cap - list->_size) * sizeof(int));

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

bool error_handling(const List *list, int *index) {
  if (!list || !list->_ptr) {
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

// public list functions

int size(const List *list) {
  if (!error_handling(list, NULL)) {
    return -1;
  }

  return list->_size;
}

int cap(const List *list) {
  if (!error_handling(list, NULL)) {
    return -1;
  }

  return list->_cap;
}

int add(List *list, const int value) {
  if (!error_handling(list, NULL))
    return -1;

  adjust(list, list->_size + 1);

  list->_ptr[list->_size - 1] = value;

  return list->_size - 1;
}

void insert(List *list, const int value, int index) {
  if (!error_handling(list, &index))
    return;

  adjust(list, list->_size + 1);
  int cur = list->_size;

  while (cur > index) {
    list->_ptr[cur] = list->_ptr[cur - 1];
    --cur;
  }

  list->_ptr[index] = value;
}

int pop(List *list) {
  if (!error_handling(list, NULL))
    return -1;

  if (!list->_size) {
    errno = ERANGE;
    return -1;
  }

  int value = list->_ptr[list->_size - 1];
  adjust(list, list->_size - 1);

  return value;
}

int delete(List *list, const int value) {
  if (!error_handling(list, NULL))
    return -1;

  int index = 0;
  for (index = 0; index < list->_size && list->_ptr[index] != value; ++index)
    ;

  if (index == list->_size) {
    errno = ENOENT;
    return -1;
  }

  int temp = index;

  while (index < list->_size - 1) {
    list->_ptr[index] = list->_ptr[index + 1];
    ++index;
  }

  adjust(list, list->_size - 1);

  return temp;
}

int deletei(List *list, int index) {
  if (!error_handling(list, &index))
    return -1;

  int value = list->get(list, index);

  int i = index;
  while (i < list->_size - 1) {
    list->_ptr[i] = list->_ptr[i + 1];
    ++i;
  }

  adjust(list, list->_size - 1);

  return value;
}

void reverse(List *list) {
  if (!error_handling(list, NULL))
    return;

  if (list->_size < 2)
    return;

  int temp;
  for (int i = 0; i < list->_size / 2; ++i) {
    temp = list->_ptr[i];
    list->_ptr[i] = list->_ptr[list->_size - i - 1];
    list->_ptr[list->_size - i - 1] = temp;
  }
}

int get(const List *list, int index) {
  if (!error_handling(list, &index))
    return -1;

  return list->_ptr[index];
}

int find(const List *list, int value) {
  if (!error_handling(list, NULL))
    return -1;

  for (int i = 0; i < list->_size; ++i) {
    if (list->_ptr[i] == value)
      return i;
  }

  return -1;
}

bool contains(const List *list, const int value) {
  if (!error_handling(list, NULL))
    return 0;

  for (int i = 0; i < list->_size; ++i)
    if (list->_ptr[i] == value)
      return 1;

  return 0;
}

void clear(List *list) {
  if (!error_handling(list, NULL))
    return;

  adjust(list, 0);
}

void print_to(FILE *stream, const List *list) {
  if (!error_handling(list, NULL))
    return;

  if (!list->_size) {
    fprintf(stream, "[]\n");
    return;
  }

  fprintf(stream, "[");
  for (int i = 0; i < list->_size - 1; ++i)
    fprintf(stream, "%d, ", list->_ptr[i]);

  fprintf(stream, "%d]\n", list->_ptr[list->_size - 1]);
}

void print(const List *list) { print_to(stdout, list); }

void print2_to(FILE *stream, const List *list) {
  if (!error_handling(list, NULL))
    return;

  fprintf(stream, "[");
  for (int i = 0; i < list->_cap - 1; ++i)
    fprintf(stream, "%d, ", list->_ptr[i]);

  fprintf(stream, "%d]\n", list->_ptr[list->_cap - 1]);
}

void print2(const List *list) { print2_to(stdout, list); }

void info(const List *list) {
  if (!error_handling(list, NULL))
    return;

  printf("Size: %d, Cap: %d\n", list->_size, list->_cap);
}

List *construct(void) {
  List *list = calloc(1, sizeof(List));
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

  list->_ptr = calloc(1, sizeof(int));
  if (!list->_ptr) {
    perror("Could not alloc array");
    exit(1);
  }

  list->_cap = 1;

  return list;
}

void deconstruct(List *list) {
  if (!error_handling(list, NULL))
    return;
  free(list->_ptr);
  free(list);
}
