.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Exercices
=========

#. Le principe de localité est un principe très important pour comprendre les performances de programmes qui accèdent beaucoup à la mémoire. Considérons tout d'abord un programme qui doit initialiser une grande zone mémoire obtenue via `malloc(3)`_.

	* Ecrivez en C une fonction d'initialisation de cette zone mémoire à la valeur ``1252`` qui profite de la localité spatiale
	* Ecrivez en C une fonction d'initialisation de cette zone mémoire qui ne profite pas du tout de la localité spatiale
	* Comparez les performances des deux programmes que vous avez écrit. Si nécessaire, désactivez l'optimisation du compilateur.

#. Un programmeur doit manipuler des tableaux contenant 100.000.000 éléments. Chaque élément du tableau contient un nombre réel et une chaîne contenant 40 caractères. Une opération très courante à effectuer est de calculer la somme de tous les éléments du tableau. A votre avis, quelles seront les performances des deux implémentations suivantes de ce programme :

	* Le tableau est implémenté comme un tableau contenant 100.000.000 structures avec dans chaque structure un ``float`` et un ``char c[40]``.
	* Le tableau est implémenté comme deux tableaux distincts. Le premier contient tous les ``float`` et le second toutes les chaînes de caractères.

#. Un programmeur propose deux fonctions différentes pour calculer la somme des éléments d'un tableau à deux dimensions. Intégrez ces fonctions dans un programme afin d'en mesurer les performances avec `gettimeofday(2)`_. Quelle est la variante la plus rapide et pourquoi ?

	.. literalinclude:: src/sumarray.c
		:encoding: utf-8
		:language: c
		:start-after: ///AAA
		:end-before: ///BBB

#. Dans le cours théorique, nous avons parlé des instructions ``set`` qui permettent de fixer la valeur d'un byte d'un registre en fonction de la valeur des drapeaux du registre ``eflags``. Comment feriez-vous pour compiler en assembleur la ligne ``b=(a>0)`` sans utilisez cette instruction et en sachant que les valeurs de ``a`` et ``b`` sont initialement dans les registres ``%eax`` et ``%ecx``. Pour répondre à cette question, écrivez d'abord un code en C semblable au code ci-dessous :

	.. code-block:: c

		if ( condition)
		    { b=1; }
		else
		    { b=0; }


#. En utilisant l'assembleur [IA32]_, écrivez les instructions assembleur qui permettent d'implémenter une fonction qui ne prend aucun argument et retourne toujours l'entier ``1``.

	.. only:: staff

		.. note::

			.. code-block:: c

				movl $1,%eax
				ret

#. Considérons une fraction de la mémoire représentée dans le tableau ci-dessous.

	==========   ========
	Adresse      Valeur
	==========   ========
	0x0C	      0x00
	0x08	      0xFF
	0x04	      0x02
	0x00         0x01
	==========   ========

	Si ``%esp`` contient initialement la valeur ``0x0C`` et que ``%eax`` et ``%ebx`` contiennent respectivement ``0x02`` et ``0x03``, que deviennent cette mémoire et les registres durant l'exécution de :

	.. code-block:: nasm

		pushl %eax
		pushl %ebx
		popl %ecx

#. En C, il n'est pas rare de voir dans certains programmes que la valeur de retour de certaines fonctions est ignorée. C'est une mauvaise pratique qui peut donner lieu à pas mal de problèmes. Connaissant la façon dont la valeur de retour d'une fonction ``int f()`` est gérée en assembleur, expliquez ce qu'il se passe en pratique lorsque la valeur de retour de ``f`` n'est pas sauvegardée.

	.. only:: staff

		.. note::

			La valeur de retour étant dans %eax, il n'y a aucun problème à l'ignorer, elle sera juste écrasée à la première utilisation de %eax



#. Trois exercices se trouvent sur Pythia. Un exercice sur la `Comparaison de Fractions <http://pythia.info.ucl.ac.be/module/10/problem/37>`_, l'implémentation d'une `Stack <http://pythia.info.ucl.ac.be/module/10/problem/38>`_ et finalement l'implémentation de `strsep <http://pythia.info.ucl.ac.be/module/10/problem/39>`_.
