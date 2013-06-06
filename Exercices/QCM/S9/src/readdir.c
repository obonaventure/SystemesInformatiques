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
  dirp=malloc(sizeof(DIR));
  if(dirp==NULL) {
    return(-1);
  }
  dp=malloc(sizeof(struct dirent));
  if(dp==NULL) {
    return -1;
  }
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


int main (int argc, char *argv[])  {




  DIR *dirp;
  struct dirent *dp;
  dirp=malloc(sizeof(DIR));
  if(dirp==NULL) {
    exit_on_error("malloc");
  }
  dp=malloc(sizeof(struct dirent));
  if(dp==NULL) {
    exit_on_error("malloc");
  }
  char name[]=".";
  dirp = opendir(name);
  if(dirp==NULL) {
    exit_on_error("opendir");
  }
  int count=0;
  while ((dp = readdir(dirp)) != NULL) {
    if (dp->d_type==DT_REG) {
      count++;
    }
  }
  printf ("%d fichiers
  int err = closedir(dirp);
  if(err<0) {
    exit_on_error("closedir");
  }


}
///BBB
