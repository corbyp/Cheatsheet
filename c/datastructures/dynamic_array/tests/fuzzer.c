#include "dynamic_array.h"
#include "tests.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int OPERATION_COUNT = 15;
char *arr[15] = {"size",     "cap",     "add",     "insert", "pop",
                 "delete",   "deletei", "reverse", "get",    "find",
                 "contains", "clear",   "print",   "print2", "info"};

void inc_size(int *size, int *cap) {
  if (errno != 0)
    return;
  ++(*size);
  if (*size == *cap)
    *cap *= 2;
}

void dec_size(int *size, int *cap) {
  if (errno != 0 || *size == 0)
    return;
  --(*size);
  if (*size == *cap / 2)
    *cap /= 2;
}

void random_operation(List *list, int *size, int *cap) {
  int operation = rand() % 15;
  int value = rand() % 100;
  int index = rand() % 100;

  switch (operation) {
  case 0:
    printf("Trying case %s\n", arr[operation]);
    printf("%d == %d\n", *size, list->size(list));
    assert(*size == list->size(list));
    break;
  case 1:
    printf("Trying case %s\n", arr[operation]);
    printf("%d == %d\n", *cap, list->cap(list));
    assert(*cap == list->cap(list));
    break;
  case 2:
    printf("Trying case %s\n", arr[operation]);
    list->add(list, value);
      inc_size(size, cap);
    break;
  case 3:
    printf("Trying case %s\n", arr[operation]);
    list->insert(list, value, index);
    inc_size(size, cap);
    break;
  case 4:
    printf("Trying case %s\n", arr[operation]);
    list->pop(list);
    dec_size(size, cap);
    break;
  case 5:
    printf("Trying case %s\n", arr[operation]);
    list->delete(list, value);
    dec_size(size, cap);
    break;
  case 6:
    printf("Trying case %s\n", arr[operation]);
    list->deletei(list, index);
    dec_size(size, cap);
    break;
  case 7:
    printf("Trying case %s\n", arr[operation]);
    list->reverse(list);
    break;
  case 8:
    printf("Trying case %s\n", arr[operation]);
    list->get(list, index);
    break;
  case 9:
    printf("Trying case %s\n", arr[operation]);
    list->find(list, value);
    break;
  case 10:
    printf("Trying case %s\n", arr[operation]);
    list->contains(list, value);
    break;
  case 11:
    printf("Trying case %s\n", arr[operation]);
    list->clear(list);
    *size = 0;
    *cap = 1;
    break;
  case 12:
    printf("Trying case %s\n", arr[operation]);
    list->print(list);
    break;
  case 13:
    printf("Trying case %s\n", arr[operation]);
    list->print2(list);
    break;
  case 14:
    printf("Trying case %s\n", arr[operation]);
    list->info(list);
    break;
  default:
    printf("Case not covered\n");
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
