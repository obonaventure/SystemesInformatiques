.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Déclarations
=============

Durant les chapitres précédents, nous avons principalement utilisé des variables locales. Celles-ci sont déclarées à l'intérieur des fonctions où elles sont utilisées. La façon dont les variables sont déclarées est importante dans un programme écrit en langage C. Dans cette section nous nous concentrerons sur des programmes C qui sont écrits sous la forme d'un seul fichier source. Nous verrons plus tard comment découper un programme en plusieurs modules qui sont répartis dans des fichiers différents et comment les variables peuvent y être déclarées.

La première notion importante concernant la déclaration des variables est leur :term:`portée`. La portée d'une variable peut être définie comme étant la partie du programme où la variable est accesible et où sa valeur peut être modifiée. Le langage C définit deux types de portée à l'intérieur d'un fichier C. La première est la :term:`portée globale`. Une variable qui est définie en dehors de toute définition de fonction a une portée globale. Une telle variable est accessible dans toutes les fonctions présentes dans le fichier. La variable ``g`` dans l'exemple ci-dessous a une portée globale.

.. code-block:: c

   float g;   // variable globale

   int f(int i) {
   int n;   // variable locale
   // ...
   for(int j=0;j<n;j++) {  // variable locale
     // ...
     }
   //...
   for(int j=0;j<n;j++) {  // variable locale
     // ...
     }
   }


Dans un fichier donné, il ne peut évidemment pas y avoir deux variables globales qui ont le même identifiant. Lorsqu'une variable est définie dans un `bloc`, la portée de cette variable est locale à ce bloc. On parle dans ce cas de :term:`portée locale`. La variable locale n'existe pas avant le début du bloc et n'existe plus à la fin du bloc. Contrairement aux identifiants de variables globales qui doivent être uniques à l'intérieur d'un fichier, il est possible d'avoir plusieurs variables locales qui ont le même identifiant à l'intérieur d'un fichier. C'est fréquent notamment pour les définitions d'arguments de fonction et les variables de boucles. Dans l'exemple ci-dessus, les variables ``n`` et ``j`` ont une portée locale. La variable ``j`` est définie dans deux blocs différents à l'intérieur de la fonction ``f``.


Le programme :download:`/Theorie/C/S3-src/portee.c` illustre la façon dont le compilateur C gère la portée de différentes variables.

.. literalinclude:: /Theorie/C/S3-src/portee.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Ce programme contient deux variables qui ont une portée globale : ``g1`` et ``g2``. Ces deux variables sont définies en dehors de tout bloc. En pratique, elles sont généralement déclarées au début du fichier, même si le compilateur C accepte un définition en dehors de tout bloc et donc par exemple en fin de fichier. La variable globale ``g1`` n'est définie qu'une seule fois. Par contre, la variable ``g2`` est définie avec une portée globale et est redéfinie à l'intérieur de la fonction ``f`` ainsi que dans la boucle ``for`` de la fonction ``main``. Redéfinir une variable globale de cette façon n'est pas du tout une bonne pratique, mais cela peut arriver lorsque par mégarde on importe un fichier header qui contient une définition de variable globale. Dans ce cas, le compilateur C utilise la variable qui est définie dans le bloc le plus proche. Pour la variable ``g2``, c'est donc la variable locale ``g2`` qui est utilisée à l'intérieur de la boucle ``for`` ou de la fonction ``f``.

Lorsqu'un identifiant de variable locale est utilisé à plusieurs endroits dans un fichier, c'est la définition la plus proche qui est utilisée. L'exécution du programme ci-dessus illustre cette utilisation des variables globales et locales.

.. literalinclude:: /Theorie/C/S3-src/portee.out
   :encoding: iso-8859-1
   :language: console

.. note:: Utilisation des variables

 En pratique, les variables globales doivent être utilisées de façon parcimonieuse et il faut limiter leur utilisation aux données qui doivent être partagées par plusieurs fonctions à l'intérieur d'un programme. Lorsqu'une variable globale a été définie, il est préférable de ne pas réutiliser son identifiant pour une variable locale. Au niveau des variables locales, les premières versions du langage C imposaient leur définition au début des blocs. Les standards récents [C99]_ autorisent la déclaration de variables juste avant leur première utilisation un peu comme en Java.

Les versions récentes de C [C99]_ permettent également de définir des variables dont la valeur sera constante durant toute l'exécution du programme. Ces déclarations de ces constants sont préfixées par le mot-clé ``const`` qui joue le même rôle que le mot clé ``final`` en Java.

.. literalinclude:: /Theorie/C/S3-src/const.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB


Il y a deux façons de définir des constantes dans les versions récentes de C [C99]_. La première est via la macro ``#define`` du préprocesseur. Cette macro permet de remplacer une chaîne de caractères (par exemple ``M_PI`` qui provient de `math.h`_) par un nombre ou une autre chaîne de caractères. Ce remplacement s'effectue avant la compilation. Dans le cas de ``M_PI`` ci-dessus, le préprocesseur remplace toute les occurences de cette chaîne de caractères par la valeur numérique de :math:`\pi`. Lorsqu'une variable ``const`` est utilisée, la situation est un peu différente. Le préprocesseur n'intervient pas. Par contre, le compilateur réserve une zone mémoire pour la variable qui a été définie comme constante. Cela a deux avantages par rapport à l'utilisation de ``#define``. Premièrement, il est possible de définir comme constante n'importe quel type de données en C, y compris des structures ou des pointeurs alors qu'avec un ``#define`` on ne peut définir que des nombres ou des chaînes de caractères. Ensuite, comme une ``const`` est stockée en mémoire, il est possible d'obtenir son adresse et de l'examiner via un :term:`debugger`.


Unions et énumérations
======================

Les structures que nous avons présentées précédemment permettent de combiner plusieurs données de types primitifs différents entre elles. Outre ces structures (``struct``), le langage C supporte également les ``enum`` et les ``union``. Le mot-clé ``enum`` est utilisé pour définir un type énuméré, c'est-à-dire un type de donnée qui permet de stocker un nombre fixe de valeurs. Quelques exemples classiques sont repris dans le fragment de programme ci-dessous :

.. literalinclude:: /Theorie/C/S3-src/enum.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Le premier ``enum`` permet de définir le type de données ``day`` qui contient une valeur énumérée pour chaque jour de la semaine. L'utilisation d'un type énuméré rend le code plus lisible que simplement l'utilisation de constantes définies via le préprocesseur.

.. literalinclude:: /Theorie/C/S3-src/enum.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///CCC
   :end-before: ///DDD

En pratique, lors de la définition d'un type énuméré, le compilateur C associe une valeur entière à chacune des valeurs énumérées. Une variable permettant de stocker la valeur d'un type énuméré occupe la même zone mémoire qu'un entier.

Outre les structures, le langage C supporte également les unions. Alors qu'une structure permet de stocker plusieurs données dans une même zone mémoire, une ``union`` permet de réserver une zone mémoire pour stocker une données parmi plusieurs types possibles. Une ``union`` est parfois utilisée pour minimiser la quantité de mémoire utilisée pour une structure de données qui peut contenir des données de plusieurs types. Pour bien comprendre la différence entre une ``union`` et une ``struct``, considérons l'exemple ci-dessous.

.. literalinclude:: /Theorie/C/S3-src/union.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB


Une union, ``u`` et une structure, ``s`` sont déclarées dans ce fragment de programme.

.. literalinclude:: /Theorie/C/S3-src/union.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///CCC
   :end-before: ///DDD

La structure ``s`` peut contenir à la fois un entier et un caractère. Par contre, l'``union`` ``u``, peut elle contenir un entier (``u.i``) *ou* un caractère (``u.c``), mais jamais les deux en même temps.
Le compilateur C alloue la taille pour l'``union`` de façon à ce qu'elle puisse contenir le type de donnée se trouvant dans l'``union`` nécessitant le plus de mémoire. Si les unions sont utiles dans certains cas très particulier, il faut faire très attention à leur utilisation. Lorsqu'une ``union`` est utilisée, le compilateur C fait encore moins de vérifications sur les types de données et le code ci-dessous est considéré comme valide par le compilateur :

.. literalinclude:: /Theorie/C/S3-src/union.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///EEE
   :end-before: ///FFF

Lors de son exécution, la zone mémoire correspondant à l'union ``u`` sera simplement interprétée comme contenant un ``char``, même si on vient d'y stocker un entier. En pratique, lorsqu'une ``union`` est vraiment nécessaire pour des raisons d'économie de mémoire, on l'encapsulera dans une ``struct`` en utilisant un type énuméré qui permet de spécifier le type de données qui est présent dans l'``union``.

.. literalinclude:: /Theorie/C/S3-src/union.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///BBB
   :end-before: ///XXX

Le programmeur pourra alors utiliser cette structure en indiquant explicitement le type de données qui y est actuellement stocké comme suit.

.. literalinclude:: /Theorie/C/S3-src/union.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///FFF
   :end-before: ///GGG


Organisation de la mémoire
==========================

Lors de l'exécution d'un programme en mémoire, le système d'exploitation charge depuis le système de fichier le programme en langage machine et le place à un endroit convenu en mémoire. Lorsqu'un programme s'exécute sur un système Unix, la mémoire peut être vue comme étant divisée en six zones principales. Ces zones sont représentées schématiquement dans la figure ci-dessous.

.. figure:: /Theorie/C/figures/figures-001-c.png
   :align: center

   Organisation d'un programme Linux en mémoire

La figure ci-dessus présente une vision schématique de la façon dont un processus Linux est organisé en mémoire centrale. Il y a d'abord une partie de la mémoire qui est réservée au système d'exploitation (OS dans la figure). Cette zone est représentée en grisé dans la figure.

Le segment text
---------------

La première zone est appelée par convention le :term:`segment text`. Cette zone se situe dans la partie basse de la mémoire [#fetext]_. C'est dans cette zone que sont stockées toutes les instructions qui sont exécutées par le micro-processeur. Elle est généralement considérée par le système d'exploitation comme étant uniquement accessible en lecture. Si un programme tente de modifier son :term:`segment text`, il sera immédiatement interrompu par le système d'exploitation. C'est dans le segment text que l'on retrouvera les instructions de langage machine correspondant aux fonctions de calcul et d'affichage du programme. Nous en reparlerons lorsque nous présenterons le fonctionnement du langage d'assemblage.

Le segment des données initialisées
-----------------------------------

La deuxième zone, baptisée :term:`segment des données initialisées`, contient l'ensemble des données et chaînes de caractères qui sont utilisées dans le programme. Ce segment contient deux types de données. Tout d'abord, il comprend l'ensemble des variables globales. Celles-ci sont soit initialisées explicitement par le programme ou alors initialisées à zéro par le compilateur. Ensuite, les constantes et les chaînes de caractères utilisées par le programme.

.. literalinclude:: /Theorie/C/S3-src/dataseg.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Dans le programme ci-dessus, la variable ``g_init``, la constante ``un`` et les tableaux ``tab`` et ``cours`` sont dans la zone réservée aux variables initialisées. En pratique, leur valeur d'initialisation sera chargée depuis le fichier exécutable lors de son chargement en mémoire. Il en va de même pour toutes les chaînes de caractères qui sont utilisées comme arguments aux appels à ``printf(3)``.

L'exécution de ce programme produit la sortie standard suivante.

.. literalinclude:: /Theorie/C/S3-src/dataseg.out
   :encoding: iso-8859-1
   :language: console


Cette sortie illustre bien les adresses où les variables globales sont stockées. La variable globale ``msg`` fait notamment partie du :term:`segment des données non-initialisées`.

Le segment des données non-initialisées
---------------------------------------

La troisième zone est le :term:`segment des données non-initialisées`. réservée aux variables non initialisées. Cette zone mémoire est initialisée à zéro par le système d'exploitation lors du démarrage du programme. Dans l'exemple ci-dessus, c'est dans cette zone que l'on stockera les valeurs de la variable ``g`` et des tableaux ``array`` et ``msg``.

.. note:: Initialisation des variables

 Un point important auquel tout programmeur C doit faire attention est l'initialisation correcte de l'ensemble des variables utilisées dans un programme. Le compilateur C est nettement plus permissif qu'un compilateur Java et il autorisera l'utilisation de variables avant qu'elles n'aient été explicitement initialisées, ce qui peut donner lieu à des erreurs parfois très difficiles à corriger.

 En C, par défaut les variables globales qui ne sont pas explicitement initialisées dans un programme sont initialisées à la valeur zéro par le compilateur. Plus précisément, la zone mémoire qui correspond à chaque variable globale non-explicitement initialisée contiendra des bits valant 0. Pour les variables locales, le langage C n'impose aucune initialisation par défaut au compilateur. Par souci de performance et sachant qu'un programmeur ne devrait jamais utiliser de variable locale non explicitement initialisée, le compilateur C n'initialise pas par défaut la valeur de ces variables. Cela peut avoir des conséquences ennuyeuses comme le montre l'exemple ci-dessous.

 .. literalinclude:: /Theorie/C/S3-src/initvar.c
    :encoding: iso-8859-1
    :language: c
    :start-after: ///AAA
    :end-before: ///BBB

  Cet extrait de programme contient deux fonctions erronées. La seconde, baptisée ``read(void)`` déclare un tableau local et retourne la somme des éléments de ce tableau sans l'initialiser. En Java, une telle utilisation d'un tableau non-initialisé serait détectée par le compilateur. En C, elle est malheureusement valide (mais fortement découragée évidemment). La première fonction, ``init(void)`` se contente d'initialiser un tableau local mais ne retourne aucun résultat. Cette fonction ne sert a priori à rien puisqu'elle n'a aucun effet sur les variables globales et ne retourne aucun résultat. L'exécution de ces fonctions via le fragment de code ci-dessous donne cependant un résultat interpellant.

 .. literalinclude:: /Theorie/C/S3-src/initvar.c
    :encoding: iso-8859-1
    :language: c
    :start-after: ///CCC
    :end-before: ///DDD

 .. literalinclude:: /Theorie/C/S3-src/initvar.out
    :encoding: iso-8859-1
    :language: console




Le tas (ou heap)
----------------

La quatrième zone de la mémoire est le :term:`tas` (ou :term:`heap` en anglais). Vu l'importance pratique de la terminologie anglaise, c'est celle-ci que nous utiliserons dans le cadre de ce document. C'est une des deux zones dans laquelle un programme peut obtenir de la mémoire supplémentaire pour stocker de l'information. Un programme peut y réserver une zone permettant de stocker des données et y associer un pointeur.

Le système d'exploitation mémorise, pour chaque processus en cours d'exécution, la limite supérieure de son :term:`heap`. Le système d'exploitation permet à un processus de modifier la taille de son heap via les appels systèmes `brk(2)`_  et `sbrk(2)`_. Malheureusement, ces deux appels systèmes se contentent de modifier la limite supérieure du :term:`heap` sans fournir une API permettant au processus d'y allouer efficacement des blocs de mémoire. Rares sont les processus qui utilisent directement `brk(2)`_  si ce n'est sous la forme d'un appel à ``sbrk(0)`` de façon à connaître la limite supérieure actuelle du :term:`heap`.

En C, la plupart des processus allouent et libèrent de la mémoire et utilisant les fonctions `malloc(3)`_ et `free(3)`_ qui font partie de la librairie standard.

La fonction `malloc(3)`_ prend comme argument la taille (en bytes) de la zone mémoire à allouer. La signature de la fonction `malloc(3)`_ demande que cette taille soit de type ``size_t``, c'est-à-dire le type retourné par l'expression ``sizeof``. Il est important de toujours utiliser ``sizeof`` lors du calcul de la taille d'une zone mémoire à allouer. `malloc(3)`_ retourne normalement un pointeur de type ``(void *)``. Ce type de pointeur est le type par défaut pour représenter dans un programme C une zone mémoire qui ne pointe pas vers un type de données particulier. En pratique, un programme va généralement utiliser `malloc(3)`_ pour allouer de la mémoire pour stocker différents types de données et le pointeur retourné par `malloc(3)`_ sera `casté` dans un pointeur du bon type.

.. note:: typcast en langage C

 Comme le langage Java, le langage C supporte des conversions implicites et explicites entre les différents types de données. Ces conversions sont possibles entre les types primitifs et les pointeurs. Nous les rencontrerons régulièrement, par exemple lorsqu'il faut récupérer un pointeur alloué par `malloc(3)`_ ou le résultat de ``sizeof``. Contrairement au compilateur Java, le compilateur C n'émet pas toujours de message de :term:`warning` lors de l'utilisation de  typecast qui risque d'engendrer une perte de précision. Ce problème est illustré par l'exemple suivant avec les nombres.

  .. literalinclude:: /Theorie/C/S3-src/typecast.c
     :encoding: iso-8859-1
     :language: c
     :start-after: ///AAA
     :end-before: ///BBB


La fonction de la librairie `free(3)`_ est le pendant de `malloc(3)`_. Elle permet de libérer la mémoire qui a été allouée par `malloc(3)`_. Elle prend comme argument un pointeur dont la valeur a été initialisée par `malloc(3)`_ et libère la zone mémoire qui avait été allouée par `malloc(3)`_ pour ce pointeur. La valeur du pointeur n'est pas modifiée, mais après libération de la mémoire il n'est évidemment plus possible [#fpossible]_ d'accéder aux données qui étaient stockées dans cette zone.

Le programme ci-dessous illustre l'utilisation de `malloc(3)`_ et `free(3)`_.

.. literalinclude:: /Theorie/C/S3-src/malloc.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Ce programme alloue trois zones mémoires. Le pointeur vers la première est sauvé dans le pointeur ``string``. Elle est destinée à contenir une chaîne de ``size`` caractères (avec un caractère supplémentaire pour stocker le caractère ``\0`` de fin de chaîne. Il y a deux points à remarquer concernant cette allocation. Tout d'abord, le pointeur retourné par `malloc(3)`_ est casté en un ``char *``. Cela indique au compilateur que ``string`` va bien contenir un pointeur vers une chaîne de caractères. Ce cast explicite rend le programme plus clair. Ensuite, la valeur de retour de `malloc(3)`_  est systématiquement testée. `malloc(3)`_ peut en effet retourner ``NULL`` lorsque la mémoire est remplie. Cela a peu de chance d'arriver dans un programme de test tel que celui-ci, mais tester les valeurs de retour des fonctions de la librairie est une bonne habitude à prendre lorsque l'on programme sous Unix. Le second pointeur, ``vector`` pointe vers une zone destiné à contenir un tableau d'entiers. Le dernier pointeur, ``fract_vect`` pointe vers une zone qui pourra stocker un tableau de ``Fraction``. Lors de son exécution, le programme affiche la sortie suivante.

.. literalinclude:: /Theorie/C/S3-src/malloc.out
   :encoding: iso-8859-1
   :language: console

Dans cette sortie, on remarque que l'appel à fonction `free(3)`_ libère la zone mémoire, mais ne modifie pas la valeur du pointeur correspondant. Le programmeur doit explicitement remettre le pointeur d'une zone mémoire libérée à ``NULL``.

Un autre exemple d'utilisation de `malloc(3)`_ est la fonction ``duplicate`` ci-dessous qui permet de retourner une copie d'une chaîne de caractères. Il est important de noter qu'en C la fonction `strlen(3)`_ retourne la longueur de la chaîne de caractères passée en argument sans prendre en compte le caractère ``\0`` qui marque sa fin. C'est la raison pour laquelle `malloc(3)`_ doit réserver un bloc de mémoire en plus. Même si généralement les ``char`` occupent un octet en mémoire, il est préférable d'utiliser explicitement ``sizeof(char)`` lors du calcul de l'espace mémoire nécessaire pour un type de données.


.. literalinclude:: /Theorie/C/S3-src/strcpy.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

`malloc(3)`_ et `free(3)`_ sont fréquemment utilisés dans des programmes qui manipulent des structures de données dont la taille varie dans le temps. C'est le cas pour les différents sortes de listes chaînées, les piles, les queues, les arbres, ... L'exemple ci-dessous (:download:`/Theorie/C/S3-src/stack.c`) illustre l'implémentation d'un pile simple en C. Le pointeur vers le sommet de la pile est défini comme une variable globale. Chaque élément de la pile est représenté comme un pointeur vers une structure qui contient un pointeur vers la donnée stockée (dans cet exemple des fractions) et l'élément suivant sur la pile. Les fonctions ``push`` et ``pop`` permettent respectivement d'ajouter un élément et de retirer un élément au sommet de la pile. La fonction ``push`` alloue la mémoire nécessaire avec `malloc(3)`_ tandis que la fonction ``pop`` utilise `free(3)`_ pour libérer la mémoire dès qu'un élément est retiré.


.. literalinclude:: /Theorie/C/S3-src/stack.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB


Ces fonctions peuvent être utilisées pour empiler et dépiler des fractions sur une pile comme dans l'exemple ci-dessous. La fonction ``display`` permet d'afficher sur :term:`stdout` le contenu de la pile.

.. literalinclude:: /Theorie/C/S3-src/stack.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///BBB
   :end-before: ///CCC

Lors de son exécution le programme :download:`/Theorie/C/S3-src/stack.c` présenté ci-dessus affiche les lignes suivantes sur sa sortie standard.

.. literalinclude:: /Theorie/C/S3-src/stack.out
   :encoding: iso-8859-1
   :language: console


Le tas (ou :term:`heap`) joue un rôle très important dans les programmes C. Les données qui sont stockées dans cette zone de la mémoire sont accessibles depuis toute fonction qui possède un pointeur vers la zone correspondante


.. note:: Ne comptez jamais sur les `free(3)`_ implicites

 Un programmeur débutant qui expérimente avec `malloc(3)`_ pourrait écrire le code ci-dessous et conclure que comme celui-ci s'exécuté correctement, il n'est pas nécessaire d'utiliser `free(3)`_. Lors de l'exécution d'un programme, le système d'exploitation réserve de la mémoire pour les différents segments du programme et ajuste si nécessaire cette allocation durant l'exécution du programme. Lorsque le programme se termine, via ``return`` dans la fonction ``main`` ou par un appel explicite à `exit(2)`_, le système d'exploitation libère tous les segments utilisés par le programme, le text, les données, le tas et la pile. Cela implique que le système d'exploitation effectue un appel implicite à `free(3)`_ à la terminaison d'un programme.

 .. literalinclude:: /Theorie/C/S3-src/nofree.c
    :encoding: iso-8859-1
    :language: c
    :start-after: ///AAA

 Un programmeur ne doit cependant `jamais` compter sur cet appel implicite à `free(3)`_. Ne pas libérer la mémoire lorsqu'elle n'est plus utilisée est un problème courant qui est généralement baptisé :term:`memory leak`. Ce problème est particulièrement gênant pour les processus tels que les serveurs Internet qui ne se terminent pas ou des processus qui s'exécutent longtemps. Une petite erreur de programmation peut causer un :term:`memory leak` qui peut après quelque temps consommer une grande partie de l'espace mémoire inutilement. Il est important d'être bien attentif à l'utilisation correcte de `malloc(3)`_ et de `free(3)`_ pour toutes les opérations d'allocation et de libération de la mémoire.


`malloc(3)` est la fonction d'allocation de mémoire la plus fréquemment utilisée [#fothermalloc]_. La librairie standard contient cependant d'autres fonctions permettant l'allocation et la réallocation de mémoire. `calloc(3)`_ est nettement moins utilisée que `malloc(3)`_. Elle a pourtant un avantage majeur par rapport à `malloc(3)`_ puisqu'elle initialise à zéro la zone de mémoire allouée. `malloc(3)`_ se contente d'allouer la zone de mémoire mais n'effectue aucune initialisation. Cela permet à `malloc(3)`_ d'être plus rapide, mais le programmeur ne doit jamais oublier qu'il ne peut pas utiliser `malloc(3)`_ sans initialiser la zone mémoire allouée. Cela peut s'observer en pratique avec le programme ci-dessous. Il alloue une zone mémoire pour ``v1``, l'initialise puis la libère. Ensuite, le programme alloue une nouvelle zone mémoire pour ``v2`` et y retrouve les valeurs qu'il avait stocké pour ``v1`` précédemment. En pratique, n'importe quelle valeur pourrait se trouver dans la zone retournée par `malloc(3)`.

.. literalinclude:: /Theorie/C/S3-src/mallocinit.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA

L'exécution du programme ci-dessus affiche le résultat suivant sur la sortie standard. Ceci illustre bien que la fonction `malloc(3)`_ n'initialise pas  les zones de mémoire qu'elle alloue.

.. literalinclude:: /Theorie/C/S3-src/mallocinit.out
   :encoding: iso-8859-1
   :language: console

Lors de l'exécution du programme, on remarque que la première zone mémoire retournée par `malloc(3)`_ a été initialisée à zéro. C'est souvent le cas en pratique pour des raisons de sécurité, mais ce serait une erreur de faire cette hypothèse dans un programme. Si la zone de mémoire doit être initialisée, la mémoire doit être allouée par `calloc(3)`_ ou via une initialisation explicite ou en utilisant des fonctions telles que `bzero(3)`_ ou `memset(3)`_.

Les arguments et variables d'environnement
------------------------------------------

Lorsque le système d'exploitation charge un programme Unix en mémoire, il initialise dans le haut de la mémoire une zone qui contient deux types de variables. Cette zone contient tout d'abord les arguments qui ont été passés via la ligne de commande. Le système d'exploitation met dans ``argc`` le nombre d'arguments et place dans ``char *argv[]`` tous les arguments passés avec dans ``argv[0]`` le nom du programme qui est exécuté.

Cette zone contient également les variables d'environnement. Ces variables sont généralement relatives à la configuration du système. Leurs valeurs sont définies par l'administrateur système ou l'utilisateur. De nombreuses variables d'environnement sont utilisées dans les systèmes Unix. Elles servent à modifier le comportement de certains programmes. Une liste exhaustive de toutes les variables d'environnement est impossible, mais en voici quelques unes qui sont utiles en pratique [#fenvbash]_:

 - ``HOSTNAME`` : le nom de la machine sur laquelle le programme s'exécute. Ce nom est fixé par l'administrateur système via la commande `hostname(1)`_
 - ``SHELL`` : l'interpréteur de commande utilisé par défaut pour l'utilisateur courant. Cet interpréteur est lancé par le système au démarrage d'une session de l'utilisateur. Il est stocké dans le fichier des mots de passe et peut être modifié par l'utilisateur via la commande `passwd(1)`_
 - ``USER`` : le nom de l'utilisateur courant. Sous Unix, chaque utilisateur est identifié par un numéro d'utilisateur et un nom uniques. Ces identifiants sont fixés par l'administrateur système via la commande `passwd(1)`_
 - ``HOME``: le répertoire d'accueil de l'utilisateur courant. Ce répertoire d'accueil appartient à l'utilisateur. C'est dans ce répertoire qu'il peut stocker tous ses fichiers.
 - ``PRINTER`` : le nom de l'imprimante par défaut qui est utilisée par la commande `lp(1posix)`_
 - ``PATH``: cette variable d'environnement contient la liste ordonnée des répertoires que le système parcourt pour trouver un programme à exécuter. Cette liste contient généralement les répertoires dans lesquels le système stocke les exécutables standards, comme ``/usr/local/bin:/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/sbin:`` ainsi que des répertoires relatifs à des programmes spécialisés comme ``/usr/lib/mozart/bin:/opt/python3/bin``. L'utilisateur peut ajouter des répertoires à son ``PATH`` avec `bash(1)`_ en incluant par exemple la commande ``PATH=$PATH:$HOME/local/bin:.`` dans son fichier ``.profile``. Cette commande ajoute au ``PATH`` par défaut le répertoire ``$HOME/local/bin`` et le répertoire courant. Car convention, Unix utilise le caractère ``.`` pour représenter ce répertoire courant.

La librairie standard contient plusieurs fonctions qui permettent de manipuler les variables d'environnement d'un processus. La fonction `getenv(3)`_ permet de récupérer la valeur associée à une variable d'environnement. La fonction `unsetenv(3)`_ permet de supprimer une variable de l'environnement du programme courant. La fonction `setenv(3)`_ permet elle de modifier la valeur d'une variable d'environnement. Cette fonction alloue de la mémoire pour stocker la nouvelle variable d'environnement et peut échouer si il n'y a pas assez de mémoire disponible pour stocker de nouvelles variables d'environnement. Ces fonctions sont utilisées notamment par l'interpréteur de commande mais parfois par des programmes dont le comportement dépend de la valeur de certaines variables d'environnement. Par exemple, la commande `man(1)`_ utilise différentes variables d'environnement pour déterminer par exemple où les pages de manuel sont stockées et la langue (variable ``LANG``) dans laquelle il faut afficher les pages de manuel.

Le programme ci-dessous illustre brièvement l'utilisation de `getenv(3)`_, `unsetenv(3)`_ et `setenv(3)`_. Outre ces fonctions, il existe également `clearenv(3)`_ qui permet d'effacer complètement toutes les variables d'environnement du programme courant et `putenv(3)`_ qui était utilisé avant `setenv(3)`_.

.. literalinclude:: /Theorie/C/S3-src/argv-env.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA


La pile (ou stack)
------------------

La :term:`pile` ou :term:`stack` en anglais est la dernière zone de mémoire utilisée par un processus. C'est une zone très importante car c'est dans cette zone que le processus va stocker l'ensemble des variables locales mais également les valeurs de retour de toutes les fonctions qui sont appelées. Cette zone est gérée comme une pile, d'où son nom. Pour comprendre son fonctionnement, nous utiliserons le programme :download:`/Theorie/C/S3-src/fact.c` qui permet de calculer une factorielle de façon récursive.

.. literalinclude:: /Theorie/C/S3-src/fact.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///BBB
   :end-before: ///AAA

Lors de l'exécution de la fonction ``compute()``, le programme ci-dessus produit la sortie suivante.


.. literalinclude:: /Theorie/C/S3-src/fact.out
   :encoding: iso-8859-1
   :language: console
   :start-after: ///FACT

Il est intéressant d'analyser en détails ce calcul récursif de la factorielle car il illustre bien le fonctionnement du stack et son utilisation.

Tout d'abord, il faut noter que les fonctions ``fact`` et ``times`` se trouvent, comme toutes les fonctions définies dans le programme à l'intérieur du :term:`segment text`. La variable ``nombre`` quant à elle se trouve sur la pile en haut de la mémoire. Il s'agit d'une variable locale qui est allouée lors de l'exécution de la fonction ``compute``. Il en va de même des arguments qui sont passés aux fonctions. Ceux-ci sont également stockés sur la pile. C'est le cas par exemple de l'argument ``n`` de la fonction ``fact``. Lors de l'exécution de l'appel à ``fact(3)``, la valeur ``3`` est stockée sur la pile pour permettre à la fonction ``fact`` d'y accéder. Ces accès sont relatifs au sommet de la pile comme nous aurons l'occasion de le voir dans la présentation du langage d'assemblage. Le premier appel récursif se fait en calculant la valeur de l'argument (``2``) et en appelant la fonction. L'argument est placé sur la pile, mais à une autre adresse que celle utilisée pour ``fact(3)``. Durant son exécution, la fonction ``fact(2)`` accède à ses variables locales sur la pile sans interférer avec les variables locales de l'exécution de ``fact(3)`` qui attend le résultat de ``fact(2)``. Lorsque ``fact(2)`` fait l'appel récursif, la valeur de son argument (``1``) est placée sur la pile et l'exécution de ``fact(1)`` démarre. Celle-ci a comme environnement d'exécution le sommet de la pile qui contient la valeur ``1`` comme argument et la fonction retourne la valeur ``1`` à l'exécution de ``fact(2)`` qui l'avait lancée. Dès la fin de ``fact(1)``, ``fact(2)`` reprend son exécution où elle avait été interrompue et applique la fonction ``times`` avec ``2`` et ``1`` comme arguments. Ces deux arguments sont placés sur le pile et ``times`` peut y accéder au début de son exécution pour calculer la valeur ``2`` et retourner le résultat à la fonction qui l'a appelé, c'est-à-dire ``fact(2)``. Cette dernière retrouve son environnement d'exécution sur la pile. Elle peut maintenant retourner son résultat à la fonction ``fact(3)`` qui l'avait appelée. Celle-ci va appeler la fonction ``times`` avec ``3`` et ``2`` comme arguments et finira par retourner la valeur ``6``.

La pile joue un rôle essentiel lors de l'exécution de programmes en C puisque toutes les variables locales, y compris celles de la fonction ``main`` y sont stockées. Comme nous le verrons lorsque nous aborderons le langage assembleur, la pile sert aussi à stocker l'adresse de retour des fonctions. C'est ce qui permet à l'exécution de ``fact(2)`` de se poursuivre correctement après avoir récupéré la valeur calculée par l'appel à ``fact(1)``. L'utilisation de la pile pour stocker les variables locales et les arguments de fonctions a une conséquence importante. Lorsqu'une variable est définie comme argument ou localement à une fonction ``f``, elle n'est accessible que durant l'exécution de la fonction ``f``. Avant l'exécution de ``f`` cette variable n'existe pas et si ``f`` appelle la fonction ``g``, la variable définie dans ``f`` n'est plus accessible à partir de la fonction ``g``.

En outre, comme le langage C utilise le passage par valeur, les valeurs des arguments d'une fonction sont copiés sur la pile avant de démarrer l'exécution de cette fonction. Lorsque la fonction prend comme argument un entier, cette copie prend un temps très faible. Par contre, lorsque la fonction prend comme argument une ou plusieurs structures de grand taille, celles-ci doivent être entièrement copiées sur la pile. A titre d'exemple, le programme ci-dessous définit une très grande structure contenant un entier et une zone permettant de stocker un million de caractères. Lors de l'appel à la fonction ``sum``, les structures ``one`` et ``two`` sont entièrement copiées sur la pile. Comme chaque structure occupe plus d'un million d'octets, cela prend plusieurs centaines de microsecondes. Cette copie est nécessaire pour respecter le passage par valeur des structures à la fonction ``sum``. Celle-ci ne peut pas modifier le contenu des structures qui lui sont passées en argument. Par comparaison, lors de l'appel à ``sumptr``, seules les adresses de ces deux structures sont copiées sur la pile. Un appel à ``sumptr`` prend moins d'une microseconde, mais bien entendu la fonction ``sumptr`` a accès via les pointeurs passés en argument à toute la zone de mémoire qui leur est associée.

.. literalinclude:: /Theorie/C/S3-src/structargs.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB


Certaines variantes de Unix et certains compilateurs permettent l'allocation de mémoire sur la pile via la fonction `alloca(3)`_. Contrairement à la mémoire allouée par `malloc(3)`_ qui doit être explicitement libérée en utilisant `free(3)`_, la mémoire allouée par `alloca(3)`_ est libérée automatiquement à la fin de l'exécution de la fonction dans laquelle la mémoire a été allouée. Cette façon d'allouer de la mémoire sur la pile n'est pas portable et il est préférable de n'allouer de la mémoire que sur le tas en utilisant `malloc(3)`_.

Les versions récentes du C et notamment [C99]_ permettent d'allouer de façon dynamique un tableau sur la pile. Cette fonctionnalité peut être utile dans certains cas, mais elle peut aussi être la source de nombreuses erreurs et difficultés. Pour bien comprendre ce problème, considérons à nouveau la fonction ``duplicate`` qui a été définie précédemment en utilisant `malloc(3)`_  et des pointeurs.

.. literalinclude:: /Theorie/C/S3-src/strcpy.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB


Un étudiant pourrait vouloir éviter d'utiliser `malloc(3)`_ et écrire plutôt la fonction suivante.

.. literalinclude:: /Theorie/C/S3-src/strcpy.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///BBB
   :end-before: ///CCC

Lors de la compilation, `gcc(1)`_ affiche le :term:`warning` ``In function ‘duplicate2’: warning: function returns address of local variable``. Ce warning indique que la ligne ``return str2;`` retourne l'adresse d'une variable locale qui n'est plus accessible à la fin de la fonction ``duplicate2``. En effet, l'utilisation de tableaux alloués dynamiquement sur la pile est équivalent à une utilisation implicite de `alloca(3)`_. La déclaration ``char str2[len];`` est équivalente à ``char *str2 =(char *)alloca(len*sizeof(char));`` et la zone mémoire allouée sur la pile pour ``str2`` est libérée lors de l'exécution de ``return str2;`` puisque toute mémoire allouée sur la pile est implicitement libérée à la fin de l'exécution de la fonction durant laquelle elle a été allouée. Donc, une fonction qui appelle ``duplicate2`` ne peut pas récupérer les données se trouvant dans la zone mémoire qui a été allouée par ``duplicate2``.



.. rubric:: Footnotes

.. [#fpossible] Pour des raisons de performance, le compilateur C ne génère pas de code permettant de vérifier automatiquement qu'un accès via un pointeur pointe vers une zone de mémoire qui est libre. Il est donc parfois possible d'accéder à une zone mémoire qui a été libérée, mais le programme n'a aucune garantie sur la valeur qu'il y trouvera. Ce genre d'accès à des zones mémoires libérées doit bien entendu être complètement proscrit.

.. [#ggetrlimit] Sur de nombreuses variantes de Unix, cette limite à la taille du stack dépend du matériel utilisé et est configurable par l'administrateur système. Un processus peut connaître la taille maximale de son stack en utilisant l'appel système `getrlimit(2)`_. L'administrateur système peut modifier ces limites via l'appel système `setrlimit(2)`_. La commande ``ulimit`` de `bash(1)`_ permet également de manipuler ces limites.

.. [#fetext] Dans de nombreuses variantes de Unix, il est possible de connaître le sommet du segment :term:`text` d'un processus grâce à la variable :term:`etext`. Cette variable, de type ``char`` est initialisée par le système au chargement du processus. Elle doit être déclarée comme variable de type ``extern char etext`` et son adresse (``&etext``) correspond au sommet du segment text.

.. [#fvmem] Nous verrons ultérieurement que grâce à l'utilisation de la mémoire virtuelle, il est possible pour un processus d'utiliser des zones de mémoire qui ne sont pas contigües.

.. [#fothermalloc] Il existe différentes alternatives à l'utilisation de `malloc(3)`_ pour l'allocation de mémoire comme `Hoard <http://www.hoard.org/>`_ ou `gperftools <http://code.google.com/p/gperftools/>`_

.. [#fenvbash] Il possible de lister les définitions actuelles des variables d'environnement via la commande `printenv(1)`_. Les interpréteurs de commande tels que `bash(1)`_ permettent de facilement modifier les valeurs de ces variables. La plupart d'entre elles sont initialisées par le système ou via les fichiers qui sont chargés automatiquement au démarrage de l'interpréteur comme ``/etc/profile`` qui contient les variables fixées par l'administrateur système ou le fichier ``.profile`` du répertoire d'accueil de l'utilisateur qui contient les variables d'environnement propres à cet utilisateur.



