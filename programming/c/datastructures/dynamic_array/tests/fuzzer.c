#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <unity/unity.h>

#include "dynamic_array.h"
#include "tests.h"

#define OPERATION_COUNT 15
#define NUMBER_OF_TEST_OPERATIONS 100
#define MAX_INDEX 100
#define MAX_VALUE 100

typedef enum operations {
  SIZE,
  CAP,
  ADD,
  INSERT,
  POP,
  DELETE,
  DELETEI,
  REVERSE,
  GET,
  FIND,
  CONTAINS,
  CLEAR,
  PRINT,
  PRINT2,
  INFO
} operations;

void inc_size(int *size, int *cap) {
  if (errno != 0)
    return;

  ++(*size);

  if (*size >= *cap)
    *cap *= EXPANSION_FACTOR;
}

void dec_size(int *size, int *cap) {
  if (errno != 0 || *size == 0)
    return;

  --(*size);

  if (*size <= *cap / EXPANSION_FACTOR)
    *cap /= EXPANSION_FACTOR;

  if (*size == 0)
    *cap = 1;
}

void clear(int *size, int *cap) {
  *size = 0;
  *cap = 1;
}

void random_operation(List *list, int *size, int *cap) {
  int operation = rand() % OPERATION_COUNT;
  int value = rand() % MAX_VALUE;
  int index = rand() % MAX_INDEX;

  switch (operation) {
  case SIZE:
    TEST_ASSERT_EQUAL_size_t(*size, list->size(list));
    break;
  case CAP:
    TEST_ASSERT_EQUAL_size_t(*cap, list->cap(list));
    break;
  case ADD:
    list->add(list, value);
    inc_size(size, cap);
    break;
  case INSERT:
    list->insert(list, value, index);
    inc_size(size, cap);
    break;
  case POP:
    list->pop(list);
    dec_size(size, cap);
    break;
  case DELETE:
    list->delete(list, value);
    dec_size(size, cap);
    break;
  case DELETEI:
    list->deletei(list, index);
    dec_size(size, cap);
    break;
  case REVERSE:
    list->reverse(list);
    break;
  case GET:
    list->get(list, index);
    break;
  case FIND:
    list->find(list, value);
    break;
  case CONTAINS:
    list->contains(list, value);
    break;
  case CLEAR:
    list->clear(list);
    clear(size, cap);
    break;
  case PRINT:
    list->print(list);
    break;
  case PRINT2:
    list->print2(list);
    break;
  case INFO:
    list->info(list);
    break;
  default:
    fprintf(stderr, "Operation %d not found!\n", operation);
    break;
  }
}

void run_fuzzer(void) {
  List *list = construct();
  int size = list->size(list);
  int cap = list->cap(list);

  for (int i = 0; i < NUMBER_OF_TEST_OPERATIONS; ++i) {
    random_operation(list, &size, &cap);
    errno = 0;
  }

  deconstruct(list);
}
