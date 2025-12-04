#include <errno.h>
#include <openssl/sha.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crack(const char *filename, unsigned char *pwd) {
  FILE *fp;
  fp = fopen(filename, "r");

  if (fp == NULL) {
    errno = ENOENT;
    return;
  }

  unsigned char hash[SHA_DIGEST_LENGTH];
  char line[256];
  int i = 0;
  while (fgets(line, sizeof(line), fp) && i++ < 5) {
    SHA1((const unsigned char *)line, strlen(line), hash);
    line[strlen(line) - 1] = '\0';

    printf("%s\n", line);
    printf("%s\n", hash);

    if (memcmp(hash, pwd, 6) == 0) {
      printf("Found password: %s\n", line);
      return;
    }
  }

  printf("Password not found!\n");
}

void string_to_bin(const char *hex_str, unsigned char *bin_out,
                   size_t bin_len) {
  for (size_t i = 0; i < bin_len; i++) {
    unsigned int byte_val;
    int result = sscanf(hex_str + (i * 2), "%02x", &byte_val);
    bin_out[i] = (unsigned char)byte_val;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Expected 2 args but got: %d\n", argc - 1);
    return 1;
  }

  unsigned char pwd[21];
  string_to_bin(argv[2], pwd, 21);

  crack(argv[1], pwd);

  return 0;
}
