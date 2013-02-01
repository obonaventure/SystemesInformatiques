.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices
=========

1. Questions de base
--------------------

#. La zone mémoire utilisée diffère d'un type primitif à un autre. Ecrivez un code qui permet d'afficher le nombre de bytes utilisés sur un système 64 bits (une machine des salles) et une machine 32 bits (sirius, voir section :ref:`ssh`) pour représenter un ``int``, ``long``, ``void *``, ``char *``, ``size_t`` et ``uint64_t``. Expliquez les différences.
        .. important::

                Il est nécessaire de recompiler le code source si vous voulez exécuter le binaire sur une autre architecture.
                Sur sirius ``gcc`` n'est pas forcément disponible, il faut dans ce cas utiliser ``cc`` à la place.

#. En utilisant des opérations binaires (décalage, and, or, ...), définissez un algorithme efficace pour trouver la valeur du bit le moins significatif d'un entier ``i`` (ex, 8 pour 56, 16 pour 208).

        .. only:: staff

            .. note::

                        La plupart des étudiants vont probablement écrire un code similaire à:

                                .. code-block:: c

                                        int c;
                                        for ( c = 0 ; !((i >> c) & 1) ; c++ ) ;
                                        printf("%d\n", 1 << c);

                        Mais il existe plus efficace:

                                .. code-block:: c

                                        printf("%d\n", i & (~i + 1));

#. Soit ``char *ptr = "Test"``. Itérez sur ce pointeur et affichez avec `printf(3)`_ la valeur et l'adresse mémoire où se trouve stocké chaque caractère de deux façons différentes. Regardez la manpage de `printf(3)`_ pour savoir comment afficher la valeur d'un pointeur.



#. Faites l'exercice sur `Pythia <http://pythia.info.ucl.ac.be/module/10/problem/27>`_

#. La structure suivante ``foo_t`` est définie de façon à ce qu'elle contienne un ``char`` suivi d'un entier. D'après vous combien de bytes occupe cette structure en mémoire ? Vérifiez ce que vous pensiez en utilisant ``sizeof``. (bonus: expliquez vos résultats.)

        .. code-block:: c

                struct foo_t {
                        char a;
                        int b;
                };


2. Mini-Projets
---------------

#. La libraire `string(3)`_ implémente un grand nombre de fonctions de manipulation des strings qui vous serons utile lors de différents projets de programmation. Pour ce mini-projet vous devriez implémenter les fonctions suivantes:

        * `strlen(3)`_
        * `strcat(3)`_
        * `strcasecmp(3)`_

   Le mini-projet est à soumettre via le gestionnaire de code partagé Subversion (SVN). Vous devez vous inscrire à subversion dans le projet ``SINF1252_2013`` en suivant le lien et les instructions sur `<http://wiki.student.info.ucl.ac.be/index.php/Svn>`_. Regardez la section :ref:`svn` pour une explication sur subversion.
   
   Sur le SVN, soumettez votre code dans le dossier ``Projet_S2``. Vous devrez créer un fichier ``string.c`` contenant la définition des fonctions et un fichier ``string.h`` avec les `déclarations <http://en.wikipedia.org/wiki/Declaration_(computer_programming)>`_ des fonctions. Vous devez aussi fournir un Makefile (cfr :ref:`make`) qui permettra à votre tuteur de recompiler facilement votre programme en tapant ``make``. Pensez à implémenter quelques tests pour vos fonctions dans la fonction ``main`` et ne placez pas l'exécutable sur le svn.



#. Lorsque l'on veut améliorer les performances d'un programme, il est utile de pouvoir mesure précisément son temps d'exécution. La commande `time(1posix)`_ permet d'effectuer cette mesure depuis la ligne de commande. Parfois, on souhaite mesurer le temps de calcul une partie critique d'un code. Une façon simple pour obtenir cette mesure est d'utiliser `gettimeofday(2)`_ comme dans l'exemple ci-dessous (:download:`/Exercices/Programmes/s2_perf.c`).

        .. literalinclude:: /Exercices/Programmes/s2_perf.c
                :encoding: iso-8859-1
                :language: c

   Pour certaines opérations, les performances dépendent du type de données utilisé. Modifiez le programme ci-dessous de façon à utiliser un calcul plus compliqué que la simple addition et comparez sur de longues itérations (:math:`10^7` ou plus) les performances de cette opération lorsqu'elle utilise des ``int``, ``long long``, ``double`` ou ``float``. Les performances sont-elles identiques ?

.. _make:

3. Introduction aux Makefiles
-----------------------------

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


.. _ssh:

4. SSH
------

`ssh(1)`_ est un outil qui permet de se connecter depuis l'Internet à la console d'une autre machine et donc d'y exécuter des commandes. Dans l'infrastructure INGI vous pouvez vous connecter via ssh aux différents machines des salles en utilisant votre login et mot de passe INGI. Pour savoir les noms de machines, visitez le `student-wiki <http://wiki.student.info.ucl.ac.be/index.php/Mat%E9riel>`_.

Depuis l'extérieur vous devez passer via ``sirius.info.ucl.ac.be`` pour ensuite pouvoir vous connecter sur les machines des salles.

Quelques exemples d'utilisation de `ssh(1)`_ qui vous seront utiles:

        * ``ssh [username]@[hostname]``: Avec ceci vous pouvez vous connecter à la machine ``hostname``. Exemple: ``ssh myUserName@yunaska.info.ucl.ac.be`` pour vous connecter à la machine ``yunaska`` de la salle intel. Il faut d'abord se connecter à sirius avant de se connecter aux machines des salles.
        * ``ssh -X [username]@[hostname]``: L'option ``-X`` vous permet d'exécuter des programmes sur la machine distante mais en voyant l'interface graphique en local sur votre machine (pour autant qu'elle supporte :term:`X11`). Exemple: ``ssh -X myUserName@yunaska.info.ucl.ac.be`` et ensuite dans le terminal ``gedit test.c`` pour ouvrir l'éditeur de texte.
        * ``ssh [username]@[hostname] [commande]``: Pour exécuter la commande sur la machine distante. Exemple: ``ssh myUserName@sirius.info.ucl.ac.be cc test.c -o test`` pour exécuter ``cc test.c -o test`` sur sirius.
        * ``scp [local_file] [username]@[hostname]:[path]``: `scp(1)`_ permet de copier des fichiers localaux vers un répertoire distant (et l'inverse). Exemple: ``scp test.c myUserName@sirius.info.ucl.ac.be:SINF1252/projet_S2/`` copie test.c vers le dossier ``SINF1252/projet_S2/`` de la machine sirius.

Le site `Getting started with SSH <http://www.ibm.com/developerworks/aix/library/au-sshsecurity/>`_ contient une bonne description de l'utilisation de ssh. Notamment l'`utilisation de ssh sur des machines UNIX/Linux <http://www.ibm.com/developerworks/aix/library/au-sshsecurity/#SSH_for_UNIX>`_. Si vous utilisez Windows, il existe des clients `ssh(1)`_ comme `putty <http://www.putty.org/>`_

