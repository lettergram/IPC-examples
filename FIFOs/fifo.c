/**
 * Used in an example on austingwalters.com,
 * as a FIFO IPC
 * Edited by Austin Walters
 * Originally from CS 241 @ UIUC
 *
 * Commandline use: ./a.out <filename>
 * In the example I do ./a.out fifo.c
 *
 * This program simply prints all the lines
 * in a file, and numbers the line number for 
 * you :D
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv) {

  /* Checks to see if file exists */
  if(access(argv[1], F_OK) == -1)
    exit(1);

  /* Creates fifo */
  mkfifo(argv[1], S_IRWXU | S_IRWXG | S_IRWXO);
  int fifo = open(argv[1], O_RDONLY);

  /* Duplicate the file 'fifo', so that file descriptor 0 points to it.
   * Note that 0 is the file descriptor of stdin. */
  dup2(fifo, 0);

  char line[1024];
  int i = 0;
  
  printf("\n\n--------- Start ----------\n\n");
  printf("Title: %s\n\n", argv[1]);
  while(fgets(line, 1024, stdin))
    printf("%3d| %s", i++, line);
  printf("\n\n--------- End  ----------\n\n");
}
