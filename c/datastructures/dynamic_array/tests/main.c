#include "dynamic_array.h"
#include "unity.h"
#include "unity_internals.h"

List *list;

void setUp(void) { list = init(); }
void tearDown(void) {}

void test_add_one(void) {
}

void test_add_many(void) {
}

void other(void) {
  list = init();
  printf("Here\n");
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_add_one);
  RUN_TEST(test_add_many);

  other();

  return UNITY_END();
}
