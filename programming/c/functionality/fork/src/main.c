#include <unistd.h>
#include <stdio.h>

int main(void) {
  int pid = fork();

  if (pid) {
    printf("Hello from the parent\n");
  } else {
    const char* path = "/usr/bin/chromium-browser";
    char* argv[] = {"chromium-browser", "--incognito", NULL}; 
    printf("Hello from the child %d\n", getpid());
    execv(path, argv);
  }
  
  return 0;
}
