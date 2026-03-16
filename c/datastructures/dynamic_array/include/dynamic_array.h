#pragma once

typedef struct List {
  int size;
  int cap;
  int *ptr;
  void (*add)(struct List *, int);
  void (*delete)(struct List *, int);
  void (*print)(struct List *);
} List;

List *init(void);
