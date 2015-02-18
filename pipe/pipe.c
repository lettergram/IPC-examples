/**
 * Written for IPC example @ austingwalters.com
 * From:
 * Pipe example for lectures in CS241 @ UIUC
 * Rewritten (in part) by Austin Walters
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  int pfds[2];
  int SIZE = 30;
  char buf[SIZE];
  char * msg = "This is a pipe example!";

  /** Generates two pipe file descriptors **/
  pipe(pfds);

  /** writer **/
  if (!fork()) {

    printf(" CHILD: writing to pipe\n");
    write(pfds[1], msg, SIZE);
    printf(" CHILD: exiting\n");

  /** reader **/
  }else{

    printf("PARENT: reading from pipe\n");
    read(pfds[0], buf, SIZE);
    printf("PARENT: read \"%s\"\n", buf);
    wait(NULL);
  }

  return 0;
}
