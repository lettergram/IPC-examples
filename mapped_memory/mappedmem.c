/**
 * Taken from example for CS 241 @ UIUC
 * Repurposed and improvements made by Austin Walters
 * Used for austingwalters.com IPC - mapped memory example
 *
 * TO USE:
 * Compile, and type: ./a.out <filename> <read/write>
 *
 * Start off by running ./a.out <filename> read
 * Then a.out <filename> write
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

static const int MAX = 200;

int main(int argc, char** argv) {

  int    fd;
  char * mapped_memory;

  /**
   * Open a file and map it to memory,
   * once it is mapped to memory we can close
   * the file because we have access.
   */
  fd = open(argv[1], O_RDWR | O_CREAT);
  mapped_memory = mmap(NULL, MAX, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);

  if(strncmp(mapped_memory, "exit", 4) == 0)
    mapped_memory[0] = '\0';

  /** If Reader **/
  if (!strcmp(argv[2], "read")) {
    while (1) {
      mapped_memory[MAX - 1] = '\0';
      printf("%s", mapped_memory);
      if(strncmp(mapped_memory, "exit", 4) == 0)
	exit(1);
      fflush(stdout);
      sleep(1);
    }

  /** If Writer **/
  } else if (!strcmp(argv[2], "write")) {
    while (strncmp(mapped_memory, "exit", 4) != 0){
      fgets(mapped_memory, MAX, stdin);
      msync(mapped_memory, MAX, MS_SYNC);
    }
  }
}
