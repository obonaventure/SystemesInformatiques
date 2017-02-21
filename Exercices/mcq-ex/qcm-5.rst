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


Question 2. Pointeurs et tableaux
---------------------------------

Les pointeurs peuvent être utilisés pour accéder à des tableaux. Considérons un fragment de code C utilisant un tableau d'entiers à une dimension :

.. code-block:: c

   int a[]={2,4,3,4,8};
   int * ptr;

   printf("%d %d %d %d\n",a[0],a[1],a[2],a[a[3]]);


Lors de son exécution, ce programme affiche ``2 4 3 8`` sur sa sortie standard.

.. question:: ptr-tableaux
   :nb_prop: 3
   :nb_pos: 1

   Après exécution de ``ptr=&(a[0]);``, une seule des instructions ci-dessous affiche la même séquence de chiffres. Laquelle ?

   .. positive::


      .. code-block:: c

         printf("%d %d %d %d\n",*ptr,*(ptr+1),*(ptr+2),*(ptr+*(ptr+3)));

   .. negative::

      .. code-block:: c

         printf("%d %d %d %d\n",*ptr,*ptr+1,*ptr+2,*(ptr+*(ptr+3)));

      .. comment::

            Cette ligne affiche ``2 3 4 8``. Sur base des règles de précédence entre les opérations, l'expression ``*ptr+1`` équivaut en fait à ``(*ptr)+1``. En cas de doute, utilisez les parenthèses.


   .. negative::

      .. code-block:: c

         printf("%d %d %d %d\n",*ptr,*(ptr++),(*ptr++),*(ptr+*(ptr++)));

      .. comment::

            Cette ligne affiche ``2 2 4 ???``. La dernière expression ``*(ptr+*(ptr++))`` accède une zone de mémoire en dehors du tableau et dont la valeur est inconnue (notez que la valeur de ``ptr++`` est la valeur de ptr AVANT l'incrémentation, contrairement à ``++ptr``).

   .. negative::

      .. code-block:: c

         printf("%d %d %d %d\n",*ptr,*(ptr+0),*(ptr+1),*ptr+*(ptr+2));

      .. comment::

            Cette ligne affiche ``2 2 4 5``. ``*(ptr+0)`` est ``a[0]`` et non ``a[1]``.

   .. negative::

      .. code-block:: c

         printf("%d %d %d %d\n",*ptr,*ptr+1,(*ptr+1),*(ptr+(ptr+3)));

      .. comment::

            Cette ligne est syntaxiquement invalide. L'expression ``ptr+(ptr+3)`` est invalide. On ne peut pas additionner deux pointeurs.



Question 3. Traitement de ``argv``
----------------------------------

Un programme C doit souvent pouvoir manipuler les arguments qui lui sont passés. Les variables ``argc`` et ``argv`` qui sont passées à la fonction ``main`` permettent d'accéder à ces arguments. Le fragment de programme ci-dessous affiche sur la sortie standard ses différents arguments.

.. code-block:: c

  while(i<argc) {
    printf("%d %p %s\n",i,&(argv[i]),argv[i]);
    i++;
  }

Un exemple d'exécution de ce fragment de programme est présenté ci-dessous :

.. code-block:: console

   #./a.out a b cd
   0 0x7fff5fbff788 ./a.out
   1 0x7fff5fbff790 a
   2 0x7fff5fbff798 b
   3 0x7fff5fbff7a0 cd

.. question:: argv
   :nb_prop: 3
   :nb_pos: 1

   A côté de la notation ``argv[i]``, il est aussi possible d'accéder à ``argv`` en utilisant des pointeurs. Parmi les fragments de programme ci-dessous, un seul est correct et affiche le même résultat que ci-dessus.

   .. positive::


      .. code-block:: c

          char **ptr;
          int i=0;
          ptr=argv;
          while(i<argc) {
            printf("%d %p %s\n",i,&(*ptr),*ptr);
            i++;
            ptr++;
          }


   .. negative::

      .. code-block:: c

         char **ptr;
         int i=0;
         ptr=argv;
         while(i<argc) {
           printf("%d %p %s\n",i,&(ptr),*ptr);
           i++;
           ptr++;
         }


      .. comment::

            ``&(ptr)`` est l'adresse à laquelle le pointeur ``ptr`` est stocké. Notez que ce n'est pas l'adresse à laquelle la chaîne de caractère argument ``i`` est stockée. Ce programme affiche :

            .. code-block:: console

               0 0x7fff5fbff738 ./a.out
               1 0x7fff5fbff738 a
               2 0x7fff5fbff738 b
               3 0x7fff5fbff738 cd

   .. negative::

      .. code-block:: c

         char *ptr;
         int i=0;
         ptr=*argv;
         while(i<argc) {
           printf("%d %p %s\n",i,&(ptr),*ptr);
           i++;
           ptr++;
         }

      .. comment::

            Notez dans ce code que ``ptr`` est déclaré comme ``char *``, alors que ``argv`` est un ``char **``. Si vous tenez d'exécutez ce code, il provoquera un segmentation fault.

   .. negative::

      .. code-block:: c

         int i=0;
         while(i<argc) {
            printf("%d %p %s\n",i,&(argv+i),*(argv+i));
            i++;
         }

      .. comment::

            La compilation de ce fragment de programme provoque un warning. L'expression ``&(argv+i)`` est invalide car ``argv`` est un pointeur (de type ``char **``) et donc ``argv+i`` est également une adresse en mémoire et l'opérateur ``&`` ne peut pas s'y appliquer.

   .. negative::

      .. code-block:: c

         int i=0;
         while(i<argc) {
           printf("%d %p %s\n",i,&(*(argv+i)),(argv+i));
           i++;
         }


      .. comment::

            Dans ce fragment de code, ``argv+i`` est de type ``char **`` alors qu'il faut un ``char *`` pour passer un string  à `printf(3)`_.



Question 4. Pointeurs et tableaux à deux dimensions
---------------------------------------------------

En C, il est possible d'accéder aux données stockées dans un tableau à deux dimensions via la notation ``a[i][j]`` mais aussi en utilisant des pointeurs. Considérons le fragment de code ci-dessous :

.. code-block:: c

   int m[3][4]= { { 1, 2, 3, 4} ,
   		  { 5, 6, 7, 8} ,
 		  { 9, 10, 11, 12} };

   printf("%p %d %d %d\n",m, m[1][2], m[0][5], m[2][2]);


Un compilateur Java n'accepterait pas de compiler ce programme qui tente d'accéder à l'élément ``m[0][5]`` de la matrice, élément qui n'existe pas sur base de l'initialisation du tableau ``m``. De nombreux compilateurs C acceptent ce fragment de code sans contrainte. Lorsque le programme s'exécute il affiche :

.. code-block:: console

   0x7fff5fbff750 7 6 11

.. question:: ptr-tableaux2d
   :nb_prop: 3
   :nb_pos: 1

   Parmi les fragments de programme ci-dessous, un seul utilisant la notation avec les pointeurs est correct et affiche la même sortie. Lequel ?

   .. positive::


      .. code-block:: c

         int *ptr;

         ptr=&(m[0][0]);
         printf("%p %d %d %d\n",ptr, *(ptr+4*1+2), *(ptr+4*0+5), *(ptr+2*4+2));


   .. negative::

      .. code-block:: c

         int **ptr=m;
         printf("%p %d %d %d\n",ptr, *(ptr+4*1+2), *(ptr+4*0+5), *(ptr+2*4+2));

      .. comment::

            La déclaration ``int **ptr=m`` est invalide.

   .. negative::

      .. code-block:: c

         int *ptr=m;
         printf("%p %d %d %d\n",ptr, *(ptr+4*1+2), *(ptr+4*0+5), *(ptr+2*4+2));


      .. comment::

            La déclaration ``int *ptr=m;`` est invalide, ``m`` n'est pas de type ``int *``.

Question 5. Variable ``errno``
------------------------------
.. question:: errno
   :nb_prop: 3
   :nb_pos: 1

   En C, la variable ``errno`` est utilisée par le système pour fournir une indication sur une erreur qui s'est produite lors de l'exécution d'un appel système ou d'une fonction de la librairie. Parmi les fonctions ci-dessous, une seule ne modifie pas ``errno`` en cas d'erreur. Laquelle ?

   .. positive::

      `getpid(2)`_

      .. comment::

         Voir page de manuel.

   .. negative::

      `malloc(3)`_

      .. comment::

         Notez que `malloc(3)`_ retourne ``NULL`` en cas d'erreur d'allocation mais met ENONMEM comme erreur dans ``errno``

   .. positive::

      `exit(2)`_

      .. comment::

         Comme cette fonction ne se termine jamais, elle ne peux pas modifier ``errno``.

   .. negative::

      `setenv(3)`_

      .. comment::

         Voir page de manuel.

   .. negative::

      `unsetenv(3)`_

      .. comment::

         Voir page de manuel.

   .. negative::

      `pthread_join(3)`_

      .. comment::

         Voir page de manuel et aussi http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_join.html. La plupart des fonctions pthread_* ne modifient pas la valeur de ``errno``, mais le standard n'est pas 100% clair sur ce qu'une implémentation doit faire. Linux ne semble pas fixer la valeur de ``errno``.


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
