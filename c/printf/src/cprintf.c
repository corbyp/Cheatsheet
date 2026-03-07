#include "cprintf.h"
#include <stdio.h>

void cwrite(char c) {
  asm(".intel_syntax noprefix;"
      "mov rax, 1;"  // write syscall
      "mov rdi, 1;"  // stdout fd
      "mov rsi, %0;" // copy string into rsi
      "mov rdx, 1;"
      "syscall;"
      ".att_syntax prefix;"
      :                            // outputs
      : "r"(&c)                    // inputs
      : "rax", "rdi", "rsi", "rdx" // clobbered registers
  );
}

// void cprint(char *str) { cwrite(str); }

void cprintf(char *str, const void **args) {
  char **arg = (char **)args;

  char *cur = str;
  while (*cur != '\0') {
    if (*cur == '%') {
      if (arg == NULL) {
        return;
      }

      char *carg = *(arg++);
      while (*carg != '\0') {
        cwrite(*(carg++));
      }
    } else {
      cwrite(*cur);
    }
    cur++;
  }
}
