.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Implémentation d'un encodeur et extension de l'outil `cat(1)`_
==============================================================

Le monde de l'informatique est fortement influencé par la mentalité du "Open Source". Le but du open source est d'ouvrir l'accès au code source des programmes et permettre à tout le monde de le modifier par rapport à ses besoins. Le monde GNU/Linux est construit de ce genre d'outils open source dont le code source est librement accessible.

Pour ce dernier projet on vous demande d'étendre une librairie open source, nottament ``coreutils``. Le package ``coreutils`` contient tout les programmes nécessaire à la gestion de votre système, comme `kill(1)`_, `cp(1)`_, `tail(1)`_, et beaucoup plus.

Programme attendu
-----------------

On vous demande d'implémenter un encodeur dans la librairie ``coreutils`` et d'étendre l'outil `cat(1)`_ (qui fait partie de ``coreutils``) pour qu'il puisse lire ce type de fichiers. De plus, vous devriez modifier `cat(1)`_ pour qu'il utilise des fichier mappé en mémoire (`mmap(2)`_).

L'encodeur est donc un nouveau binaire que vous devriez intégrer dans le package ``coreutils``. Son utilisation est définie par le suivant:

    .. code-block:: console

        $ encode input-file output-file

Donc, l'outil ``encode`` lit le fichier ``input-file``, l'encode avec l'algorithme de "Run-length encoding" et écrit cet encodage dans le fichier ``output-file``. Pour avoir des informations sur l'algorithme, voyez la section ci-dessous.

Pour le décodage, vous devriez étendre l'outil `cat(1)`_ avec l'option `-x`. Cette option (qui ne prend pas d'argument), spécifie que l'input doît être interprèté comme étant un fichier créé par l'outil ``encode``.

N'oubliez pas d'adapter les manpages dans le dossier ``man`` de la librairie ``coreutils``.

Run-length encoding
-------------------

Le run-length encoding est une facon d'encodage qui essaye de profiter du fait que le même caractère se répète plusieurs fois, pour réduire la taille d'un fichier. Le run-length encoding est donc une suite de bytes, dont le premier byte est identifié comme étant le ``length``. Le length est un entier non-signé sur 8 bits avec la signification suivante:

    * si ``length <= 128``, le byte suivant ``length`` est repété ``length`` fois.
    * si ``length > 128``, les ``length - 128`` bytes suivant ``length`` ne sont pas repèté.

Voici un exemple sur un fichier contenant du texte:

    * Original: ``aaaabcdaaaa`` - Cec peut être encodé de la facon suivant: Le premier byte est mis à '4', suivi par un 'a'. Ensuite, on encode un '131' sur un byte suivi de la séquence 'bcd'. Cela signifie donc que les 131 - 128 = 3 bytes suivant le '131' ne sont pas répété. Ensuite vous pouvez de nouveau encoduer un '4', suivi par un 'a'.

Vous êtes libre à décider si dans votre encodage vous utilisez un length plus grand que 128, ou pas. Cela a une forte influence sur le taux de compression de l'encodeur.

Compilation de coreutils
------------------------

Vous pouvez récuprer le code source de ``coreutils`` en suivant le lien `<http://ftp.gnu.org/gnu/coreutils/coreutils-8.21.tar.xz>`_.

Pour l'extraire, vous exécutez la commande `tar(1)`_:

    .. code-block:: console

        $ tar -xJf coreutils-8.21.tar.xz

Les différents outils et leur code-source se trouvent dans le dossier ``src``. Les manpages sont dans le dossier ``man``.

Pour compiler, suivez les étapes suivantes dans le dossier ``coreutils-8.21``:

    .. code-block:: console

        $ ./configure
        $ make

Les binaires vont se trouver dans le dossier ``src``.


Consignes
---------

TODO - adapter

Le projet est à soumettre pour le 17 mai à 12h00 via le XXX du deuxième projet. Vous devez donc vous inscrire ensemble avec votre binôme sur le SVN ''SINF1252_2013_PROJET_2'' sur le
site `<https://scm.info.ucl.ac.be/cgi-bin/inscription.sh>`_.
Vous devez fournir sur le SVN dans votre dossier de groupe:

	- Le code source de votre projet (pas de binaires) ainsi qu'un ``Makefile`` (lorsque l'on tape ``make`` un binaire ``filter`` doit être généré.). Vous devez compiler votre programme avec les options *-Wall* et *-Werror* de gcc.
	- Un rapport de *4 pages maximum* (12pt) qui décrit vos choix architecturaux ainsi que les problèmes rencontrés. Le rapport doit être nommé *rapport.pdf* et présent dans votre dossier de groupe.

Les critères de cotation sont les suivants (liste non-exhaustive):

        - Votre impémentation doît fonctionner dans les salles informatiques du département;
	- Intégration de vos changements dans l'infrastructure de coreutils;
	- Intégralité de votre implémentation (manpages,...);
	- Optimalité de votre algorithme d'encodage;
	- Respect des consignes.

