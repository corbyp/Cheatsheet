#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main(void) {
  struct sockaddr_in sa;
  char rb[1024];
  int fd1 = socket(AF_INET, SOCK_DGRAM, 0);
  sa.sin_family = AF_INET;
  sa.sin_port = htons(5000);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);
  if (!bind(fd1, (struct sockaddr *)&sa, sizeof(sa))) {
    return 1;
  }

  while (1) {
    int n = recv(fd1, rb, sizeof(rb) - 1, 0);
    rb[n] = '\0';
    printf("Received %s\n", rb);
  }

  return 0;
}
