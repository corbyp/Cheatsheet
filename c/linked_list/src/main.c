#include <stdlib.h>
#include <stdio.h>

struct List {
  struct List* next;
  int value;
};

void print_item(struct List* item) {
  printf("%p, %d, %p\n", item, item->value, item->next);
}

void print_list(struct List* root) {
  struct List* curr = root;

  while (curr != NULL) {
    print_item(curr);
    curr = curr->next;
  }
}

struct List* l_add(struct List* root, int val) {
  if (root == NULL) {
    root = (struct List*) malloc(sizeof(struct List));

    if (root == NULL) {
      goto error_handling;
    }

    root->value = val;
    return root;
  } else {
    struct List* temp = root;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = (struct List*) malloc(sizeof(struct List));

    if (temp->next == NULL) {
      goto error_handling;
    }

    temp->next->value = val;
    return root;
  }

  error_handling:
      fprintf(stderr, "Could not malloc for %d\n", val);
      exit(1);
}

struct List* l_remove(struct List* root, int val) {
  if (root == NULL) {
    fprintf(stderr, "Tried to remove from empty list!\n");
    exit(1);
  } else if (root->value == val) {
    struct List* temp = root->next;
    free(root);
    return temp;
  } else {
    struct List* temp = root;
    struct List* parent = NULL;
    
    while (temp != NULL) {
      if (temp->value == val) {
        parent->next = temp->next;
        free(temp);
        return root;
      }
      parent = temp;
      temp = temp->next;
    }

    return root;
  }
}

struct List* reverse(struct List* root) {
  if (root == NULL) {
    fprintf(stderr, "Tried reversing an empty list!\n");
    exit(1);
  } else {
    struct List* temp;
    struct List* parent = NULL;
    struct List* child = root;

    while (child != NULL) {
      temp = child->next;
      child->next = parent;
      parent = child;
      child = temp;
    }

    return parent;
  }
}


int main(void) {
  struct List* root = NULL;

  for (int i = 0; i < 100; ++i) {
    root = l_add(root, i);
  }

  root = reverse(root);
  print_list(root);
  
  return 0;
}
