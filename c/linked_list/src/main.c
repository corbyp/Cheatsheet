#include <stdlib.h>
#include <stdio.h>

struct List {
  struct List* next;
  int value;
};

_Bool insert(struct List* root, int val) {
  if (root == NULL) {
    root = malloc(sizeof(struct List));

    if (root == NULL) {
      fprintf(stderr, "Could not malloc for root\n");
      exit(1);
    }

    printf("Here\n");
    root->value = val;
    return 1;
  } else {
    struct List* curr = root;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = malloc(sizeof(struct List));

    if (curr->next == NULL) {
      fprintf(stderr, "Could not malloc for root\n");
      exit(1);
    }

    curr->next->value = val;
    return 1;
  }

  return 0;
}

void print_list(struct List* root) {
  struct List* curr = root;

  while (curr->next != NULL) {
    printf("%d", curr->value);
    curr = curr->next;
  }
}

int main(void) {
  struct List list;
  insert(&list, 10);
  print_list(&list);
  
  return 0;
}
