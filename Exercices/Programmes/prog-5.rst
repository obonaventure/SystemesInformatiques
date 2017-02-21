.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Exercices
=========


#. La fonction `pthread_join(3)`_ utilise un deuxième argument de type ``void **``. Pourquoi est-il nécessaire d'utiliser un pointeur vers un pointeur et pas simplement un pointeur ``void *`` ?

#. A votre avis, pourquoi le premier argument de la fonction `pthread_create(3)`_ est-il un pointeur de type `pthread_t *` alors que le premier argument de la fonction `pthread_join(3)`_ est lui simplement de type `pthread_t`?

#. Avec les threads POSIX, comment peut-on passer plusieurs arguments à la fonction démarrée par `pthread_create(3)`_ ? Ecrivez un petit exemple en C qui permet de passer un entier et un caractère à cette fonction.

#. Ecrivez un code qui permet de récupérer un tableau d'entiers d'un thread. Exercice disponible sur `INGInious <https://inginious.info.ucl.ac.be/course/LSINF1252/threads_1>`_.

#. Essayez de lancer un grand nombre de threads d'exécution sur votre machine. Quel est le nombre maximum de threads que `pthread_create(3)`_ vous autorise à lancer ?

#. Quelle différence voyez-vous entre `pthread_exit(3)`_ et `exit(3)`_ ?

#. Un étudiant souhaite passer un tableau d'entiers comme argument à un thread et écrit le code suivant. Qu'en pensez-vous ?

   .. literalinclude:: /Programmes/src/pthread-array.c
      :encoding: utf-8
      :language: c
      :start-after: ///AAA

#. Considérons le programme de test des threads POSIX ci-dessous. Ce programme utilise 4 threads qui incrémentent chacun un million de fois une variable globale.

   .. literalinclude:: /Programmes/src/pthread-test.c
      :encoding: utf-8
      :language: c
      :start-after: ///AAA

   Exécutez ce programme (:download:`/Programmes/src/pthread-test.c`) et observez le résultat qu'il affiche à l'écran. Pouvez-vous expliquer le comportement de ce programme ?

#. Résolvez des sudokus. Exercice disponible sur `INGInious <https://inginious.info.ucl.ac.be/course/LSINF1252/sudoku>`_.

Mini-projet: Mesure de performance
==================================

On vous demande de transformer un code monothreadé en un code multithreadé. Vous devez vous baser sur le code présent dans l'archive: :download:`/Programmes/src/prog-5-measure/prog-5-measure.tar.gz`. Le programme permet de chiffrer ou déchiffrer des mots de passe passés en argument au programme. Ce dernier prend plusieurs arguments additionels:

    * ``-p`` définit le mot de passe à utiliser
    * ``-n`` définit le nombre de fois que chaque mot de passe est chiffré/déchiffré
    * ``-d`` définit que le programme doit déchiffrer les mots de passes (il chiffre par défaut)

Un exemple d'utilisation du programme est le suivant:

    .. code-block:: c

        $ ./crypt -p toto -n 10000 test Bonjour!
        CAC7EF483F90C988 0F5766990DFA0914
        $ ./crypt -p toto -n 10000 -d CAC7EF483F90C988 0F5766990DFA0914
        test Bonjour!

Vous devez donc vous baser sur le code existant afin de paralléliser le chiffrement/déchiffrement des mots de passe. Vous ne devez pas nécessairement afficher les mots de passe (ou chiffrés) dans l'ordre. Vous devez cependant ajouter un argument ``-t`` au programme qui définit le nombre de threads que le programme exécutera en parallèle.

On vous demande également d'évaluer l'impact des arguments ``-t`` et ``-n`` sur l'exécution du programme. Pensez à exécuter votre programme avec un argument ``-n`` suffisamment grand si vous voulez évaluer l'impact de ``-t``. On vous demande plus spécifiquement de générer un graphique qui montre pour différentes valeurs le temps de calcul. Vous pouvez utiliser `time(1posix)`_ afin de récupérer le temps d'exécution d'un programme:

    .. code-block:: c

        $ time ./crypt -p toto -n 10000 -d CAC7EF483F90C988 0F5766990DFA0914
        test Bonjour!

        real	0m0.019s
        user	0m0.016s
        sys	0m0.000s
        $ time ./crypt -p toto -n 9999999 -d 774069EB86ED86FA 7D1AC0A4CF56F942
        test Bonjour!

        real	0m16.104s
        user	0m16.101s
        sys	0m0.000s
