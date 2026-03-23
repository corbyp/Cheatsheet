#include "dynamic_array.h"
#include "tests.h"
#include "unity.h"

#include <errno.h>

void test_insert_tail(void) {
  fill_list();

  list->insert(list, 5, list->size(list));
  TEST_ASSERT_EQUAL(ERANGE, errno);

  // ERANGE error because cant insert into last position
  TEST_ASSERT_EQUAL(ERANGE, errno);
  // Should remain unchanged
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
  // Should remain unchanged
  TEST_ASSERT_EQUAL(ARR_SIZE, list->size(list));
}

void test_pop_tail(void) {
  fill_list();

  TEST_ASSERT_EQUAL(ARR[ARR_SIZE - 1], list->pop(list));
  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
  TEST_ASSERT_EQUAL(ARR_SIZE - 1, list->size(list));
}

void test_delete_tail(void) {
  fill_list();

  TEST_ASSERT_EQUAL(ARR_SIZE - 1, list->delete(list, ARR[ARR_SIZE - 1]));
  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
  TEST_ASSERT_EQUAL(ARR_SIZE - 1, list->size(list));
}

void test_deletei_tail(void){
  fill_list();

  TEST_ASSERT_EQUAL(ARR[ARR_SIZE - 1], list->deletei(list, ARR_SIZE - 1));
  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
  TEST_ASSERT_EQUAL(ARR_SIZE - 1, list->size(list));
}

void test_get_tail(void){
  fill_list();

  TEST_ASSERT_EQUAL(ARR[ARR_SIZE - 1], list->get(list, ARR_SIZE - 1));
  TEST_ASSERT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
  TEST_ASSERT_EQUAL(ARR_SIZE, list->size(list));
}
