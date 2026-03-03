#include "double_linked_list.h"

int main(void) {
  List list;

  for (int i = 0; i < 20; ++i) {
    dll_add(&list, i);
  }
  
  dll_print2(&list);

  dll_clear(&list);
  
  dll_print(&list);

  return 0;
}
