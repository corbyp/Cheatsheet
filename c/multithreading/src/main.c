#include <signal.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

volatile sig_atomic_t stop_flag = 1;

void* behaviour1(void* arg) {
  while (1) {
    char c = getchar();

    switch (c) {
    case 'q':
      printf("Here\n");
      return NULL;
    }
  }
}

void* behaviour2(void* arg) {
  int i = 0;
  while (stop_flag) {
    // sleep(1);
    printf("%d\n", i++);
  }

  return NULL;
}

int main(void) {
  pthread_t io;
  pthread_t threads[100];

  printf("%d\n", getpid());
  
  pthread_create(&io, NULL, behaviour1, NULL);
  for (int i = 0; i < 100; ++i) {
    pthread_create(&threads[i], NULL, behaviour2, NULL);
  }

  pthread_join(io, NULL);
  stop_flag = 0;
  for (int i = 0; i < 100; ++i) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
