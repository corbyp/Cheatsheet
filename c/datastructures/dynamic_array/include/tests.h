#pragma once
#include "dynamic_array.h"

// Common variables needed by all tests
extern List *list;

extern const int ARR_SIZE;
extern const int ARR_CAP;
extern const int ARR[];

extern const int ARR_SIZE_RESIZE;
extern const int ARR_CAP_RESIZE;
extern const int ARR_RESIZE[];

// Helper functions
void fill_list(void);
void fill_list_resize(void);
void set_list_null(void);
void one_element_list(void);

// Tests for when the list already has elements
void test_size_full(void);
void test_cap_full(void);
void test_add_full(void);
void test_insert_full(void);
void test_pop_full(void);
void test_delete_full(void);
void test_deletei_full(void);
void test_reverse_full(void);
void test_get_full(void);
void test_find_full(void);
void test_contains_full(void);
void test_clear_full(void);

// Trying to insert/pop/etc. the element in last position
void test_insert_tail(void);
void test_pop_tail(void);
void test_delete_tail(void);
void test_deletei_tail(void);
void test_get_tail(void);

// Tests for when the list needs to resize
void test_add_resize(void);
void test_insert_resize(void);
void test_pop_resize(void);
void test_delete_resize(void);
void test_deletei_resize(void);

// Tests for when the _ptr is NULL
void test_size_null(void);
void test_cap_null(void);
void test_add_null(void);
void test_insert_null(void);
void test_pop_null(void);
void test_delete_null(void);
void test_deletei_null(void);
void test_reverse_null(void);
void test_get_null(void);
void test_find_null(void);
void test_contains_null(void);
void test_clear_null(void);

// Tests for when the last remaining element gets deleted
void test_size_last(void);
void test_cap_last(void);
void test_pop_last(void);
void test_delete_last(void);
void test_deletei_last(void);

// Tests for when the list is empty
void test_size_empty(void);
void test_cap_empty(void);
void test_add_empty(void);
void test_insert_empty(void);
void test_pop_empty(void);
void test_delete_empty(void);
void test_deletei_empty(void);
void test_reverse_empty(void);
void test_get_empty(void);
void test_find_empty(void);
void test_contains_empty(void);
void test_clear_empty(void);

