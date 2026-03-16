#include "double_linked_list.h"
#include "unity.h"
#include "unity_internals.h"

List *list;

void setUp(void) { list = dll_create(); }
void tearDown(void) {}

void test_add_one(void) {
  dll_add(list, 1);

  TEST_ASSERT_EQUAL(1, list->root->value);
  TEST_ASSERT_EQUAL(1, list->size);
  TEST_ASSERT_EQUAL(NULL, list->root->nxt);
  TEST_ASSERT_EQUAL(NULL, list->root->prv);
}

void test_add_many(void) {
  for (int i = 0; i < 20; ++i) {
    dll_add(list, i);
    TEST_ASSERT_EQUAL(i + 1, list->size);
  }
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_add_one);
  RUN_TEST(test_add_many);

  return UNITY_END();
}
