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

Chaque règle commence par une ligne de dépendance qui définit une ou plusieurs cibles (``target``) suivies par le caractère ``:`` et éventuellement une liste de composants (``components``) dont dépend la cible. Une cible ou un composant peut être un fichier ou un simple label.

Il est important de se rendre compte que l'espacement derrière les ``command``
doit impérativement commencer par une *tabulation*.
Ça ne peut pas commencer par des espaces.
Il ne faut pas non plus confondre la touche tabulation du clavier
qui est souvent interprétée par les éditeurs de texte
par une indentation et le caractère de tabulation
(souvent écrit ``\t`` comme en C ou en bash) qui sont souvent affichés
avec 2, 3, 4 ou 8 espacements en fonction des préférences de l'utilisateur.
On parle bien ici du caractère de tabulation.
Heureusement, bien que beaucoup de gens configurent
leur éditeur de texte pour indenter avec des espaces,
la plupart des bons éditeurs reconnaissent que c'est
un Makefile et indentent avec des tabulations.

Le fichier suivant reprend un exemple de règle où la cible et le composant sont des fichiers.

    .. code-block:: make

        text.txt: name.txt
            echo "Salut, " > text.txt
            cat name.txt >> text.txt

Lorsque ``make`` est exécuté en utilisant ce Makefile, on obtient:

    .. code-block:: console

        $ make
        make: *** No rule to make target `name.txt', needed by `text.txt'.  Stop.

Comme ``text.txt`` dépend de ``name.txt``, il faut que ce dernier soit défini comme cible dans le Makefile ou existe en tant que fichier. Si nous créons le fichier ``name.txt`` contenant ``Tintin`` et que ``make`` est ré-exécuté, on obtient la sortie suivante :

    .. code-block:: console

        $ make
        echo "Salut, " > text.txt
        cat name.txt >> text.txt
        $ cat text.txt
        Salut,
        Tintin

Lorsqu'une dépendance change, ``make`` le détecte et ré-exécute les commandes associées à la cible. Dans le cas suivant, le fichier ``name.txt`` est modifié, ce qui force la regénération du fichier ``text.txt``.

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

Ce Makefile permettra de générer un binaire ``test`` à chaque fois que le fichier source aura changé.

Les variables
~~~~~~~~~~~~~

.. sectionauthor:: Alexis Nootens <alexis.nootens@student.uclouvain.be>

Il est possible d'utiliser des variables dans un fichier Makefile. Celles-ci sont généralement définies au début du fichier, une par ligne comme :

    .. code-block:: make

        CC = GCC
        OPT = -ansi
        VARIABLE_AU_NOM_TRES_LONG = 1

Notez que les noms sont écrits en majuscule par convention. Leur appel est semblable à celui en script shell (bash) excepté les parenthèses après le symbole $.
On écrit par exemple ``$(CC)``, ``$(CFLAGS)``, ``$(VARIABLE_AU_NOM_TRES_LONG)``. Make autorise de remplacer les parenthèses par des accolades mais cette pratique est moins répandue.

    .. code-block:: make

        CC = GCC
        CFLAGS = -ansi

        build:
            $(CC) $(CFLAGS) foo.c -o foo

Vous aurez compris qu'ici, la cible ``build`` effectue la commande ``gcc -ansi foo.c -o foo``.
Il est très intéressant de savoir que toutes les variables d’environnement présentes lors de l’appel au Makefile sont également disponibles avec la même notation.
Vous pouvez donc très bien utiliser la variable ``$(HOME)`` indiquant le répertoire attribué à l'utilisateur sans la définir.

Il existe six différentes manières d'assigner une valeur à une variable. Nous ne nous intéresserons qu'à quatre d'entre elles.

    .. code-block:: make

        VARIABLE = value
        VARIABLE := value
        VARIABLE ?= value
        VARIABLE += value

- La première permet de lier la variable à une valeur (ici value). Mais celle-ci ne sera évaluée qu'à son appel.
- La seconde permet de déclarer une variable et de l'évaluer directement en même temps.
- La troisième permet d'assigner une valeur à la variable uniquement si celle-ci n'en a pas encore.
- La quatrième permet d'ajouter une valeur à une autre déjà déclarée.

Une description détaillée de ces méthodes d'assignation et des deux autres restantes se trouve à l'adresse suivante `<http://www.gnu.org/software/make/manual/make.html#Setting>`_

Les conditions
~~~~~~~~~~~~~~

Les variables ne servent pas uniquement à éviter la redondance d'écriture dans votre fichier. On peut aussi les utiliser pour
réaliser des opérations conditionnelles comme :

    .. code-block:: make

        DEBUG = 1

        build:
        ifeq ($(DEBUG), 1)
            gcc -Wall -Werror -o foo foo.c
        else
            gcc -o foo foo.c
        endif

Ici ``ifeq`` permet de tester un "si égal". Il existe aussi l'opération opposée ``ifneq`` pour "si non-égal". Remarquez que les conditions ne doivent pas être tabulées au risque d'obtenir une erreur
de syntaxe incompréhensible. Les conditions peuvent avoir différentes syntaxes. Vous pouvez les trouver sur cette page http://www.gnu.org/software/make/manual/make.html#Conditional-Syntax

Avec les sections précédentes et la suivante nous allons pouvoir nous aventurer dans la création de Makefiles plus complexes.
On peut vouloir effectuer des compilations différentes suivant l'environnement de l'utilisateur comme son OS, son matériel ou juste son nom.
Encore une fois Make nous gâte en nous offrant la possibilité d'exécuter des commandes shell dans nos Makefiles.
Imaginez avoir besoin d'options de compilation supplémentaires à cause de votre OS que seul vous avez besoin. Vous pouvez effectuer une compilation
conditionnelle sur votre nom.

    .. code-block:: make

        USER := $(shell whoami)

        build:
        ifeq ($(USER), sfeldman)
            gcc -I($HOME)/local/include -o foo foo.c
        else
            gcc -o foo foo.c
        endif

Ici ``$(shell whoami)`` est un appel à la fonction shell (de Make) qui nous permet d'assigner à la variable ``USER``, en évaluant immédiatement l'appel, le résultat de la commande shell (bash) ``whoami`` renvoyant le
nom de l'utilisateur actuel. Cela ne fonctionnera que si la commande ``whoami`` est disponible dans le shell évidemment.

La cible .PHONY
~~~~~~~~~~~~~~~

Make compare les dates de modification des fichiers produits avec les dates de leur(s) source(s) pour savoir si celles-ci ont été modifiées depuis leur dernière compilation. Cela lui permet de ne pas devoir recompiler des fichiers qui n'auraient pas changé d'un appel à
l'autre. Malheureusement ce comportement qui peut sembler avantageux amène aussi des problèmes, en l’occurrence pour des règles ne produisant aucun fichier.
Une solution pour pallier le problème consiste à indiquer que la règle ne crée rien. Pour faire cela il existe une cible spéciale ``.PHONY`` permettant de définir
quelles règles doivent toujours être exécutées à nouveau. Ainsi une règle ``.PHONY`` ne rencontrera jamais le problème d'être déjà à jour.
Une bonne pratique est de déclarer dans ``.PHONY`` toutes les règles de nettoyage de votre projet.

    .. code-block:: make

        build:
            gcc -o foo foo.c

        .PHONY: clean

        clean:
            rm -f *.o

Cela est aussi pratique pour forcer une re-compilation.

    .. code-block:: make

        build:
            gcc -o foo foo.c

        .PHONY: clean rebuild

        clean:
            rm -f *.o foo

        rebuild: clean build

Compléments
~~~~~~~~~~~

Afin de rendre vos Makefiles plus lisibles, vous pouvez y insérer des commentaires en plaçant un croisillon en début de ligne.
Cette syntaxe est semblable au script shell.

    .. code-block:: make

        # Commentaire sur
        # plusieurs lignes
        build:
            gcc -o foo foo.c # commentaire en fin de ligne

Débugger les erreurs de vos Makefiles peut sembler difficile lorsque vous êtes baignés dans un flux d'instructions. Vous pouvez néanmoins régler leur verbosité.
Il est possible de rendre silencieuse une commande en plaçant une arobase devant. Ceci indique juste à Make de ne pas imprimer la ligne de commande. La sortie
standard de cette commande restera visible.

    .. code-block:: make

        build:
            @echo "Building foo"
            @gcc -o foo foo.c

Pour plus d'informations en français sur l'écriture ou utilisation des Makefiles voir [DeveloppezMake]_.

Documentation complète en anglais sur le site officiel [GNUMake]_.
