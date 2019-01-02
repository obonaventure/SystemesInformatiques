.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_




Questions à choix multiples
===========================

:task_id: sinf1252-7


Question 1. Utilisation des sémaphores
--------------------------------------

.. question:: sem1
   :nb_prop: 3
   :nb_pos: 1

   Avant d'être utilisé, un sémaphore doit être déclaré et initialisé. Après son utilisation, il doit être détruit. Parmi les séquences d'instructions ci-dessous, une seule initialise correctement un sémaphore à la valeur 1. Laquelle ?

   .. positive::

      .. code-block:: c

           sem_t semaphore;

           sem_init(&semaphore, 0,1);

           // ...

           sem_destroy(&semaphore);


   .. positive

      .. code-block:: c

         sem_t *semaphore;
         semaphore=(sem_t *)malloc(sizeof(struct sem_t));
         if (semaphore==NULL)
            error("malloc");

         sem_init(semaphore, 0,1);

         // ...

         sem_destroy(semaphore);


   .. negative::

      .. code-block:: c

         sem_t semaphore;

         sem_init(semaphore, 1,0);

         // ...

         sem_destroy(semaphore);

      .. comment::

         `sem_init(3)`_ et `sem_destroy(3)`_ prennent comme premier argument un pointeur vers une structure ``sem_t``. `sem_init(3)`_ prend comme troisième argument la valeur initiale du sémaphore.

   .. negative::

      .. code-block:: c

         sem_t semaphore;

         sem_init(&semaphore, 1,0);

         // ...

         sem_destroy(&semaphore);

      .. comment::

         `sem_init(3)`_ prend comme troisième argument la valeur initiale du sémaphore.

   .. negative::

      .. code-block:: c

         sem_t *semaphore;
         semaphore=(sem_t *)malloc(sizeof(struct sem_t));
         if (semaphore==NULL)
            error("malloc");

         sem_init(semaphore, 1, 0);

         // ...

         sem_destroy(semaphore);

      .. comment::

         `sem_init(3)`_ prend comme troisième argument la valeur initiale du sémaphore.


   .. negative::

      .. code-block:: none

         sem_t *semaphore;
         semaphore=(sem_t *)malloc(sizeof(struct sem_t));
         if (semaphore==NULL)
            error("malloc");

         sem_init(semaphore, 1, 0);

         // ...

         sem_destroy(&semaphore);

       .. comment::

          `sem_init(3)`_ prend comme troisième argument la valeur initiale du sémaphore. `sem_destroy(3)`_ prennent comme premier argument un pointeur vers une structure ``sem_t``.


Question 2. Exclusion mutuelle
------------------------------

.. question:: semmutex
   :nb_prop: 3
   :nb_pos: 1

   Les sémaphores peuvent être utilisés tout comme les mutex pour résoudre des problèmes d'exclusion mutuelle. Parmi les extraits de programmes ci-dessous, une seule est une solution correcte au problème de l'exclusion mutuelle en utilisant des sémaphores. Laquelle ?

   .. positive::


      .. code-block:: c


         static sem_t semaphore;
         long global=0;

         int increment(int i) {
            // ...
         }

         void *inc(void * param) {
           for(int j=0;j<1000000;j++) {
             sem_wait(&semaphore);
             global=increment(global);
             sem_post(&semaphore);
           }
         }

         int main (int argc, char *argv[])  {
           pthread_t thread[NTHREADS];
           int err;

           sem_init(&semaphore, 0,1);

           for(int i=0;i<NTHREADS;i++) {
             err=pthread_create(&(thread[i]),NULL,&inc,NULL);
             if(err!=0)
               error(err,"pthread_create");
           }

           // reste non fourni
         }

   .. positive::

      .. code-block:: c


         sem_t * semaphore;
         long global=0;

         int increment(int i) {
            // ...
         }

         void *inc(void * param) {
           for(int j=0;j<1000000;j++) {
             sem_wait(semaphore);
             global=increment(global);
             sem_post(semaphore);
           }
         }

         int main (int argc, char *argv[])  {
           pthread_t thread[NTHREADS];
           int err;
           semaphore=(sem_t *)malloc(sizeof(sem_t))
           if(semaphore==NULL)
             error("malloc");

           sem_init(semaphore, 0,1);

           for(int i=0;i<NTHREADS;i++) {
             err=pthread_create(&(thread[i]),NULL,&inc,NULL);
             if(err!=0)
               error(err,"pthread_create");
           }

           // reste non fourni
         }

   .. negative::


      .. code-block:: c


         static sem_t semaphore;
         long global=0;

         int increment(int i) {
            // ...
         }

         void *inc(void * param) {
           for(int j=0;j<1000000;j++) {
             sem_wait(&semaphore);
             global=increment(global);
             sem_post(&semaphore);
           }
         }

         int main (int argc, char *argv[])  {
           pthread_t thread[NTHREADS];
           int err;

           sem_init(&semaphore, 0,0);

           for(int i=0;i<NTHREADS;i++) {
             err=pthread_create(&(thread[i]),NULL,&inc,NULL);
             if(err!=0)
               error(err,"pthread_create");
           }

           // reste non fourni
         }

      .. comment::

         Pour résoudre un problème d'exclusion mutuelle, il faut initialiser le sémaphore à ``1`` avec `sem_init(3)`_ et non à ``0`` comme dans cet exemple.

   .. negative::

      .. code-block:: c


         static sem_t semaphore;
         long global=0;

         int increment(int i) {
            // ...
         }

         void *inc(void * param) {
           for(int j=0;j<1000000;j++) {
             sem_post(&semaphore);
             global=increment(global);
             sem_wait(&semaphore);
           }
         }

         int main (int argc, char *argv[])  {
           pthread_t thread[NTHREADS];
           int err;

           sem_init(&semaphore, 0,0);

           for(int i=0;i<NTHREADS;i++) {
             err=pthread_create(&(thread[i]),NULL,&inc,NULL);
             if(err!=0)
               error(err,"pthread_create");
           }

           // reste non fourni
         }

      .. comment::

         Pour résoudre un problème d'exclusion mutuelle, il faut initialiser le sémaphore à ``1`` avec `sem_init(3)`_ et non à ``0`` comme dans cet exemple. En outre, l'accès à la section critique doit être précédée par un appel à `sem_wait(3)`_  et suivie par un appel à `sem_post(3)`_ et non l'inverse comme dans cet exemple.

   .. negative::

      .. code-block:: c


         sem_t * semaphore;
         long global=0;

         int increment(int i) {
            // ...
         }

         void *inc(void * param) {
           for(int j=0;j<1000000;j++) {
             sem_wait(semaphore);
             global=increment(global);
             sem_post(semaphore);
           }
         }

         int main (int argc, char *argv[])  {
           pthread_t thread[NTHREADS];
           int err;
           semaphore=(sem_t *)malloc(sizeof(sem_t))
           if(semaphore==NULL)
             error("malloc");

           sem_init(semaphore, 0,0);

           for(int i=0;i<NTHREADS;i++) {
             err=pthread_create(&(thread[i]),NULL,&inc,NULL);
             if(err!=0)
               error(err,"pthread_create");
           }

           // reste non fourni
         }

      .. comment::

         Pour résoudre un problème d'exclusion mutuelle, il faut initialiser le sémaphore à ``1`` avec `sem_init(3)`_ et non à ``0`` comme dans cet exemple.

   .. negative::

      .. code-block:: c


         sem_t * semaphore;
         long global=0;

         int increment(int i) {
            // ...
         }

         void *inc(void * param) {
           for(int j=0;j<1000000;j++) {
             sem_post(semaphore);
             global=increment(global);
             sem_wait(semaphore);
           }
         }

         int main (int argc, char *argv[])  {
           pthread_t thread[NTHREADS];
           int err;
           semaphore=(sem_t *)malloc(sizeof(sem_t))
           if(semaphore==NULL)
             error("malloc");

           sem_init(semaphore, 0,0);

           for(int i=0;i<NTHREADS;i++) {
             err=pthread_create(&(thread[i]),NULL,&inc,NULL);
             if(err!=0)
               error(err,"pthread_create");
           }

           // reste non fourni
         }

      .. comment::

         Pour résoudre un problème d'exclusion mutuelle, il faut initialiser le sémaphore à ``1`` avec `sem_init(3)`_ et non à ``0`` comme dans cet exemple. En outre, l'accès à la section critique doit être précédée par un appel à `sem_wait(3)`_  et suivie par un appel à `sem_post(3)`_ et non l'inverse comme dans cet exemple.



Question 3. Fonctions 'thread-safe'
-----------------------------------

.. question:: threadsafe
   :nb_prop: 3
   :nb_pos: 1

   La plupart des fonctions de la librairie standard sont des fonctions thread-safe, c'est-à-dire des fonctions que l'on peut utiliser dans plusieurs threads distincts sans risquer de problèmes d'accès concurrent. Cependant, certaines fonctions, souvent parmi les plus anciennes, ne sont pas thread-safe. Parmi les fonctions ci-dessous, une seule est thread-safe. Laquelle ?

   .. positive::

      `gettimeofday(2)`_

      .. comment::

         Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

   .. positive::

      `strsep(3)`_

      .. comment::

         Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

   .. negative::

      `getenv(3)`_

      .. comment::

         Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

   .. negative::

      `getopt(3)`_

      .. comment::

         Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

   .. negative::

      `asctime(3)`_

      .. comment::

         Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

   .. negative::

      `strtok(3)`_

      .. comment::

         Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

   .. negative::

      `strerror(3)`_

      .. comment::

         Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

   .. negative::

      `getopt(3)`_

      .. comment::

         Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.


