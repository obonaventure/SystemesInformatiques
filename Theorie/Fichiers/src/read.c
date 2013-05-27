/**************************************
 * read.c
 *
 * Programme d'exemple d'utilisation de
 * fichiers
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void exit_on_error(char *s) {
  perror(s);
  exit(EXIT_FAILURE);
}

int main (int argc, char *argv[])  {
  int n=1252;
  int n2;
  short ns=1252;
  short ns2;
  long nl=125212521252;
  long nl2;
  float f=12.52;
  float f2;
  char *s="sinf1252";
  char *s2=(char *) malloc(strlen(s)*sizeof(char )+1);
  int err;
  int fd;

  fd=open("test.dat",O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
  if(fd==-1) {
    perror("open");
    exit(EXIT_FAILURE);
  }
  if( write(fd, (void *) s, strlen(s)) == -1 )
    exit_on_error("write s");
  if (write(fd, (void *) &n, sizeof(int )) == -1)
    exit_on_error("write n");
  if (write(fd, (void *) &ns, sizeof(short int))==-1)
    exit_on_error("write ns");
  if (write(fd, (void *) &nl, sizeof(long int))==-1)
    exit_on_error("write nl");
  if (write(fd, (void *) &f, sizeof(float))==-1)
    exit_on_error("write f");
  if (close(fd)==-1)
    exit_on_error("close ");

  // lecture
  fd=open("test.dat",O_RDONLY);
  if(fd==-1) {
    perror("open");
    exit(EXIT_FAILURE);
  }
  printf("Fichier ouvert\n");

  if(read(fd, (void *) s2, strlen(s))==-1)
    exit_on_error("read s");
  printf("Donnée écrite : %s, lue: %s\n",s,s2);

  if(read(fd, (void *) &n2, sizeof(int))==-1)
    exit_on_error("read n");
  printf("Donnée écrite : %d, lue: %d\n",n,n2);

  if(read(fd, (void *) &ns2, sizeof(short))==-1)
    exit_on_error("read ns");
  printf("Donnée écrite : %d, lue: %d\n",ns,ns2);

  if(read(fd, (void *) &nl2, sizeof(long))==-1)
    exit_on_error("read nl");
  printf("Donnée écrite : %ld, lue: %ld\n",nl,nl2);

  if(read(fd, (void *) &f2, sizeof(float))==-1)
    exit_on_error("read f");
  printf("Donnée écrite : %f, lue: %f\n",f,f2);
  err=close(fd);
  if(err==-1){
   perror("close");
    exit(EXIT_FAILURE);
  }

  return(EXIT_SUCCESS);
}
///BBB
