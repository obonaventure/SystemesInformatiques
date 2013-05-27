/**************************************
 * cp2.c
 *
 * copie de fichier avec mmap
 *
 *************************************/
///AAA
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char *argv[]) {
 int file1, file2;
 void *src, *dst;
 struct stat file_stat;
 char dummy=0;

 if (argc != 3) {
   fprintf(stderr,"Usage : cp2 source dest\n");
   exit(EXIT_FAILURE);
 }
 // ouverture fichier source
 if ((file1 = open (argv[1], O_RDONLY)) < 0) {
   perror("open(source)");
   exit(EXIT_FAILURE);
 }

 if (fstat (file1,&file_stat) < 0) {
   perror("fstat");
   exit(EXIT_FAILURE);
 }
 // ouverture fichier destination
 if ((file2 = open (argv[2], O_RDWR | O_CREAT | O_TRUNC, file_stat.st_mode)) < 0) {
   perror("open(dest)");
   exit(EXIT_FAILURE);
 }

 // le fichier destination doit avoir la même taille que le source
 if (lseek (file2, file_stat.st_size - 1, SEEK_SET) == -1) {
   perror("lseek");
   exit(EXIT_FAILURE);
 }

 // écriture en fin de fichier
 if (write (file2, &dummy, sizeof(char)) != 1) {
   perror("write");
   exit(EXIT_FAILURE);
 }

 // mmap fichier source
 if ((src = mmap (NULL, file_stat.st_size, PROT_READ, MAP_SHARED, file1, 0))  == NULL) {
   perror("mmap(src)");
   exit(EXIT_FAILURE);
 }

 // mmap fichier destination
 if ((dst = mmap (NULL, file_stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, file2, 0)) == NULL) {
   perror("mmap(src)");
   exit(EXIT_FAILURE);
 }

 // copie complète
 memcpy (dst, src, file_stat.st_size);

 // libération mémoire
 if(munmap(src,file_stat.st_size)<0) {
   perror("munmap(src)");
   exit(EXIT_FAILURE);
 }

 if(munmap(dst,file_stat.st_size)<0) {
   perror("munmap(dst)");
   exit(EXIT_FAILURE);
 }
 // fermeture fichiers
 if(close(file1)<0) {
   perror("close(file1)");
   exit(EXIT_FAILURE);
 }

 if(close(file2)<0) {
   perror("close(file2)");
   exit(EXIT_FAILURE);
 }
 return(EXIT_SUCCESS);
}
