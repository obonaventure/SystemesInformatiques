.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices
=========

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

 .. only:: staff

		.. note::

			.. code-block:: c

				movl $1,%eax
				ret


    De la même façon, écrivez la fonction ``add`` qui prend deux arguments de type ``int`` et retourne la somme de ces deux arguments.

 .. only:: staff

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

 .. only:: staff

		.. note::

			La valeur de retour étant dans %eax, il n'y a aucun problème à l'ignorer, elle sera juste écrasée à la première utilisation de %eax




#. Vous trouverez sur INGInious plusieurs exemples de questions typiques sur l'assembleur à l'examen. Ces questions portent sur la traduction d'un code assembleur dans son équivalent en C. `Première question <https://inginious.info.ucl.ac.be/course/LSINF1252/asm1>`_, `deuxième question <https://inginious.info.ucl.ac.be/course/LSINF1252/asm2>`_, `troisième question <https://inginious.info.ucl.ac.be/course/LSINF1252/asm3>`_ et `quatrième question <https://inginious.info.ucl.ac.be/course/LSINF1252/asm4>`_ .

