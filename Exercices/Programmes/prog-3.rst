.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Questions INGINIOUS
-------------------

#. Le premier exercice INGINIOUS porte sur le heap et le stack : https://inginious.info.ucl.ac.be/course/LSINF1252/stack_vs_heap

#. `malloc(3)`_ est une fonction clé en C puisqu'elle permet d'allouer une zone de mémoire. Elle a l'inconvénient de ne *pas* initialiser cette mémoire, contrairement à `calloc(3)`_. Lisez les pages de manuel de ces deux fonctions et implémentez vous-même la fonction `calloc(3)`_ en utilisant `malloc(3)`_ : https://inginious.info.ucl.ac.be/course/LSINF1252/calloc2

#. Lorsque l'on utilise les fonctions de la librairie ou les appels systèmes, il est *nécessaire* de vérifier chaque fois leur valeur de retour pour éviter tout problème. Dans cet exercice, vous écrivez une variante de `malloc(3)`_ qui essaye plusieurs fois d'allouer de la mémoire pour pallier à un problème temporaire de manque de mémoire : https://inginious.info.ucl.ac.be/course/LSINF1252/sleep_malloc

#. La question suivante porte sur les déclarations de types de données (faites seulement les 7 premières sous-questions) : https://inginious.info.ucl.ac.be/course/LSINF1252/types

#. `strcpy(3)`_ est une fonction de la librairie standard qui permet de copier une chaîne de caractères. Cet exercice vous propose d'écrire une variante de cette fonction : https://inginious.info.ucl.ac.be/course/LSINF1252/strcpy

#. Lorsque l'on travaille avec les pointeurs, il est possible d'accéder à n'importe quel endroit de la mémoire. Cet exercice vous permet de tester vos compétences de manipulation des pointeurs: https://inginious.info.ucl.ac.be/course/LSINF1252/pointer_types

#. Un exercice classique pour montrer que l'on comprend bien les pointeurs est de manipuler des listes chainées: https://inginious.info.ucl.ac.be/course/LSINF1252/basic_linked_list

#. Un exercice sur le parcours simple d'un arbre binaire de recherche https://inginious.info.ucl.ac.be/course/LSINF1252/BST

#. Un exercice où vous devez analyser l'information reçue d'un modem : https://inginious.info.ucl.ac.be/course/LSINF1252/modem_read

#. Maintenant que vous avez écrit de nombreuses fonctions sur INGINIOUS, il est temps pour vous d'écrire votre premier programme directement en C. Utilisez un éditeur de texte pour écrire le fichier ``test.c`` qui implémente un sous-ensemble du programme standard `test(1)`_. Pensez à structurer votre code en utilisant des sous-fonctions. Compilez votre programme sur votre ordinateur avant de le soumettre sur INGINIOUS. https://inginious.info.ucl.ac.be/course/LSINF1252/commandetest



Questions complémentaires
-------------------------

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

#. Un étudiant a fait l'implémentation d'un sous-ensemble des fonctions définies dans string.h, mais il rencontre quelques problèmes avec son code :download:`/Programmes/src/string.c`. Utilisez `gdb <http://sites.uclouvain.be/SystInfo/notes/Outils/html/gdb.html>`_ pour corriger son code. Utilisez le flag ``-g`` de ``gcc`` pour ajouter les informations de debug dans votre executable. Pour rappel, voici quelques commandes importantes de `gdb <http://sites.uclouvain.be/SystInfo/notes/Outils/html/gdb.html>`_:

   - ``run [ARGS]`` permet de lancer l'execution du programme avec les arguments ARGS si spécifiés.
   - ``break string.c:9`` met un point d'arrêt à la ligne 9 du fichier string.c
   - ``next`` permet d'executer la ligne courante et de s'arrêter à la ligne suivante
   - ``print var`` affiche la valeur de la variable ``var``
   - ``backtrace`` affiche la pile d'appel des fonctions courantes
   - ``quit`` quitte `gdb <http://sites.uclouvain.be/SystInfo/notes/Outils/html/gdb.html>`_

	 .. only:: staff

           .. note::

	      4 erreurs: strlen ne check pas NULL, strlen appelé à chaque itération de strcat, argc pas vérifié, concat_2 pas initialisé

#. Vous travaillez sur un programme qui doit manipuler des vecteurs. Afin de pouvoir supporter des vecteurs de taille quelconque, vous décidez de réimplémenter ces vecteurs vous même en utilisant des pointeurs. Votre programme définit la structure ``struct vector_t`` et les fonctions ci-dessous.
   Implémentez ces fonctions sans jamais utiliser la notation des tableaux en C (``[`` et ``]``).


		  .. literalinclude:: /Programmes/src/vector.c
		     :encoding: utf-8
		     :language: c
		     :start-after: ///AAA
		     :end-before: ///BBB



		.. only:: staff

		   #. Faites l'exercice relatif aux `linked lists <https://inginious.info.ucl.ac.be/course/LSINF1252/linked_lists_1>`_ sur INGInious.


		.. only:: staff

		   #. Expliquez la différence entre `malloc(3)`_ et `calloc(3)`_. D'après vous, quel appel sera le plus lent ?

		.. only:: staff

		   #. Dans la fonction ``push`` du programme de manipulation d'un pile :download:`/../Theorie/C/S3-src/stack.c`, faut-il remplacer l'appel à `malloc(3)`_ par un appel à `calloc(3)`_

			    .. note::

					Non. La zone mémoire est initialisée directement après.

		.. only:: staff

		    #.  Le prototype de la fonction ``push`` du programme de manipulation d'une pile :download:`/../Theorie/C/S3-src/stack.c`,  est ``void push(struct fraction_t *)``. Serait-il possible d'écrire une function push ayant comme prototype ``void push(struct fraction_t)`` ? Qu'est-ce qui changerait dans ce cas ?

			    .. note::

					Pas possible.

		.. only:: staff

		   #. Les fonctions ``push`` et ``pop`` définies dans l'exemple de manipulation d'une pile :download:`/../Theorie/C/S3-src/stack.c` utilisent une pile qui est définie par un pointeur qui est une variable globale. Est-il possible de réécrire ces fonctions de façon à ce qu'elles prennent comme argument un pointeur vers la pile ? Leurs prototypes deviendraient :

		      - ``void push(struct node_t *, struct fraction_t *);``
		      - ``struct fraction_t * pop(struct node_t *);``

			    .. note::

				Oui, idéalement dans ce cas, il faudrait définir une fonction init qui renverrait un ``struct node_t *``.

		.. only:: staff


		   #. Considérons la structure suivante:

			.. code-block:: c

				typedef struct {
					char c;
					long l;
					short s;
				} test_t;


		   Combien de bytes seront utilisés en mémoire pour représenter cette structure? Représentez graphiquement la position en mémoire de chaque élément (utilisez `printf(3)`_ et ``%p``), observez-vous des trous ? Expliquez.
		   Serait-il possible d'utiliser moins de bytes pour représenter cette structure ? Si oui, comment ?

				.. note::

					La structure prend 16 bytes d'espace (sur une machine 64-bits - 12 bytes sur une machine 32 bits). C'est dû au fait que les champs sont alignés à des multiples de 64 bits (resp. 32 bits) pour éviter d'avoir des parties de variables copié sur plusieurs registres. Pour optimiser, il suffit de reordonner les champs. Par exemple:

						.. code-block:: c

							typedef struct {
								char c;
								short s;
								long l;
							} test_t;

				.. only:: staff

						.. note::

								Elle bypasse l'alignement décrit dans la question précédente. L'avantage est que la structure prend l'espace minimale n'importe soit l'ordonnancement des champs. Le désavatage est que la CPU doît faire plus de travail pour lire la variable, car des parties de la variable sont sur plusieurs registres, et donc la CPU doît faire des bit-shifts.

#. Expliquez à quoi sert l'attribut ``packed`` des structures dans `gcc(1)`_ (regardez la manpage). Appliquez cet attribut à la structure de l'exercice précédent. Qu'observez-vous comme différence ? Quel sont les avantages et désavantages d'utiliser cet attribut ? Dans quel cas est-il intéressant de l'utiliser ?

		.. only:: staff

				.. note::

						Il bypasse l'alignement décrit dans la question précédente. L'avantage est que la structure prend l'espace minimal n'importe soit l'ordonnancement des champs. Le désavantage est que la CPU doît faire plus de travail pour lire la variable, car des parties de la variable sont sur plusieurs registres, et donc la CPU doît faire des bit-shifts.


		.. only:: staff

				#. Exécutez plusieurs fois le code suivant. Expliquez les différents résultats obtenus.
					.. code-block:: c

						int global;
						int main (int argc, char** argv)
						{
							int local;
							int *ptr1 = (int *)malloc(sizeof(*ptr1));
							int *ptr2 = (int *)malloc(sizeof(*ptr2));

							printf("global %p loc %p p1 %p p2 %p\n", &global, &local, ptr1, ptr2);
							return EXIT_SUCCESS;
						}


Questions de bilan final
------------------------

#. Lisez attentivement le code suivant et essayez de deviner ce qui sera affiché
   sur la sortie standard. Ensuite, compilez le code en activant l'option 
   ``-fno-stack-protector`` de `gcc(1)`_ et exécutez le code. Avez-vous bien
   deviné ? Comment expliquez-vous les lignes affichées par le programme ?

	   .. code-block:: c

		 		#include <stdlib.h>
				#include <stdio.h>
				#include <string.h>
				#include <stdint.h>
                                
				int f() {
				        uint32_t zero = 0;
				        char a = 'a';
				        char b = 'b';
				        char str[8] = "Hello !";
				        printf("1) str = \"%s\",\t\tzero = %d,\ta = %c,\tb = %c\n", str, zero, a, b);
				        strcpy(str, "I love  sour!");
				        printf("2) str = \"%s\",\tzero = %d,\ta = %c,\tb = %c\n", str, zero, a, b);
				        a = 'a';
				        b = 'b';
				        printf("3) str = \"%s\",\tzero = %d,\ta = %c,\tb = %c\n", str, zero, a, b);
				        return 0;
				}

				int main(int argc, char *argv[]) {
				        return f();
				}

#. *Question ouverte*. Soit la structure ``pair_t`` suivante :

     .. code-block:: c

        typedef struct pair {
          int a;
          int b;
        } pair_t;


   Comment feriez-vous pour stocker dans les
   variables ``pair_t *p1, *p2`` les pointeurs vers deux instances de ``pair_t``
   allouées sur le heap de manière contiguë (i.e. les deux structures se suivent
   directement dans la mémoire) ?
