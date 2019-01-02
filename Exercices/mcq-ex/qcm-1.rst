.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Questions à choix multiples
===========================
:task_id: sinf1252-1

Ces questions ont pour objectif de vous permettre de tester vous-même votre compréhension de la matière couverte par cette mission de mise en route. Elles supposent que vous avez lu le premier chapitre du syllabus contenant l'introduction à Unix et au langage C.


Question 1. Commande `man(1)`_
------------------------------

.. question:: man 
   :nb_prop: 3           
   :nb_pos: 1

   La commande `man(1)`_ permet de lire les pages de manuel d'un système Unix. Elle est particulièrement utile pour vérifier les arguments à donner à un programme en ligne de commande ou pour savoir comment utiliser certaines fonctions de la librairie standard ou appels systèmes. Comment faut-il appeler la commande `man(1)`_ pour lister toutes les pages de manuel dont le résumé contient le mot ''intro'' ?

   .. positive::

      .. code-block:: console

         man -k intro

   .. negative::

      .. code-block:: console

         man intro

      .. comment::

         Cette commande permet d'obtenir la page dénommée ``intro`` mais uniquement dans la première section du manuel. Elle ne liste pas toutes les pages dont le résumé contient le mot clé ``intro``.

   .. negative::

      .. code-block:: console

         man -k *intro*

      .. comment::

         Par défaut, lorsque vous passez un argument tel que ``*intro*`` en ligne de commande, le shell va tenter de remplacer ``*intro*`` par tous les noms de fichiers du répertoire courant qui contiennent l'expression régulière qui commence par n'importe quelle suite de caractères, contient ``intro`` et se termine par n'importe quelle suite de caractères. Si le répertoire dans lequel vous exécutez cette commande contient les fichiers ``intro.txt`` et ``intro.dat``, ``man`` recevra ces deux noms de fichiers comme arguments.


Question 2. Commande `ls(1)`_
-----------------------------

.. question:: ls 
   :nb_prop: 3
   :nb_pos: 1 

   La commande `ls(1)`_ permet de lister le contenu d'un répertoire. Elle supporte de nombreux paramètres. Parmi les groupes d'affirmation suivants, un seul est valide, lequel ?

   .. positive::

        - Dans un répertoire, la commande ``ls -a`` sans argument permet d'afficher la liste de tous les fichiers et répertoires présents
        - La commande ``ls -r`` permet de lister les répertoires présents dans le répertoire courant en inversant l'ordre
        - La commande ``ls -l`` permet d'obtenir la liste détaillée du contenu du répertoire courant avec toutes les informations relatives à chaque fichier et répertoire non cachés

     .. comment::  Réponse correcte. 

   .. positive::

        - Dans un répertoire, la commande ``ls -a`` sans argument permet d'afficher la liste de tous les fichiers et répertoires présents
        - La commande ``ls -R`` permet de lister de façon récursive le contenu du répertoire courant et de ses sous-répertoires
        - La commande ``ls -l`` permet d'obtenir la liste détaillée du contenu du répertoire courant avec toutes les informations relatives à chaque fichier et répertoire non cachés

     .. comment::  Réponse correcte. 

   .. negative::

        - Dans un répertoire, la commande ``ls *`` permet d'afficher la liste de tous les fichiers et répertoires présents
        - La commande ``ls -f`` permet de lister le contenu du répertoire courant sans trier les fichiers par nom
        - La commande ``ls -l`` permet d'obtenir la liste détaillée du contenu du répertoire courant avec toutes les informations relatives à chaque fichier et répertoire

      .. comment:: Relisez la page de manuel de `ls(1)`_. Sous Unix, le shell va remplacer ``*`` par l'ensemble des fichiers présents dans le répertoire courant

   .. negative::

        - Dans un répertoire, l'appel à `ls(1)`_ sans argument permet d'afficher la liste de tous les fichiers et répertoires présents
        - La commande ``ls -r`` permet de lister de façon récursive le contenu du répertoire courant et de ses sous-répertoires
        - La commande ``ls -l`` permet d'obtenir la liste détaillée du contenu du répertoire courant avec toutes les informations relatives à chaque fichier et répertoire

      .. comment:: Relisez la page de manuel de `ls(1)`_. Sous Unix, l'appel à `ls(1)`_ sans argument dans le shell affichera l'ensemble des fichiers présents dans le répertoire courant



Question 3. Premier programme en langage C
------------------------------------------

.. question:: hello 
   :nb_prop: 3           
   :nb_pos: 1 


   Depuis la publication du livre de référence [KernighanRitchie1998], le premier programme écrit en langage C affiche à l'écran la chaîne de caractères "Hello, world". Parmi les codes source ci-dessous, un seul est entièrement correct. Lequel ?


   .. positive::

      .. code-block:: c

         #include <stdio.h>
         int main(int argc, const char *argv[]) {
           printf("Hello, world\n");
         }

     .. comment::  Réponse correcte. 

   .. positive::

      .. code-block:: c

         #include <stdio.h>
         int main(int argc, const char *argv[]) {
           printf("Hello,");
           printf(" world\n");
         }

     .. comment::  Réponse correcte. 

   .. negative::

      .. code-block:: c

         #include <stdio.h>
         void main(int argc, const char *argv[]) {
           printf("Hello, world\n");
         }

      .. comment:: En C, contrairement à Java, la fonction ``main`` retourne une valeur de type ``int``.

   .. negative::

      .. code-block:: c

         int main(int argc, const char *argv[]) {
           printf("Hello, world\n");
         }


      .. comment:: La fonction `printf(3)`_ utilisée par ce programme fait partie de la librairie standard de gestion des I/O. Pour l'utiliser, il faut inclure le header `stdio.h`_. Même si certains compilateurs pouvaient l'inclure par défaut, il est préférable de spécifier ce header explicitement.

   .. negative::

      .. code-block:: c

         #include <stdlib.h>
         int main() {
           printf("Hello, world\n");
         }


      .. comment:: En C, la signature de la fonction ``main`` est ``int main(int argc, const char *argv[])`` même si certains compilateurs peuvent être tolérants. `printf(3)`_ est défini via `stdio.h`_ et non `stdlib.h`_.

   .. negative::

      .. code-block:: c

         #include <stdlib.h>
         void main()
            printf("Hello, world\n");
         }


      .. comment:: En C, la signature de la fonction ``main`` est ``int main(int argc, const char *argv[])`` même si certains compilateurs peuvent être tolérants. `printf(3)`_ est défini via `stdio.h`_ et non `stdlib.h`_.


Question 4. Deuxième programme en langage C
--------------------------------------------

.. question:: 2ndprog 
   :nb_prop: 3 
   :nb_pos: 1 

   Votre deuxième programme en langage C doit afficher à l'écran la chaîne de caractères `SINF1252`. Lequel parmi les programmes ci-dessous affiche-t-il correctement cette chaîne de caractères ?

   .. positive::

      .. code-block:: c

         #include <stdio.h>
         int main(int argc, const char *argv[]) {
           int a = 1252;
           printf("SINF%d\n", a);
         }

      .. comment:: En C, la fonction `printf(3)`_ prend un nombre variable d'arguments. Le premier est toujours une spécification de formatage qui indique la chaîne de caractères à afficher. Les autres arguments sont des identifiants de variables dont les valeurs seront utilisées pour construire la chaîne de caractères à afficher. Le deuxième argument remplace le premier format `%d`, le troisième argument le deuxième format, etc. La page de manuel de `printf(3)`_ fournit de nombreux détails sur le fonctionnement de cette fonction qui accepte de nombreux paramètres.

   .. positive::

      .. code-block:: c

         #include <stdio.h>
         int main(int argc, const char *argv[]) {
          int a = 1252;
          printf("SINF");
          printf("%d\n", a);
         }

      .. comment:: En C, la fonction `printf(3)`_ prend un nombre variable d'arguments. Le premier est toujours une spécification de formatage qui indique la chaîne de caractères à afficher. Les autres arguments sont des identifiants de variables dont les valeurs seront utilisées pour construire la chaîne de caractères à afficher. Le deuxième argument remplace le premier format `%d`, le troisième argument le deuxième format, etc. La page de manuel de `printf(3)`_ fournit de nombreux détails sur le fonctionnement de cette fonction qui accepte de nombreux paramètres.

   .. negative::

      .. code-block:: none

         #include <stdio.h>
         int main(int argc, const char *argv[]) {
           int a = 1252;
           printf("SINF%a\n", a);
         }

      .. comment:: Dans la fonction `printf(3)`_, ``%a`` est utilisé lorsque l'on veut placer dans une chaîne de caractères un nombre réel en notation hexadécimale. Dans ce cas, ``a`` étant un entier, il aurait fallu utiliser ``%d``.

   .. negative::

      .. code-block:: none

         #include <stdio.h>
         int main(int argc, const char *argv[]) {
           int a = 1252;
           printf(SINF);
           printf(%d\n, a);
         }

      .. comment:: En C, une chaîne de caractères (ou un descripteur de format pour `printf(3)`_ qui est aussi une chaîne de caractères) commence et se termine par le caractère ``"``.

   .. negative::

      .. code-block:: c

         #include <stdio.h>
         int main(int argc, const char *argv[]) {
           int a = 1252;
           printf("SINF$a\n", a);
         }

      .. comment:: Dans la fonction `printf(3)`_ en C, et contrairement à d'autres langages, le caractère ``$`` ne joue pas de rÃ´le particulier. Le programme ci-dessus affichera donc simplement ``SINF$a`` à l'écran.


Question 5. Arguments passés à un programme C
-----------------------------------------------


.. question:: args
   :nb_prop: 3 
   :nb_pos: 1 

   Considérons le programme C ci-dessous qui permet de manipuler les arguments passés en ligne de commande.

   .. code-block:: c


      #include <stdio.h>
      #include <stdlib.h>
      int main(int argc, const char *argv[])
      {
        int a = atoi(argv[1]);
        printf("%d\n", a);
      }


   Parmi les groupes d'affirmations ci-dessous, un seul ne contient que des affirmations qui sont toutes vraies. Lequel ?


   .. positive::

      - Lors de l'exécution de la fonction ``main``, ``argc`` est initialisé au nombre d'arguments passés au programme (y compris le nom de l'exécutable lui-même).
      - Lors de l'exécution de la fonction ``main``, le tableau ``argv[]`` contient dans ``argv[0]`` le nom du programme, dans ``argv[1]`` le premier argument, etc.
      - La fonction ``atoi`` permet de convertir une chaîne de caractères en l'entier équivalent.

     .. comment::  Réponse correcte. 

   .. negative::


        - Lors de l'exécution de la fonction ``main``, ``argc`` est initialisé à zéro.
        - Lors de l'exécution de la fonction ``main``, le tableau ``argv[]`` contient dans ``argv[0]`` le premier argument, dans ``argv[1]`` le second argument, etc.
        - La fonction ``atoi`` calcule la taille de son argument.

      .. comment:: Les trois affirmations sont fausses. ``argc`` sera toujours initialisé à un vu que le nom du programme est toujours passé en argument. Le premier élément du tableau ``argv[]``, ``argv[0]``, est le nom du programme qui est exécuté. Enfin, la fonction ``atoi`` permet de convertir une chaîne de caractères en l'entier équivalent.

   .. negative::

        - Lors de l'exécution de la fonction ``main``, ``argc`` est le nombre maximum d'arguments que l'on peut lui passer.
        - Lors de l'exécution de la fonction ``main``, le tableau ``argv[]`` contient dans ``argv[0]`` le premier argument, dans ``argv[1]`` le second argument, etc.
        - La fonction ``atoi`` doit prendre comme argument une chaîne de caractères qui ne contient que des chiffres.

      .. comment:: Les deux premières affirmations sont fausses. ``argc`` contient le nombre d'arguments passés effectivement au programme. Le premier élément du tableau ``argv[]``, ``argv[0]``, est le nom du programme qui est exécuté.

   .. negative::

        - Lors de l'exécution de la fonction ``main``, le tableau ``argv[]`` contient dans ``argv[0]`` le premier argument, dans ``argv[1]`` le second argument, etc.
        - La fonction ``atoi`` permet de convertir une chaîne de caractères en l'entier équivalent.

      .. comment:: Le premier élément du tableau ``argv[]``, ``argv[0]``, est le nom du programme qui est exécuté.

