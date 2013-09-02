.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Implémentation d'un encodeur et extension de l'outil `cat(1)`_
==============================================================

Le monde de l'informatique est fortement influencé par la mentalité "Open Source". Par exemple, les systèmes GNU/Linux sont basés sur ce genre d'outils. Le but de l'open source est d'ouvrir l'accès au code source des programmes et permettre à tout le monde de le modifier par rapport à ses besoins.

Pour ce dernier projet du cours SINF1252 on vous demande d'étendre la librairie open source: *GNU core utilities* ou ``coreutils``. Le package ``coreutils`` contient tout les programmes nécessaire à la gestion de votre système, comme `kill(1)`_, `cp(1)`_, `tail(1)`_, et beaucoup d'autres.

Programme attendu
-----------------

On vous demande d'implémenter un outil de compression de fichier dans la librairie ``coreutils`` ainsi qu'étendre l'outil `cat(1)`_ (qui fait partie de ``coreutils``) pour qu'il puisse lire ce type de fichiers. De plus, on vous demande de modifier `cat(1)`_ pour qu'il utilise des fichier mappé en mémoire (`mmap(2)`_). On vous demande également d'utiliser `mmap(2)`_ dans votre encodeur.

L'encodeur est donc un nouveau binaire que vous devriez intégrer dans le package ``coreutils``. Son utilisation est défini comme suit:

    .. code-block:: console

        $ encode input-file output-file

L'outil ``encode`` lit le fichier ``input-file``, le compresse avec l'algorithme de "Run-length encoding" et écrit la version compressée dans le fichier ``output-file``. Pour avoir des informations sur l'algorithme, voyez la section ci-dessous.

Pour le décodage, vous devez étendre l'outil `cat(1)`_ avec l'option ``-x``. Cette option (qui ne prend pas d'argument), spécifie que l'input doît être interprété comme étant un fichier créé par l'outil ``encode``.

N'oubliez pas d'adapter le Makefile, les manpages dans le dossier ``man`` de la librairie ``coreutils``.

Run-length encoding
-------------------

Le run-length encoding est un algorithme de compression de fichier qui essaye de profiter du fait que le même caractère se répète plusieurs fois, pour réduire la taille d'un fichier. Le run-length encoding est donc une suite de octets, dont le premier est identifié comme étant le ``length``. Ce dernier est un entier non-signé sur 8 bits avec la signification suivante:

    * si ``length <= 128``, le byte suivant est repété ``length`` fois.
    * si ``length > 128``, les ``length - 128`` octets suivant ne sont pas repèté.

Voici un exemple sur un fichier contenant du texte:

    * ``aaaabcdaaaa`` peut être encodé de la façon suivant: Le premier octet est mis à '4', suivi par un 'a'. Ensuite, on encode un '131' sur un octet suivi de la séquence 'bcd'. Cela signifie donc que les 131 - 128 = 3 octets suivant le '131' ne sont pas répété. Ensuite vous pouvez de nouveau encoder un '4', suivi par un 'a'.

Vous êtes libre à décider si dans votre encodage vous utilisez un ``length`` plus grand que 128, ou pas. Cela a une forte influence sur le taux de compression de l'encodeur.

Compilation de coreutils
------------------------

Vous pouvez récupérer le code source de ``coreutils`` en suivant le lien `<http://ftp.gnu.org/gnu/coreutils/coreutils-8.21.tar.xz>`_.

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

Le projet est à soumettre pour le jeudi 16 mai à 23h55 via le SVN du troisième projet. Vous devez donc vous inscrire ensemble avec votre binôme sur le SVN ''SINF1252_2013_P3'' sur le
site `<https://scm.info.ucl.ac.be/cgi-bin/inscription.sh>`_.
Vous devez fournir sur le SVN dans votre dossier de groupe:

	- Le code source de votre projet (pas de binaires). Les codes sources doivent se trouver dans le répertoire *grpXY/coreutils-8.21/*. Il doit être possible pour les assistants du cours de générer un patch de vos changements à l'aide de la commande: ``diff -rNu grpXY/coreutils-8.21/ <source_originale_de_coreutils>``. Cette commande doit uniquement retourner vos changements.

	- Un rapport de *2 pages maximum* (12pt) qui décrit vos choix de design ainsi que les problèmes rencontrés. Le rapport doit être nommé *rapport.pdf* et présent dans votre dossier de groupe (*grpXY/rapport.pdf*).

Les critères de cotation sont les suivants (liste non-exhaustive):

	- Votre impémentation doit fonctionner dans les salles informatiques du département;
	- Intégration de vos changements dans l'infrastructure de coreutils;
	- L'appel à ``make`` génère correctement un binaire ``src/encode`` (sans warning ni erreurs).
	- Intégralité de votre implémentation (manpages, ...);
	- Optimalité de votre algorithme d'encodage;
	- Respect des consignes;
	- ...

