/**************************************
 * execbomb.c
 *
 * Programme qui ne se termine jamais
 *
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void f1() {
  /*  ok
  char *arguments[]={"echo", "-n", "SINF1252", NULL};
  char *environnement[]={"LANG=fr",NULL};
  int err=execve("/bin/echo", arguments, environnement);
  if(err!=0) {
    perror("execve");
    exit(EXIT_FAILURE);
  }

  */

  /* ok
  char prog[]="echo";
  char param1[]="-n";
  char param2[]="SINF1252";
  char *arguments[4];
  arguments[0]=prog;
  arguments[1]=param1;
  arguments[2]=param2;
  arguments[3]=NULL;
  char *environnement[]={"LANG=fr"};
  int err=execve("/bin/echo", arguments, environnement);
  if(err!=0) {
    perror("execve");
    exit(EXIT_FAILURE);
  }
  */

}


extern char **environ;

int main (int argc, char *argv[])  {

  f1();
}

