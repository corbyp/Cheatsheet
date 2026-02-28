#include "printf.h"

void write(char* str) {
  long len = 0;

  for (char* cur = str; *cur != '\0'; ++cur) {
    ++len;
  }
  
  asm(
    ".intel_syntax noprefix;"
    "mov rax, 1;" // write syscall
    "mov rdi, 1;" // stdout fd
    "mov rsi, %0;" // copy string into rsi
    "mov rdx, %1;"
    "syscall;"
    ".att_syntax prefix;"
    : //outputs
    :"r"(str), "r"(len) // inputs
    :"rax", "rdi", "rsi", "rdx" // clobbered registers
  );
}

void print(char *str) {
  write(str);
}


