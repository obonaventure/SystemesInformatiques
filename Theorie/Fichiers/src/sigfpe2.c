/**************************************
 * sigfpe.c
 *
 * Programme d'exemple de signal sigfpe
 * handler incorrect
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

static void sigfpe_handler(int);

int main (int argc, char *argv[])  {

  int n=1252;
  void (*handler)(int);

  handler=signal(SIGFPE,sigfpe_handler);
  if(handler==SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }

  for(int i=1;i<argc;i++) {
    char *endptr;
    printf("Traitement de argv[%d]=%s\n",i,argv[i]);
    fflush(stdout);
    long val=strtol(argv[i],&endptr,10);
    if(*endptr=='\0') {
      int resultat=n/(int) val;
      printf("%d/%d=%d\n",n,(int) val,resultat);
    }
    else {
      printf("Argument incorrect : %s\n",argv[i]);
    }
  }
  return(EXIT_SUCCESS);
}

static void sigfpe_handler(int signum) {
  char *msg="Signal SIGFPE reçu\n";
  write(STDOUT_FILENO,msg,strlen(msg));

}

///BBB
