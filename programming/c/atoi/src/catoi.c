#include "catoi.h"

int catoi(const char *str) {
  int acc = 0;
  for (char *cur = (char *) str; *cur != 0; cur++) {
    if (*cur < 48 || *cur > 57) {
      return 0;
    }
    acc *= 10;
    acc += *cur - 48;
  }

  return acc;
}

