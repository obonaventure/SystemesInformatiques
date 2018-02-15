.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. raw:: html

  <script type="text/javascript" src="js/jquery-1.7.2.min.js"></script>
  <script type="text/javascript" src="js/jquery-shuffle.js"></script>
  <script type="text/javascript" src="js/rst-form.js"></script>
  <script type="text/javascript" src="js/prettify.js"></script>
  <script type="text/javascript">$nmbr_prop = 3</script>


============================
Semaine 2 : Types de données
============================

La matière couverte cette semaine la section relative aux `types de données <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/C/datatypes.html>`_ (jusque et y compris la section relative aux `expressions de manipulation de bits <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/C/datatypes.html#les-expressions-de-manipulation-de-bits>`_


Question 1. Conversion de types
-------------------------------

En C tout comme dans des langages comme Java, il est possible de convertir des nombres d'un type primitif vers un autre. Cependant, alors que le compilateur Java vérifie si la conversion est sans risque, le compilateur C ne fait aucune vérification et suppose que si le programmeur a effectué une conversion explicite entre types, il a pris ses précautions. Sur une architecture où les types de données sont stockés comme suit :

.. code:: c

    // char			1 octet(s)
    // unsigned char		1 octet(s)
    // short			2 octet(s)
    // unsigned short		2 octet(s)
    // int			4 octet(s)
    // unsigned int		4 octet(s)


    int i;
    short s;
    long l;
    char c;
    unsigned int ui;
    unsigned char uc;
    unsigned long ul;
    unsigned short us;

Un seul des fragments de code ci-dessous contient des conversions de type qui sont sans risque. Lequel ?

.. class:: positive

-
 .. code:: c

    i=(int ) s;
    s=(short) uc;
    l=(long )i;

-
 .. code:: c

    ui=(unsigned int) us;
    s=(short) c;
    ul=(unsigned long )ui;


.. class:: negative

-
 .. code:: c

    ui=(unsigned int ) s;
    us=(unsigned short) uc;
    l=(long )i;

 .. class:: comment

    Si ``s`` est négatif, la conversion en ``unsigned int`` risque de poser problème.


-
 .. code:: c

    i=(int ) us;
    us=(unsigned short) i;
    l=(long )c;

 .. class:: comment

    La conversion d'un ``int`` en un ``unsigned short`` risque de poser problème.

-
 .. code:: c

    ui=(unsigned int) s;
    s=(short) c;
    ul=(unsigned long )ui;

 .. class:: comment

    La première conversion risque de poser des problèmes.

Question 2. Notation hexadécimale
---------------------------------

Parmi les affirmations suivantes relatives aux nombres en représentation hexadécimale, une seule est vraie. Laquelle ?

.. class:: positive

- La représentation hexadécimale du nombre entier positif ``27`` est ``1B``

- La représentation hexadécimale du nombre entier positif ``67`` est ``43``

.. class:: negative

- La représentation hexadécimale du nombre entier positif ``67`` est ``34``

  .. class:: comment

     :math:`3*16+4` ne vaut pas ``67``


- La représentation hexadécimale du nombre entier positif ``27`` est ``B1``

  .. class:: comment

     :math:`11*16+1` ne vaut pas ``27``

- La représentation hexadécimale du nombre entier positif ``62`` est ``B1``

  .. class:: comment

     :math:`11*16+1` ne vaut pas ``62``

- La représentation hexadécimale du nombre entier positif ``128`` est ``FF``

  .. class:: comment

     :math:`15*16+15` ne vaut pas ``128``


Question 3. Notation binaire
----------------------------

Parmi les affirmations suivantes relatives aux nombres en représentation binaire, une seule est vraie. Laquelle ?


.. class:: positive

- La représentation binaire du nombre entier positif ``99``  est ``1100011``

- La représentation binaire du nombre entier positif ``176``  est ``10110000``

.. class:: negative

- La représentation binaire du nombre entier positif ``90``  est ``1100011``

  .. class:: comment

     La représentation binaire de ``90`` est  ``1011010``

- La représentation binaire du nombre entier positif ``176``  est ``10110001``

  .. class:: comment

     C'est la représentation de ``177``.

- La représentation binaire du nombre entier positif ``166``  est ``10110001``

  .. class:: comment

     C'est la représentation de ``177``.

- La représentation binaire d'un nombre entier positif impair a toujours ``0`` comme bit de poids faible.

  .. class:: comment

     Ce sont les entiers positifs pairs (et zéro) qui ont ``0`` comme bit de poids faible.


Question 4. Notation binaire
----------------------------

Parmi les affirmations suivantes relatives aux nombres signés en représentation binaire, une seule est vraie. Laquelle ?


.. class:: positive

- Si la variable ``x`` est un ``short`` (signé) sur 16 bits, alors la représentation binaire de ``-17`` est ``11111111 11101111``

- Si la variable ``x`` est un ``short`` (signé) sur 16 bits, alors la représentation binaire de ``-23`` est ``11111111 11101001``

.. class:: negative

- Si la variable ``x`` est un ``short`` (signé) sur 16 bits, alors la représentation binaire de ``-17`` est ``00000000 00010001``

  .. class:: comment

     C'est la représentation de ``17`` mais en non-signé


- Si la variable ``x`` est un ``short`` (signé) sur 16 bits, alors la représentation binaire de ``-17`` est ``10000000 00010001``

  .. class:: comment

     C'est la représentation de ``-32751``

- Si la variable ``x`` est un ``short`` (signé) sur 16 bits, alors la représentation binaire de ``-23`` est ``00000000 00010111``


  .. class:: comment

     C'est la représentation de ``23``


- Si la variable ``x`` est un ``short`` (signé) sur 16 bits, alors la représentation binaire de ``-23`` est ``11111111 11100110``


  .. class:: comment

     C'est la représentation de ``-26``


.. http://www.binaryconvert.com/ pour des conversions sur le web



Question 5. Manipulations de bits
---------------------------------


Si la variable ``c`` est de type ``unsigned char`` sur 8 bits, laquelle des suites d'instructions ci-dessous permet d'en échanger les 4 bits de poids faible avec les 4 bits de poids fort ?


.. class:: positive

-
 .. code:: c

    unsigned char temp1, temp2;
    temp1 = c & 0x0F;
    temp2 = c & 0xF0;
    temp1=temp1 << 4;
    temp2=temp2 >> 4;
    c= temp2|temp1;

-
 .. code:: c

    unsigned char temp1, temp2;
    temp1=c << 4;
    temp2=c >> 4;
    c= temp2|temp1;


.. class:: negative

-
 .. code:: c

    unsigned char temp1, temp2;
    temp1=c << 4;
    temp2=c >> 4;
    c= temp2||temp1;


 .. class:: comment

    Ne confondez pas l'opérateur binaire ``|`` avec la disjonction logique ``||``.


-
 .. code:: c

    unsigned char temp1, temp2;
    temp1=4 << temp1;
    temp2=4 >> temp2;
    c= temp2|temp1;


 .. class:: comment

    Cette utilisation de l'opérateur ``>>`` est incorrecte. Vous décalez de ``temp1`` bits (c'est-à-dire 0) la représentation binaire de ``4``.

-
 .. code:: c

    unsigned char temp1, temp2;
    temp1 = c && 0x0F;
    temp2 = c && 0xF0;
    temp1=temp1 << 4;
    temp2=temp2 >> 4;
    c= temp2|temp1;


 .. class:: comment

    Ne confondez pas la l'opérateur binaire ``&`` avec la conjonction logique ``&&``.


Question 6. Multiplication entière
----------------------------------


Parmi les expressions suivantes, une seule permet de calculer ``x*7`` lorsque ``x`` est un nombre entier. Laquelle ?


.. class:: positive

-
 .. code:: c

    (x<<3)-x


 .. class:: comment

    Cette expression calcule en effet ``x<<3=x*8`` puis retire ``x``.

.. class:: negative

-
 .. code:: c

    (x>>3)-x


 .. class:: comment

    Cette expression divise d'abord ``x`` par ``8`` puis retire x au résultat de cette division.

-
 .. code:: c

    (x<<3)+x

 .. class:: comment

    Cette expression multiplie ``x`` par ``8`` puis ajoute ``x`` au résultat. Elle multiple donc ``x`` par ``9``.


-
 .. code:: c

     (x<<7)


 .. class:: comment

    Cette expression multiplie ``x`` par :math:`2^7`


-
 .. code:: c

     (x>>7)


 .. class:: comment

    Cette expression divise ``x`` par :math:`2^7`

Question 7. Extraction de bits
------------------------------


Il est parfois nécessaire en C de manipuler directement la représentation binaire d'un nombre. Si ``f`` est un nombre de type ``float`` stocké sur 32 bits, laquelle des expressions ci-dessous peut-elle être intégrée dans ce code pour afficher positif ou négatif en fonction du signe de ce nombre ?

.. code:: c

   if(<à compléter>)
     printf("positif\n");
   else
     printf("negatif\n");


.. class:: positive

-
 .. code:: c

    !(((unsigned int) f) & 0x80000000)

-
 .. code:: c

    !(((unsigned int) f) >> 31)

.. class:: negative

-
 .. code:: c

    !(((unsigned int) f) & 0x10000000)

 .. class:: comment

    En faisant ``& 0x10000000``, vous mettez tous les bits de ``f`` à ``0`` sauf le bit ``28`` alors que le bit de signe est le bit de poids fort (``31``).

-
 .. code:: c

    !(((unsigned int) f) << 31)

 .. class:: comment

    Cette opération décale la représentation binaire de ``f`` de 31 bits vers la gauche, c'est-à-dire que seul le bit de poids faible reste. Malheureusement, le signe se trouve dans le bit de poids faible et non dans le bit de poids fort.


-
 .. code:: c

    !(((unsigned int) f) > 31)

 .. class:: comment

    Ne confondez pas ``>`` et ``>>``.


-
 .. code:: c

    !(((unsigned int) f) & 31)

 .. class:: comment

    Cette opération masque le nombre ``f`` avec ``00000000 00000000 00000000 00011111``



Question 8. Chaînes de caractères
---------------------------------

Une seule des fonctions ci-dessous retourne correctement le nombre d'occurrences du caractère ``c`` dans la chaîne de caractères ``c``. Laquelle ?

.. class:: positive

-
 .. code:: c

   int count1(char *s, char c) {
     int i=0;
     int count=0;
     while(*(s+i)!='\0') {
       if(*(s+i)==c) {
          count++;
       }
       i++;
     }
     return(count);
    }


-
 .. code:: c

    int count(char *s, char c) {
      int count=0;
      while(*(s)!='\0') {
        if(*(s)==c) {
          count++;
        }
        s++;
      }
      return(count);
    }


.. class:: negative


-
 .. code:: c

   int count1(char *s, char c) {
     int i=0;
     int count=0;
     while(i<s.length) {
       if(*(s+i)==c) {
          count++;
       }
       i++;
     }
     return(count);
    }

 .. class:: comment

    ``s`` est un pointeur vers une chaînes de caractères et non une structure. Ce code ne compile pas.

-
 .. code:: c

   int count1(char *s, char c) {
     int i=0;
     int count=0;
     while(*s!='\0') {
       if(*(s+i)==c) {
          count++;
       }
       i++;
     }
     return(count);
    }

 .. class:: comment

    La boucle ``while`` se termine-t-elle ? Quelle est sa condition d'arrêt ?

-
 .. code:: c

    int count(char *s, char c) {
      int count=0;
      while(*(s)!='\0') {
        s++;
        if(*(s)==c) {
          count++;
        }
      }
      return(count);
    }

 .. class:: comment

    Ce code compte-il correctement le caractère si il est présent en première position de la chaîne ?


-
 .. code:: c

    int count(char *s, char c) {
      int count=0;
      while(s!='\0') {
        if(s==c) {
          count++;
        }
        s++;
      }
      return(count);
    }

 .. class:: comment

    Ce code compare le pointeur ``s`` c'est-à-dire *l'adresse* du première caractère de la chaîne ``s`` en mémoire avec ``\0`` et ``c`` et non le caractère pointé par ``s``.


Question 9. Pointeurs
---------------------

Si ``ptr`` a été déclaré sous la forme ``int *ptr``, un seul des groupes d'affirmations suivantes est vrai, lequel ?

.. class:: positive

-
  - l'expression ``*(ptr + 1)`` est une valeur entière
  - l'expression ``ptr[1]`` est une valeur entière
  - l'expression ``ptr`` est une adresse en mémoire


-
  - l'expression ``*(ptr) + 1`` est une valeur entière
  - l'expression ``ptr[2]`` est une valeur entière
  - l'expression ``ptr++`` est une adresse en mémoire


.. class:: negative

-
  - l'expression ``&(ptr) + 1`` est un nombre entier
  - l'expression ``ptr[2]`` est une valeur entière
  - l'expression ``&ptr`` est une adresse en mémoire

-
  - l'expression ``*(ptr+1)==ptr[1]`` est syntaxiquement invalide
  - l'expression ``ptr[2]`` est une valeur entière
  - l'expression ``&ptr`` est une adresse en mémoire

-
  - l'expression ``*(ptr+1)==ptr[1]`` est toujours vraie
  - l'expression ``ptr--`` est syntaxiquement invalide


Question 10. Pointeurs et tableaux
----------------------------------

Considérons le tableau ``tab`` déclaré comme suit :

 .. code:: c

    #define SIZE 30
    int tab[SIZE];
    int *ptr;

Dans une architecture 32 bits, un seul des groupes d'affirmations ci-dessous est vrai. Lequel ?


.. class:: positive

-
  - l'expression ``tab[i]`` correspond à la même valeur dans le tableau que ``*(tab+i)`` lorsque ``0<=i<29``
  - l'assignation ``ptr=(tab+i)`` est valide et après cette assignation, ``*ptr`` retourne la même valeur que ``tab[i]`` lorsque ``0<=i<29``


-
  - l'expression ``tab[0]`` correspond à la même valeur dans le tableau que ``*(tab)``
  - l'assignation ``ptr=(tab+i)`` est valide et après cette assignation, ``*ptr`` retourne la même valeur que ``tab[i]`` lorsque ``0<=i<29``


.. class:: negative

-
  - l'expression ``tab[i]`` correspond à la même valeur dans le tableau que ``*(tab+i)`` lorsque ``0<=i<29``
  - l'assignation ``tab=(tab+i)`` est valide et après cette assignation, ``*tab`` retourne le ième élément du tableau lorsque ``0<=i<29``

  .. class:: comment

     Lorsque ``tab`` est déclaré comme étant un tableau, il est interdit de modifier sa valeur.

-
  - l'expression ``tab[0]`` correspond à la même valeur dans le tableau que ``&(tab)``
  - l'assignation ``tab=(tab+i)`` est valide et après cette assignation, ``*tab`` retourne le ième élément du tableau lorsque ``0<=i<29``

  .. class:: comment

     Les deux affirmations sont fausses.

-
  - l'expression ``tab[i]`` correspond à la même valeur dans le tableau que ``*(tab)+i`` lorsque ``0<=i<29``
  - l'assignation ``ptr=(tab)`` est valide et après cette assignation, ``*(ptr+i)`` retourne le ième élément du tableau lorsque ``0<=i<29``

  .. class:: comment

     La première affirmation est fausse, ``*(tab)+i`` équivaut à ``tab[0]+i``


Question 11. Pointeurs
----------------------

Considérons le fragment de code ci-dessous.

.. code:: c

   int tab[]={ 10, 20, 30, 40 };
   int *ptr1=&tab[1];
   int *ptr2=&tab[3];

Dans ce code, une seule des affirmations suivantes est vraie, laquelle ?

.. class:: positive

- l'expression ``ptr2-ptr1`` vaut ``2``

- les expressions ``*(ptr1-1)`` et ``*(ptr2-3)`` retournent toutes les deux la même valeur, ``10``

.. class:: negative

- l'expression ``ptr2-ptr1`` vaut ``20``

  .. class:: comment

     ``ptr2`` et ``ptr1`` sont des pointeurs vers des entiers. L'arithmétique des pointeurs s'applique pour cette opération. Vu leur initialisation, la différence vaut ``2``.

- les expressions ``*(ptr1-1)`` et ``*(ptr2-3)`` retournent toutes les deux la même valeur, ``1``

  .. class:: comment

     L'expression ``*(ptr1-1)`` équivaut à ``tab[0]`` et ``*(ptr2-3)`` à ``tab[0]``. Cet élément du tableau contient la valeur ``10``.

- l'expression ``*(ptr2-ptr1)`` retourne la valeur ``20``

  .. class:: comment

     ``ptr2`` et ``ptr1`` sont des pointeurs vers des entiers. L'arithmétique des pointeurs s'applique pour cette opération. Vu leur initialisation, la différence vaut ``2``. L'expression ``*(2)`` correspond à une donnée à une adresse dans le bas de la mémoire qui n'est normalement pas accessible au programme.



Question 12. Pointeurs et fonctions
-----------------------------------

En C, il est parfois nécessaire d'échanger le contenu de deux variables. Si ``a`` et ``b`` sont des variables de type ``int``,  laquelle des fonctions ci-dessous permet de réaliser cette échange entre les contenu des variables ?


.. class:: positive

-
 .. code:: c

    void swap(int *i, int *j) {
      int k;
      k=*i;
      *i=*j;
      *j=k;
    }
    //échange
    swap(&a,&b);


-
 .. code:: c

    void swap(int *i, int *j) {
      int k;
      k=*j;
      *j=*i;
      *i=k;
    }
    //échange
    swap(&a,&b);

.. class:: negative

-
 .. code:: c

    void swap(int i, int j) {
      int k;
      k=i;
      i=j;
      j=k;
    }
    //échange
    swap(a,b);

 .. class:: comment

    Cette fonction ne fait rien du tout d'utile.

-
 .. code:: c

    void swap(int i, int j) {
      int k;
      k=i;
      i=j;
    }
    //échange
    swap(&a,&b);

 .. class:: comment

    Cette fonction reçoit comme argument l'adresse de ``a`` et l'adresse de ``b`` mais ne modifie en rien le contenu de ces variables.

-
 .. code:: c

    void swap(int i, int j) {
      int k;
      int *i_ptr=&i;
      int *j_ptr=&j;
      k=i;
      *(i_ptr)=j;
      *(j_ptr)=k;
    }
    //échange
    swap(a,b);

 .. class:: comment

    Lors de son exécution, la fonction ``swap`` ci-dessus reçoit les valeurs des variables ``a`` et ``b``, mais elle n'a aucune idée de l'endroit où ces variables sont stockées en mémoire. Elle ne peut donc pas modifier leur contenu.

Question 13. Pointeurs et structures
------------------------------------


Dans un programme de manipulation de fractions, on définit la structure suivante pour représenter une fraction entière :

    .. code:: c

       struct fract_t {
            int num;
            int denum;
       };

   On veut pouvoir facilement écrire une fonction de type ``void`` qui remplace la valeur stockée dans la fraction par le résultat de l'addition de la fraction et un nombre entier passé en fragment. La spécification de cette fonction pourrait être :

 .. code:: c

    /*
     * augmente la fraction passé en argument de l'entier n et place
     * la somme calculée dans la fraction
     * Exemples
     *  Si f vaut 1/3, alors l'application de la fonction avec f et 2 comme
     *  arguments a comme résultat de stocker la valeur 7/3 dans f
     *  Si f vaut 2/1, alors l'application de la fonction avec f et 1 comme
     *  arguments a comme résultat de stocker la valeur 3/1 dans f
     */


Laquelle des signatures ci-dessous peut-elle être utilisée pour effectuer cette opération et modifier la fraction passé en argument ?


.. class:: positive


-
 .. code:: c

    void scale(struct fract_t *f, int s);
    // appel à la fonction :
    // scale(&f,3);

.. class:: negative

-
 .. code:: c

    void scale(struct fract_t f, int s);
    // appel à la fonction :
    // scale(f,3);
-
 .. code:: c

    void scale(int num, int den, int s);
    // appel à la fonction :
    // scale(f.num, f.denum,3);



.. include:: ../../../links.rst
.. include:: ../../../man_links.rst
.. include:: ../../../incl_links.rst
