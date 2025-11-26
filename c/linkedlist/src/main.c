#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Element {
  struct Element *next;
  int value;
};

struct List {
  struct Element *head;
  size_t size;
};

void print_list(struct List *root) {
  struct Element *curr = root->head;

  size_t str_len = 4; // 2 for "[" and "]\n\0" at the end

  for (curr = root->head; curr != NULL; curr = curr->next) {
    str_len += snprintf(NULL, 0, "%d", curr->value); // len of number

    if (curr->next != NULL) {
      str_len += 2; // 2 more len for ", "
    }
  }

  char str[str_len];
  str[0] = '[';

  size_t ctr = 1;

  for (curr = root->head; curr != NULL; curr = curr->next) {
    char temp[11 + 1]; // 11 because of max int size: "-2147483648\0"

    int len = snprintf(temp, 11 + 1, "%d", curr->value);

    strncpy(str + ctr, temp, len);
    ctr += len;

    if (curr->next != NULL) {
      strncpy(str + ctr, ", ", 2);
      ctr += 2;
    }
  }

  str[str_len - 3] = ']';
  str[str_len - 2] = '\n';
  str[str_len - 1] = '\0';

  printf("%s\n", str);
}

struct List *init() {
  struct List *root = (struct List *)malloc(sizeof(struct List));
  if (root == NULL) {
    fprintf(stderr, "Could not malloc to init list\n");
    exit(1);
  }

  root->head = NULL;
  root->size = 0;

  return root;
}

void l_add(struct List *root, int val) {
  struct Element *head = root->head;
  if (head == NULL) {
    head = (struct Element *)malloc(sizeof(struct Element));

    if (head == NULL) {
      goto error_handling;
    }

    head->value = val;

    root->head = head;
    root->size++;
    return;
  } else {
    struct Element *curr = head;

    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = (struct Element *)malloc(sizeof(struct Element));

    if (curr->next == NULL) {
      goto error_handling;
    }

    curr->next->value = val;
    root->size++;
    return;
  }

error_handling:
  fprintf(stderr, "Could not malloc for %d\n", val);
  exit(1);
}

void l_remove(struct List *root, int val) {
  struct Element *head = root->head;

  if (head == NULL) {
    fprintf(stderr, "Tried to remove from empty list!\n");
  } else if (head->value == val) {
    struct Element *temp = root->head;
    root->head = head->next;
    free(temp);
    root->size--;
  } else {
    struct Element *curr = head->next;
    struct Element *parent = head;

    while (curr != NULL) {
      if (curr->value == val) {
        parent->next = curr->next;
        free(curr);
        root->size--;
        return;
      }
      parent = curr;
      curr = curr->next;
    }

    fprintf(stderr, "Item %d not found!\n", val);
  }
}

void reverse(struct List *root) {
  struct Element *head = root->head;
  if (head == NULL) {
    fprintf(stderr, "Tried reversing an empty list!\n");
  } else {
    struct Element *temp;
    struct Element *parent = NULL;
    struct Element *child = head;

    while (child != NULL) {
      temp = child->next;
      child->next = parent;
      parent = child;
      child = temp;
    }

    root->head = parent;
  }
}

void print_help() { printf("q: quit, c: create, a: add, p: print\n"); }

void interactive() {
  printf("Starting user input\n");
  int c;

  struct List *root;
  int count = 0;

  while (1) {
    c = getc(stdin);

    switch (c) {
    case 'q':
      printf("Stopping\n");
      return;
    case 'c':
      printf("Creating list\n");
      root = init();
      break;
    case 'a':
      printf("Doing insert\n");
      l_add(root, count++);
      break;
    case 'p':
      print_list(root);
      break;
      // default:
      // print_help();
      // break;
    }
  }
}

int main(void) {
  struct List *root = init();

  for (int i = 0; i < 400; ++i) {
    l_add(root, i);
  }

  // reverse(root);

  print_list(root);

  // interactive();

  return 0;
}
