#include "dynamic_array.h"
#include "unity.h"
#include "unity_internals.h"

List *list;

void setUp(void) {
  list = construct();
  list->add(list, 2);
  list->add(list, 9);
  list->add(list, 13);
}
void tearDown(void) { deconstruct(list); }

void test_add_resize(void) {
  TEST_ASSERT_EQUAL(3, list->add(list, 420));

  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));
  TEST_ASSERT_EQUAL(13, list->get(list, 2));
  TEST_ASSERT_EQUAL(420, list->get(list, 3));

  TEST_ASSERT_EQUAL(4, list->_size);
  TEST_ASSERT_EQUAL(8, list->_cap);
}

void test_add(void) {
  TEST_ASSERT_EQUAL(3, list->add(list, 420));
  TEST_ASSERT_EQUAL(4, list->add(list, 1337));

  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));
  TEST_ASSERT_EQUAL(13, list->get(list, 2));
  TEST_ASSERT_EQUAL(420, list->get(list, 3));
  TEST_ASSERT_EQUAL(1337, list->get(list, 4));

  TEST_ASSERT_EQUAL(5, list->_size);
  TEST_ASSERT_EQUAL(8, list->_cap);
}

void test_add_many(void) {
  for (int i = 3; i < 32768; ++i) {
    TEST_ASSERT_EQUAL(i, list->add(list, i));
  }

  for (int i = 3; i < 32768; ++i) {
    TEST_ASSERT_EQUAL(i, list->get(list, i));
  }

  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));
  TEST_ASSERT_EQUAL(13, list->get(list, 2));
  TEST_ASSERT_EQUAL(32768, list->_size);
  TEST_ASSERT_EQUAL(32768 * 2, list->_cap);
}

void test_insert_resize(void) {
  TEST_ASSERT_EQUAL(2, list->insert(list, 420, 2));

  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));
  TEST_ASSERT_EQUAL(420, list->get(list, 2));
  TEST_ASSERT_EQUAL(13, list->get(list, 3));

  TEST_ASSERT_EQUAL(4, list->_size);
  TEST_ASSERT_EQUAL(8, list->_cap);
}

void test_insert(void) {
  TEST_ASSERT_EQUAL(2, list->insert(list, 420, 2));
  TEST_ASSERT_EQUAL(1, list->insert(list, 1337, 1));

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
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_add);
  RUN_TEST(test_add_resize);
  RUN_TEST(test_add_many);
  RUN_TEST(test_insert_resize);
  RUN_TEST(test_insert);
  RUN_TEST(test_pop);
  RUN_TEST(test_delete);
  RUN_TEST(test_deletei);

  return UNITY_END();
}
