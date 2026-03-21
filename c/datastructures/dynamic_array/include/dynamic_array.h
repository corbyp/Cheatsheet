/**
 * @file dynamic_array.h
 * @brief A dynamic integer list with automatic capacity doubling.
 *
 * Capacity starts at 1 and doubles on each expansion, keeping it a
 * power of 2. Functions are exposed as function pointers on the struct
 * itself and should be called with the list itself as the first argument.
 * All operations that can fail set errno on error.
 *
 * @note All functions fail gracefully if passed a NULL pointer by
 *       returning early and writing EINVAL to errno. If a function has
 *       a return value but no errno documentation, refer to this note.
 *
 * @note Negative indeces can also be used instead of positive ones. They
 *       automatically get translated using l->size - index
 *
 * Example:
 * @code
 *   List *l = construct();
 *   l->add(l, 10);
 *   l->add(l, 20);
 *   l->print(l);   // [10, 20]
 *   deconstruct(l);
 * @endcode
 * Do not access underscore-prefixed field directly.
 */
#pragma once

 #include <stdbool.h>

typedef struct List {
  int _size;
  // How many elements the list can hold until it needs to be
  // expanded. On expansion: 2 * _cap, thus making _cap a power of 2.
  int _cap;
  int *_ptr;

  /**
   * @brief Returns size.
   *
   * @param[in,out] list  Pointer to an initialised List.
   * @return _size or -1.
   */
  int (*size)(const struct List *list);

  /**
   * @brief Returns _cap.
   *
   * @param[in,out] list  Pointer to an initialised List.
   * @return _cap or -1.
   */
  int (*cap)(const struct List *list);
  
  /**
   * @brief Adds element to end of list.
   *
   * If size == capacity, list is expanded to 2 * capacity
   * by reallocating memory to that exact size.
   * Worst-case O(n) operation.
   *
   * @param[in,out] list  Pointer to an initialised List.
   * @param[in]     value Value to be added.
   * @return index of element (size - 1) or -1.
   */
  int (*add)(struct List *list, const int value);

  /**
   * @brief Inserts element at specific index.
   *
   * Can only insert between 0 and size - 1.
   * If index out of bounds, sets errno to ERANGE.
   * Worst-case O(n) operation.
   *
   * @param[in,out] list  Pointer to an initialised List.
   * @param[in]     value Value that is to be inserted.
   * @param[in]     index Index where to insert value.
   */
  void (*insert)(struct List *list, const int value, int index);

  /**
   * @brief Removes element at last position and returns its value.
   *
   * If no elements in list, set errno to ERANGE and returns -1.
   * Worst-case O(n) operation.
   *
   * @param[in,out] list Pointer to an initialised List.
   * @return value of removed element or -1.
   */
  int (*pop)(struct List *list);

  /**
   * @brief Removes given value and returns index.
   *
   * If value not present in list, returns -1.
   * Worst-case O(n) operation.
   *
   * @param[in,out] list  Pointer to an initialised List.
   * @param[in]     value Value to remove.
   * @return index of removed value or -1.
   */
  int (*delete)(struct List *list, const int value);

  /**
   * @brief Removes element at given index and returns value.
   *
   * If index is out of bounds, sets errno to ERANGE and returns -1.
   * Worst-case O(n) operation.
   *
   * @param[in,out] list  Pointer to an initialised List.
   * @param[in]     index Index to remove.
   * @return value that was deleted or -1.
   */
  int (*deletei)(struct List *list, int index);

  /**
   * @brief Reverses list.
   *
   * Worst-case O(n/2) operation.
   *
   * @param[in,out] list Pointer to an initialised List.
   */
  void (*reverse)(struct List *list);

  /**
   * @brief Returns value at given index.
   *
   * If index not within bounds, sets errno to ERANGE and returns -1.
   * Worst-case O(1) operation.
   *
   * @param[in] list  Pointer to an initialised List.
   * @param[in] index Index to be returned.
   * @return value of index if present or -1.
   */
  int (*get)(const struct List *list, int index);

  /**
   * @brief Finds index of value.
   *
   * Uses linear search since sort is not a requirement.
   * Worst-case O(n) operation.
   *
   * @param[in] list  Pointer to an initialised List.
   * @param[in] value Value to be found.
   * @return index of value if present, otherwise -1.
   */
  int (*find)(const struct List *list, const int value);

  /**
   * @brief Checks if element is contained in list.
   *
   * Uses linear search since sort is not a requirement.
   * Worst-case O(n) operation.
   *
   * @param[in] list  Pointer to an initialised List.
   * @param[in] value Value to be checked.
   * @return true if value is present in list, otherwise false.
   */
  bool (*contains)(const struct List *list, const int value);

  /**
   * @brief Removes all elements of list.
   *
   * Worst-case O(1) operation.
   *
   * Sets size to 0, capacity to 1 and reallocates
   * the memory accordingly.
   *
   * @param[in,out] list Pointer to an initialised List.
   */
  void (*clear)(struct List *list);

  /**
   * @brief Prints list in format [1, 2, 3]
   *
   * Only prints elements within size of list.
   * O(n) operation.
   *
   * @param[in] list Pointer to an initialised List.
   */
  void (*print)(const struct List *list);

  /**
   * @brief Prints list in format [1, 2, 3, 0, 0]
   *
   * Also prints uninitialised values that are not within
   * size but within capacity.
   * O(n) operation.
   *
   * @param[in] list Pointer to an initialised List.
   */
  void (*print2)(const struct List *list);

  /**
   * @brief Prints size and capacity of list.
   *
   * O(1) operation.
   *
   * @param[in] list Pointer to an initialised List.
   */
  void (*info)(const struct List *list);
} List;

/**
 * @brief Initialise the List with capacity 1.
 *
 * Allocates internal storage and binds functions. Must be paired with a call
 * to deconstruct() to avoid memory leaks.
 *
 * @return a pointer to a list initialised on the heap.
 */
List *construct(void);

/**
 * @brief Release all resources held by the list.
 *
 * After this call, @p s must not be used unless re-initialised.
 *
 * @param[out] list Pointer to an initialised List.
 */
void deconstruct(struct List *list);
