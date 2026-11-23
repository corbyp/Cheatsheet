#include "dynamic_array.h"
#include "tests.h"
#include "unity.h"

#include <errno.h>

void test_add_resize(void) {
  fill_list_resize();

  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP_RESIZE, list->cap(list));

  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE, list->add(list, 5));

  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE + 1, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP_RESIZE * 2, list->cap(list));
}

void test_insert_resize(void) {
  fill_list_resize();

  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP_RESIZE, list->cap(list));

  list->insert(list, 5, ARR_SIZE_RESIZE / 2);

  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE + 1, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP_RESIZE * 2, list->cap(list));
}

void test_pop_resize(void) {
  fill_list_resize();

  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP_RESIZE, list->cap(list));

  TEST_ASSERT_EQUAL(ARR_RESIZE[ARR_SIZE_RESIZE - 1], list->pop(list));

  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE - 1, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP_RESIZE / 2, list->cap(list));
}

void test_delete_resize(void) {
  fill_list_resize();

  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP_RESIZE, list->cap(list));

  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE / 2, list->delete(list, ARR[ARR_SIZE_RESIZE / 2]));

  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE - 1, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP_RESIZE / 2, list->cap(list));
}

void test_deletei_resize(void) {
  fill_list_resize();

  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP_RESIZE, list->cap(list));

  TEST_ASSERT_EQUAL(ARR[ARR_SIZE_RESIZE / 2], list->deletei(list, ARR_SIZE_RESIZE / 2));

  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(ARR_SIZE_RESIZE - 1, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP_RESIZE / 2, list->cap(list));
}
