.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. raw:: html

  <script type="text/javascript" src="js/jquery-1.7.2.min.js"></script>
  <script type="text/javascript" src="js/jquery-shuffle.js"></script>
  <script type="text/javascript" src="js/rst-form.js"></script>
  <script type="text/javascript" src="js/prettify.js"></script>
  <script type="text/javascript">$nmbr_prop = 3</script>



=================
Troisième semaine
=================

Cette semaine, la matière porte sur l'organisation de la mémoire et l'utilisation des fonctions `malloc(3)`_ et `free(3)`_

 - http://sites.uclouvain.be/SystInfo/notes/Theorie/html/C/malloc.html#organisation-de-la-memoire



Question 1. Portée des variables
--------------------------------

Lorsque l'on écrit un programme C, il est préférable d'éviter d'avoir deux variables qui ont le même nom et peuvent être utilisées dans une fonction. Un étudiant a écrit le programme ci-dessous :

 .. code-block:: c

    #include <stdio.h>
    int i = 1;
    int main(int argc, char * argv[])
    {
     int k;
     printf("A:%d\n", i);
     for(k=0; k<1; k++)
     {
       int i = 2, j = 1252;
       printf("B:%d %d\n", i, j);
       {
         int i = 0;
      	 printf("C:%d %d\n", i, j);
       }
       printf("D:%d\n", i);
     }
     return 0;
    }

Lors de son exécution, ce programme affiche :

.. class:: positive

-
 .. code-block:: console

    A:1
    B:2 1252
    C:0 1252
    D:2


.. class:: negative

- Le programme ne se compile pas, il est interdit de redéfinir la variable globale ``i``.

   .. class:: comment

      On peut redéfinir une variable dans plusieurs niveaux de portée différents, même si il vaut mieux l'éviter.

-
 .. code-block:: console

    A:1
    B:1 1252
    C:1 1252
    D:1

-
 .. code-block:: console

    A:1
    B:2 1252
    C:2 1252
    D:2

-
 .. code-block:: console

    A:1
    B:2 1252
    C:0 1252
    D:0

Question 2. Portée des variables
--------------------------------

L'extrait ci-dessous provient d'un programme écrit par un étudiant.

 .. code-block:: c

    #include <stdio.h>
    int i = 1252;
    void f(int i) {
      // code non fourni
    }
    void g(char* c) {
      // code non fourni
    }
    int main(int argc, char * argv[])
    {
      f(argc);
      g(argv[0]);
    }

Parmi les affirmations suivantes, un seul groupe est correct. Lequel ?

.. class:: positive

-
   - La fonction ``g`` peut accéder à la variable globale ``i`` et modifier sa valeur
   - La fonction ``g`` ne peut lire la valeur de ``argc``
   - La fonction ``f`` ne peut modifier la valeur de la variable globale ``i``

.. class:: negative

-
   - La fonction ``g`` peut lire la variable globale ``i`` mais pas modifier sa valeur
   - La fonction ``g`` ne peut lire la valeur de ``argc``
   - La fonction ``f`` peut modifier la valeur de la variable globale ``i``

   .. class:: comment

      La fonction ``g`` peut accéder à la variable globale ``i`` et modifier sa valeur par contre la fonction ``f`` ne peut pas le faire car elle ne peut accéder qu'à son argument nommé également ``i``.


-
   - La fonction ``f`` peut lire la variable globale ``i`` mais pas modifier sa valeur
   - La fonction ``g`` peut lire la valeur de ``argc``
   - La fonction ``f`` peut modifier la valeur de la variable globale ``i``

   .. class:: comment

      Aucune de ces affirmations n'est vraie


-
   - La fonction ``f`` peut lire la variable globale ``i`` et modifier sa valeur
   - La fonction ``g`` ne peut lire la valeur de ``argc``
   - La fonction ``f`` ne peut modifier la valeur de la variable globale ``i``

   .. class:: comment

      La fonction ``f`` n'a pas accès à la variable globale ``i``.



Question 3. Organisation de la mémoire
--------------------------------------

Considérons le fragment de programme ci-dessous.

 .. code-block:: c

    #include <stdio.h>
    int i,j,k = 1252;        // ligne A
    int tab[1000];           // ligne B
    void f(int i) {          // ligne C
      int j;                 // ligne D
      // code non fourni
    }
    void g(char c) {
      int i;                 // ligne E
      // code non fourni
    }
    int main(int argc, char * argv[])
    {
      int k=1;               // ligne F

      f(argc);
      g('a');
    }


Lors de l'exécution de ce programme, les valeurs des différentes variables sont stockées en mémoire. Un seul des groupes d'affirmations ci-dessous est correct. Lequel ?


.. class:: positive

-
 - la variable ``i`` déclarée et initialisée en ``ligne A`` est stockée dans la zone des variable initialisées
 - l'argument ``i`` déclaré en ``ligne C`` est stocké sur la pile
 - la variable ``j`` déclarée en ``ligne D`` est stockée sur la pile
 - la variable ``k`` déclarée en ``ligne F`` est stockée sur la pile


-
 - la variable ``i`` déclarée et initialisée en ``ligne A`` est stockée dans la zone des variable initialisées
 - le tableau ``tab`` déclaré en ``ligne B`` est stocké dans la zone des variables non-initialisées
 - l'argument ``i`` déclaré en ``ligne C`` est stocké sur la pile
 - la variable ``i`` déclarée en ``ligne E`` est stockée sur la pile



.. class:: negative

-

 - le tableau ``tab`` déclaré en ``ligne B`` est stocké dans la zone des variables initialisées
 - l'argument ``i`` déclaré en ``ligne C`` est stocké sur la pile
 - la variable ``j`` déclarée en ``ligne D`` est stockée sur la pile
 - la variable ``i`` déclarée en ``ligne E`` est stockée sur la pile
 - la variable ``k`` déclarée en ``ligne F`` est stockée dans la zone des variables non-initialisées

-

 - le tableau ``tab`` déclaré en ``ligne B`` est stocké dans la zone des variables non-initialisées
 - l'argument ``i`` déclaré en ``ligne C`` est stocké sur le tas
 - la variable ``k`` déclarée en ``ligne F`` est stockée sur la pile


-
 - le tableau ``tab`` déclaré en ``ligne B`` est stocké dans la zone des variables non-initialisées
 - l'argument ``i`` déclaré en ``ligne C`` est stocké sur la pile
 - la variable ``j`` déclarée en ``ligne D`` est stockée sur la pile
 - la variable ``i`` déclarée en ``ligne E`` est stockée sur le tas
 - la variable ``k`` déclarée en ``ligne F`` est stockée sur la pile


-
 - la variable ``i`` déclarée et initialisée en ``ligne A`` est stockée dans la zone des variable initialisées
 - le tableau ``tab`` déclaré en ``ligne B`` est stocké dans la zone des variables non-initialisées
 - l'argument ``i`` déclaré en ``ligne C`` est stocké sur la pile
 - la variable ``k`` déclarée en ``ligne F`` est stockée sur le tas


Question 4. Initialisation des variables
----------------------------------------

En C, une règle de bonne pratique est d'initialiser toutes les variables avant leur utilisation. Utiliser une variable qui n'a pas été correctement initialisée pour être une source de problèmes. Un étudiant a écrit les déclarations ci-dessous :

 .. code-block:: c

  int k=0;
  int i;
  short j;
  float f;
  double d;
  char c[10];
  char* string;
  void* v;
  int* ptr;
  ptr=(int*) malloc(5*sizeof(int));


Après exécution de ces lignes, un seul des groupes d'affirmations ci-dessous est correct. Lequel ?

.. class:: positive

-
 - la variable ``i`` est initialisée à  la valeur ``0``
 - le pointeur ``string`` est initialisé à la valeur ``NULL``
 - ``c[2]`` contient le caractère ``'\0'``
 - Après exécution de ``malloc``, le contenu de l'adresse ``ptr+1`` est indéterminé

 .. class:: comment

    Pour des raisons d'efficacité, `malloc(3)`_ n'initialise pas à zéro les zones mémoires allouées, contrairement à `calloc(3)`_

-
 - la variable ``j`` est initialisée à  la valeur ``0``
 - le pointeur ``v`` est initialisé à la valeur ``NULL``
 - ``c[4]`` contient le caractère ``'\0'``
 - Après exécution de ``malloc``, le contenu de l'adresse ``ptr+4`` est indéterminé

 .. class:: comment

    Pour des raisons d'efficacité, `malloc(3)`_ n'initialise pas à zéro les zones mémoires allouées, contrairement à `calloc(3)`_

.. class:: negative

-
 - la variable ``f`` est initialisée à  la valeur ``0.0``
 - le pointeur ``string`` n'a aucune valeur et n'est pas utilisable
 - ``c[2]`` contient le caractère espace
 - Après exécution de ``malloc``, l'adresse ``ptr+1`` contient le caractère ``'\0'``

 .. class:: comment

    `malloc(3)`_ n'initialise pas la zone mémoire allouée. ``string`` contient ``NULL`` et ``c[2]`` le caractère ``'\0'``

-
 - la variable ``f`` est initialisée à  la valeur ``0.0``
 - le pointeur ``v`` n'a aucune valeur et n'est pas utilisable
 - ``c[2]`` contient le caractère espace
 - Après exécution de ``malloc``, l'adresse ``ptr`` contient le caractère ``'\0'``

-
 - la variable ``f`` est initialisée à  la valeur ``0.0``
 - le pointeur ``string`` est initialisé à ``NULL``
 - ``c[10]`` contient le caractère espace
 - Après exécution de ``malloc``, l'adresse ``ptr+3`` contient le caractère ``'\0'``

 .. class:: comment

    ``c[10]`` est hors du tableau ``c``. `malloc(3)`_ n'initialise pas la zone mémoire allouée.

-
 - la variable ``f`` est initialisée à  la valeur ``0.0``
 - le pointeur ``v`` est initialisé à ``NULL``
 - ``c[6]`` contient le caractère ``'\0'``
 - Après exécution de ``malloc``, l'adresse ``ptr+5`` contient le caractère ``'\0'``

 .. class:: comment

    `malloc(3)`_ n'initialise pas la zone mémoire allouée. De plus, ``ptr+5`` se trouve en dehors de la zone mémoire allouée par `malloc(3)`_


Question 5. `malloc(3)`_ et compagnie
-------------------------------------


Les fonctions `malloc(3)`_ et `free(3)`_ sont importantes pour la manipulation de la mémoire sur le tas. Parmi les groupes d'affirmation suivants, un seul est correct. Lequel ?

.. class:: positive

-
  - la fonction `malloc(3)`_ retourne un pointeur de type ``void *``
  - la fonction `free(3)`_ prend comme argument un pointeur de type ``void *`` qui a été précédemment alloué par la fonction `malloc(3)`_
  - si l'appel à `calloc(3)`_ a retourné un pointeur différent de ``NULL``, alors la zone mémoire demandée a été allouée et est initialisée à zéro
  - une implémentation possible (non efficace) de `realloc(3)`_ est :

    .. code-block:: c

       void *realloc(void *ptr, size_t len)
       {
         void *r;

	 r = malloc(len);
	 if(r!=NULL)
	 {
	    memcpy(r, ptr, len);
	    free(ptr);
	 }
         return r;
       }



.. class:: negative

-
  - la fonction `malloc(3)`_ retourne un pointeur de type ``void *``
  - la fonction `free(3)`_ prend comme argument n'importe quel type de pointeur
  - si l'appel à `malloc(3)`_ a retourné un pointeur différent de ``NULL``, alors la zone mémoire demandée a été allouée mais n'est pas initialisée à zéro
  - une implémentation possible (non efficace) de `realloc(3)`_ est :

    .. code-block:: c

       void *realloc(void *ptr, size_t len)
       {
         void *r;
	 r = malloc(len);
	 memcpy(r, ptr, len);
	 return r;
       }



-
  - la fonction `calloc(3)`_ retourne un pointeur de type ``void *``
  - la fonction `free(3)`_ prend comme argument un pointeur de type ``void *`` qui a été précédemment alloué par la fonction `malloc(3)`_
  - si l'appel à `malloc(3)`_ a retourné un pointeur différent de ``NULL``, alors la zone mémoire demandée a été allouée et est initialisée
  - une implémentation possible (non efficace) de `realloc(3)`_ est :

    .. code-block:: c

       void *realloc(void *ptr, size_t len)
       {
         return malloc(len);
       }


-
  - la fonction `calloc(3)`_ retourne un pointeur de type ``void *``
  - la fonction `free(3)`_ prend comme argument un pointeur de type ``void *`` qui a été précédemment alloué par la fonction `malloc(3)`_
  - si l'appel à `malloc(3)`_ a retourné un pointeur différent de ``NULL``, alors la zone mémoire demandée a été allouée et est initialisée
  - une implémentation possible (non efficace) de `realloc(3)`_ est :

    .. code-block:: c

       void *realloc(void *ptr, size_t len)
       {
         void *r;

	 r = malloc(len);
	 if(r)
	 {
	    return r;
	 }
	 else
	 {
	    return NULL;
	 }
       }



Question 6. Stack
-----------------

Considérons le programme `stack.c` présenté dans le syllabus. Cette implémentation d'une pile permet d'ajouter et de retirer un élément de la pile. Laquelle des implémentations ci-dessous est-elle une implémentation correcte d'une fonction ``size`` permettant de calculer le nombre d'éléments stockés dans la pile ?

.. class:: positive

-
  .. code-block:: c

     int size(struct node_t* stack)
     {
         struct node_t *curr = stack;
         int count = 0;
         while (curr!=NULL) {
             count ++;
 	     curr = curr->next;
         }
         return count;
     }


-
  .. code-block:: c

     int size(struct node_t* stack)
     {
         int count = 0;
         while (stack!=NULL) {
             count ++;
             stack = stack->next;
         }
         return count;
     }



.. class:: negative

-
  .. code-block:: c

     int size(struct node_t* stack)
     {
         int count = 0;
         while (stack!=NULL) {
             count ++;
	     stack++;
         }
         return count;
     }


-
  .. code-block:: c

     int size(struct node_t* stack)
     {
         return sizeof(stack);
     }



-
  .. code-block:: c

     int size(struct node_t* stack)
     {
         struct node_t *curr = stack;
         int count = 0;
         while (curr) {
             count ++;
 	     curr++;
         }
         return count;
     }

-
  .. code-block:: c

     int size(struct node_t stack)
     {
         struct node_t curr = stack;
         int count = 0;
         while (curr) {
             count ++;
 	     curr = stack->next;
         }
         return count;
     }


Question 7. `strdup(3)`_
------------------------

La librairie standard contient la fonction `strdup(3)`_. Laquelle des fonctions ci-dessous est-elle
une implémentation de `strdup(3)`_ ?

.. class:: positive

-
  .. code-block:: c

     char *strdup(const char *s)
     {
         char *new = (char *) malloc ((strlen(s)+1) * sizeof(char));
         if (new == NULL)
             return NULL;
         return memcpy(new, s, (strlen(s)+1) * sizeof(char));
     }

-
  .. code-block:: c

     char *strdup(const char *s)
     {
         char *new = (char *) malloc ((strlen(s)+1) * sizeof(char));
         if (!new)
             return NULL;
         return memcpy(new, s, (strlen(s)+1) * sizeof(char));
     }


.. class:: negative

-
  .. code-block:: c

     char *strdup(const char s)
     {
         void *new = malloc (strlen(s));
         if (new == NULL)
             return NULL;
         return memcpy(new, s, strlen(s));
     }

-
  .. code-block:: c

     char *strdup(const char *s)
     {
         char new [strlen(s)+1];
         return memcpy(new, s, (strlen(s)+1) * sizeof(char));
     }


-
  .. code-block:: c

     char *strdup(const char * s)
     {
         void *new = malloc (strlen(s+1));
         return memcpy(new, s, strlen(s+1));
     }

-
  .. code-block:: c

     char *strdup(const char *s)
     {
         char *new = (char *) calloc (strlen(s) * sizeof(char));
         if (new == NULL)
             return NULL;
         return memcpy(new, s, (strlen(s) * sizeof(char)));
     }

-
  .. code-block:: c

     char *strdup(const char *s)
     {
         char *new = (char *) malloc (strlen(s) * sizeof(char));
         return memcpy(new, s, (strlen(s) * sizeof(char));
     }




.. include:: ../../../links.rst
.. include:: ../../../man_links.rst
.. include:: ../../../incl_links.rst
