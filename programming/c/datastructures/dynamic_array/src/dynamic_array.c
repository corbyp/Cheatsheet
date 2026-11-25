#include "dynamic_array.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// private helper functions

size_t _size;
size_t _cap;
int *_ptr;

void adjust(const size_t new_size) {
  if (new_size >= _cap) {
    _cap *= 2;
    _ptr = reallocarray(_ptr, _cap, sizeof(int));

    if (!_ptr) {
      perror("Could not realloc array on add");
      exit(1);
    }

    memset(_ptr + _size, 0, (_cap - _size) * sizeof(int));
  } else if (new_size <= _cap / 2) {
    if (new_size == 0)
      _cap = 1;
    else
      _cap /= 2;

    _ptr = reallocarray(_ptr, _cap, sizeof(int));

    if (!_ptr) {
      perror("Could not realloc array on delete");
      exit(1);
    }
  }
  _size = new_size;
}

int check_index(size_t index) {
  if (index < 0 || index >= _size) {
    errno = -ERANGE;
    return -1;
  }

  return 0;
}

size_t calculate_index(size_t index) {
  if (index < 0) {
    return index + _size;
  }

  return index;
}

int check_list(const List *list) {
  if (!list || !_ptr) {
    errno = -EINVAL;
    return -1;
  }

  return 0;
}

// public list functions

// read only methods
size_t size(const List *list) {
  if (check_list(list) < 0) {
    return -1;
  }

  return _size;
}

size_t cap(const List *list) {
  if (check_list(list) < 0) {
    return -1;
  }

  return _cap;
}

int get(const List *list, int index) {
  if (check_list(list) < 0 || check_index(index)) {
    return -1;
  }

  return _ptr[index];
}

int find(const List *list, int value) {
  if (check_list(list) < 0) {
    return -1;
  }

  for (size_t index = 0; index < _size; ++index) {
    if (_ptr[index] == value)
      return index;
  }

  errno = -ENOENT;
  return -1;
}

int contains(const List *list, const int value) {
  if (check_list(list) < 0) {
    return -1;
  }

  return find(list, value) >= 0;
}

int add(List *list, const int value) {
  if (check_list(list) < 0) {
    return -1;
  }

  adjust(_size + 1);
  _ptr[_size - 1] = value;

  return _size - 1;
}

int insert(List *list, const int value, size_t index) {
  index = calculate_index(index);

  if (check_list(list) < 0 || index < 0 || index > _size) {
    return -1;
  }

  adjust(_size + 1);

  size_t cur = _size;
  while (cur > index) {
    _ptr[cur] = _ptr[cur - 1];
    --cur;
  }

  _ptr[index] = value;

  return index;
}

int pop(List *list) {
  if (check_list(list) < 0) {
    return -1;
  }

  if (_size == 0) {
    errno = -ERANGE;
    return -1;
  }

  int value = _ptr[_size - 1];
  adjust(_size - 1);

  return value;
}

int delete(List *list, const int value) {
  if (check_list(list) < 0)
    return -1;

  size_t index = find(list, value);

  if (index < 0)
    return -1;

  int temp = index;

  while (index < _size - 1) {
    _ptr[index] = _ptr[index + 1];
    ++index;
  }

  adjust(_size - 1);

  return temp;
}

int deletei(List *list, size_t index) {
  if (check_list(list) < 0 || check_index(index)) {
    return -1;
  }

  int value = list->get(list, index);

  size_t i = index;
  while (i < _size - 1) {
    _ptr[i] = _ptr[i + 1];
    ++i;
  }

  adjust(_size - 1);

  return value;
}

int reverse(List *list) {
  if (check_list(list) < 0) {
    return -1;
  }

  if (_size < 2)
    return 0;

  int temp;
  for (size_t i = 0; i < _size / 2; ++i) {
    temp = _ptr[i];
    _ptr[i] = _ptr[_size - i - 1];
    _ptr[_size - i - 1] = temp;
  }

  return 0;
}

int clear(List *list) {
  if (check_list(list) < 0) {
    return -1;
  }

  adjust(0);

  return 0;
}

int print_to(FILE *stream, const List *list) {
  if (check_list(list) < 0) 
    return -1;

  if (_size == 0) {
    fprintf(stream, "[]\n");
    return 0;
  }

  fprintf(stream, "[");
  for (size_t i = 0; i < _size - 1; ++i)
    fprintf(stream, "%d, ", _ptr[i]);

  fprintf(stream, "%d]\n", _ptr[_size - 1]);

  return 0;
}

int print(const List *list) {
  if (check_list(list) < 0) {
    return -1;
  }

  return print_to(stdout, list);
}

int print2_to(FILE *stream, const List *list) {
  if (check_list(list) < 0) {
    return -1;
  }

  fprintf(stream, "[");
  for (int i = 0; i < _cap - 1; ++i)
    fprintf(stream, "%d, ", _ptr[i]);

  fprintf(stream, "%d]\n", _ptr[_cap - 1]);

  return 0;
}

int print2(const List *list) {
  if (check_list(list) < 0) {
    return -1;
  }

  print2_to(stdout, list);

  return 0;
}

int info(const List *list) {
  if (check_list(list) < 0) {
    return -1;
  }

  printf("Size: %d, Cap: %d\n", _size, _cap);
  return 0;
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

  _ptr = calloc(1, sizeof(int));
  if (!_ptr) {
    perror("Could not alloc array");
    exit(1);
  }

  _cap = 1;

  return list;
}

int deconstruct(List *list) {
  if (check_list(list) < 0) {
    return -1;
  }

  free(_ptr);
  free(list);

  return 0;
}
