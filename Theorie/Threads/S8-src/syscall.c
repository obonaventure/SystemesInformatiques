/**************************************
 * syscall.c
 *
 * Programme d'exemple d'utilisation de syscall
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>


int main (int argc, char *argv[])  {
  int pid=getpid();
  int pid2=syscall(SYS_getpgid);
  printf("Processus %d, pid:%d\n",pid,pid2);

  return(EXIT_SUCCESS);
}
