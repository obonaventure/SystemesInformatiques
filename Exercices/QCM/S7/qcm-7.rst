.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. raw:: html

  <script type="text/javascript" src="js/jquery-1.7.2.min.js"></script>
  <script type="text/javascript" src="js/jquery-shuffle.js"></script>
  <script type="text/javascript" src="js/rst-form.js"></script>
  <script type="text/javascript" src="js/prettify.js"></script>
  <script type="text/javascript">$nmbr_prop = 4</script>


================
Septième semaine
================


Question 1. Utilisation des sémaphores
--------------------------------------

Avant d'être utilisé, un sémaphore doit être déclaré et initialisé. Après son utilisation, il doit être détruit. Parmi les séquences d'instructions ci-dessous, une seule initialise correctement un sémaphore à la valeur 1. Laquelle ?

.. class:: positive

-
 .. code-block:: console

    sem_t semaphore;

    sem_init(&semaphore, 0,1);

    // ...

    sem_destroy(&semaphore);


-
 .. code-block:: console

    sem_t *semaphore;
    semaphore=(sem_t *)malloc(sizeof(struct sem_t));
    if (semaphore==NULL)
       error("malloc");

    sem_init(semaphore, 0,1);

    // ...

    sem_destroy(semaphore);


.. class:: negative

-
 .. code-block:: console

    sem_t semaphore;

    sem_init(semaphore, 1,0);

    // ...

    sem_destroy(semaphore);

 .. class:: comment

    `sem_init(3)`_ et `sem_destroy(3)`_ prennent comme premier argument un pointeur vers une structure ``sem_t``. `sem_init(3)`_ prend comme troisième argument la valeur initiale du sémaphore.

-
 .. code-block:: console

    sem_t semaphore;

    sem_init(&semaphore, 1,0);

    // ...

    sem_destroy(&semaphore);

 .. class:: comment

    `sem_init(3)`_ prend comme troisième argument la valeur initiale du sémaphore.

-
 .. code-block:: console

    sem_t *semaphore;
    semaphore=(sem_t *)malloc(sizeof(struct sem_t));
    if (semaphore==NULL)
       error("malloc");

    sem_init(semaphore, 1, 0);

    // ...

    sem_destroy(semaphore);

 .. class:: comment

    `sem_init(3)`_ prend comme troisième argument la valeur initiale du sémaphore.


-
 .. code-block:: console

    sem_t *semaphore;
    semaphore=(sem_t *)malloc(sizeof(struct sem_t));
    if (semaphore==NULL)
       error("malloc");

    sem_init(semaphore, 1, 0);

    // ...

    sem_destroy(&semaphore);

 .. class:: comment

    `sem_init(3)`_ prend comme troisième argument la valeur initiale du sémaphore. `sem_destroy(3)`_ prend comme premier argument un pointeur vers une structure ``sem_t``.



Question 2. Exclusion mutuelle
------------------------------

Les sémaphores peuvent être utilisés tout comme les mutex pour résoudre des problèmes d'exclusion mutuelle. Parmi les extraits de programmes ci-dessous, une seule est une solution correcte au problème de l'exclusion mutuelle en utilisant des sémaphores. Laquelle ?

.. class:: positive

-
 .. code-block:: console


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
-
 .. code-block:: console


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

.. class:: negative

-
 .. code-block:: console


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

 .. class:: comment

    Pour résoudre un problème d'exclusion mutuelle, il faut initialiser le sémaphore à ``1`` avec `sem_init(3)`_ et non à ``0`` comme dans cet exemple.

-
 .. code-block:: console


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

 .. class:: comment

    Pour résoudre un problème d'exclusion mutuelle, il faut initialiser le sémaphore à ``1`` avec `sem_init(3)`_ et non à ``0`` comme dans cet exemple. En outre, l'accès à la section critique doit être précédée par un appel à `sem_wait(3)`_  et suivie par un appel à `sem_post(3)`_ et non l'inverse comme dans cet exemple.

-
 .. code-block:: console


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

 .. class:: comment

    Pour résoudre un problème d'exclusion mutuelle, il faut initialiser le sémaphore à ``1`` avec `sem_init(3)`_ et non à ``0`` comme dans cet exemple.

-
 .. code-block:: console


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

 .. class:: comment

    Pour résoudre un problème d'exclusion mutuelle, il faut initialiser le sémaphore à ``1`` avec `sem_init(3)`_ et non à ``0`` comme dans cet exemple. En outre, l'accès à la section critique doit être précédée par un appel à `sem_wait(3)`_  et suivie par un appel à `sem_post(3)`_ et non l'inverse comme dans cet exemple.



Question 3. Fonctions 'thread-safe'
-----------------------------------

La plupart des fonctions de la librairie standard sont des fonctions thread-safe, c'est-à-dire des fonctions que l'on peut utiliser dans plusieurs threads distincts sans risquer de problèmes d'accès concurrent. Cependant, certaines fonctions, souvent parmi les plus anciennes, ne sont pas thread-safe. Parmi les fonctions ci-dessous, une seule est thread-safe. Laquelle ?

.. class:: positive

- `gettimeofday(2)`_

   .. class:: comment

      Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

- `strsep(3)`_

   .. class:: comment

      Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

.. class:: negative

- `getenv(3)`_

   .. class:: comment

      Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

- `getopt(3)`_

   .. class:: comment

      Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

- `asctime(3)`_

   .. class:: comment

      Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

- `strtok(3)`_

   .. class:: comment

      Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

- `strerror(3)`_

   .. class:: comment

      Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.

- `getopt(3)`_

   .. class:: comment

      Les fonctions qui ne sont pas thread-safe sont listées dans `pthreads(7)`_.



.. include:: ../../../links.rst
.. include:: ../../../man_links.rst
.. include:: ../../../incl_links.rst
