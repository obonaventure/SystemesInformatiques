/**************************************
 * nfork.c
 *
 * Programme lançant plusieurs copies
 * de lui même
 *
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, char *argv[])  {

  int n=2;
  for(int i=0; i<n ; i++) {
    printf("i=%d\n",i);
    pid_t pid;
    pid=fork();
    if (pid==-1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else {
      if(pid!=0) {
	printf("Running in %d\n",pid);
      }
    }
  }
  return(EXIT_SUCCESS);
}

