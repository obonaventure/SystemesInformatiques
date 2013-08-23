/**************************************
 * getpid.c
 *
 * Programme d'exemple de getpid
 *
 **************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main (int argc, char *argv[])  {
  int pid=getpid();
  int ppid=getppid();
  printf("Processus %d, parent:%d\n",pid,ppid);

  return(EXIT_SUCCESS);
}
///BBB
