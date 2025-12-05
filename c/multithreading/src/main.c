#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* behaviour1(void* arg) {
  while (1) {
    char c = getchar();

    switch (c) {
    case 'q':
      return NULL;
    }
  }
}

void* behaviour2(void* arg) {
  for (int i = 0; i < 10; ++i) {
    sleep(1);
    printf("%d\n", i);
  }

  return NULL;
}

int main(void) {
  pthread_t thread1;
  pthread_t thread2;
  
  pthread_create(&thread1, NULL, behaviour1, NULL);
  pthread_create(&thread2, NULL, behaviour2, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
