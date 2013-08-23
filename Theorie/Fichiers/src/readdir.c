/**************************************
 * readdir.c
 *
 * Programme d'exemple d'utilisation de
 * répertoires
 *
 *************************************/
///AAA
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void exit_on_error(char *s) {
  perror(s);
  exit(EXIT_FAILURE);
}

int main (int argc, char *argv[])  {

  DIR *dirp;
  struct dirent *dp;
  char name[]=".";
  dirp = opendir(name);
  if(dirp==NULL) {
    exit_on_error("opendir");
  }
  while ((dp = readdir(dirp)) != NULL) {
    printf("%s\n",dp->d_name);
  }
  int err = closedir(dirp);
  if(err<0) {
    exit_on_error("closedir");
  }


}
///BBB
