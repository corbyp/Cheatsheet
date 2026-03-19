#pragma once

#include <stdbool.h>

typedef struct List {
  int _size;
  // How many elements the list can hold until it needs to be
  // expanded. On expansion: 2 * _cap, thus making _cap a power of 2.
  int _cap;
  int *_ptr;

  // adds element at the end of list and returns index
  int (*add)(struct List *, const int);

  // inserts element at specific index and returns index
  void (*insert)(struct List *, const int, int);

  // deletes and returns last element of list
  int (*pop)(struct List *);

  // deletes first instance of element and returns index
  int (*delete)(struct List *, const int);

  // deletes element at index and returns value
  int (*deletei)(struct List *, const int);

  // reverses list
  void (*reverse)(struct List *);

  // gets element at specific index
  int (*get)(const struct List *, const int);

  // Finds element in list and returns index.
  // If not found returns -1.
  int (*find)(const struct List *, const int);

  // returns 0 if element not in list, otherwise 1
  bool (*contains)(const struct List *, const int);

  // clears all elements of list
  void (*clear)(struct List *);

  // prints list in format [1, 2, 3]
  void (*print)(const struct List *);

  // prints list in format [1, 2, 3, 0, 0]
  // which also prints all values of current capacity
  void (*print2)(const struct List *);

  // gives info about list: size, capacity
  void (*info)(const struct List *);
} List;

List *construct(void);
void deconstruct(struct List *);
