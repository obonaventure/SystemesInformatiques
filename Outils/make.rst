.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. _make:

Introduction aux Makefiles
--------------------------

Les Makefiles sont des fichiers utilisés par le programme `make(1)`_ afin d'automatiser un ensemble d'actions permettant la génération de fichiers, la plupart du temps résultant d'une compilation.

Un Makefile est composé d'un ensemble de règles de la forme:

	.. code-block:: make
		
		target [target ...]: [component ...]
			[command]
			...
			[command]

Chaque règle commence par une ligne de dépendance qui défini une ou plusieurs cibles (``target``) suivies par le caractère ``:`` et éventuellement une liste de composants (``components``) dont dépend la cible. Une cible ou un composant peut-être un ficher ou un simple label.

Le fichier suivant reprend un exemple de règle où la cible et le composant sont des fichiers. 
	
	.. code-block:: make
	
		text.txt: name.txt
			echo "Salut, " > text.txt
			cat name.txt >> text.txt

Lorsque ``make`` est exécuté en utilisant ce Makefile, on obtient:

	.. code-block:: console
	
		$ make
		make: *** No rule to make target `name.txt', needed by `text.txt'.  Stop.

Comme ``text.txt`` dépend de ``name.txt``, il faut que ce dernier soit défini comme cible dans le Makefile ou exister en tant que fichier. Si nous créons le fichier ``name.txt`` contenant ``Tintin`` et que ``make`` est ré-exécuté, on obtient la sortie suivante :

	.. code-block:: console
	
		$ make
		echo "Salut, " > text.txt
		cat name.txt >> text.txt
		$ cat text.txt
		Salut, 
		Tintin

Lorsqu'une dépendance change, ``make`` le détecte et ré-exécute les commandes associées à la cible. Dans le cas suivant le fichier ``name.txt`` est modifié ce qui force la regénération du fichier ``text.txt``.

	.. code-block:: console
	
		$ make
		make: `text.txt' is up to date.
		$ echo Milou > name.txt
		$ make
		echo "Salut, " > text.txt
		cat name.txt >> text.txt
		$ cat text.txt
		Salut, 
		Milou

Comme spécifié précédemment, les Makefiles sont principalement utilisés pour automatiser la compilation de projets. Si un projet dépend d'un fichier source ``test.c``, le Makefile permettant d'automatiser sa compilation peut s'écrire de la façon suivante:

.. code-block:: make

	test: test.c
		gcc -o test test.c

Ce Makefile permettra de générer un binaire ``test`` à chaque fois que le fichier source aura changé. Pour plus d'information sur l'écriture ou utilisation des Makefiles voir http://gl.developpez.com/tutoriel/outil/makefile/

