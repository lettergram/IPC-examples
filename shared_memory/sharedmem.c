/**
 * Example Written by Austin Walters,
 * for austingwalters.com to demonstrate
 * shared memory IPCs
 * 
 * References:
 * http://www.cs.cf.ac.uk/Dave/C/node27.html
 * Brighten Godfrey - UIUC Professor/Lecturer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 4096 // Size of shared memory

int main(int argc, char *argv[]) {

  key_t key;
  int id;
  char *msg;
  int write_mode = 0644;

  /**
   * Make a key!
   * This Key will be used to 
   * keep track of the datas
   * location in memory
   */
  if ((key = ftok(argv[0], 22)) == -1)
    exit(1);

  /**
   * Obtains identifier for the shared
   * memory location, given the key.
   *
   * FROM MAN PAGES:
   * shmget: Returns the identifier 
   * of the shared memory segment 
   * associated with the value of the 
   * argument key.
   */
  if ((id = shmget(key, SIZE, write_mode | IPC_CREAT)) == -1)
    exit(1);


  /**
   * Given the identifier,
   * uses shmat to retrieve 
   * the message from memory
   */
  msg = shmat(id, 0, 0);


  /**
   * Using the pointer to the physical
   * memory we either read or write to
   * or from the mapped physical memory.
   */
  char * header = "\nWriting Message: ";
  if (argc == 2)
    strncpy(msg, argv[1], SIZE);
  else
    header = "\nRead Message Contains: ";
  printf("%s\"%s\"\n\n", header, msg);


  /**
   * Detatches from the physical
   * memory location
   */
  shmdt(msg);

  return 0;
}
