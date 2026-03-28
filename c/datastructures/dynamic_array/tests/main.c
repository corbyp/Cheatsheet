#include "dynamic_array.h"
#include "tests.h"
#include "unity.h"

#include <errno.h>
#include <stdlib.h>

List *list;
const int ARR_SIZE = 6;
const int ARR_CAP = 8;
const int ARR[6] = {2, 9, 13, 7, 4, 0};

const int ARR_SIZE_RESIZE = 3;
const int ARR_CAP_RESIZE = 4;
const int ARR_RESIZE[3] = {2, 9, 13};

void setUp(void) {
  list = construct();
  errno = 0;
}

void tearDown(void) { deconstruct(list); }

void fill_list(void) {
  for (int i = 0; i < ARR_SIZE; ++i) {
    list->add(list, ARR[i]);
  }
}

void fill_list_resize(void) {
  for (int i = 0; i < ARR_SIZE_RESIZE; ++i) {
    list->add(list, ARR_RESIZE[i]);
  }
}

void set_list_null(void) {
  free(list->_ptr);
  list->_ptr = NULL;
}

void one_element_list(void) { list->add(list, ARR[0]); }

// Tests for when list already has elements.
// Size should not change
void test_full(void) {
  printf("---Testing functions with list that contains values---\n");
  RUN_TEST(test_size_full);
  RUN_TEST(test_cap_full);
  RUN_TEST(test_add_full);
  RUN_TEST(test_insert_full);
  RUN_TEST(test_pop_full);
  RUN_TEST(test_delete_full);
  RUN_TEST(test_deletei_full);
  RUN_TEST(test_reverse_full);
  RUN_TEST(test_get_full);
  RUN_TEST(test_find_full);
  RUN_TEST(test_contains_full);
  RUN_TEST(test_clear_full);
  printf("\n");
}

// Tests for when list already has elements and work is being done on the last
// element. Size should not change
void test_tail(void) {
  printf("---Testing functions when explicitly reading/writing the last "
         "element---\n");
  RUN_TEST(test_insert_tail);
  RUN_TEST(test_pop_tail);
  RUN_TEST(test_delete_tail);
  RUN_TEST(test_deletei_tail);
  RUN_TEST(test_get_tail);
  printf("\n");
}

// Tests writing operations where list has to resize
void test_resize(void) {
  printf("---Testing functions when writing leads to a resize---\n");
  RUN_TEST(test_add_resize);
  RUN_TEST(test_insert_resize);
  RUN_TEST(test_pop_resize);
  RUN_TEST(test_delete_resize);
  RUN_TEST(test_deletei_resize);
  printf("\n");
}

// Tests for when the _ptr is NULL
void test_null(void) {
  printf("---Testing functions when _ptr is null---\n");
  RUN_TEST(test_size_null);
  RUN_TEST(test_cap_null);
  RUN_TEST(test_add_null);
  RUN_TEST(test_insert_null);
  RUN_TEST(test_pop_null);
  RUN_TEST(test_delete_null);
  RUN_TEST(test_deletei_null);
  RUN_TEST(test_reverse_null);
  RUN_TEST(test_get_null);
  RUN_TEST(test_find_null);
  RUN_TEST(test_contains_null);
  RUN_TEST(test_clear_null);
  printf("\n");
}

// Tests for when the last remaining element gets deleted
void test_last(void) {
  printf("---Testing read/write when only one element in list---\n");
  RUN_TEST(test_pop_last);
  RUN_TEST(test_delete_last);
  RUN_TEST(test_deletei_last);
  printf("\n");
}

// Tests for when list has no elements.
void test_empty(void) {
  printf("---Testing functions empty list---\n");
  RUN_TEST(test_size_empty);
  RUN_TEST(test_cap_empty);
  RUN_TEST(test_add_empty);
  RUN_TEST(test_insert_empty);
  RUN_TEST(test_pop_empty);
  RUN_TEST(test_delete_empty);
  RUN_TEST(test_deletei_empty);
  RUN_TEST(test_reverse_empty);
  RUN_TEST(test_get_empty);
  RUN_TEST(test_find_empty);
  RUN_TEST(test_contains_empty);
  RUN_TEST(test_clear_empty);
  printf("\n");
}

int main(void) {
  UNITY_BEGIN();

  test_full();
  test_tail();
  test_resize();
  test_null();
  test_last();
  test_empty();

  return 0;
  // return UNITY_END();
}
