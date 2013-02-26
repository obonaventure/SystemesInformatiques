.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Exercices
=========

#. Considérons un tableau contenant des fractions. Chacun de ces fractions est définie en utilisant la structure ``fraction_t``. Comment feriez-vous pour trier ce tableau en ordre croissant en utilisant `qsort(3)`_ ? Ecrivez la fonction de comparaison et l'appel à `qsort(3)`_

#. Proposez une implémentation d'un sous-ensemble de la fonction `strsep(3)`_ de la librairie. Pour votre implémentation, supposez que votre version de `strsep(3)`_ est toujours appelée avec un pointeur vers un seul caractère comme second argument. Comparez votre implémentation avec celle de la librairie standard.

#. La fonction `pthread_join(3)`_ utilise un deuxième argument de type ``void **``. Pourquoi est-il nécessaire d'utiliser un pointeur vers un pointeur et pas simplement un pointeur ``void *`` ?

#. Le programme :download:`/Exercices/Programmes/src/stack.c` que nous avons vu précédemment implémente un stack en utilisant un pointer vers le sommet de la pile qui est une variable globale. Comment pourriez-vous réécrire les fonctions ``push`` et ``pop`` de façon à ce qu'elles puissent être génériques et s'appliquer à une pile quelconque qui est indiquée dans leur premier argument. Astuce: pensez à utiliser des pointeurs vers des pointeurs.

#. A votre avis, pourquoi le premier argument de la fonction `pthread_create(3)`_ est-il un pointeur de type `pthread_t *` alors que le premier argument de la fonction `pthread_join(3)`_ est lui simplement de type `pthread_t`?

#. Avec les threads POSIX, comment peut-on passer plusieurs arguments à la fonction démarrée par `pthread_create(3)`_ ? Ecrivez un petit exemple en C qui permet de passer un entier et un caractère à cette fonction.

#. Ecrivez un code qui permet de récupérer un tableau d'entier d'un thread. Exercice disponible sur `pythia <http://pythia.info.ucl.ac.be/module/10/problem/41>`_.

#. Essayez de lancer un grand nombre de threads d'exécution sur votre machine. Quel est le nombre maximum de threads que `pthread_create(3)`_ vous autorise de lancer ?

#. Quelle différence voyez-vous entre `pthread_exit(3)`_ et `exit(3)`_ ?

#. Un étudiant souhaite passer un tableau d'entiers comme argument à un thread et écrit le code suivant. Qu'en pensez-vous ?

 .. literalinclude:: /Programmes/Exercices/src/pthread-array.c
    :encoding: iso-8859-1
    :language: c
    :start-after: ///AAA

#. Considérons le programme de test des threads POSIX ci-dessous. Ce programme utilise 4 threads qui incrémentent chacun un million de fois une variable globale. 

 .. literalinclude:: /Exercices/Programmes/src/pthread-test.c
    :encoding: iso-8859-1
    :language: c
    :start-after: ///AAA
 
 Exécutez ce programme (:download:`/Exercices/Programmes/src/pthread-test.c`) et observez le résultat qu'il affiche à l'écran. Pouvez-vous expliquer le comportement de ce programme ?
 
#. Résolvez des sudokus. Exercice disponible sur `pythia <http://pythia.info.ucl.ac.be/module/10/problem/42>`_.

