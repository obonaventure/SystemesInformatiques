.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Questions
---------

#. Expliquez la différence entre `malloc(3)`_ et `calloc(3)`_. D'après vous, quel appel sera le plus lent ?

#. Dans la fonction ``push`` du programme de manipulation d'un pile :download:`/../Theorie/C/S3-src/stack.c`, faut-il remplacer l'appel à `malloc(3)`_ par un appel à `calloc(3)`_

	.. only:: staff

	    .. note::

			Non. La zone mémoire est initialisée directement après.

#.  Le prototype de la fonction ``push`` du programme de manipulation d'une pile :download:`/../Theorie/C/S3-src/stack.c`,  est ``void push(struct fraction_t *)``. Serait-il possible d'écrire une function push ayant comme prototype ``void push(struct fraction_t)`` ? Qu'est-ce qui changerait dans ce cas ?

	.. only:: staff

	    .. note::

			Pas possible.

#. Les fonctions ``push`` et ``pop`` définies dans l'exemple de manipulation d'une pile :download:`/../Theorie/C/S3-src/stack.c` utilisent une pile qui est définie par un pointeur qui est une variable locale. Est-il possible de réécrire ces fonctions de façon à ce qu'elles prennent comme argument un pointeur vers la pile ? Leurs prototypes deviendraient :

   - ``void push(struct node_t *, struct fraction_t *);``
   - ``struct fraction_t * pop(struct node_t *);``

	.. only:: staff

	    .. note::

		Oui, idéalement dans ce cas, il faudrait définir une fonction init qui renverrait un ``struct node_t *``.


#. En C, on peut définir des tableaux à deux dimensions avec une déclaration comme ``int a[3][3];``. Ecrivez un petit programme qui utilise des pointeurs pour déterminer si un tel tableau à deux dimensions est stocké ligne par ligne ou colonne par colonne.

	.. only:: staff

	    .. note::

		.. code-block:: c

			void main(void) {
				int a[3][3];

				if (&a[0][0] + 1 == &a[1][0])
					printf("Par ligne\n");
				else if (&a[0][0] + 1 == &a[0][1])
					printf("Par colonne\n");
				else
					printf("WTF!!!\n");
			}


#. Considérons la structure suivante:

	.. code-block:: c

		typedef struct {
			char c;
			long l;
			short s;
		} test_t;


   Combien de bytes seront utilisés en mémoire pour représenter cette structure? Représentez graphiquement la position en mémoire de chaque élément (utilisez `printf(3)`_ et ``%p``), observez-vous des trous ? Expliquez.
   Serait-il possible d'utiliser moins de bytes pour représenter cette structure ? Si oui, comment ?


	.. only:: staff

		.. note::

			La structure prend 16 bytes d'espace (sur une machine 64-bits - 12 bytes sur une machine 32 bits). C'est dû au fait que les champs sont alignés à des multiples de 64 bits (resp. 32 bits) pour éviter d'avoir des parties de variables copié sur plusieurs registres. Pour optimiser, il suffit de reordonner les champs. Par exemple:

				.. code-block:: c

					typedef struct {
						char c;
						short s;
						long l;
					} test_t;

#. Expliquez à quoi sert l'attribut ``packed`` des structures dans `gcc(1)`_ (regardez la manpage). Appliquez cet attribut à la structure de l'exercice suivant. Qu'observez-vous comme différence ? Quel sont les avantages et désavantages d'utiliser cet attribut ? Dans quel cas est-il intéressant de l'utiliser ?

	.. only:: staff

		.. note::

			Elle bypasse l'alignement décrit dans la question précédente. L'avantage est que la structure prend l'espace minimale n'importe soit l'ordonnancement des champs. Le désavatage est que la CPU doît faire plus de travail pour lire la variable, car des parties de la variable sont sur plusieurs registres, et donc la CPU doît faire des bit-shifts.


#. Exécutez plusieurs fois le code suivant. Expliquez les différents résultats obtenus.
	.. code-block:: c

		int global;
		void main(void)
		{
			int local;
			int *ptr1 = (int *)malloc(sizeof(*ptr1));
			int *ptr2 = (int *)malloc(sizeof(*ptr2));

			printf("global %p loc %p p1 %p p2 %p\n", &global, &local, ptr1, ptr2);
		}

   	.. only:: staff

		.. note::

			L'adresse de ``global`` ne change pas, car elle fait partie du segment texte du programme. Les autres sont soit sur la pile (stack), ou sur le tas (heap).

#. Faites l'exercice sur `INGInious <https://inginious.info.ucl.ac.be/course/LSINF1252-new/linked_lists_1>`_

#. Vous travaillez sur un programme qui doit manipuler des vecteurs. Afin de pouvoir supporter des vecteurs de taille quelconque, vous décidez de réimplémenter ces vecteurs vous même en utilisant des pointeurs. Votre programme définit la structure ``struct vector_t`` et les fonctions ci-dessous.
Implémentez ces fonctions sans jamais utiliser la notation des tableaux en C (``[`` et ``]``).

 .. literalinclude:: /Programmes/src/vector.c
    :encoding: utf-8
    :language: c
    :start-after: ///AAA
    :end-before: ///BBB

