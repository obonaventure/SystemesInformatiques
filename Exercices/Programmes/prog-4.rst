.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices INGINIOUS
===================

Deux sortes d'exercices INGINIOUS vous sont proposés durant cette semaine. Les premiers portent sur les structures chaînées car ces structures de données permettent de bien vérifier la compréhension des pointeurs en C.

 - https://inginious.info.ucl.ac.be/course/LSINF1252/simple_stack
 - https://inginious.info.ucl.ac.be/course/LSINF1252/cmp_func
 - https://inginious.info.ucl.ac.be/course/LSINF1252/linked_structs
 - https://inginious.info.ucl.ac.be/course/LSINF1252/advanced_queue
 - https://inginious.info.ucl.ac.be/course/LSINF1252/order_relation_linked_list 

Après avoir écrit de nombreuses fonctions C, il est maintenant temps pour vous de commencer à écrire des 
programmes composés de plusieurs fonctions. Pour cela, l'utilitaire `make(1)`_ vous sera très utile. Prenez un peu de temps pour lire le chapitre qui lui est consacré dans le syllabus et essayez de répondre aux questions ci-dessous :

 - https://inginious.info.ucl.ac.be/course/LSINF1252/s2_make
 - https://inginious.info.ucl.ac.be/course/LSINF1252/s2_make_calc
 - https://inginious.info.ucl.ac.be/course/LSINF1252/s2_make_mcq

.. only:: staff

    - https://inginious.info.ucl.ac.be/course/LSINF1252/s3_make
    - https://inginious.info.ucl.ac.be/course/LSINF1252/s3_make_mcq
    - https://inginious.info.ucl.ac.be/course/LSINF1252/s3_cunit_basics
    - https://inginious.info.ucl.ac.be/course/LSINF1252/s3_make_tests

Lorsque l'on écrit des programmes en C ou dans un autre langage, il est important de tester
le bon fonctionnement de toutes les fonctions du programme pour éviter des erreurs et autres
bugs difficiles à corriger. L'idéal est de commencer par écrire les tests qui valident le bon 
fonctionnement de chaque fonction *avant* d'écrire cette fonction. Plusieurs librairies peuvent vous
aider à écrire de tels tests. CUnit (:ref:`outils:ref_cunit`) est l'un d'entre elles. 
Prenez le temps de lire le chapitre
qui lui est consacré dans le syllabus.

Pour démontrer votre bon utilisation de `make(1)`_ et CUnit, reprenez le programme que vous
avez écrit pour l'exercice `test <https://inginious.info.ucl.ac.be/course/LSINF1252/commandetest>`_ 
,
divisez-le en plusieurs fichiers, ajoutez-y des tests unitaires pour chaque fonction et
utilisez `make(1)`_ pour automatiser le tout. Si vous voulez allez plus loin, essayez d'utiliser
la librarie `getopt(3)`_ pour traiter les arguments reçus en ligne de commande.


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

.. only:: staff

   #. Dans le cours théorique, nous avons parlé des instructions ``set`` qui permettent de fixer la valeur d'un byte d'un registre en fonction de la valeur des drapeaux du registre ``eflags``. Comment feriez-vous pour compiler en assembleur la ligne ``b=(a>0)`` sans utilisez cette instruction et en sachant que les valeurs de ``a`` et ``b`` sont initialement dans les registres ``%eax`` et ``%ecx``. Pour répondre à cette question, écrivez d'abord un code en C semblable au code ci-dessous :

	.. code-block:: c

		if ( condition)
		    { b=1; }
		else
		    { b=0; }


   #. Avec le compilateur gcc, il est aussi possible de compiler du code assembleur directement dans une programme C. Cette fonctionnalité est intéressante si vous voulez tester de petites fonctions écrites en langage assembleur. Ainsi, une fonction baptisée ``rien`` et qui ne fait absolument rien peut s'écrire comme suit:


    .. code-block:: c

       extern void rien();  // indique au compilateur que la fonction est externe

       __asm__(
       "rien:\n"
       "   ret\n"
       );


    En utilisant l'assembleur [IA32]_, écrivez les instructions assembleur qui permettent d'implémenter une fonction qui ne prend aucun argument et retourne toujours l'entier ``1``.

		.. note::

			.. code-block:: c

				movl $1,%eax
				ret


    De la même façon, écrivez la fonction ``add`` qui prend deux arguments de type ``int`` et retourne la somme de ces deux arguments.

                  .. note::

		       .. code-block:: c

		          /* add(int a, int b) */
			  __asm__(
			  "add:\n"
			  "   subl $8, %esp\n"
			  "   movl 16(%esp), %eax\n"
			  "   movl 12(%esp), %ebx\n"
			  "   movl %ebx, %eax\n"
			  "   addl $8, %esp\n"
			  "   ret\n"
        		  );


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

		.. note::

			La valeur de retour étant dans %eax, il n'y a aucun problème à l'ignorer, elle sera juste écrasée à la première utilisation de %eax



     #. Trois exercices se trouvent sur INGInious. Un exercice sur la `Comparaison de Fractions <https://inginious.info.ucl.ac.be/course/LSINF1252/fractions>`_, un nouvel exercice sur les `les listes chaînées <https://inginious.info.ucl.ac.be/course/LSINF1252/linked_lists_2>`_ et finalement l'implémentation de `strsep <https://inginious.info.ucl.ac.be/course/LSINF1252/strsep>`_.

     #. Vous trouverez également sur INGInious plusieurs exemples de questions typiques sur l'assembleur à l'examen. Ces questions portent sur la traduction d'un code assembleur dans son équivalent en C. `Première question <https://inginious.info.ucl.ac.be/course/LSINF1252/asm1>`_, `deuxième question <https://inginious.info.ucl.ac.be/course/LSINF1252/asm2>`_, `troisième question <https://inginious.info.ucl.ac.be/course/LSINF1252/asm3>`_ et `quatrième question <https://inginious.info.ucl.ac.be/course/LSINF1252/asm4>`_ .


Question de bilan final
=======================

Considérez le programme suivant.

	.. literalinclude:: src/s4_qbf.c
                :encoding: utf-8
                :language: c

* Dessinez le schéma de l'organisation mémoire du programme. Identifiez dessus où se trouvent toutes les variables présentes dans le programme.
* Pour chaque ligne du programme, indiquez quelles zones mémoires sont accédées et leur contenu après exécution.

.. only:: staff

	Cette question est importante à réaliser, n'hésitez pas à y passer une bonne demi-heure. Insistez pour commencer à dessiner le schema au tableau et que les étudiants interagissent directement dessus.

	Dans la section code: f, main.
	Dans la section initialisée: cours et 97850 (insistez sur ce dernier!).
	Dans la section heap: la zone mémoire pointée par tab.
	Dans la stack (à des niveaux différents): d, tab, res, c, x. Notez que les arguments des fonctions sont aussi mis sur la stack (y compris a, b, argc et argv), mais insistez là-dessus lors de l'exécution du programme.
	Dans la zone param/env: le contenu de argv.