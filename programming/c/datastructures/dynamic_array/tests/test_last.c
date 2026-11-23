#include "dynamic_array.h"
#include "tests.h"
#include "unity.h"

#include <errno.h>

void test_pop_last(void) {
  one_element_list();

  TEST_ASSERT_EQUAL(ARR[0], list->pop(list));
  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(0, list->size(list));
  TEST_ASSERT_EQUAL(1, list->cap(list));
}

void test_delete_last(void) {
  one_element_list();

  TEST_ASSERT_EQUAL(0, list->delete(list, ARR[0]));
  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(0, list->size(list));
  TEST_ASSERT_EQUAL(1, list->cap(list));
}

void test_deletei_last(void) {
  one_element_list();

  TEST_ASSERT_EQUAL(ARR[0], list->deletei(list, 0));
  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(0, list->size(list));
  TEST_ASSERT_EQUAL(1, list->cap(list));
}
