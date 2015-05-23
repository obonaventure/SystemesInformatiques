.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. raw:: html

  <script type="text/javascript" src="js/jquery-1.7.2.min.js"></script>
  <script type="text/javascript" src="js/jquery-shuffle.js"></script>
  <script type="text/javascript" src="js/rst-form.js"></script>
  <script type="text/javascript" src="js/prettify.js"></script>
  <script type="text/javascript">$nmbr_prop = 3</script>


===============
Sixième Semaine
===============

Cette semaine porte sur la communication et la synchronisation entre threads. Plus précisément, la matière est décrite dans les deux sections suivantes :


.. - :ref:`complementsC`

- `Communication entre threads <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Threads/threads2.html>`_
- `Coordination entre threads <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Threads/threads2.html#coordination-entre-threads>`_

.. - :ref:`thread`

Question 1. Algorithme de Peterson
----------------------------------

L'algorithme de Peterson peut s'écrire de différentes façons. Pour bien comprendre son fonctionnement, il est utile de réfléchir à d'autres formulations que celle utilisées dans le syllabus. Parmi les fragments de code ci-dessous, un seul implémente correctement l'algorithme de Peterson. Lequel ?


.. class:: positive

-
 .. code-block:: console

    /* initialisation */
    bool in1 = false;
    bool in2 = false;
    int last = 1;
    // thread 1
    while (true) {
      in1 = true;
      last = 1;
      while ( in2 &&  (last==1)) {};
      section_critique();
      in1=false;
      // ...
     }
     // thread2
     while (true) {
      in2 = true;
      last = 2;
      while ( in1 &&  (last==2)) {};
      section_critique();
      in2=false;
      // ...
     }

-
 .. code-block:: console

    /* initialisation */
    bool in1 = false;
    bool in2 = false;
    int last = 2;
    // thread 1
    while (true) {
      in1 = true;
      last = 1;
      while ( in2 &&  (last==1)) {};
      section_critique();
      in1=false;
      // ...
     }
     // thread2
     while (true) {
      in2 = true;
      last = 2;
      while ( in1 &&  (last==2)) {};
      section_critique();
      in2=false;
      // ...
     }

.. class:: negative

-
 .. code-block:: console

    // initialisation
    bool in1 = false;
    bool in2 = false;
    int last = 1;
    // thread 1
    while (true) {
      in1 = true;
      last = 1;
      while ( in1 &&  (last==1)) {};
      section_critique();
      in1=false;
      // ...
     }
     // thread2
     while (true) {
      in2 = true;
      last = 2;
      while ( in2 &&  (last==2)) {};
      section_critique();
      in2=false;
      // ...
     }

 .. class:: comment

    Cette solution ne fonctionne pas. Si un des deux threads est seul, il n'entrera jamais en section critique.

-
 .. code-block:: console

    // initialisation
    bool in1 = false;
    bool in2 = false;
    int last = 2;
    // thread 1
    while (true) {
      in1 = true;
      last = 1;
      while ( in2 &&  (last==2)) {};
      section_critique();
      in1=false;
      // ...
     }
     // thread2
     while (true) {
      in2 = true;
      last = 2;
      while ( in1 &&  (last==1)) {};
      section_critique();
      in2=false;
      // ...
     }

 .. class:: comment

    Cette solution ne fonctionne pas. Il est possible que le thread 1 rentre en section critique puis le thread 2 met ``last`` à 2 et peut également y entrer sans que thread 1 n'en soit sorti.

-
 .. code-block:: console

    // initialisation
    bool in1 = false;
    bool in2 = false;
    int last = 1;
    // thread 1
    while (true) {
      last = 1;
      in1 = true;
      while ( in2 &&  (last==1)) {};
      section_critique();
      in1=false;
      // ...
     }
     // thread2
     while (true) {
      last = 2;
      in2 = true;
      while ( in1 &&  (last==2)) {};
      section_critique();
      in2=false;
      // ...
     }

 .. class:: comment

    Cette solution ne fonctionne pas. Il y a un risque de violation de section critique. Si le thread 1 fait ``last=1;`` puis est interrompu avant de faire ``in1=true;``. Le thread 2 exécute alors ``last=2;`` suivi de ``in2=true;``. A cet instant, ``in2==false`` et le thread 2 rentre en section critique puisque ``in1==false``. Le thread 1 se réveille et exécute ``in1=true;``. Il peut ensuite immédiatement entre en section critique puisque ``last`` vaut ``2`` à cet instant.

Question 2. Initialisation de mutex
-----------------------------------

Avant de pouvoir utiliser un mutex POSIX, il est nécessaire de déclarer la structure correspondante et initialiser le mutex. Parmi les fragments de code ci-dessous, lequel est celui qui déclare et initialise correctement un mutex ?

.. class:: positive

-
 .. code-block:: console

   pthread_mutex_t mutex;
   pthread_mutexattr_t attr;

   err= pthread_mutexattr_init(&attr);
   if(err!=0)
     error(err,"pthread_mutexattr_init");

   err=pthread_mutex_init( &mutex, &attr);
   if(err!=0)
     error(err,"pthread_mutex_init");

 .. class:: comment

    Notez que dans ce cas, le mutex est initialisé avec les attributs par défaut.


-
 .. code-block:: console

   pthread_mutex_t mutex;

   err=pthread_mutex_init( &mutex, NULL);
   if(err!=0)
     error(err,"pthread_mutex_init");

 .. class:: comment

    Notez que dans ce cas, le mutex est initialisé avec les attributs par défaut.

.. class:: negative

-
 .. code-block:: console

   pthread_mutex_t mutex;
   pthread_mutexattr_t attr;

   err= pthread_mutexattr_init(attr);
   if(err!=0)
     error(err,"pthread_mutexattr_init");

   err=pthread_mutex_init(mutex, attr);
   if(err!=0)
     error(err,"pthread_mutex_init");

 .. class:: comment

    Tant `pthread_mutexattr_init(3posix)`_ que `pthread_mutex_init(3posix)`_ prennent comme arguments un *pointeur* vers une structure de type ``pthread_mutex_t``. Ces deux fonctions modifient le contenu de cette structure et doivent donc en recevoir l'adresse comme argument.



-
 .. code-block:: console

   pthread_mutex_t mutex;
   pthread_mutexattr_t attr;

   err= pthread_mutexattr_init(&attr);
   if(err!=0)
     error(err,"pthread_mutexattr_init");

   err=pthread_mutex_init(&mutex, attr);
   if(err!=0)
     error(err,"pthread_mutex_init");

 .. class:: comment

    Tant `pthread_mutexattr_init(3posix)`_ que `pthread_mutex_init(3posix)`_ prennent comme arguments un *pointeur* vers une structure de type ``pthread_mutex_t``. Ces deux fonctions modifient le contenu de cette structure et doivent donc en recevoir l'adresse comme argument.


-
 .. code-block:: console

   pthread_mutex_t *mutex;
   pthread_mutexattr_t *attr;

   err= pthread_mutexattr_init(attr);
   if(err!=0)
     error(err,"pthread_attr_init");

   err=pthread_mutex_init(mutex, attr);
   if(err!=0)
     error(err,"pthread_mutex_init");

 .. class:: comment

    Tant `pthread_mutexattr_init(3posix)`_ que `pthread_mutex_init(3posix)`_ prennent comme arguments un *pointeur* vers une structure de type ``pthread_mutex_t``. La mémoire permettant de stocker ces deux structures doit avoir été réservée en utilisant `malloc(3)`_ avant de faire appel à ces deux fonctions.



Question 3. Utilisation de `pthread_mutex_lock(3posix)`_ et `pthread_mutex_unlock(3posix)`_
-------------------------------------------------------------------------------------------

Un programme utilisant plusieurs threads doit mettre à jour une variable globale partagée entre tous les threads. Pour cela, le développeur écrit une fonction ``update`` qui prend comme arguments la variable à mettre à jour et le mutex qui y est associé. Parmi les extraits ci-dessous, lequel permet de mettre à jour la variable sans risque de contention entre les threads qui y accèdent ?

.. class:: positive

-
  .. code-block:: console

     void update(int * val, pthread_mutex_t * mutex) {

     err=pthread_mutex_lock(mutex);
     if(err!=0)
       error(err,"pthread_mutex_lock");

     // mise à jour de la variable globale

     err=pthread_mutex_unlock(mutex);
     if(err!=0)
       error(err,"pthread_mutex_unlock");

     }


.. class:: negative

-
  .. code-block:: console

     void update(int * val, pthread_mutex_t * mutex) {

     err=pthread_mutex_unlock(mutex);
     if(err!=0)
       error(err,"pthread_mutex_unlock");

     // mise à jour de la variable globale

     err=pthread_mutex_lock(mutex);
     if(err!=0)
       error(err,"pthread_mutex_lock");

     }

  .. class:: comment

     Ce code est incorrect. Un mutex s'utilise en faisant d'abord ``pthread_mutex_lock`` et ensuite ``pthread_mutex_unlock``.

-
  .. code-block:: console

     void update(int val, pthread_mutex_t mutex) {

     err=pthread_mutex_lock(mutex);
     if(err!=0)
       error(err,"pthread_mutex_lock");

     // mise à jour de la variable globale

     err=pthread_mutex_unlock(mutex);
     if(err!=0)
       error(err,"pthread_mutex_unlock");

     }

  .. class:: comment

     L'utilisation de cette fonction implique que la structure ``pthread_mutex_t`` doit être copiée sur le stack avant de pouvoir être utilisée par la fonction. Cette solution ne peut fonctionner car la structure de données qui contient toute l'information relative à un mutex et placée à un endroit donné en mémoire et ne peut pas être copiée.



-
  .. code-block:: console

     void update(int * val, pthread_mutex_t mutex) {

     err=pthread_mutex_lock(&mutex);
     if(err!=0)
       error(err,"pthread_mutex_lock");

     // mise à jour de la variable globale

     err=pthread_mutex_unlock(&mutex);
     if(err!=0)
       error(err,"pthread_mutex_unlock");

     }

  .. class:: comment

     L'utilisation de cette fonction implique que la structure ``pthread_mutex_t`` doit être copiée sur le stack avant de pouvoir être utilisée par la fonction. Cette solution ne peut fonctionner car la structure de données qui contient toute l'information relative à un mutex et placée à un endroit donné en mémoire et ne peut pas être copiée.



Question 4. Utilisation de plusieurs mutex
------------------------------------------

Dans certains programmes, il est nécessaire de définir plusieurs mutex qui sont utilisés par différents threads pour gérer l'accès à des variables partagées. Considérons un programme qui utilise trois variables globales et est découpé en plusieurs threads.

.. code-block:: console

   long a=5;   // variable globale partagée
   long b=7;   // variable globale partagée
   long c=9;   // variable globale partagée

   pthread_mutex_t x; // variable globale associée à a
   pthread_mutex_t y; // variable globale associée à b
   pthread_mutex_t z; // variable globale associée à c


   void update(int * val1, int * val2, pthread_mutex_t * mutex1, pthread_mutex_t * mutex2) {

     err=pthread_mutex_lock(mutex1);
     if(err!=0)
       error(err,"pthread_mutex_lock");
     err=pthread_mutex_lock(mutex2);
     if(err!=0)
       error(err,"pthread_mutex_lock");

      // mise à jour val1
      // mise à jour val2

     err=pthread_mutex_unlock(mutex1);
     if(err!=0)
       error(err,"pthread_mutex_unlock");

     err=pthread_mutex_unlock(mutex2);
     if(err!=0)
       error(err,"pthread_mutex_unlock");

   }

Ce programme utilise plusieurs threads qui modifient les variables ``a``, ``b`` et ``c``. Parmi les fragments de code ci-dessous qui utilisent plusieurs threads, un seul est correct. Lequel ?

.. class:: positive

-
  .. code-block:: console

     // thread A

     update(&a,&b,&x,&y);
     update(&a,&c,&x,&z);

     // thread B

     update(&b,&c,&y,&z);
     update(&a,&c,&x,&z);


-
  .. code-block:: console

     // thread A

     update(&a,&b,&x,&y);
     update(&b,&c,&y,&z);

     // thread B

     update(&b,&c,&y,&z);
     update(&a,&c,&x,&z);


.. class:: negative

-
  .. code-block:: console

     // thread A

     update(&a,&b,&x,&y);
     update(&c,&a,&z,&x);

     // thread B

     update(&b,&c,&y,&z);
     update(&a,&c,&x,&z);

  .. class:: comment

     Lorsqu'un thread utilise plusieurs ressources protégées par un mutex, il est important que les accès à ces mutex se fassent chaque fois dans le même ordre. Dans cet exemple, il faut toujours accéder à ``x`` puis à ``y`` puis à ``z`` (ou un autre ordre). Accéder à ``z``  puis à ``x`` dans le thread A et à ``x`` puis à ``z`` dans le thread B est une source de deadlocks potentiels.


-
  .. code-block:: console

     // thread A

     update(&a,&b,&x,&y);
     update(&a,&c,&x,&z);

     // thread B

     update(&b,&c,&y,&z);
     update(&c,&a,&z,&x);

  .. class:: comment

     Lorsqu'un thread utilise plusieurs ressources protégées par un mutex, il est important que les accès à ces mutex se fassent chaque fois dans le même ordre. Dans cet exemple, il faut toujours accéder à ``x`` puis à ``y`` puis à ``z`` (ou un autre ordre). Accéder à ``z``  puis à ``x`` dans le thread B et à ``x`` puis à ``z`` dans le thread A est une source de deadlocks potentiels.

-
  .. code-block:: console

     // thread A

     update(&a,&b,&x,&y);
     update(&a,&b,&x,&y);

     // thread B

     update(&b,&a,&y,&x);
     update(&a,&c,&x,&z);

  .. class:: comment

     Lorsqu'un thread utilise plusieurs ressources protégées par un mutex, il est important que les accès à ces mutex se fassent chaque fois dans le même ordre. Dans cet exemple, il faut toujours accéder à ``x`` puis à ``y`` puis à ``z`` (ou un autre ordre). Accéder à ``a``  puis à ``y`` dans le thread A et à ``y`` puis à ``x`` dans le thread B est une source de deadlocks potentiels.


.. include:: ../../../links.rst
.. include:: ../../../man_links.rst
.. include:: ../../../incl_links.rst
