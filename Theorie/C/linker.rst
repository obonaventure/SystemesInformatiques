.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. _complementsC:


Compléments de C
================


Dans les sections précédentes, nous n'avons pas pu couvrir l'ensemble des concepts avancés qui sont relatifs à une bonne utilisation du langage C. Cette section contient quelques notions plus avancées qui sont importantes en pratique.


Pointeurs
---------

Les pointeurs sont très largement utilisés dans les programmes écrits en langage C. Nous avons utilisé des pointeurs vers des types de données primitifs tel que les ``int``, ``char`` ou ``float`` et des pointeurs vers des structures. En pratique, il est possible en C de définir des pointeurs vers n'importe quel type d'information qui est manipulée par un programme C.

Un premier exemple sont les pointeurs vers des fonctions. Comme nous l'avons vu dans le chapitre précédent, une fonction est une séquence d'instructions assembleur qui sont stockées à un endroit bien précis de la mémoire. Cette localisation précise des instructions qui implémentent la fonction permet d'appeler une fonction avec l'instruction ``calll``. En C, il est parfois aussi souhaitable de pouvoir appeler une fonction via un pointeur vers cette fonction plutôt qu'en nommant la fonction directement. Cela peut rendre le code plus flexible et plus facile à adapter. Nous avons déjà utilisé des pointeurs vers des fonctions sans le savoir lorsque nous avons utilisé ``printf("fct : %p\n",f)`` où ``f`` est un nom de fonction. L'exemple ci-dessous montre une autre utilisation intéressante des pointeurs vers des fonctions. Lorsque l'on écrit du code C, il est parfois utile d'ajouter des commandes qui permettent d'afficher à l'écran des informations de debugging. L'exemple ci-dessous est une application qui supporte trois niveaux de debugging. Rien n'est affiché au niveau ``0``, une ligne s'affiche au niveau ``1`` et des informations plus détaillées sont affichées au niveau ``2``. Lors de son exécution , l'application affiche la sortie suivante.

.. code-block:: console

  $./fctptr 0
  fct debug_print : 0x100000d28
  $ ./fctptr 1
  fct debug_print : 0x100000d32
  debug: Hello
  $ ./fctptr 2
  fct debug_print : 0x100000d5f
  debug: Hello
  g=1

Cette application qui supporte plusieurs niveaux de debugging utilise pourtant toujours le même appel pour afficher l'information de debugging : ``(debug_print[debug_level])(...);``. Cet appel profite des pointeurs vers les fonctions. Le tableau ``debug_print`` est un tableau de pointeurs vers des fonctions qui chacune prend comme argument un ``char *``. La variable globale ``debug_level`` est initialisée sur base de l'argument passé au programme.

.. literalinclude:: /C/S5-src/fctptr.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB


Ce n'est pas la seule utilisation des pointeurs vers des fonctions. Il y a notamment la fonction de la librairie `qsort(3)`_ qui permet de trier un tableau contenant n'importe quel type d'information. Cette fonction prend plusieurs arguments :

.. code-block:: c

  void qsort(void *base, size_t nel, size_t width,
             int (*compar)(const void *, const void *));

Le premier est un pointeur vers le début de la zone mémoire à trier. Le second est le nombre d'éléments à trier. Le troisième contient la taille des éléments stockés dans le tableau. Le quatrième argument est un pointeur vers la fonction qui permet de comparer deux éléments du tableau. Cette fonction retourne un entier négatif si son premier argument est inférieur au second et positif ou nul sinon. Un exemple de fonction de comparaison est la fonction `strcmp(3)`_ de la librairie standard. Un autre exemple est repris ci-dessous avec une fonction de comparaison simple qui permet d'utiliser `qsort(3)`_ pour trier un tableau de ``double``.

.. literalinclude:: /C/S5-src/qsort.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Il est utile d'analyser en détails les arguments de la fonction de comparaison utilisée par `qsort(3)`_. Celle-ci prend deux arguments de type ``const void *``. L'utilisation de pointeurs ``void *`` est nécessaire car la fonction doit être générique et pouvoir traiter n'importe quel type de pointeurs. ``void *`` est un pointeur vers une zone quelconque de mémoire qui peut être casté vers n'importe quel type de pointeur par la fonction de comparaison. Le qualificatif ``const`` indique que la fonction n'a pas le droit de modifier la donnée référencée par ce pointeur, même si elle reçoit un pointeur vers cette donnée. On retrouvera régulièrement cette utilisation de ``const`` dans les signatures des fonctions de la librairie pour spécifier des contraintes sur les arguments passés à une fonction [#frestrict]_.

.. todo:: restrict

Le second type de pointeurs que nous n'avons pas encore abordé en détails sont les pointeurs vers des pointeurs. En fait, nous les avons utilisés sans vraiment le savoir dans la fonction ``main``. En effet, le second argument de cette fonction est un tableau de pointeurs qui pointent chacun vers des chaînes de caractères différentes. La notation ``char *argv[]`` est équivalente à la notation ``char **argv``. ``**argv`` est donc un pointeur vers une zone qui contient des pointeurs vers des chaînes de caractères. Ce pointeur vers un pointeur doit être utilisé avec précaution. ``argv[0]`` est un pointeur vers une chaîne de caractères. La construction ``&(argv[0])`` permet donc d'obtenir un pointeur vers un pointeur vers une chaîne de caractères, ce qui correspond bien à la déclaration ``char **``. Ensuite, l'utilisation de ``*p`` pourrait surprendre. ``*p`` est un pointeur vers une chaîne de caractères. Il peut donc être comparé à ``NULL`` qui est aussi un pointeur, incrémenté et la chaîne de caractères qu'il référencie peut être affichée par `printf(3)`_.

.. literalinclude:: /C/S5-src/ptrptr.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

En pratique, ces pointeurs vers des pointeurs se retrouveront lorsque l'on doit manipuler des structures multidimensionnelles, mais aussi lorsqu'il faut qu'une fonction puisse modifier une adresse qu'elle a reçue en argument.

.. C'est notamment le cas lorsqu'il faut mettre à jour une structure chaînée. Lorsque nous avons construit une structure chaînée permettant de manipuler une pile, les fonctions ``push`` et ``pop`` récupéraient le sommet de la pile dans une variable globale. Cet aspect sera couvert par un des exercices.


Un autre exemple d'utilisation de pointeurs vers des pointeurs est la fonction `strtol(3)`_ de la librairie standard. Cette fonction est une généralisation des fonctions comme `atoi(3)`_. Elle permet de convertir une chaîne de caractères en un nombre. La fonction `strtol(3)`_ prend trois arguments et retourne un ``long``. Le premier argument est un pointeur vers la chaîne de caractères à convertir. Le troisième argument est la base utilisée pour cette conversion.

.. code-block:: c

    #include <stdlib.h>
    long
    strtol(const char *restrict str, char **restrict endptr, int base);

L'utilisation principale de `strtol(3)`_ est de convertir une chaîne de caractères en un nombre. La fonction `atoi(3)`_ fait de même et l'expression ``atoi("1252")`` retourne l'entier ``1252``. Malheureusement, la fonction `atoi(3)`_ ne traite pas correctement les chaînes de caractères qui ne contiennent pas un nombre. Elle ne retourne pas de code d'erreur et ne permet pas de savoir quelle partie de la chaîne de caractères passée en argument était en erreur.

`strtol(3)`_ est un exemple de fonction qui doit retourner deux types d'informations. Tout d'abord, `strtol(3)`_ retourne un résultat (dans ce cas un nombre). Si la chaîne de caractères à convertir est erronée, `strtol(3)`_ convertit le début de la chaîne et retourne un pointeur indiquant le premier caractère en erreur. Pour bien comprendre le fonctionnement de `strtol(3)`_, considérons l'exemple ci-dessous.

.. literalinclude:: /C/S5-src/strtol.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA

Lors de son exécution, ce programme affiche la sortie suivante.

.. literalinclude:: /C/S5-src/strtol.out
   :encoding: utf-8
   :language: console

L'appel à `strtol(3)`_ prend trois arguments. Tout d'abord un pointeur vers la chaîne de caractères à convertir. Ensuite l'adresse d'un pointeur vers une chaîne de caractères. Enfin la base de conversion. La première chaîne de caractères est correcte. Elle est convertie directement. La seconde par contre contient un caractère erroné. Lors de son exécution, `strtol(3)`_ va détecter la présence du caractère ``m`` et placera un pointeur vers ce caractère dans ``*p``. Pour que la fonction `strtol(3)`_ puisse retourner un pointeur de cette façon, il est nécessaire que son second argument soit de type ``char **``. Si le second argument était de type ``char *``, la fonction `strtol(3)`_ recevrait l'adresse d'une zone mémoire contenant un caractère. Comme le langage C utilise le passage par valeur, `strtol(3)`_ pourrait modifier la caractère pointé par ce pointeur mais pas son adresse. En utilisant un second argument de type ``char **``, `strtol(3)`_ a la possibilité de modifier la valeur pointée par ce pointeur.

Une implémentation partielle de `strtol(3)`_ pourrait être la suivante.

.. literalinclude:: /C/S5-src/mystrtol.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Cette partie de code utilise la fonction `isdigit(3)`_ pour vérifier si les caractères présents dans la chaîne de caractères sont des chiffres. Sinon, elle fixe via son second argument la valeur du pointeur vers le caractère en erreur. Cela est réalisé par l'expression ``*endptr=(char *)(str+i);``. Il faut noter que ``*endptr`` est bien une zone mémoire pointée par le pointeur ``endptr`` reçu comme second argument. Cette valeur peut donc être modifiée.

Il existe d'autres fonctions de la librairie standard qui utilisent des pointeurs vers des pointeurs comme arguments dont notamment `strsep(3)`_ et `strtok_r(3)`_.

.. .. note: Le qualificateur ``restrict``

..  Explication de ``restrict``

.. todo:: mettre plus de détails

De grands programmes en C
-------------------------

Lorsque l'on développe de grands programmes en C, il est préférable de découper le programme en modules. Chaque module contient des fonctions qui traitent d'un même type de problème et sont fortement couplées. A titre d'exemple, un module ``stack`` pourrait regrouper différentes fonctions de manipulation d'une pile. Un autre module pourrait regrouper les fonctions relatives au dialogue avec l'utilisateur, un autre les fonctions de gestion des fichiers, ...

Pour comprendre l'utilisation de ces modules, considérons d'abord un programme trivial composé de deux modules. Le premier module est celui qui contient la fonction ``main``. Tout programme C doit contenir une fonction ``main`` pour pouvoir être exécuté. C'est en général l'interface avec l'utilisateur. Le second module contient une fonction générique qui est utilisée par le module principal.

.. literalinclude:: /C/S5-src/main.c
   :encoding: utf-8
   :language: c

Un module d'un programme C est en général décomposé en deux parties. Tout d'abord, le fichier :term:`fichier header` contient les définitions de certaines constantes et les signatures des fonctions exportées par ce module. Ce fichier est en quelque sorte un résumé du module, ou plus précisément de son interface externe. Il doit être inclus dans tout fichier qui utilise les fonctions du module correspondant. Dans un tel fichier :term:`fichier header`, on retrouve généralement trois types d'informations :

 - les signatures des fonctions qui sont définies dans le module. En général, seules les fonctions qui sont destinées à être utilisées par des modules extérieures sont reprises dans le :term:`fichier header`
 - les constantes qui sont utilisées à l'intérieur du module et doivent être visibles en dehors de celui-ci, notamment par les modules qui utilisent les fonctions du module. Ces constantes peuvent être définies en utilisant des directives ``#define`` du préprocesseur
 - les variables globales qui sont utilisées par les fonctions du module et doivent être accessibles en dehors de celui-ci

.. literalinclude:: /C/S5-src/min.h
   :encoding: utf-8
   :language: c

.. note:: Un :term:`fichier header` ne doit être inclus qu'une seule fois

 L'exemple de :term:`fichier header` ci-dessus illustre une convention courante dans l'écriture de ces fichiers. Parfois, il est nécessaire d'inclure un :term:`fichier header` dans un autre fichier header. Suite à cela, il est possible que les mêmes définitions d'un :term:`fichier header` soient incluses deux fois ou plus dans le même module. Cela peut causer des erreurs de compilation qui risquent de perturber certains programmeurs. Une règle de bonne pratique pour éviter ce problème est d'inclure le contenu du :term:`fichier header` de façon conditionnelle comme présenté ci-dessus. Une constante, dans ce cas ``_MIN_H_``, est définie pour le :term:`fichier header` concerné. Cette constante est définie dans la première ligne effective du :term:`fichier header`. Celui-ci n'est inclus dans un module que si cette constante n'a pas été préalablement définie. Si cette constante est connue par le préprocesseur, cela indique qu'un autre :term:`fichier header` a déjà inclus les définitions de ce fichier et qu'elles ne doivent pas être incluses une seconde fois.

.. literalinclude:: /C/S5-src/min.c
   :encoding: utf-8
   :language: c

.. note:: Localisation des fichiers header

 Un programmeur C peut utiliser deux types de fichiers header. Il y a tout d'abord les fichiers headers standards qui sont fournis avec le système. Ce sont ceux que nous avons utilisés jusque maintenant. Ces headers standards se reconnaissent car ils sont entourés des caractères ``<`` et ``>`` dans la directive ``#include``. Ceux-ci se trouvent dans des répertoires connus par le compilateur, normalement ``/usr/include``. Les fichiers headers qui accompagnent un module se trouvent eux généralement dans le même répertoire que le module. Dans l'exemple ci-dessus, le header ``min.h`` est inclus via la directive ``#include "min.h"``. Lorsque le préprocesseur rencontre une telle directive, il cherche le fichier dans le répertoire courant. Il est possible de spécifier des répertoires qui contiennent des fichiers headers via l'argument ``-I`` de `gcc(1)`_  ou en utilisant les variables d'environnement ``GCC_INCLUDE_DIR`` ou ``CPATH``.

Lorsque l'on doit compiler un programme qui fait appel à plusieurs modules, quelle que soit sa taille, il est préférable d'utiliser `make(1)`_ pour automatiser sa compilation. Le fichier ci-dessous est un exemple minimaliste de :term:`Makefile` utilisable pour un tel projet.

.. literalinclude:: /C/S5-src/Makefile2
   :encoding: utf-8
   :language: makefile
   :start-after: ###AAA
   :end-before: ###BBB

La compilation d'un tel programme se déroule en plusieurs étapes. La première étape est celle du préprocesseur. Celui-ci est directement appelé par le compilateur `gcc(1)`_ mais il est également possible de l'invoquer directement via `cpp(1)`_. Le préprocesseur remplace toutes les macros telles que les ``#define`` et insère les fichiers headers sur base des directives ``#include``. La sortie du préprocesseur est utilisée directement par le compilateur. Celui-ci transforme le module en langage C en langage assembleur. Ce module en assembleur est ensuite assemblé par `as(1)`_ pour produire un :term:`fichier objet`. Ce :term:`fichier objet` n'est pas directement exécutable. Il contient les instructions en langage machine pour les différentes fonctions définies dans le module, les définitions des constantes et variables globales ainsi qu'une table reprenant tous les symboles (noms de fonction, noms de variables globales, ...) définis dans ce module. Ces phases sont exécutées pour chaque module utilisé. Par convention, les fichiers objets ont en général l'extension ``.o``. Ces fichiers objet sont créés par les deux dernières cibles du fichier ``Makefile`` ci-dessus. L'option ``-c`` passée à `gcc(1)`_ indique à `gcc(1)`_ qu'il doit générer un fichier objet sans le transformer en exécutable. Cette dernière opération est réalisée par la première cible du ``Makefile``. Dans cette cible, `gcc(1)`_ fait office d'éditeur de liens ou de :term:`linker` en anglais. Le :term:`linker` combine différents fichiers objets en faisant les liens nécessaires entre les fichiers. Dans notre exemple, le fichier ``main.o`` contient une référence vers la fonction ``min`` qui n'est pas connue lors de la compilation de ``main.c``. Par contre, cette référence est connue dans le fichier ``min.o``. L'éditeur de liens va combiner ces références de façon à permettre aux fonctions d'un module d'exécuter n'importe quelle fonction définie dans un autre module.

La figure ci-dessous représente graphiquement les différentes étapes de compilation des modules ``min.c`` et ``main.c``.

.. figure:: /C/figures/figures-007-c.png
   :align: center
   :scale: 60

   Etapes de compilation


Lorsque plusieurs modules, potentiellement développés par des programmeurs qui ne se sont pas concertés, doivent être intégrés dans un grand programme, il y a des risques de conflits entre des variables et fonctions qui pourraient être définies dans plusieurs modules différents. Ainsi, deux modules pourraient définir la fonction ``int min(int, int)`` ou la variable globale ``float dist``. Le langage C intègre des facilités qui permettent d'éviter ou de contrôler ces problèmes.

Tout d'abord, les variables locales sont locales au bloc dans lequel elles sont définies. Ce principe permet d'utiliser le même nom de variable dans plusieurs blocs d'un même fichier. Il s'étend naturellement à l'utilisation de variables locales dans des fichiers différents.

Pour les variables globales, la situation est différente. Si une variable est définie en dehors d'un bloc dans un fichier, cette variable est considérée comme étant globale. Par défaut, elle est donc accessible depuis tous les modules qui composent le programme. Cela peut en pratique poser des difficultés si le même nom de variable est utilisé dans deux modules différents. Pour contourner ce problème, le langage C utilise le qualificateur ``static``. Lorsque ce qualificateur est placé devant une déclaration de variable en dehors d'un bloc dans un module, il indique que la variable doit être accessible à toutes les fonctions du module mais pas en dehors du module. Lorsqu'un module utilise des variables qui sont communes à plusieurs fonctions mais ne doivent pas être visibles en dehors du module, il est important de les déclarer comme étant ``static``. Le deuxième qualificateur relatif aux variables globales est ``extern``. Lorsqu'une déclaration de variable globale est préfixée par ``extern``, cela indique au compilateur que la variable est définie dans un autre module qui sera linké ultérieurement. Le compilateur réserve une place pour cette variable dans la table des symboles du fichier objet, mais cette place ne pourra être liée à la zone mémoire qui correspond à cette variable que lorsque l'éditeur de liens combinera les différents fichiers objet entre eux.

.. note:: Les deux utilisations de ``static`` pour des variables

 La qualificateur ``static`` peut être utilisé à la fois pour des variables qui sont définies en dehors d'un bloc et dans un bloc. Lorsqu'une variable est définie comme étant ``static`` hors d'un bloc dans un module, elle n'est accessible qu'aux fonctions de ce module. Par contre, lorsqu'une variable est définie comme étant ``static`` à l'intérieur d'un bloc, par exemple dans une fonction, le qualificatif indique que cette variable doit toujours se trouver à la même localisation en mémoire, quel que soit le moment où elle est appelée. Ces variables ``static`` sont placées par le compilateur dans le bas de la mémoire, avec les variables globales. Contrairement aux variables locales traditionnelles, une variable locale ``static`` garde sa valeur d'une invocation de la fonction à l'autre. En pratique, les variables locales ``static`` doivent être utilisées avec précaution et bien documentées. Un de leurs intérêt est qu'elles ne sont initialisées qu'au lancement du programme et pas à chaque invocation de la fonction où elles sont définies.


La qualificateur ``static`` peut aussi précéder des déclarations de fonctions. Dans ce cas, il indique que la fonction ne doit pas être visible en dehors du module dans lequel elle est définie. Sans le qualificateur ``static``, une fonction déclarée dans un module est accessible depuis n'importe quel autre module.

Afin d'illustrer l'utilisation de ``static`` et ``extern``, considérons le programme ``prog.c`` ci-dessous qui inclut le module ``module.c`` et également le module ``min.c`` présenté plus haut.

.. literalinclude:: /C/S5-src/module.h
   :encoding: utf-8
   :language: c

.. literalinclude:: /C/S5-src/module.c
   :encoding: utf-8
   :language: c

Ce module contient deux fonctions, ``vmin`` et ``min``. ``vmin`` est déclarée sans qualificatif. Elle est donc accessible depuis n'importe quel module. Sa signature est reprise dans le :term:`fichier header` ``module.h``. La fonction ``min`` par contre est déclarée avec le qualificatif ``static``. Cela implique qu'elle n'est utilisable qu'à l'intérieur de ce module et invisible de tout autre module. La variable globale ``num1`` est accessible depuis n'importe quel module. La variable ``num2`` également, mais elle est initialisée dans un autre module. Enfin, la variable ``num3`` n'est accessible qu'à l'intérieur de ce module.

.. literalinclude:: /C/S5-src/prog.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA

Ce module inclus les fichiers ``min.h`` et ``module.h`` qui contiennent les signatures des fonctions se trouvant dans ces deux modules. Trois variables globales sont utilisées par ce module. ``num1`` est définie dans un autre module (dans ce cas ``module.c``). ``num2`` est initialisée dans ce module mais accessible depuis n'importe quel autre module. ``num3`` est une variable globale qui est accessible uniquement depuis le module ``prog.c``. Même si cette variable porte le même nom qu'une autre variable déclarée dans ``module.c``, il n'y aura pas de conflit puisque ces deux variables sont ``static``.

La fonction ``f`` mérite que l'on s'y attarde un peu. Cette fonction contient la définition de la variable ``static n``. Même si cette variable est locale à la fonction ``f`` et donc invisible en dehors de cette fonction, le compilateur va lui réserver une place dans la même zone que les variables globales. La valeur de cette variable ``static`` sera initialisée une seule fois : au démarrage du programme. Même si cette variable parait être locale, elle ne sera jamais réinitialisée lors d'un appel à la fonction ``f``. Comme cette variable est stockée en dehors de la pile, elle conserve sa valeur d'une invocation à l'autre de la fonction ``f``. Ceci est illustré par l'exécution du programme qui produit la sortie suivante.

.. literalinclude:: /C/S5-src/prog.out
   :encoding: utf-8
   :language: console

Le dernier point à mentionner concernant cet exemple est relatif à la fonction ``min`` qui est utilisée dans la fonction ``main``. Le module ``prog.c`` étant linké avec ``module.c`` et ``min.c``, le linker associe à ce nom de fonction la déclaration qui se trouve dans le fichier ``min.c``. La déclaration de la fonction ``min`` qui se trouve dans ``module.c`` est ``static``, elle ne peut donc pas être utilisée en dehors de ce module.


Traitement des erreurs
----------------------

Certaines fonctions de la librairie et certains appels systèmes réussissent toujours. C'est le cas par exemple pour `getpid(2)`_. D'autres fonctions peuvent échouer et il est important de tester la valeur de retour de chaque fonction/appel système utilisé pour pouvoir réagir correctement à toute erreur. Pour certaines fonctions ou appels systèmes, il est parfois nécessaire de fournir à l'utilisateur plus d'information sur l'erreur qui s'est produite. La valeur de retour utilisée pour la plupart des fonctions de la libraire et appels systèmes (souvent un ``int`` ou un pointeur), ne permet pas de fournir de l'information précise sur l'erreur qui s'est produite.

Les systèmes Unix utilisent la variable globale :term:`errno` pour résoudre ce problème et permettre à une fonction de la librairie ou un appel système qui a échoué de donner plus de détails sur les raisons de l'échec. Cette variable globale est définie dans `errno.h`_ qui doit être inclus par tout programme voulant tester ces codes d'erreur. Cette variable est de type ``int`` et `errno.h` contient les définitions des constantes correspondants aux cas d'erreurs possibles. Il faut noter que la librairie standard fournit également les fonctions `perror(3)`_  et `strerror(3)`_ qui facilitent l'écriture de messages d'erreur compréhensibles pour l'utilisateur.

A titre d'exemple, le programme ci-dessous utilise `strerror(3)`_ pour afficher un message d'erreur plus parlant lors d'appels erronés à la fonction `setenv(3)`_.

.. literalinclude:: /C/S5-src/errno.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA

.. note:: La valeur de ``errno`` n'indique pas la réussite ou l'échec d'une fonction

 Il faut noter que la variable ``errno`` n'est modifiée par les fonctions de la librairie ou les appels systèmes que si l'appel échoue. Si l'appel réussit, la valeur de ``errno`` n'est pas modifiée. Cela implique qu'il ne faut surtout pas tester la valeur de ``errno`` pour déterminer si une fonction de la librairie a échoué ou réussi. Il ne faut surtout par utiliser le pattern suivant :

  .. code-block:: c

   setenv("PATH","/usr/bin",1);
   if(errno!=0) {
     fprintf(stderr,"Erreur : errno=%d %s\n",errno,strerror(errno);
   }

 Le code ci-dessus est erroné car il ne teste pas la valeur de retour de `setenv(3)`_. Comme les fonctions de la librairie et les appels systèmes ne modifient ``errno`` que lorsqu'une erreur survient, le code ci-dessus pourrait afficher un message d'erreur relatif à un appel système précédent qui n'a absolument rien à voir avec l'appel à la fonction `setenv(3)`_. Le code correct est évidemment de tester la valeur de retour de `setenv(3)`_ :

  .. code-block:: c

   err=setenv("PATH","/usr/bin",1);
   if(err!=0) {
     fprintf(stderr,"Erreur : errno=%d %s\n",errno,strerror(errno));
   }

.. linker : gcc -v pour voir ce qu'il se passe dans gcc, montrer cpp et les include

.. rubric:: Footnotes


.. [#frestrict] La qualificateur ``restrict`` est également parfois utilisé pour indiquer des contraintes sur les pointeurs passés en argument à une fonction [Walls2006]_.



