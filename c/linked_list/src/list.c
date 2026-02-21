#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ll_print(List *list) {
  Node *curr = list->head;

  size_t str_len = 3; // 2 for "[" and "]\0" at the end

  for (curr = list->head; curr != NULL; curr = curr->next) {
    str_len += snprintf(NULL, 0, "%d", curr->value); // len of number

    if (curr->next != NULL) {
      str_len += 2; // 2 more len for ", "
    }
  }

  char str[str_len];
  str[0] = '[';

  size_t ctr = 1;
  char temp[12]; // 12 because of max int size: "-2147483648\0"

  for (curr = list->head; curr != NULL; curr = curr->next) {
    int len = snprintf(temp, 11 + 1, "%d", curr->value);

    for (size_t i = 0; i < len; ++i) {
      str[ctr + i] = temp[i];
    }

    ctr += len;

    if (curr->next != NULL) {
      str[ctr] = ',';
      str[ctr + 1] = ' ';
      ctr += 2;
    }
  }

  str[str_len - 2] = ']';
  str[str_len - 1] = '\0';

  printf("%s\n", str);
}

List *ll_init() {
  List *list = (List *)malloc(sizeof(List));

  if (list == NULL) {
    fprintf(stderr, "Could not malloc to init list\n");
    exit(1);
  }

  list->head = NULL;
  list->size = 0;

  return list;
}

void ll_add(List *list, int val) {
  Node *head = list->head;

  if (head == NULL) {
    head = (Node *)malloc(sizeof(Node));

    if (head == NULL) {
      goto error_handling;
    }

    head->value = val;

    list->head = head;
    list->size++;
    return;
  } else {
    Node *curr = head;

    while (curr->next != NULL) {
      curr = curr->next;
    }

    curr->next = (Node *)malloc(sizeof(Node));

    if (curr->next == NULL) {
      goto error_handling;
    }

    curr->next->value = val;
    list->size++;
    return;
  }

error_handling:
  fprintf(stderr, "Could not malloc for %d\n", val);
  exit(1);
}

void ll_insert(List* list, size_t index, int val) {
  if (index >= list->size || index < 0) {
    fprintf(stderr, "Tried inserting into position %lu but list only has length %lu\n", index, list->size);
    return;
  } else {
    Node* curr = list->head;
    index--;

    while (index-- > 0) {
      curr = curr->next;
    }

    printf("%d\n", curr->value);
  }
}

void ll_remove(List *list, int val) {
  Node *head = list->head;

  if (head == NULL) {
    fprintf(stderr, "Tried to remove from empty list!\n");
  } else if (head->value == val) {
    Node *temp = list->head;
    list->head = head->next;
    free(temp);
    list->size--;
  } else {
    Node *curr;
    Node *parent = head;

    for (curr = head->next; curr != NULL; curr = curr->next) {
      if (curr->value == val) {
        parent->next = curr->next;
        free(curr);
        list->size--;
        return;
      }
      parent = curr;
    }

    fprintf(stderr, "Item %d not found!\n", val);
  }
}

void ll_reverse(List *list) {
  Node *head = list->head;

  if (head == NULL) {
    fprintf(stderr, "Tried reversing an empty list!\n");
  } else {
    Node *temp;
    Node *parent = NULL;
    Node *curr = head;

    for (curr = head; curr != NULL; curr = temp) {
      temp = curr->next;
      curr->next = parent;
      parent = curr;
      curr = temp;
    }

    list->head = parent;
  }
}

_Bool ll_includes(List *list, int val) {
  Node *curr;

  for (curr = list->head; curr != NULL; curr = curr->next) {
    if (curr->value == val) {
      return 1;
    }
  }

  return 0;
}

int ll_get(List *list, unsigned long index) {
  if (index >= list->size || index < 0) {
    fprintf(stderr, "%lu not in list of length %lu\n", index, list->size);
    exit(1);
  }

  unsigned long i = 0;

  Node *curr;

  for (curr = list->head; curr != NULL; curr = curr->next) {
    if (i++ == index) {
      return curr->value;
    }
  }

  printf("List not long enough for index %lu\n", index);
  exit(1);
}
