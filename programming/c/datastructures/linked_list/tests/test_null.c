#include "linked_list.h"
#include "tests.h"
#include "unity.h"

#include <errno.h>

void test_size_null(void) {
  set_list_null();

  TEST_ASSERT_EQUAL(-1, list->size(list));
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_cap_null(void) {
  set_list_null();
  
  TEST_ASSERT_EQUAL(-1, list->cap(list));
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_add_null(void) {
  set_list_null();

  TEST_ASSERT_EQUAL(-1, list->add(list, 0));
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_insert_null(void) {
  set_list_null();

  list->insert(list, 0, 0);
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_pop_null(void) {
  set_list_null();

  TEST_ASSERT_EQUAL(-1, list->pop(list));
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_delete_null(void) {
  set_list_null();

  TEST_ASSERT_EQUAL(-1, list->delete(list, 0));
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_deletei_null(void) {
  set_list_null();

  TEST_ASSERT_EQUAL(-1, list->deletei(list, 0));
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_reverse_null(void) {
  set_list_null();

  list->reverse(list);
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_get_null(void) {
  set_list_null();

  TEST_ASSERT_EQUAL(-1, list->get(list, 0));
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_find_null(void) {
  set_list_null();

  TEST_ASSERT_EQUAL(-1, list->find(list, 0));
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_contains_null(void) {
  set_list_null();

  TEST_ASSERT_EQUAL(0, list->contains(list, 0));
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_clear_null(void) {
  set_list_null();

  list->clear(list);
  TEST_ASSERT_EQUAL(EINVAL, errno);
}

