.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Questions à choix multiples
===========================

:task_id: sinf1252-5

Cette semaine porte sur deux modules de théorie. Le premier est la fin du chapitre consacré aux bases du langage C :

 - :ref:`complementsC`

Le second est le début du chapitre consacré aux systèmes multiprocesseurs et l'utilisation de threads en particulier :

 - :ref:`threads`

Question 1. Pointeurs en assembleur
-----------------------------------

Pour comprendre le fonctionnement des pointeurs en C, il est parfois utile de se ramener à la traduction en assembleur de fragments de code C. Considérons les lignes suivantes :

   .. code-block:: c

      int a=1252;
      int * ptr;

      int main(int argc, const char *argv[]) {
          ptr=&a;
      }

.. question:: ptrasm
   :nb_prop: 3
   :nb_pos: 1

   Parmi les séquences d'instructions en assembleur ci-dessous, une seule est la traduction de l'assignation de l'adresse de ``a`` au pointeur ``ptr``. Laquelle

   .. positive::


      .. code-block:: nasm

         leal    a, %eax
         movl    %eax, ptr

   .. negative::


      .. code-block:: nasm

         movl    a, %eax
         movl    ptr, %ecx
         movl    %eax, (%ecx)

      .. comment:: Cette séquence d'instructions est la traduction de ``*ptr=a``.

   .. negative::

      .. code-block:: nasm

         movl    a, %eax
         movl    %eax, ptr

      .. comment:: Cette séquence d'instructions est la traduction de ``ptr=(int )a;``.

   .. negative::


      .. code-block:: nasm

             pushl   %eax
             leal    (%esp), %eax
             movl    a, %ecx
             movl    %ecx, (%esp)
             movl    %eax, ptr
             popl    %eax

      .. comment::

            Cette séquence d'instructions est la traduction de :

            .. code-block:: c

               int b=a;
               ptr=&(b);

   .. negative::


      .. code-block:: nasm

             leal    a, %eax
             addl    $4, %eax
             movl    %eax, ptr

      .. comment::

            Cette séquence d'instructions est la traduction de ``ptr=&a+1;``.



Question 6. Utilisation de `pthread_create(3)`_
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



Question 7. Passage d'arguments à un thread
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


.. include:: ../../links.rst
.. include:: ../../man_links.rst
.. include:: ../../incl_links.rst
