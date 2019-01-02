.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Questions à choix multiples 
===========================

:task_id: sinf1252-6

Cette semaine porte sur la communication et la synchronisation entre threads. Plus précisément, la matière est décrite dans les deux sections suivantes :

 - :ref:`theorie:threads` (sauf la section `Utilisation d'instruction atomique`)
 - :ref:`theorie:comthreads` (jusqu'à la section `Le problème des philosophes`) 

..  - `Communication entre threads <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Threads/threads2.html>`_
.. - `Coordination entre threads <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Threads/threads2.html#coordination-entre-threads>`_




Question 1. Utilisation de `pthread_create(3)`_
------------------------------------------------


.. question:: pthread_create 
   :nb_prop: 3 
   :nb_pos: 1 


   La fonction `pthread_create(3)`_ permet de créer un thread. Parmi les fragments de code ci-dessous, un seul crée correctement un thread qui appelle la fonction ``f`` en lui passant la chaîne de caractères ``s`` comme argument. Lequel ?

   .. positive::

      .. code-block:: c 

         void * f( void * param) {
          // incomplet 
          return NULL;
         }

         int main (int argc, char *argv[])  {

           pthread_t t;
           int err;
           char *s;
           err=pthread_create(&t,NULL,&(f),(void *) s);
         }


   .. negative::

      .. code-block:: c 

         void * f (void * param) {
          // incomplet 
          return NULL;
         }

         int main (int argc, char *argv[])  {

           pthread_t t;
           int err;
           char *s;
           err=pthread_create(&t,NULL,&(f),(void *) &s);
         }

      .. comment:: Ce fragment contient une erreur. La fonction ``f`` a la bonne signature, mais le dernier argument à `pthread_create(3)`_ doit être de type ``void *``, or ``s`` est un ``char *`` et donc ce dernier argument doit être ``(void *) s``. 

   .. negative::

      .. code-block:: c 

         void f(void * param) {
          // incomplet 
          return NULL;
         }

         int main (int argc, char *argv[])  {

          pthread_t *t;
          int err;
          char *s;
          err=pthread_create(t,NULL,*f,(void *) *s);
         }

      .. comment:: Ce fragment contient plusieurs erreurs. La fonction ``f`` n'a pas la bonne signature (d'ailleurs ``return NULL;`` pour une fonction ``void`` est incorrect). Ensuite, l'appel à `pthread_create(3)`_ doit prendre comme premier argument l'adresse vers une structure de type ``pthread_t`` qui est stockée en mémoire. Ce n'est pas le cas ici. Les troisième et quatrième arguments sont également incorrects.

   .. negative::

      .. code-block:: c


         void *f(void ** param) {
          // incomplet
          return NULL;
         }

         int main (int argc, char *argv[])  {

           pthread_t t;
           int err;
           char s;
           err=pthread_create(&t,NULL,&(f),(void *) s);
         }

      .. comment:: Dans ce fragment de code, la signature de la fonction ``f`` ainsi que l'appel à `pthread_create(3)`_ sont incorrects.



Question 2. Passage d'arguments à un thread
-------------------------------------------

Considérons un thread qui a pour objectif de convertir une fraction en un nombre en virgule flottante. Ce n'est pas une bonne utilisation de threads puisque le calcul à effectuer est très simple, mais cela nous permettra de voir comment un thread peut recevoir des arguments directement. En dehors des threads, cette fonction de conversion pourrait s'écrire :

.. code-block:: c

   struct fraction {
     int num;
     int denum;
   };

   typedef struct fraction Fraction_t;

   float tofloat(Fraction_t t) {
     return (float) t.num/ (float) t.denum;
   }

.. question:: argthread
   :nb_prop: 3
   :nb_pos: 1

   Parmi les programmes ci-dessous, un seul calcule correctement la valeur attendue (le test des valeurs de retour des fonctions n'est pas présenté pour garder le code concis). Lequel ?


   .. positive::


      .. code-block:: c

         void *mythread(void * param) {
          Fraction_t *f=(Fraction_t *) param;
          float *r=(float *)malloc(sizeof(float));
          *r=(float) f->num/ (float) f->denum;
          return((void *) r);
         }

         int main (int argc, char *argv[])  {

          pthread_t t;
          Fraction_t f;
          f.num=1;
          f.denum=3;
          float *r;
          int err;

          err=pthread_create(&t,NULL,&mythread,&(f));

          err=pthread_join(t,(void **) &r);

         }


   .. negative::

      .. code-block:: c

         void *mythread(void * param) {
           Fraction_t f= *param;
           float r;
           r=(float) f.num/ (float) f.denum;
           return((void *) &r);
         }

         int main (int argc, char *argv[])  {

           pthread_t t;
           Fraction_t f;
           f.num=1;
           f.denum=3;
           float r;
           int err;

           err=pthread_create(&t,NULL,&mythread,&(f));

           err=pthread_join(t,(void **) &r);

         }

      .. comment:: La fonction ``mythread``  est incorrect. L'initialisation de ``f`` ne fonctionne pas et en plus le résultat de la fonction est une variable locale (``r``) qui disparaît après son exécution. L'adresse de cette variable, même en étant castée en ``void *`` ne peut pas être retournée à la fonction ``main``.

   .. negative::

      .. code-block:: c


         void *mythread(void * param) {
           Fraction_t *t=(Fraction_t *) param;
           float *r=(float *)malloc(sizeof(float));
           *r=(float) t->num/ (float) t->denum;
           return((void *) r);
         }

         int main (int argc, char *argv[])  {

           pthread_t t;
           Fraction_t f;
           f.num=1;
           f.denum=3;
           float r;
           int err;

           err=pthread_create(&t,NULL,&mythread,&f);
           r=pthread_join(t,NULL);

         }

      .. comment:: Dans cette variable, l'appel à `pthread_join(3)`_ est incorrect.

   .. negative::

      .. code-block:: c

         float mythread(Fraction_t param) {
           float *r=(float *)malloc(sizeof(float));
           *r=(float) param->num/ (float) param->denum;
           return(r);
         }

         int main (int argc, char *argv[])  {
           pthread_t t;
           Fraction_t f;
           f.num=1;
           f.denum=3;
           printf("%f \n",tofloat(f));
           float *r;
           int err;

           err=pthread_create(&t,NULL,&mythread,&(f));

           err=pthread_join(t,(void *) &r);
         }

      .. comment:: Cette variante contient deux erreurs. La première est le prototype de la fonction ``mythread``. Celle-ci doit obligatoirement être de type ``void * fct(void * param)``, il n'est pas possible d'utiliser un autre prototype. Ensuite, l'appel à `pthread_join(3)`_ est incorrect puisque le deuxième argument de `pthread_join(3)`_ doit être de type ``void **`` et non ``void *``.


Question 3. Algorithme de Peterson
----------------------------------

.. question:: peterson
   :nb_prop: 3
   :nb_pos: 1

   L'algorithme de Peterson peut s'écrire de différentes façons. Pour bien comprendre son fonctionnement, il est utile de réfléchir à d'autres formulations que celle utilisées dans le syllabus. Parmi les fragments de code ci-dessous, un seul implémente correctement l'algorithme de Peterson. Lequel ?


   .. positive::

      .. code-block:: c

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

   .. positive::

      .. code-block:: c

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

   .. negative::


      .. code-block:: c

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

      .. comment::

         Cette solution ne fonctionne pas. Si un des deux threads est seul, il n'entrera jamais en section critique.

   .. negative::

      .. code-block:: c

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

      .. comment::

         Cette solution ne fonctionne pas. Il est possible que le thread 1 rentre en section critique puis le thread 2 met ``last`` à 2 et peut également y entrer sans que thread 1 n'en soit sorti.

   .. negative::

      .. code-block:: c

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

      .. comment::

         Cette solution ne fonctionne pas. Il y a un risque de violation de section critique. Si le thread 1 fait ``last=1;`` puis est interrompu avant de faire ``in1=true;``. Le thread 2 exécute alors ``last=2;`` suivi de ``in2=true;``. A cet instant, ``in2==false`` et le thread 2 rentre en section critique puisque ``in1==false``. Le thread 1 se réveille et exécute ``in1=true;``. Il peut ensuite immédiatement entre en section critique puisque ``last`` vaut ``2`` à cet instant.

Question 4. Initialisation de mutex
-----------------------------------

.. question:: mutexinit
   :nb_prop: 3
   :nb_pos: 1

   Avant de pouvoir utiliser un mutex POSIX, il est nécessaire de déclarer la structure correspondante et initialiser le mutex. Parmi les fragments de code ci-dessous, lequel est celui qui déclare et initialise correctement un mutex ?

   .. positive::

      .. code-block:: c

        pthread_mutex_t mutex;
        pthread_mutexattr_t attr;

        err= pthread_mutexattr_init(&attr);
        if(err!=0)
          error(err,"pthread_mutexattr_init");

        err=pthread_mutex_init( &mutex, &attr);
        if(err!=0)
          error(err,"pthread_mutex_init");

      .. comment::

         Notez que dans ce cas, le mutex est initialisé avec les attributs par défaut.


   .. positive::

      .. code-block:: c

         pthread_mutex_t mutex;

         err=pthread_mutex_init( &mutex, NULL);
         if(err!=0)
           error(err,"pthread_mutex_init");

      .. comment::

         Notez que dans ce cas, le mutex est initialisé avec les attributs par défaut.

   .. negative::


      .. code-block:: c

         pthread_mutex_t mutex;
         pthread_mutexattr_t attr;

         err= pthread_mutexattr_init(attr);
         if(err!=0)
           error(err,"pthread_mutexattr_init");

         err=pthread_mutex_init(mutex, attr);
         if(err!=0)
           error(err,"pthread_mutex_init");

      .. comment:: Tant `pthread_mutexattr_init(3posix)`_ que `pthread_mutex_init(3posix)`_ prennent comme arguments un *pointeur* vers une structure de type ``pthread_mutex_t``. Ces deux fonctions modifient le contenu de cette structure et doivent donc en recevoir l'adresse comme argument.


   .. negative::

      .. code-block:: c

         pthread_mutex_t mutex;
         pthread_mutexattr_t attr;

         err= pthread_mutexattr_init(&attr);
         if(err!=0)
           error(err,"pthread_mutexattr_init");

         err=pthread_mutex_init(&mutex, attr);
         if(err!=0)
           error(err,"pthread_mutex_init");

      .. comment:: Tant `pthread_mutexattr_init(3posix)`_ que `pthread_mutex_init(3posix)`_ prennent comme arguments un *pointeur* vers une structure de type ``pthread_mutex_t``. Ces deux fonctions modifient le contenu de cette structure et doivent donc en recevoir l'adresse comme argument.


   .. negative::

      .. code-block:: c

         pthread_mutex_t *mutex;
         pthread_mutexattr_t *attr;

         err= pthread_mutexattr_init(attr);
         if(err!=0)
           error(err,"pthread_attr_init");

         err=pthread_mutex_init(mutex, attr);
         if(err!=0)
           error(err,"pthread_mutex_init");

      .. comment:: Tant `pthread_mutexattr_init(3posix)`_ que `pthread_mutex_init(3posix)`_ prennent comme arguments un *pointeur* vers une structure de type ``pthread_mutex_t``. La mémoire permettant de stocker ces deux structures doit avoir été réservée en utilisant `malloc(3)`_ avant de faire appel à ces deux fonctions.



Question 5. Utilisation de `pthread_mutex_lock(3posix)`_ et `pthread_mutex_unlock(3posix)`_
-------------------------------------------------------------------------------------------

.. question:: pthread_mutex_lock
   :nb_prop: 3
   :nb_pos: 1

   Un programme utilisant plusieurs threads doit mettre à jour une variable globale partagée entre tous les threads. Pour cela, le développeur écrit une fonction ``update`` qui prend comme arguments la variable à mettre à jour et le mutex qui y est associé. Parmi les extraits ci-dessous, lequel permet de mettre à jour la variable sans risque de contention entre les threads qui y accèdent ?

   .. positive::


      .. code-block:: c

         void update(int * val, pthread_mutex_t * mutex) {

         err=pthread_mutex_lock(mutex);
         if(err!=0)
           error(err,"pthread_mutex_lock");

         // mise à jour de la variable globale

         err=pthread_mutex_unlock(mutex);
         if(err!=0)
           error(err,"pthread_mutex_unlock");

         }


   .. negative::


      .. code-block:: c

         void update(int * val, pthread_mutex_t * mutex) {

         err=pthread_mutex_unlock(mutex);
         if(err!=0)
           error(err,"pthread_mutex_unlock");

         // mise à jour de la variable globale

         err=pthread_mutex_lock(mutex);
         if(err!=0)
           error(err,"pthread_mutex_lock");

         }

      .. comment:: Ce code est incorrect. Un mutex s'utilise en faisant d'abord ``pthread_mutex_lock`` et ensuite ``pthread_mutex_unlock``.

   .. negative::

      .. code-block:: c

         void update(int val, pthread_mutex_t mutex) {

         err=pthread_mutex_lock(mutex);
         if(err!=0)
           error(err,"pthread_mutex_lock");

         // mise à jour de la variable globale

         err=pthread_mutex_unlock(mutex);
         if(err!=0)
           error(err,"pthread_mutex_unlock");

         }

      .. comment:: L'utilisation de cette fonction implique que la structure ``pthread_mutex_t`` doit être copiée sur le stack avant de pouvoir être utilisée par la fonction. Cette solution ne peut fonctionner car la structure de données qui contient toute l'information relative à un mutex et placée à un endroit donné en mémoire et ne peut pas être copiée.


   .. negative::

      .. code-block:: c

         void update(int * val, pthread_mutex_t mutex) {

         err=pthread_mutex_lock(&mutex);
         if(err!=0)
           error(err,"pthread_mutex_lock");

         // mise à jour de la variable globale

         err=pthread_mutex_unlock(&mutex);
         if(err!=0)
           error(err,"pthread_mutex_unlock");

         }

      .. comment:: L'utilisation de cette fonction implique que la structure ``pthread_mutex_t`` doit être copiée sur le stack avant de pouvoir être utilisée par la fonction. Cette solution ne peut fonctionner car la structure de données qui contient toute l'information relative à un mutex et placée à un endroit donné en mémoire et ne peut pas être copiée.



Question 6. Utilisation de plusieurs mutex
------------------------------------------



Dans certains programmes, il est nécessaire de définir plusieurs mutex qui sont utilisés par différents threads pour gérer l'accès à des variables partagées. Considérons un programme qui utilise trois variables globales et est découpé en plusieurs threads.

.. code-block:: c

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

.. question:: plusieursmutex
   :nb_prop: 3
   :nb_pos: 1

   Ce programme utilise plusieurs threads qui modifient les variables ``a``, ``b`` et ``c``. Parmi les fragments de code ci-dessous qui utilisent plusieurs threads, un seul est correct. Lequel ?

   .. positive::


      .. code-block:: c

         // thread A

         update(&a,&b,&x,&y);
         update(&a,&c,&x,&z);

         // thread B

         update(&b,&c,&y,&z);
         update(&a,&c,&x,&z);


   .. positive::

      .. code-block:: c

         // thread A

         update(&a,&b,&x,&y);
         update(&b,&c,&y,&z);

         // thread B

         update(&b,&c,&y,&z);
         update(&a,&c,&x,&z);


   .. negative::


      .. code-block:: c

         // thread A

         update(&a,&b,&x,&y);
         update(&c,&a,&z,&x);

         // thread B

         update(&b,&c,&y,&z);
         update(&a,&c,&x,&z);

      .. comment:: Lorsqu'un thread utilise plusieurs ressources protégées par un mutex, il est important que les accès à ces mutex se fasse chaque fois dans le même ordre. Dans cet exemple, il faut toujours accéder à ``x`` puis à ``y`` puis à ``z`` (ou un autre ordre). Accéder à ``z``  puis à ``x`` dans le thread A et à ``x`` puis à ``z`` dans le thread B est une source de deadlocks potentiels.

   .. negative::

      .. code-block:: none

         // thread A

         update(&a,&b,&x,&y);
         update(&a,&c,&x,&z);

         // thread B

         update(&b,&c,&y,&z);
         update(&c,&a,&z,&x);

         .. comment:: Lorsqu'un thread utilise plusieurs ressources protégées par un mutex, il est important que les accès à ces mutex se fasse chaque fois dans le même ordre. Dans cet exemple, il faut toujours accéder à ``x`` puis à ``y`` puis à ``z`` (ou un autre ordre). Accéder à ``z``  puis à ``x`` dans le thread B et à ``x`` puis à ``z`` dans le thread A est une source de deadlocks potentiels.

   .. negative::

      .. code-block:: c

         // thread A

         update(&a,&b,&x,&y);
         update(&a,&b,&x,&y);

         // thread B

         update(&b,&a,&y,&x);
         update(&a,&c,&x,&z);

      .. comment:: Lorsqu'un thread utilise plusieurs ressources protégées par un mutex, il est important que les accès à ces mutex se fasse chaque fois dans le même ordre. Dans cet exemple, il faut toujours accéder à ``x`` puis à ``y`` puis à ``z`` (ou un autre ordre). Accéder à ``a``  puis à ``y`` dans le thread A et à ``y`` puis à ``x`` dans le thread B est une source de deadlocks potentiels.

