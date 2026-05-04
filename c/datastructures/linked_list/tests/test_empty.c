#include "tests.h"
#include "unity.h"

#include <errno.h>

// helper function
void test_size_and_cap(void) {
  TEST_ASSERT_EQUAL(0, list->size(list));
  TEST_ASSERT_EQUAL(1, list->cap(list));
}

void test_size_empty(void) {
  TEST_ASSERT_EQUAL(0, list->size(list));
  TEST_ASSERT_EQUAL(0, errno);
}

void test_cap_empty(void) {
  TEST_ASSERT_EQUAL(1, list->cap(list));
  TEST_ASSERT_EQUAL(0, errno);
}

void test_add_empty(void) {
  for (int i = 0; i < 32768; ++i) {
    TEST_ASSERT_EQUAL(i, list->add(list, i));
    TEST_ASSERT_EQUAL(i + 1, list->size(list));
    TEST_ASSERT_EQUAL(0, errno);
  }

  for (int i = 0; i < 32768; ++i) {
    TEST_ASSERT_EQUAL(i, list->get(list, i));
  }

  TEST_ASSERT_EQUAL(32768, list->size(list));
  TEST_ASSERT_EQUAL(32768 * 2, list->cap(list));
}

void test_insert_empty(void) {
  int val_to_insert = 420;
  int index_to_insert = 0;

  list->insert(list, val_to_insert, index_to_insert);
  TEST_ASSERT_EQUAL(ERANGE, errno);

  test_size_and_cap();
}

void test_pop_empty(void) {
  TEST_ASSERT_EQUAL(-1, list->pop(list));
  TEST_ASSERT_EQUAL(ERANGE, errno);

  test_size_and_cap();
}

void test_delete_empty(void) {
  int index_to_delete = 0;

  TEST_ASSERT_EQUAL(-1, list->delete(list, ARR[index_to_delete]));
  TEST_ASSERT_EQUAL(0, errno);

  test_size_and_cap();
}

void test_deletei_empty(void) {
  int index_to_delete = 1;

  TEST_ASSERT_EQUAL(-1, list->deletei(list, index_to_delete));
  TEST_ASSERT_EQUAL(ERANGE, errno);

  test_size_and_cap();
}

void test_reverse_empty(void) {
  list->reverse(list);
  TEST_ASSERT_EQUAL(0, errno);

  // Should remain the same
  test_size_and_cap();
}

void test_get_empty(void) {
  TEST_ASSERT_EQUAL(-1, list->get(list, 0));
  TEST_ASSERT_EQUAL(ERANGE, errno);

  test_size_and_cap();
}

void test_find_empty(void) {
  TEST_ASSERT_EQUAL(-1, list->find(list, ARR[0]));
  TEST_ASSERT_EQUAL(0, errno);

  test_size_and_cap();
}

void test_contains_empty(void) {
  TEST_ASSERT_EQUAL(0, list->contains(list, ARR[0]));
  TEST_ASSERT_EQUAL(0, errno);

  test_size_and_cap();
}

void test_clear_empty(void) {
  list->clear(list);
  TEST_ASSERT_EQUAL(0, errno);

  test_size_and_cap();
}
