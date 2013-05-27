/**************************************
 * mmap.c
 *
 * Programme d'exemple d'utilisation de
 * mincore
 *
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <float.h>

void create_file(int n, char *filename)  {
  int fd=open(filename, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
  if(fd==-1) {
    perror("open");
    exit(EXIT_FAILURE);
  }
  for (int i=0;i<n;i++) {
    float f=(float ) i;
    if(write(fd,(void *)&f,sizeof(float)) <0) {
      perror("write");
      exit(EXIT_FAILURE);
    }
  }
  int err=close(fd);
  if (err<0) {
    perror("close");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]) {
    int fd;
    struct stat file_stat;
    void *file_mmap;

    create_file(100,"sinf1252.dat");

    fd = open("sinf1252.dat",O_RDONLY);
    if(fd<0) {
      perror("open");
      exit(EXIT_FAILURE);
    }
    if (fstat(fd, &file_stat)<0) {
      perror("fstat");
      exit(EXIT_FAILURE);
    }
    // fichier est un vecteur d'entiers
    file_mmap = mmap((void *) 0, file_stat.st_size, PROT_READ, MAP_FILE, fd, 0);
    if(file_mmap==NULL) {
      perror("mmap");
      exit(EXIT_FAILURE);
    }
    printf("%p mmap\n",file_mmap);
    float * vector=(float *) file_mmap;
    float min=FLT_MAX;
    for(int i=0;i<file_stat.st_size/sizeof(float);i++) {
      if (*vector<min) {
	min=*vector;
      }
      vector++;
    }
    munmap(file_mmap, file_stat.st_size);
    close(fd);
    return(EXIT_SUCCESS);
}
