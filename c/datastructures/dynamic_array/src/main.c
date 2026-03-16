#include "dynamic_array.h"

int main(void) {
  List *l = init();
  for (int i = 0; i < 20; ++i) {
    l->add(l, i);
  }
  l->print(l);
  l->delete(l, 5);
  return 0;
}
