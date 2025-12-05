#include <errno.h>
#include <getopt.h>
#include <openssl/sha.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_lines(const char* filename) {
  FILE *fp;
  fp = fopen(filename, "r");
  int lines = 0;
  char line[255];
 
  while (fgets(line, sizeof(line), fp)) {
    ++lines;
  }

  fclose(fp);

  return lines;
}

void crack(const char *filename, unsigned char *pwd, _Bool verbose) {
  int lines = count_lines(filename);

  FILE *fp;
  fp = fopen(filename, "r");

  if (verbose) {
    printf("Reading file %s\n", filename);
  }

  if (fp == NULL) {
    fprintf(stderr, "Error while reading file %d\n", errno);
    errno = ENOENT;
    return;
  }

  if (verbose) {
    printf("%s read successfully\n", filename);
  }

  if (verbose) {
    printf("Starting to crack...\n");
  }

  unsigned char hash[SHA_DIGEST_LENGTH];
  char line[256];
  int count = 0;
  while (fgets(line, sizeof(line), fp)) {
    line[strlen(line) - 1] = '\0';
    SHA1((const unsigned char *)line, strlen(line), hash);

    if (verbose && (count % 1000) == 0) {
      printf("\rAttempted passwords: %.2f%%", ((double) count / lines) * 100.0);
      fflush(stdout);
    }

    if (memcmp(hash, pwd, 6) == 0) {
      printf("\nFound password: %s\n", line);
      fclose(fp);
      return;
    }

    ++count;
  }

  printf("\nPassword not found!\n");
  fclose(fp);
}

void string_to_bin(const char *hash, unsigned char *bin_out) {
  for (size_t i = 0; i < sizeof(bin_out); i++) {
    unsigned int byte_val;
    int result = sscanf(hash + (i * 2), "%02x", &byte_val);
    bin_out[i] = (unsigned char)byte_val;
  }
}

void parse_opt(int argc, char *argv[], char **filename, char **hash,
               _Bool *verbose) {
  int opt;
  while ((opt = getopt(argc, argv, "vf:")) != -1) {
    switch (opt) {
    case 'v':
      *verbose = true;
      break;
    case 'f':
      *filename = optarg;
      break;
    case '?':
      printf("Usage: %s <HASH> -f <FILE>\n", argv[0]);
      break;
    }
  }

  if (optind < argc) {
    *hash = argv[optind++];
  } else {
    fprintf(stderr, "Missing hash: %s <hash>\n", argv[0]);
    exit(1);
  }

  if (optind < argc) {
    fprintf(stderr, "Too many arguments!\n");
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  char *filename = NULL;
  char *hash = NULL;
  _Bool verbose = false;

  parse_opt(argc, argv, &filename, &hash, &verbose);

  unsigned char pwd[21];
  string_to_bin(hash, pwd);

  crack(filename, pwd, verbose);

  return errno;
}
