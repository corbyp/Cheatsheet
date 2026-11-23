#include "tests.h"
#include "unity.h"

#include <errno.h>

void test_size_full(void) {
  fill_list();

  TEST_ASSERT_EQUAL(ARR_SIZE, list->size(list));
  TEST_ASSERT_EQUAL(0, errno);
}

void test_cap_full(void) {
  fill_list();

  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
  TEST_ASSERT_EQUAL(0, errno);
}

void test_add_full(void) {
  fill_list();

  for (int i = ARR_SIZE; i < 32768; ++i) {
    TEST_ASSERT_EQUAL(i, list->add(list, i));
    TEST_ASSERT_EQUAL(i + 1, list->size(list));
    TEST_ASSERT_EQUAL(0, errno);
  }

  TEST_ASSERT_EQUAL(2, list->get(list, 0));
  TEST_ASSERT_EQUAL(9, list->get(list, 1));
  TEST_ASSERT_EQUAL(13, list->get(list, 2));
  for (int i = ARR_SIZE; i < 32768; ++i) {
    TEST_ASSERT_EQUAL(i, list->get(list, i));
  }

  TEST_ASSERT_EQUAL(32768, list->size(list));
  TEST_ASSERT_EQUAL(32768 * 2, list->cap(list));
}

void test_insert_full(void) {
  fill_list();

  int val_to_insert = 420;
  int index_to_insert = 2;
  int index_offset = 0;

  list->insert(list, val_to_insert, index_to_insert);
  TEST_ASSERT_EQUAL(0, errno);

  // Test if all values in list are correct
  for (int i = 0; i < ARR_SIZE - 1; ++i) {
    if (i == index_to_insert)
      index_offset = 1;
    TEST_ASSERT_EQUAL(ARR[i], list->get(list, i + index_offset));
  }

  TEST_ASSERT_EQUAL(ARR_SIZE + 1, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
}

void test_pop_full(void) {
  fill_list();

  TEST_ASSERT_EQUAL(ARR[ARR_SIZE - 1], list->pop(list));
  TEST_ASSERT_EQUAL(0, errno);

  for (int i = 0; i < ARR_SIZE - 1; ++i) {
    TEST_ASSERT_EQUAL(ARR[i], list->get(list, i));
  }

  TEST_ASSERT_EQUAL(ARR_SIZE - 1, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
}

void test_delete_full(void) {
  fill_list();

  int index_to_delete = 2;
  int index_offset = 0;

  TEST_ASSERT_EQUAL(index_to_delete, list->delete(list, ARR[index_to_delete]));
  TEST_ASSERT_EQUAL(0, errno);

  for (int i = 0; i < ARR_SIZE - 1; ++i) {
    if (i == index_to_delete)
      index_offset = 1;
    TEST_ASSERT_EQUAL(ARR[i + index_offset], list->get(list, i));
  }

  TEST_ASSERT_EQUAL(ARR_SIZE - 1, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
}

void test_deletei_full(void) {
  fill_list();

  int index_to_delete = 1;
  int index_offset = 0;

  TEST_ASSERT_EQUAL(ARR[index_to_delete], list->deletei(list, index_to_delete));
  TEST_ASSERT_EQUAL(0, errno);

  for (int i = 0; i < ARR_SIZE - 1; ++i) {
    if (i == index_to_delete)
      index_offset = 1;
    TEST_ASSERT_EQUAL(ARR[i + index_offset], list->get(list, i));
  }

  TEST_ASSERT_EQUAL(ARR_SIZE - 1, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
}

void test_reverse_full(void) {
  fill_list();

  list->reverse(list);
  TEST_ASSERT_EQUAL(0, errno);

  for (int i = 0; i < ARR_SIZE; ++i) {
    TEST_ASSERT_EQUAL(ARR[ARR_SIZE - i - 1], list->get(list, i));
  }

  // Should remain the same
  TEST_ASSERT_EQUAL(ARR_SIZE, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
}

void test_get_full(void) {
  fill_list();

  for (int i = 0; i < ARR_SIZE - 1; ++i) {
    TEST_ASSERT_EQUAL(ARR[i], list->get(list, i));
    TEST_ASSERT_EQUAL(0, errno);
  }

  TEST_ASSERT_EQUAL(ARR_SIZE, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
}

void test_find_full(void) {
  fill_list();

  for (int i = 0; i < ARR_SIZE - 1; ++i) {
    TEST_ASSERT_EQUAL(i, list->find(list, ARR[i]));
    TEST_ASSERT_EQUAL(0, errno);
  }

  TEST_ASSERT_EQUAL(ARR_SIZE, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
}

void test_contains_full(void) {
  fill_list();

  for (int i = 0; i < ARR_SIZE - 1; ++i) {
    TEST_ASSERT_EQUAL(1, list->contains(list, ARR[i]));
    TEST_ASSERT_EQUAL(0, errno);
  }

  TEST_ASSERT_EQUAL(ARR_SIZE, list->size(list));
  TEST_ASSERT_EQUAL(ARR_CAP, list->cap(list));
}

void test_clear_full(void) {
  fill_list();

  list->clear(list);
  TEST_ASSERT_EQUAL(0, errno);

  TEST_ASSERT_EQUAL(0, list->size(list));
  TEST_ASSERT_EQUAL(1, list->cap(list));
}
