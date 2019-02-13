.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_



Questions INGINIOUS
-------------------

#. Faites l'exercice relatif à `printf(3)`_ sur INGINIOUS : https://inginious.info.ucl.ac.be/course/LSINF1252/printf

#. Un utilisateur peut adapter le comportement d'un programme via les arguments passés en ligne de commande. Ecrivez un programme permettant d'afficher un argument sur deux tel qu'indiqué sur INGINIOUS: https://inginious.info.ucl.ac.be/course/LSINF1252/main_argc

#. L'an dernier, vous avez écrit un programme permettant de détecter si une chaîne de caractères était un palindrome. Faites de même en C avec l'exercice INGINIOUS https://inginious.info.ucl.ac.be/course/LSINF1252/palindrome

#. Ecrivez le corps de la fonction `swap2 <https://inginious.info.ucl.ac.be/course/LSINF1252/swap2int>`_ permettant d'échanger les valeurs stockées dans deux variables de type entier. Faites de même lorsque les arguments de cette fonction sont des structures contenant des fractions : https://inginious.info.ucl.ac.be/course/LSINF1252/swap2int

#. La libraire `string(3)`_ implémente un grand nombre de fonctions de manipulation des strings qui vous serons utile lors de différents projets de programmation. 

        * `strlen(3)`_
        * `strcat(3)`_
        * `strcasecmp(3)`_

   
   Ecrivez le code implémentant ces trois fonctions. Pour cela, créez un fichier ``string.c`` contenant la définition des fonctions et un fichier ``string.h`` avec les `déclarations <http://en.wikipedia.org/wiki/Declaration_(computer_programming)>`_ des fonctions. Vous devez aussi fournir un Makefile (cfr :ref:`outils:make`) qui permet de recompiler facilement votre programme en tapant ``make``. Pensez à implémenter quelques tests pour vos fonctions dans la fonction ``main`` et n'incluez pas l'exécutable dans l'archive. Pour la réalisation de ces tests, utilisez une librairie de tests unitaires telle que `CUnit <http://cunit.sourceforge.net>`_

   Lorsque vous considérez que votre programme est correct, testez son bon fonctionnement via l'exercice correspondant sur inginious : https://inginious.info.ucl.ac.be/course/LSINF1252/mini-projet-string

#. Faites l'exercice `swap <https://inginious.info.ucl.ac.be/course/LSINF1252/swap>`_ sur INGInious

#. Faites les exercices de manipulation de bits sur `INGInious <https://inginious.info.ucl.ac.be/course/LSINF1252>`_. Pour réaliser ces exercices, réfléchissez d'abord sur papier, par exemple sur des blocs de 4 ou 8 bits. Pour la plupart des questions, il faut combiner des décalages à gauche ou à droite avec des opérations ``AND`` (``&``), ``OR`` (``|``) et ``NOT`` (``~``) bit à bit.

   - https://inginious.info.ucl.ac.be/course/LSINF1252/bits_leftmost
   - https://inginious.info.ucl.ac.be/course/LSINF1252/bits_rightmost
   - https://inginious.info.ucl.ac.be/course/LSINF1252/set_bit
   - https://inginious.info.ucl.ac.be/course/LSINF1252/bits_spin
   - https://inginious.info.ucl.ac.be/course/LSINF1252/bits_sum
   - https://inginious.info.ucl.ac.be/course/LSINF1252/bits_strong


Questions de discussion
-----------------------

.. only:: staff 

   #. La zone mémoire utilisée diffère d'un type primitif à un autre. Ecrivez un code qui permet d'afficher le nombre de bytes utilisés sur un système 64 bits (une machine des salles) et une machine 32 bits (sirius, voir section :ref:`outils:ssh`) pour représenter un ``int``, ``long``, ``void *``, ``char *``, ``size_t`` et ``uint64_t``. Expliquez les différences.

        .. important::

                Il est nécessaire de recompiler le code source si vous voulez exécuter le binaire sur une autre architecture. Le type ``uint64_t`` est défini dans `stdint.h`_.
                Sur sirius ``gcc`` n'est pas forcément disponible, il faut dans ce cas utiliser ``cc`` à la place

.. only:: staff

   #. En utilisant des opérations binaires (décalage, and, or, ...), définissez un algorithme efficace pour trouver la valeur du bit le moins significatif d'un entier ``i`` (ex, 8 pour 56, 16 pour 208).

            .. note::

                        La plupart des étudiants vont probablement écrire un code similaire à:

                                .. code-block:: c

                                        int c;
                                        for ( c = 0 ; !((i >> c) & 1) ; c++ ) ;
                                        printf("%d\n", 1 << c);

                        Mais il existe plus efficace:

                                .. code-block:: c

                                        printf("%d\n", i & (~i + 1));

#. Soit ``char *ptr = "Test"``. Itérez sur ce pointeur et affichez avec `printf(3)`_ la valeur et l'adresse mémoire où se trouve stocké chaque caractère de deux façons différentes. Regardez la manpage de `printf(3)`_ pour savoir comment afficher la valeur d'un pointeur.

#. Lorsque l'on veut améliorer les performances d'un programme, il est utile de pouvoir mesurer précisément son temps d'exécution. La commande `time(1posix)`_ permet d'effectuer cette mesure depuis la ligne de commande. Parfois, on souhaite mesurer le temps de calcul une partie critique d'un code. Une façon simple pour obtenir cette mesure est d'utiliser `gettimeofday(2)`_ comme dans l'exemple ci-dessous (:download:`/Programmes/s2_perf.c`).

        .. literalinclude:: /Programmes/s2_perf.c
                :encoding: utf-8
                :language: c

   Pour certaines opérations, les performances dépendent du type de données utilisé. Modifiez le programme ci-dessous de façon à utiliser un calcul plus compliqué que la simple addition et comparez sur de longues itérations (:math:`10^7` ou plus) les performances de cette opération lorsqu'elle utilise des ``int``, ``long long``, ``double`` ou ``float``. Les performances sont-elles identiques ?


Questions de bilan final
------------------------

#. La structure suivante ``foo_t`` est définie de façon à ce qu'elle contienne un ``char`` suivi d'un entier. D'après vous combien de bytes occupe cette structure en mémoire ? Vérifiez ce que vous pensiez en utilisant ``sizeof``. (bonus: expliquez vos résultats.)

        .. code-block:: c

                struct foo_t {
                        char a;
                        int b;
                };


#. Considérez le programme suivant.

        .. literalinclude:: /Programmes/s2_qbf.c
                :encoding: utf-8
                :language: c

      * Sans executer le programme, essayez de comprendre son fonctionnement. En particulier, quelles seront les adresses affichées à chaque tour de boucle?
      * Compilez le programme et exécutez le. Expliquez sa sortie et comparez avec vos attentes.
      * (Bonus) Expliquez les valeurs affichées lors de l'exécution de la dernière boucle.
