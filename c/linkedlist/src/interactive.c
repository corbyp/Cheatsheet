#include "list.h"
#include <stdio.h>

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
      root = ll_init();
      break;
    case 'a':
      printf("Doing insert\n");
      ll_add(root, count++);
      break;
    case 'p':
      ll_print(root);
      break;
    case '\n':
      break;
    default:
      print_help();
      break;
    }
  }
}
