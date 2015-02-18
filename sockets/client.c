/**
 * Example taken from CS 241 @ UIUC
 * Edited by Austin Walters
 * Used as example for austingwalters.com,
 * in socket IPC explanation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char** argv){

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  struct addrinfo info, *result;
  memset(&info, 0, sizeof(struct addrinfo));
  info.ai_family = AF_INET;
  info.ai_socktype = SOCK_STREAM;

  if(0 != getaddrinfo("localhost", "8080", &info, &result))
    exit(1);
  
  /* Connects to bound socket on the server */  
  connect(sock_fd, result->ai_addr, result->ai_addrlen)

  char *buffer = "GET / HTTP/1.0\r\n\r\n";
  printf("SENDING: %s", buffer);
  printf("===\n");
  write(sock_fd, buffer, strlen(buffer));

  char resp[1000];
  int len = read(sock_fd, resp, 999);
  resp[len] = '\0';
  printf("%s\n", resp);

  return 0;
}
