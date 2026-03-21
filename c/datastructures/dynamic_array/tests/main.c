#include "dynamic_array.h"
#include "unity.h"
#include "unity_internals.h"

#include <errno.h>
#include <stdlib.h>

List *list;

void setUp(void) {
  list = construct();
  list->add(list, 2);
  list->add(list, 9);
  list->add(list, 13);
  errno = 0;
}

void tearDown(void) { deconstruct(list); }

void test_add_null(void) {
  free(list->_ptr);
  list->_ptr = NULL;

  TEST_ASSERT_EQUAL(-1, list->add(list, 0));
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_add(void) {
  for (int i = 3; i < 32768; ++i) {
    TEST_ASSERT_EQUAL(i, list->add(list, i));
    TEST_ASSERT_EQUAL(i + 1, list->_size);
    TEST_ASSERT_EQUAL(0, errno);
  }

  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));
  TEST_ASSERT_EQUAL(13, list->get(list, 2));
  for (int i = 3; i < 32768; ++i) {
    TEST_ASSERT_EQUAL(i, list->get(list, i));
  }

  TEST_ASSERT_EQUAL(32768, list->_size);
  TEST_ASSERT_EQUAL(32768 * 2, list->_cap);
}

void test_insert_null(void) {
  free(list->_ptr);
  list->_ptr = NULL;

  list->insert(list, 0, 0);
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_insert_last(void) {
  list->insert(list, 69, 3);
  TEST_ASSERT_EQUAL(ERANGE, errno);
}

void test_insert(void) {
  list->insert(list, 420, 2);
  TEST_ASSERT_EQUAL(0, errno);
  
  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));
  TEST_ASSERT_EQUAL(420, list->get(list, 2));
  TEST_ASSERT_EQUAL(13, list->get(list, 3));

  TEST_ASSERT_EQUAL(4, list->_size);
  TEST_ASSERT_EQUAL(8, list->_cap);

  list->insert(list, 1337, 1);
  TEST_ASSERT_EQUAL(0, errno);

  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(1337, list->get(list, 1));
  TEST_ASSERT_EQUAL(9, list->get(list, 2));
  TEST_ASSERT_EQUAL(420, list->get(list, 3));
  TEST_ASSERT_EQUAL(13, list->get(list, 4));

  TEST_ASSERT_EQUAL(5, list->_size);
  TEST_ASSERT_EQUAL(8, list->_cap);
}

void test_pop(void) {
  TEST_ASSERT_EQUAL(13, list->pop(list));
  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));

  TEST_ASSERT_EQUAL(2, list->_size);
  TEST_ASSERT_EQUAL(2, list->_cap);

  TEST_ASSERT_EQUAL(9, list->pop(list));
  TEST_ASSERT_EQUAL(2, list->get(list, 0));

  TEST_ASSERT_EQUAL(1, list->_size);
  TEST_ASSERT_EQUAL(1, list->_cap);

  TEST_ASSERT_EQUAL(2, list->pop(list));
  TEST_ASSERT_EQUAL(0, list->_size);
  TEST_ASSERT_EQUAL(1, list->_cap);

  TEST_ASSERT_EQUAL(-1, list->pop(list));
  TEST_ASSERT_EQUAL(ERANGE, errno);
}

void test_delete(void) {
  TEST_ASSERT_EQUAL(1, list->delete(list, 9));
  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(13, list->get(list, 1));

  TEST_ASSERT_EQUAL(2, list->_size);
  TEST_ASSERT_EQUAL(2, list->_cap);

  TEST_ASSERT_EQUAL(0, list->delete(list, 2));
  TEST_ASSERT_EQUAL(13, list->get(list, 0));

  TEST_ASSERT_EQUAL(1, list->_size);
  TEST_ASSERT_EQUAL(1, list->_cap);

  TEST_ASSERT_EQUAL(0, list->delete(list, 13));

  TEST_ASSERT_EQUAL(0, list->_size);
  TEST_ASSERT_EQUAL(1, list->_cap);

  TEST_ASSERT_EQUAL(-1, list->delete(list, 0));
  TEST_ASSERT_EQUAL(ERANGE, errno);
}

void test_deletei(void) {
  TEST_ASSERT_EQUAL(9, list->deletei(list, 1));
  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(13, list->get(list, 1));

  TEST_ASSERT_EQUAL(2, list->_size);
  TEST_ASSERT_EQUAL(2, list->_cap);

  TEST_ASSERT_EQUAL(2, list->deletei(list, 0));
  TEST_ASSERT_EQUAL(13, list->get(list, 0));

  TEST_ASSERT_EQUAL(1, list->_size);
  TEST_ASSERT_EQUAL(1, list->_cap);

  TEST_ASSERT_EQUAL(13, list->deletei(list, 0));

  TEST_ASSERT_EQUAL(0, list->_size);
  TEST_ASSERT_EQUAL(1, list->_cap);
  
  TEST_ASSERT_EQUAL(-1, list->deletei(list, 0));
  TEST_ASSERT_EQUAL(ERANGE, errno);
}

void test_reverse(void) {
  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));
  TEST_ASSERT_EQUAL(13, list->get(list, 2));

  TEST_ASSERT_EQUAL(3, list->_size);
  TEST_ASSERT_EQUAL(4, list->_cap);

  list->reverse(list);

  TEST_ASSERT_EQUAL(13, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));
  TEST_ASSERT_EQUAL(2, list->get(list, 2));

  // Should remain the same
  TEST_ASSERT_EQUAL(3, list->_size);
  TEST_ASSERT_EQUAL(4, list->_cap);
}

void test_get(void) {
  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));
  TEST_ASSERT_EQUAL(13, list->get(list, 2));

  TEST_ASSERT_EQUAL(-1, list->get(list, 420));
  TEST_ASSERT_EQUAL(ERANGE, errno);
}

void test_find(void) {
  TEST_ASSERT_EQUAL(0, list->find(list, 2));
  TEST_ASSERT_EQUAL(1, list->find(list, 9));
  TEST_ASSERT_EQUAL(2, list->find(list, 13));
  TEST_ASSERT_EQUAL(-1, list->find(list, 420));
}

void test_contains(void) {
  TEST_ASSERT_EQUAL(1, list->contains(list, 2));
  TEST_ASSERT_EQUAL(1, list->contains(list, 9));
  TEST_ASSERT_EQUAL(1, list->contains(list, 13));

  TEST_ASSERT_EQUAL(0, list->contains(list, 1));
  TEST_ASSERT_EQUAL(0, list->contains(list, 4));
}

void test_clear(void) {
  for (int i = 3; i < 32768; ++i) {
    TEST_ASSERT_EQUAL(i, list->add(list, i));
    TEST_ASSERT_EQUAL(i + 1, list->_size);
  }

  list->clear(list);

  TEST_ASSERT_EQUAL(0, list->_size);
  TEST_ASSERT_EQUAL(1, list->_cap);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_add_null);
  RUN_TEST(test_add);
  RUN_TEST(test_insert_null);
  RUN_TEST(test_insert);
  RUN_TEST(test_pop);
  RUN_TEST(test_delete);
  RUN_TEST(test_deletei);
  RUN_TEST(test_reverse);
  RUN_TEST(test_get);
  RUN_TEST(test_find);
  RUN_TEST(test_contains);
  RUN_TEST(test_clear);

  return UNITY_END();
}
