#pragma once

typedef struct Node {
  struct Node* next;
  int value;
} Node;

typedef struct List {
  struct Node* head;
  unsigned long size;
} List;

/*
Print LIST of size n in format "[x1, x2, ..., xn]"
*/
void ll_print(List *list);

/*
Initializes list on heap and gives back pointer
*/
List *ll_init();

/*
Adds element with VAL to end of LIST
*/
void ll_add(List *list, int val);

/*
Removes VAL from LIST
*/
void ll_remove(List *list, int val);

/*
Reverses LIST
*/
void ll_reverse(List *list);

/*
Returns VAL in position INDEX from LIST
*/
int ll_get(List *list, unsigned long index);

/*
Returns 1 if VAL is in LIST, otherwise 0
*/
_Bool ll_includes(List *list, int val);

/*
Inserts VAL into LIST at position INDEX
*/
void ll_insert(List *list, unsigned long index, int val);
