.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


1. Questions de base
--------------------

#. La zone mémoire utilisée diffère d'un type primitif à un autre. Ecrivez un code qui permet d'afficher le nombre de bytes utilisés sur un système 64 bits (une machine des salles) et une machine 32 bits (sirius, voir section :ref:`outils:ssh`) pour représenter un ``int``, ``long``, ``void *``, ``char *``, ``size_t`` et ``uint64_t``. Expliquez les différences.

        .. important::

                Il est nécessaire de recompiler le code source si vous voulez exécuter le binaire sur une autre architecture. Le type ``uint64_t`` est défini dans `stdint.h`_.
                Sur sirius ``gcc`` n'est pas forcément disponible, il faut dans ce cas utiliser ``cc`` à la place.

#. En utilisant des opérations binaires (décalage, and, or, ...), définissez un algorithme efficace pour trouver la valeur du bit le moins significatif d'un entier ``i`` (ex, 8 pour 56, 16 pour 208).

        .. only:: staff

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



#. Faites l'exercice sur `INGInious <https://inginious.info.ucl.ac.be/course/LSINF1252-new/swap>`_

#. La structure suivante ``foo_t`` est définie de façon à ce qu'elle contienne un ``char`` suivi d'un entier. D'après vous combien de bytes occupe cette structure en mémoire ? Vérifiez ce que vous pensiez en utilisant ``sizeof``. (bonus: expliquez vos résultats.)

        .. code-block:: c

                struct foo_t {
                        char a;
                        int b;
                };


Mini-Projets
------------

#. La libraire `string(3)`_ implémente un grand nombre de fonctions de manipulation des strings qui vous serons utile lors de différents projets de programmation. Pour ce mini-projet vous devriez implémenter les fonctions suivantes:

        * `strlen(3)`_
        * `strcat(3)`_
        * `strcasecmp(3)`_

   Le mini-projet est à soumettre via iCampus dans la partie Travaux.
   
   Soumettez votre code dans une archive zip ou tar contenant un dossier ``Projet_S2``. Vous devrez créer un fichier ``string.c`` contenant la définition des fonctions et un fichier ``string.h`` avec les `déclarations <http://en.wikipedia.org/wiki/Declaration_(computer_programming)>`_ des fonctions. Vous devez aussi fournir un Makefile (cfr :ref:`outils:make`) qui permettra à votre tuteur de recompiler facilement votre programme en tapant ``make``. Pensez à implémenter quelques tests pour vos fonctions dans la fonction ``main`` et n'incluez pas l'exécutable dans l'archive.



#. Lorsque l'on veut améliorer les performances d'un programme, il est utile de pouvoir mesurer précisément son temps d'exécution. La commande `time(1posix)`_ permet d'effectuer cette mesure depuis la ligne de commande. Parfois, on souhaite mesurer le temps de calcul une partie critique d'un code. Une façon simple pour obtenir cette mesure est d'utiliser `gettimeofday(2)`_ comme dans l'exemple ci-dessous (:download:`/Programmes/s2_perf.c`).

        .. literalinclude:: /Programmes/s2_perf.c
                :encoding: utf-8
                :language: c

   Pour certaines opérations, les performances dépendent du type de données utilisé. Modifiez le programme ci-dessous de façon à utiliser un calcul plus compliqué que la simple addition et comparez sur de longues itérations (:math:`10^7` ou plus) les performances de cette opération lorsqu'elle utilise des ``int``, ``long long``, ``double`` ou ``float``. Les performances sont-elles identiques ?


