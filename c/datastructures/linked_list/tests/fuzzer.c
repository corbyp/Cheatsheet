#include "linked_list.h"
#include "tests.h"
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int OPERATION_COUNT = 15;
char *arr[15] = {"size",     "cap",     "add",     "insert", "pop",
                 "delete",   "deletei", "reverse", "get",    "find",
                 "contains", "clear",   "print",   "print2", "info"};

void inc_size(int *size, int *cap) {
  if (errno != 0)
    return;
  ++(*size);
  if (*size >= *cap)
    *cap *= 2;
}

void dec_size(int *size, int *cap) {
  if (errno != 0 || *size == 0)
    return;
  --(*size);
  if (*size <= *cap / 2)
    *cap /= 2;

  if (*size == 0)
    *cap = 1;
}

void random_operation(List *list, int *size, int *cap) {
  int operation = rand() % 15;
  int value = rand() % 100;
  int index = rand() % 100;

  printf("Operation: %s with value %d\n", arr[operation], value);

  switch (operation) {
  case 0:
    // assert(*size == list->size(list));
    break;
  case 1:
    // assert(*cap == list->cap(list));
    break;
  case 2:
    list->add(list, value);
    inc_size(size, cap);
    break;
  case 3:
    list->insert(list, value, index);
    inc_size(size, cap);
    break;
  case 4:
    list->pop(list);
    dec_size(size, cap);
    break;
  case 5:
    // list->print(list);
    printf("Here\n");
    list->delete(list, value);
    // list->print(list);
    dec_size(size, cap);
    break;
  case 6:
    list->deletei(list, index);
    dec_size(size, cap);
    break;
  case 7:
    list->reverse(list);
    break;
  case 8:
    list->get(list, index);
    break;
  case 9:
    list->find(list, value);
    break;
  case 10:
    list->contains(list, value);
    break;
  case 11:
    list->clear(list);
    *size = 0;
    *cap = 1;
    break;
  case 12:
    // list->print(list);
    break;
  case 13:
    list->print2(list);
    break;
  case 14:
    list->info(list);
    break;
  }
}

void run_fuzzer(void) {
  List *list = construct();
  int size = list->size(list);
  int cap = list->cap(list);

  for (int i = 0; i < 10000; ++i) {
    random_operation(list, &size, &cap);
    errno = 0;
  }

  deconstruct(list);
}
