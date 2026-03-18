#pragma once

typedef struct List {
  int _size;
  struct Node *root;

  // adds element at the end of list and returns index
  int (*add)(struct List *, const int);

  // inserts element at specific index and returns index
  int (*insert)(struct List *, const int, const int);

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

  // returns 0 if element not in list, otherwise 1
  int (*contains)(const struct List *, const int);

  // Clears all elements from list
  void (*clear)(struct List *);

  // prints list in format [1, 2, 3]
  void (*print)(const struct List *);

  // prints list in format
  // nil -> 1 -> 2
  // 1 -> 2 -> nill
  void (*print2)(const struct List *);

  // gives info about list: size, capacity
  void (*info)(const struct List *);
} List;

List *construct(void);
void deconstruct(struct List *);
