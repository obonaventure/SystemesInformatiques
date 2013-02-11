 .. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices
=========

Les systèmes d'exploitation de type Unix sont multitâches et multi-utilisateurs. Cela signifie qu'il est possible d'exécuter simultanément plusieurs programmes qui appartiennent potentiellement à différents utilisateurs. Sous Unix, l'unité d'exécution d'un programme est appelée un :term:`processus`. Lorsque vous exécutez un programme C que vous avez compilé depuis la ligne de commande, le shell lance un nouveau :term:`processus`. Chaque processus est identifié `par le système d'exploitation via son :term:`pid` ou :term:`process identifier`. Ce :term:`pid` est alloué par le système d'exploitation à de la création du processus. A tout instant, le système d'exploitation maintient une :term:`table des processus` qui contient la liste de tous les processus qui sont en cours d'exécution. Comme nous aurons l'occasion de nous en rendre compte plus tard, cette table contient énormément d'informations qui sont utiles au système. A ce stade, l'information importante qui se trouve dans la table des processus est le :term:`pid` de chaque processus et l'utilisateur qui possède le processus. La commande `ps(1)`_ permet de consulter de façon détaillée la table des processus sur un système Unix. Voici un exemple d'utilisation de cette commande sur un système Linux.

.. code-block:: console

  $ ps u
  USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
  obo      16272  0.0  0.0 110464  1884 pts/1    Ss   11:35   0:00 -bash
  obo      16353  0.0  0.0 110184  1136 pts/1    R+   11:43   0:00 ps u


Dans cet exemple, l'utilisateur ``obo`` possède actuellement deux processus. Le premier est l'interpréteur de commande `bash(1)`_ et le second le processus `ps(1)`_. L'interpréteur de commande a ``16272`` comme :term:`pid` tandis que le :term:`pid` de `ps(1)`_ est 16353. 

`ps(1)`_ n'est pas la seule commande permettant de consulter la table des processus. Parmi les autres commandes utiles, on peut mentionner `top(1)`_ qui permet de visualiser les processus qui s'exécutent actuellement et le temps CPU qu'ils consomment ou `pstree(1)`_ qui présente les processus sous la forme d'un arbre. Sous Linux, le répertoire ``/proc``, qui est documenté dans `proc(5)`_ contient de nombreux pseudos fichiers avec énormément d'informations relatives aux processus qui sont en cours d'exécution. Parcourir le répertoire ``/proc`` et visualiser avec ``less(1)`` les fichiers qui s'y trouvent est une autre façon de consulter la table des processus sous Linux. 

Pour comprendre le fonctionnement des processus, il est intéressant d'expérimenter avec le processus ci-dessous. Celui-ci utilise l'appel système `getpid(2)`_ pour récupérer son :term:`pid`, l'affiche et utilise la fonction `sleep(3)`_ de la librairie pour se mettre en veille pendant trente secondes avant de se terminer.

.. literalinclude:: /S3/src/getpid.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA

Ce programme peut être compilé avec `gcc(1)`_ pour produire un exécutable. 

.. code-block:: console

 $ ls -l getpid*
 -rw-r--r--  1 obo  obo   608 10 fév 12:11 getpid.c
 $ gcc -Wall -o getpid getpid.c
 $ ls -l getpid*
 -rwxr-xr-x  1 obo  obo  8800 10 fév 12:12 getpid
 -rw-r--r--  1 obo  obo   608 10 fév 12:11 getpid.c

Cet exemple utilise la commande `ls(1)`_ pour lister le contenu d'un répertoire. L'argument ``-l`` permet de d'obtenir pour chaque fichier son nom, sa date de modification, sa taille, l'utilisateur et le group auxquels il appartient ainsi que ses permissions. Sous Unix, les permissions associées à un fichier sont divisées en trois blocs. Le premier bloc correspond aux permissions qui sont applicables à l'utilisateur qui possède le fichier. Pour l'exécutable ``getpid``, les permissions du propriétaire sont ``rwx``. Elles indiquent que le propriétaire peut lire le fichier (permission ``r``), l'écrire ou l'effacer (permission ``w``) et l'exécuter (permission ``x``). Sous Unix, seuls les fichiers qui possèdent la permission à l'exécution peuvent être lancés depuis l'interpréteur. Ces permissions peuvent être modifiées en utilisant la commande `chmod(1)`_. Les deux autres blocs de permissions sont relatifs aux membres du même groupe que le propriétaire et à un utilisateur quelconque. Nous y reviendrons plus en détails lorsque nous aborderons les systèmes de fichiers. En pratique, il est important de savoir qu'un fichier shell ou un fichier compilé qui n'a pas le bit de permission ``x`` ne peut pas être exécuté par le système. Ceci est illustré par l'exemple ci-dessous.

.. code-block:: console

  $ chmod -x getpid
  $ ls -l getpid*
  -rw-r--r--  1 obo  obo  8800 10 fév 12:12 getpid
  -rwxr-xr-x  1 obo  obo  8800 10 fév 12:11 getpid.o
  $ ./getpid
  -bash: ./getpid: Permission denied
  $ chmod +x getpid
  $ ./getpid
  Processus : 11147

L'interpréteur de commande `bash(1)`_ permet lancer plusieurs processus en tâche de fond. Cela se fait en suffixant la commande avec ``&``. Des détails complémentaires sont disponibles dans la section ``JOB CONTROL`` du manuel de `bash(1)`_. Lorsqu'un processus est lancé en tâche de fond, il est détaché et n'a plus accès à l'entrée standard. Par contre, il continue à pouvoir écrire sur la sortie standard et la sortie d'erreur standard. L'exemple ci-dessous illustre l'exécution de deux instances de ``getpid``.

.. code-block:: console

 $ ./getpid &
 [1] 10975
 $ Processus : 10975
 [pid=10975] Sleep : 30 secondes
 ./getpid &
 [2] 10976
 $ Processus : 10976
 [pid=10976] Sleep : 30 secondes
 ps u
 USER   PID  %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND
 obo   8361   0,0  0,0  2435548    208 s003  S+    9:24     0:00.14 -bash
 obo  10975   0,0  0,0  2434832    340 s000  S    12:05     0:00.00 ./getpid
 obo  10976   0,0  0,0  2434832    340 s000  S    12:05     0:00.00 ./getpid
 $ [pid=10975] Fin du processus
 [pid=10976] Fin du processus
 [1]-  Done                    ./getpid
 [2]+  Done                    ./getpid

Ces deux instances partagent la même sortie standard. En pratique, lorsque l'on lance un processus en tâche de fond, il est préférable de rediriger sa sortie et son erreur standard. Lorsque l'on développe de premiers programmes en C, il arrive que celui-ci se lance dans une boucle infinie. Deux techniques sont possibles pour interrompre un tel processus qui consomme inutilement les ressources de la machine et peut dans certains cas la surcharger fortement. 

Si le programme a été lancé depuis un shell, il suffit généralement de taper sur `Ctrl-C` pour interrompre son exécution, comme dans l'exemple ci-dessous.

.. code-block:: console 

   $ ./getpid
   Processus : 11281
   [pid=11281] Sleep : 30 secondes
   ^C


Parfois cependant `Ctrl-C` n'est pas suffisant. C'est le cas notamment lorsqu'un processus a été lancé en tâche de fond. Dans ce cas, la meilleure technique est d'utiliser `ps(1)`_ pour trouver l'identifiant du processus et l'interrompre via la commande `kill(1)`_. Cette commande permet d'envoyer un :term:`signal` au processus. Nous verrons plus tard le fonctionnement des signaux sous Unix. A ce stade, le signal permettant de terminer avec certitude un processus est le signal ``KILL``. C'est celui qui est utilisé dans l'exemple ci-dessous.

.. code-block:: console

   $ ./getpid &
   [1] 11285
   $ Processus : 11285
   [pid=11285] Sleep : 30 secondes
   ps
   PID TTY           TIME CMD
   384 ttys000      0:00.32 -bash
   11285 ttys000    0:00.00 ./getpid
   $ kill -KILL 11285
   $ ps
    PID TTY           TIME CMD
    384 ttys000    0:00.33 -bash
    [1]+  Terminated              ./getpid



1. Petits exercices
-------------------

#. Considérons un programme C dans lequel la fonction ``main`` appelle une fonction ``f``. Le fonction ``f`` peut-elle accéder au nombre d'arguments définis dans la ligne de commande ? Si oui comment, si non pourquoi ?

#. Expliquez la différence entre `malloc(3)`_ et `calloc(3)`_. D'après vous, quel appel sera le plus lent ?

#. Dans la fonction ``push`` du programme de manipulation d'un pile :download:`src/stack.c`, faut-il remplacer l'appel à `malloc(3)`_ par un appel à `calloc(3)`_

	.. only:: staff 

	    .. note::
		
			Non. La zone mémoire est initialisée directement après.

#.  Le prototype de la fonction ``push`` du programme de manipulation d'une pile :download:`src/stack.c`,  est ``void push(struct node_t *)``. Serait-il possible d'écrire une function push ayant comme prototype ``void push(struct node_t)`` ? Qu'est-ce qui changerait dans ce cas ?

	.. only:: staff 

	    .. note::
		
			Pas possible.

#. Les fonctions ``push`` et ``pop`` définies dans l'exemple de manipulation d'une pile :download:`src/stack.c` utilisent une pile qui est définie par un pointeur qui est une variable locale. Est-il possible de réécrire ces fonctions de façon à ce qu'elles prennent comme argument un pointeur vers la pile ? Leurs prototypes deviendraient :

   - ``void push(struct node_t *, struct fraction_t *);``
   - ``struct fraction_t * pop(struct node_t *);``

	.. only:: staff 

	    .. note::
		
			Oui, idéalement dans ce cas, il faudrait définir une fonction init qui renverrait un struct node_t *.

#. Dans le programme :download:`src/stack.c`, implémentez une fonction ``size`` qui calcule le nombre d'éléments se trouvant sur la pile.

	.. only:: staff 

	    .. note::
		
			.. code-block:: c
				
				int size(void)
				{
					struct node_t *curr = stack;
					int count = 0;

					while (curr) {
						count ++;
						curr = stack->next;
					}

					return count;
				}

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

#. Soit une méthode ``main`` qui a la signature suivante: ``int main(int argc, long argv);``. Est-il possible avec une telle signature d'afficher tous les arguments du programme ? Si oui, pourquoi et comment?

	.. only:: staff
	
		.. note::
		
			Il suffit de caster l'argument argv vers un char **

#. Reprenez l'exercice 12 de la semaine passée. Expliquez vos résultats à l'aide de la stack.

	.. only:: staff

		.. note::

			La variable a est défini au même endroit sur la stack, donc elle reprend la valeur qui était défini par foo(), car bar() ne redéfini pas la variable "a".

#. Soit la structure suivante:
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

#.  Quelles lignes sont correctes dans le code suivant:
	.. literalinclude:: /S3/src/exercices/const.c
   		:language: c

   	.. only:: staff

		.. note::

			.. code-block:: c

				p1 = &b;

				p2[0] = b;

#. (bonus) Le code suivant ne compile pas, on obtient l'erreur suivante: `assignment of read-only location`. Comment corriger ce problème sans changer la signature de la fonction ``foo()``. Comment dire à `gcc(1)`_ de ne pas permettre de bypasser cette protection de `const`.

	.. literalinclude:: /S3/src/exercices/const2.c
   		:language: c

   	.. only:: staff

		.. note::

			Il suffit de caster a en ``*((int *)a) = 2`` pour bypasser le const. L'option ``-Wcast-qual`` permet à gcc de vérifier ceci.

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


#. Implémentez `strdup(3)`_ en respectant les spécifications de la manpage.


   	.. only:: staff

		.. note::

			.. code-block:: c

				char *strdup(const char *s)
				{
					char *new = (char *) malloc ((strlen(s)+1) * sizeof(char));

					memcpy(new, s, (strlen(s)+1) * sizeof(char));
				}

.. #. retourner un tableau sur la pile


.. #. Différents architectures ont différents facon de lire les données de la mémoire. La différence se voît dans la ``Endianness``_ des machines. Une machine
..	Détectez la endianness de votre machine.
..
..	TODO IMPLEMENTER ENDIAN_SWAP

.. #. variables static :
..	static a;
..	foo () {
..		printf(a);
..	}

.. #. file_1.c : int a;
..   file_2.c : extern int a;
..
..   linker
..   main du file_2 on fait le pritnf(a);

.. #. Fonctions static / fonctions non-static

.. Question bilan final:
.. #. Vous travaillez sur un programme qui doit manipuler des vecteurs. Afin de pouvoir supporter des .. vecteurs de taille quelconque, vous décidez de réimplémenter ces vecteurs vous même en utilisation .. des pointeurs. Votre programme définit la structure ``struct vector_t`` et les fonctions ci-dessous. .. Implémentez ces fonctions sans jamais utiliser de tableau en C.
..	.. literalinclude:: /S3/src/vector.c
..    :encoding: iso-8859-1
..    :language: c
..    :start-after: ///AAA
..    :end-before: ///BBB

2. Mini-Projet
--------------

#. On vous demande d'implémenter une file générique à l'aide d'une structure chainée. Vous devez implémenter les fonctions suivantes:
	- ``queue_t *queue_init(void);``
	- ``void enqueue(queue_t *q, void *data);``
	- ``void *dequeue(queue_t *q);``
	- ``void queue_free(queue_t *q);``
   On vous demande également d'utiliser un ``Makefile``. Vous devez également fournir un binaire ``test_queue`` qui exécute différent tests de votre implémentation. Ce dernier doit être généré lorsque ``make`` est exécuté. Vos sources doivent se trouver dans le dossier du SVN: ``grpXX/projet_S3/file/``.

#. Le fichier :download:`mini_projet/mini_projet.tar` contient les fichiers nécessaire pour le deuxième mini-projet. C'est une archive et vous pouvez l'extraire avec la commande ``tar -xf mini_projet.tar`` de l'utilitaire `tar(1)`_. Cet archive contient deux petits programmes en c (``ex1.c`` et ``ex2.c``) qui initialisent et parcourent un tableau. Les différences entre ces deux programmes sont minimes et à priori ils font exactement le même nombre d'opérations. Néanmoins, leurs performances sont très différents. On vous demande d'exécuter le script ``generate.sh``. Celui-ci va exécuter un grand nombre de fois les programmes ex1 et ex2 avec des tailles de tableau qui varient (attention, l'exécution prend un temps considérable (de l'ordre d'une heure)). Ensuite, le script génère un graphique avec sur l'axe des X la taille des tableaux en octets, et sur l'axe des Y la différence de temps d'exécution entre le programme ex2 et ex1.

   Pour ce mini-projet on vous demande de réfléchir à une explication des résultats obtenus. Générez le graphe avec le script ``generate.sh``, et écrivez un à deux paragraphes qui analysent votre résultat. Placez le tout dans le dossier du SVN: ``grpXX/projet_S3/graphe/``.

   Petite astuce: Regardez le data-sheet du processeur sur lequel vous exécutez le script. Par exemple, pour les machines en salle, regardez: :download:`mini_projet/data_sheet.pdf`


