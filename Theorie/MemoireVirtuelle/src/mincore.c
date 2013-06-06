/**************************************
 * mincore.c
 *
 * Programme d'exemple d'utilisation de
 * mincore
 *
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

///AAA
#dfine _BSD_SOURCE

#define SIZE 10*4096

int main(int argc, char *argv[]) {

  char *mincore_vec;
  size_t page_size = getpagesize();
  size_t page_index;
  char *mem;

  mem=(char *)malloc(SIZE*sizeof(char));
  if(mem==NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  for(int i=0;i<SIZE/2;i++) {
    *(mem+i)='A';
  }

  mincore_vec = calloc(sizeof(char), SIZE/page_size);
  if(mincore_vec==NULL) {
    perror("calloc");
    exit(EXIT_FAILURE);
  }
  if(mincore(mem, SIZE, mincore_vec)!=0) {
    perror("mincore");
    exit(EXIT_FAILURE);
  }

  for (page_index = 0; page_index < SIZE/page_size; page_index++) {
    printf("%lu :", (unsigned long)page_index);
    if (mincore_vec[page_index]&MINCORE_INCORE) {
      printf(" incore");
    }
    if (mincore_vec[page_index]&MINCORE_REFERENCED) {
      printf(" referenced_by_us");
    }
    if (mincore_vec[page_index]&MINCORE_MODIFIED) {
      printf(" modified_by_us");
    }
    printf("\n");
  }
  free(mincore_vec);
  free(mem);
  return (EXIT_SUCCESS);
}

