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

/*
 * name!=NULL
 * retourne le nombre de fichiers dans le répertoire name
 * et -1 en cas d'erreur
 */

int nfiles(char * name) {

  DIR *dirp;
  struct dirent *dp;
  dirp = opendir(name);
  if(dirp==NULL) {
    return -1;
  }
  int count=0;
  while ((dp = readdir(dirp)) != NULL) {
    if (dp->d_type==DT_REG) {
      count++;
    }
  }
  int err = closedir(dirp);
  if(err<0) {
    return -1;
  }
  return(count);
}

/*
int nfiles2(char * name) {

  DIR dirp;
  struct dirent dp;
  dirp = opendir(name);
  if(dirp==-1) {
    return -1;
  }
  int count=0;
  while ((dp = readdir(dirp)) != -1) {
    if (dp->d_type==DT_REG) {
      count++;
    }
  }
  int err = closedir(dirp);
  if(err<0) {
    return -1;
  }
  return(count);
}
*/

int main (int argc, char *argv[])  {



  printf("%d \n",nfiles("."));

}
///BBB
