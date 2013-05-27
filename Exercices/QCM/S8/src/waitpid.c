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
#include <errno.h>
#include <string.h>

int main (int argc, char *argv[])  {

  int status;
  int err=waitpid(getpid(),&status,0);
  printf("%s\n",strerror(errno));
}

