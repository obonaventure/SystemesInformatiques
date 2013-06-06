/**************************************
 * sigfpe.c
 *
 * Programme d'exemple de signal sigfpe
 * fichiers
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

sigjmp_buf buf;

static void sigfpe_handler(int);

int main (int argc, char *argv[])  {

  int n=1252;
  if(signal(SIGFPE,sigfpe_handler)==SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }

  for(int i=1;i<argc;i++) {
    char *endptr;
    int r;
    printf("Traitement de argv[%d]=%s\n",i,argv[i]);
    long val=strtol(argv[i],&endptr,10);
    if(*endptr=='\0') {
      r=sigsetjmp(buf,1);
      if(r==0) {
	int resultat=n/(int) val;
	printf("%d/%d=%d\n",n,(int) val,resultat);
      }
      else {
	printf("%d/%d=NaN\n",n,(int) val);
      }
    }
    else {
      printf("Argument incorrect : %s\n",argv[i]);
    }
  }
  return(EXIT_SUCCESS);
}

static void sigfpe_handler(int signum) {
  // ignorer la donnée et passer à la suivante
  siglongjmp(buf,1);
}

///BBB
