.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. _gdb-ref:

GDB
---

`gdb(1)`_ permet de débugger vos programmes plus facilement en permettant d'analyser l'état de l'exécution. A titre d'exemple, essayez de lancer le programme :download:`src/gdb.c`. Ce programme contient plusieurs bugs que vous pourrez détecter plus facilement avec `gdb(1)`_.

Pour pouvoir analyser votre exécutable avec `gdb(1)`_, vous devez ajouter les symboles de débuggage lors de la compilation en utilisant l'option ``-g`` de `gcc(1)`_:

	.. code-block:: console

		gcc -g gdb.c -o my_program

Lancez gdb avec la commande ``gdb my_program``. Ceci va vous ouvrir la console de gdb qui vous permet de lancer, le programme et de l'analyser. Pour démarrer le programme, tapez ``run``. gdb va arrêter l'exécution au  premier problème trouvé. Vous pouvez afficher la pile des appels de fonction avec la commande ``backtrace``. Votre programme tourne encore pour l'instant. Arrètez-le avec la commande ``kill``.

Pour analyser un programme, vous pouvez y placer des breakpoints. Un breakpoint permet de mettre en pause l'exécution d'un programme à un endroit donné pour pouvoir afficher l'état des variables et faire une exécution pas-à-pas. Pour mettre un breakpoint, vous avez plusieurs choix:
 
	* ``break [function]`` met en pause l'exécution à l'appel de la fonction argument de la commande 
	* ``break [filename:linenumber]`` spécifie le fichier du code source et la ligne à laquelle l'exécution doit s'arrêter

Pour notre petit programme, mettez un breakpoint à l'appel à la fonction *iter*, en tappant ``break iter`` dans la console de gdb. Ensuite lancez le programme de nouveau avec ``run``. Votre programme va s'arrèter au début de la fonction *iter*, juste avant l'appel à *printf*. Pour continuer l'exécution vous avez plusieurs choix:
 
	* ``next`` exécute la prochaine instruction de votre code source, mais sans rentrer dans des fonctions externes.
	* ``step`` exécute la prochaine instruction de votre code source, mais en entrant dans le code des fonctions appelées.
	* ``continue`` continue le reste de l'exécution.

Dans notre programme on vient de s'arrêter juste avant l'appel à *printf*. Vu qu'on n'est pas intéressé par les détails d'exécution de cette fonction, on passe à la prochaine instruction en tappant ``next``. Tapez de nouveau ``next`` pour que gdb entre dans la boucle ``for`` de la fonction *iter*. gdb va s'arrèter maintenant juste avant l'appel à la fonction *calc*. Cette fonction pourrait contenir le bug, donc on passe à la prochaine instruction en tapant ``step`` pour que gdb nous montre les détails de *calc*.

gdb permet nous d'afficher le contenu des variables au moment auquel on vient de mettre en pause notre programme. Pour afficher des variables vous avez les options suivantes:
 
	* ``p/x`` - affiche en format hexadécimal la variable spécifiée
	* ``p/d`` - en format d'un entier signé
	* ``p/f`` - en format floating point
	* ``p/c`` - affiche un caractère.

Dans notre exemple on est intéressé par les valeurs des variables *num* et *i*. Tapez ``p/d num`` et ensuite ``p/d i`` pour afficher leur contenu. Vous verrez que *i* vaut 0 et que donc vous avez une division par zéro qui est la cause du bug.

Pour arrêter la console de gdb, tappez ``quit``.

Plus d'informations sur `gdb(1)`_ peuvent être trouvées sur:
 
	* http://www.cprogramming.com/gdb.html
	* http://www.ibm.com/developerworks/library/l-gdb/


