/**************************************
 * pthread-rw.c
 *
 * Programme d'exemple de pthread avec
 * readers-writers lock
 *
 **************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#define SIZE 1000000
#define READERS 10
#define WRITERS 2
#define LOOP 10000


pthread_t p[READERS+WRITERS];
pthread_rwlock_t lock;

volatile int v[SIZE];

void *writer( void *arg)
{
  for(int i=0;i<SIZE;i++) {
    pthread_rwlock_wrlock(&lock);
    v[i]=rand()%SIZE;
    pthread_rwlock_wrunlock(&lock);
  }
  // ...
  printf ("Writer %d terminé\n",gettid());
  return(NULL);


}
void* reader ( void* arg )
{
  int result;
  for(int i=0;i<LOOP;i++) {
    int id=rand()%SIZE;
    pthread_rwlock_rdlock(&lock);
    result=v[id];
    pthread_rwlock_rdunlock(&lock);
  }
  // ...
  printf ("Reader %d terminé\n",gettid());
  return(NULL);
}

///BBB
int main ( int argc, char *argv[])
{
   int i;

   srand(getpid());

   pthread_rwlock_init(&lock, 0);

   for (i = 0; i < READERS+WRITERS; i++) {
     if(i<READERS)
       pthread_create(&p[i], NULL, reader, NULL );
     else
       pthread_create(&p[i], NULL, writer, NULL );
   }

   for (i = 0; i < READERS+WRITERS; i++)
     pthread_join(p[i], NULL);

   pthread_rwlock_destroy(&lock);

   return (EXIT_SUCCESS);
}
