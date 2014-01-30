.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et GrÃ©gory Detal
.. Ce fichier est distribuÃ© sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. raw:: html

  <script type="text/javascript" src="js/jquery-1.7.2.min.js"></script>
  <script type="text/javascript" src="js/jquery-shuffle.js"></script>
  <script type="text/javascript" src="js/rst-form.js"></script>
  <script type="text/javascript">$nmbr_prop = 4</script>


=========================
Mission 1 : Mise en Route
=========================

Ces questions ont pour objectif de vous permettre de tester vous-mÃªme votre comprÃ©hension de la matiÃ¨re couverte par cette mission de mise en route.

Ces questions supposent que vous avez lu le premier chapitre du syllabus contenant l'introduction Ã  Unix et au langage C.


Question 1. Commande `man(1)`_
------------------------------

La commande `man(1)`_ permet de lire les pages de manuel d'un systÃ¨me Unix. Elle est particuliÃ¨rement utile pour vÃ©rifier les arguments Ã  donner Ã  un programme en ligne de commande ou pour savoir comment utiliser certaines fonctions de la librairie standard ou appels systÃ¨mes. Comment faut-il appeler la commande `man(1)`_ pour lister toutes les pages de manuel dont le rÃ©sumÃ© contient le mot ''intro'' ?

.. class:: positive

-
  .. code:: console

     man -k intro


.. class:: negative

-
 .. code:: console

    man intro

 .. class:: comment

    Cette commande permet d'obtenir la page dÃ©nommÃ©e ``intro`` mais uniquement dans la premiÃ¨re section du manuel. Elle ne liste pas toutes les pages dont le rÃ©sumÃ© contient le mot clÃ© ``intro``.

-
 .. code:: console

    man -k *intro*

 .. class:: comment

    Par dÃ©faut, lorsque vous passez un argument tel que ``*intro*`` en ligne de commande, le shell va tenter de remplacer ``*intro*`` par tous les noms de fichiers du rÃ©pertoire courant qui contiennent l'expression rÃ©guliÃ¨re qui commence par n'importe quelle suite de caractÃ¨res, contient ``intro`` et se termine par n'importe quelle suite de caractÃ¨res. Si le rÃ©pertoire dans lequel vous exÃ©cutez cette commande contient les fichiers ``intro.txt`` et ``intro.dat``, ``man`` recevra ces deux noms de fichiers comme arguments.

Question 2. Commande `ls(1)`_
-----------------------------

La commande `ls(1)`_ permet de lister le contenu d'un rÃ©pertoire. Elle supporte de nombreux paramÃ¨tres. Parmi les groupes d'affirmation suivants, un seul est valide, lequel ?

.. class:: positive

-
  - Dans un rÃ©pertoire, la commande ``ls -a`` sans argument permet d'afficher la liste de tous les fichiers et rÃ©pertoires prÃ©sents
  - La commande ``ls -r`` permet de lister les rÃ©pertoires prÃ©sents dans le rÃ©pertoire courant en inversant l'ordre
  - La commande ``ls -l`` permet d'obtenir la liste dÃ©taillÃ©e du contenu du rÃ©pertoire courant avec toutes les informations relatives Ã  chaque fichier et rÃ©pertoire non cachÃ©s


-
  - Dans un rÃ©pertoire, la commande ``ls -a`` sans argument permet d'afficher la liste de tous les fichiers et rÃ©pertoires prÃ©sents
  - La commande ``ls -R`` permet de lister de faÃ§on rÃ©cursive le contenu du rÃ©pertoire courant et de ses sous-rÃ©pertoires
  - La commande ``ls -l`` permet d'obtenir la liste dÃ©taillÃ©e du contenu du rÃ©pertoire courant avec toutes les informations relatives Ã  chaque fichier et rÃ©pertoire non cachÃ©s


.. class:: negative

-
  - Dans un rÃ©pertoire, la commande ``ls *`` permet d'afficher la liste de tous les fichiers et rÃ©pertoires prÃ©sents
  - La commande ``ls -f`` permet de lister le contenu du rÃ©pertoire courant sans trier les fichiers par nom
  - La commande ``ls -l`` permet d'obtenir la liste dÃ©taillÃ©e du contenu du rÃ©pertoire courant avec toutes les informations relatives Ã  chaque fichier et rÃ©pertoire

  .. class:: comment

     Relisez la page de manuel de `ls(1)`_. Sous Unix, le shell va remplacer ``*`` par l'ensemble des fichiers prÃ©sents dans le rÃ©pertoire courant

-
  - Dans un rÃ©pertoire, l'appel Ã  `ls(1)`_ sans argument permet d'afficher la liste de tous les fichiers et rÃ©pertoires prÃ©sents
  - La commande ``ls -r`` permet de lister de faÃ§on rÃ©cursive le contenu du rÃ©pertoire courant et de ses sous-rÃ©pertoires
  - La commande ``ls -l`` permet d'obtenir la liste dÃ©taillÃ©e du contenu du rÃ©pertoire courant avec toutes les informations relatives Ã  chaque fichier et rÃ©pertoire

  .. class:: comment

     Relisez la page de manuel de `ls(1)`_. Sous Unix, l'appel Ã  `ls(1)`_ sans argument dans le shell affichera l'ensemble des fichiers prÃ©sents dans le rÃ©pertoire courant



Question 3. Premier programme en langage C
------------------------------------------

Depuis la publication du livre de rÃ©fÃ©rence [KernighanRitchie1998], le premier programme Ã©crit en langage C affiche Ã  l'Ã©cran la chaÃ®ne de caractÃ¨res "Hello, world". Parmi les codes source ci-dessous, un seul est entiÃ¨rement correct. Lequel ?


.. class:: positive

-
 .. code:: c

    #include <stdio.h>
    int main(int argc, const char *argv[]) {
        printf("Hello, world\n");
    }

-
 .. code:: c

    #include <stdio.h>
    int main(int argc, const char *argv[]) {
        printf("Hello,");
	printf(" world\n");
    }

.. class:: negative

-
 .. code:: c

    #include <stdio.h>
    void main(int argc, const char *argv[]) {
        printf("Hello, world\n");
    }


 .. class:: comment

      En C, contrairement Ã  Java, la fonction ``main`` retourne une valeur de type ``int``.

-
 .. code:: c

    int main(int argc, const char *argv[]) {
        printf("Hello, world\n");
    }


 .. class:: comment

       La fonction `printf(3)`_ utilisÃ©e par ce programme fait partie de la librairie standard de gestion des I/O. Pour l'utiliser, il faut inclure le header `stdio.h`_. MÃªme si certains compilateurs pouvaient l'inclure par dÃ©faut, il est prÃ©fÃ©rable de spÃ©cifier ce header explicitement.

-
 .. code:: c

    #include <stdlib.h>
    int main() {
        printf("Hello, world\n");
    }


 .. class:: comment

    En C, la signature de la fonction ``main`` est ``int main(int argc, const char *argv[])`` mÃªme si certains compilateurs peuvent Ãªtre tolÃ©rants. `printf(3)`_ est dÃ©fini via `stdio.h`_ et non `stdlib.h`_.

-
 .. code:: c

    #include <stdlib.h>
    void main()
        printf("Hello, world\n");
    }


 .. class:: comment

    En C, la signature de la fonction ``main`` est ``int main(int argc, const char *argv[])`` mÃªme si certains compilateurs peuvent Ãªtre tolÃ©rants. `printf(3)`_ est dÃ©fini via `stdio.h`_ et non `stdlib.h`_.


Question 4. DeuxiÃ¨me programme en langage C
--------------------------------------------

Votre deuxiÃ¨me programme en langage C doit afficher Ã  l'Ã©cran la chaÃ®ne de caractÃ¨res `SINF1252`. Lequel parmi les programmes ci-dessous affiche-t-il correctement cette chaÃ®ne de caractÃ¨res ?

.. class:: positive

-
 .. code:: c

    #include <stdlio.h>
    int main(int argc, const char *argv[]) {
        int a = 1252;
        printf("SINF%d\n", a);
    }

 .. class:: comment

    En C, la fonction `printf(3)`_ prend un nombre variable d'arguments. Le premier est toujours une spÃ©cification de formatage qui indique la chaÃ®ne de caractÃ¨res Ã  afficher. Les autres arguments sont des identifiants de variables dont les valeurs seront utilisÃ©es pour construire la chaÃ®ne de caractÃ¨res Ã  afficher. Le deuxiÃ¨me argument remplace le premier format `%d`, le troisiÃ¨me argument le deuxiÃ¨me format, etc. La page de manuel de `printf(3)`_ fournit de nombreux dÃ©tails sur le fonctionnement de cette fonction qui accepte de nombreux paramÃ¨tres.

-
 .. code:: c

    #include <stdlio.h>
    int main(int argc, const char *argv[]) {
        int a = 1252;
        printf("SINF");
	printf("%d\n", a);
    }

 .. class:: comment

    En C, la fonction `printf(3)`_ prend un nombre variable d'arguments. Le premier est toujours une spÃ©cification de formatage qui indique la chaÃ®ne de caractÃ¨res Ã  afficher. Les autres arguments sont des identifiants de variables dont les valeurs seront utilisÃ©es pour construire la chaÃ®ne de caractÃ¨res Ã  afficher. Le deuxiÃ¨me argument remplace le premier format `%d`, le troisiÃ¨me argument le deuxiÃ¨me format, etc. La page de manuel de `printf(3)`_ fournit de nombreux dÃ©tails sur le fonctionnement de cette fonction qui accepte de nombreux paramÃ¨tres.

.. class:: negative

-
 .. code:: c

    #include <stdlio.h>
    int main(int argc, const char *argv[]) {
        int a = 1252;
        printf("SINF%a\n", a);
    }

 .. class:: comment

    Dans la fonction `printf(3)`_, ``%a`` est utilisÃ© lorsque l'on veut placer dans une chaÃ®ne de caractÃ¨res un nombre rÃ©el en notation hexadÃ©cimale. Dans ce cas, ``a`` Ã©tant un entier, il aurait fallu utiliser ``%d``.

-
 .. code:: c

    #include <stdlio.h>
    int main(int argc, const char *argv[]) {
        int a = 1252;
        printf(SINF);
	printf(%d\n, a);
    }

 .. class:: comment

    En C, une chaÃ®ne de caractÃ¨res (ou un descripteur de format pour `printf(3)`_ qui est aussi une chaÃ®ne de caractÃ¨res) commence et se termine par le caractÃ¨re ``"``.

-
 .. code:: c

    #include <stdlio.h>
    int main(int argc, const char *argv[]) {
        int a = 1252;
        printf("SINF$a\n", a);
    }

 .. class:: comment

    Dans la fonction `printf(3)`_ en C, et contrairement Ã  d'autres langages, le caractÃ¨re ``$`` ne joue pas de rÃ´le particulier. Le programme ci-dessus affichera donc simplement ``SINF$a`` Ã  l'Ã©cran.


Question 5. Arguments passÃ©s Ã  un programme C
-----------------------------------------------

ConsidÃ©rons le programme C ci-dessous qui permet de manipuler les arguments passÃ©s en ligne de commande.

        .. code-block:: c

                #include <stdlio.h>
                #include <stdlib.h>
                int main(int argc, const char *argv[])
                {
                        int a = atoi(argv[1]);
                        printf("%d\n", a);
                }

Parmi les groupes d'affirmations ci-dessous, un seul ne contient que des affirmations qui sont toutes vraies. Lequel ?


.. class:: positive

-

  - Lors de l'exÃ©cution de la fonction ``main``, ``argc`` est initialisÃ© au nombre d'arguments passÃ©s au programme (y compris le nom de l'exÃ©cutable lui-mÃªme).
  - Lors de l'exÃ©cution de la fonction ``main``, le tableau ``argv[]`` contient dans ```argv[0]`` le nom du programme, dans ``argv[1]`` le premier argument, etc.
  - La fonction ``atoi`` permet de convertir une chaÃ®ne de caractÃ¨res en l'entier Ã©quivalent.


.. class:: negative

-
  - Lors de l'exÃ©cution de la fonction ``main``, ``argc`` est initialisÃ© Ã  zÃ©ro.
  - Lors de l'exÃ©cution de la fonction ``main``, le tableau ``argv[]`` contient dans ``argv[0]`` le premier argument, dans ``argv[1]`` le second argument, etc.
  - La fonction ``atoi`` calcule la taille de son argument.

  .. class:: comment

     Les trois affirmations sont fausses. ``argc`` sera toujours initialisÃ© Ã  un vu que le nom du programme est toujours passÃ© en argument. Le premier Ã©lÃ©ment du tableau ``argv[]``, ``argv[0]``, est le nom du programme qui est exÃ©cutÃ©. Enfin, la fonction ``atoi`` permet de convertir une chaÃ®ne de caractÃ¨res en l'entier Ã©quivalent.

-
  - Lors de l'exÃ©cution de la fonction ``main``, ``argc`` est le nombre maximum d'arguments que l'on peut lui passer.
  - Lors de l'exÃ©cution de la fonction ``main``, le tableau ``argv[]`` contient dans ``argv[0]`` le premier argument, dans ``argv[1]`` le second argument, etc.
  - La fonction ``atoi`` doit prendre comme argument une chaÃ®ne de caractÃ¨res qui ne contient que des chiffres.

  .. class:: comment

     Les deux premiÃ¨res affirmations sont fausses. ``argc`` contient le nombre d'arguments passÃ©s effectivement au programme. Le premier Ã©lÃ©ment du tableau ``argv[]``, ``argv[0]``, est le nom du programme qui est exÃ©cutÃ©.

-
  - Lors de l'exÃ©cution de la fonction ``main``, le tableau ``argv[]`` contient dans ```argv[0]`` le premier argument, dans ``argv[1]`` le second argument, etc.
  - La fonction ``atoi`` permet de convertir une chaÃ®ne de caractÃ¨res en l'entier Ã©quivalent.

  .. class:: comment

     Le premier Ã©lÃ©ment du tableau ``argv[]``, ``argv[0]``, est le nom du programme qui est exÃ©cutÃ©.

.. include:: ../../../links.rst
.. include:: ../../../man_links.rst
.. include:: ../../../incl_links.rst
