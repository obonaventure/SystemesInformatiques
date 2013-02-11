.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. _ref_cunit:

CUnit: librarie de tests
------------------------

`CUnit <http://cunit.sourceforge.net>`_ est une librarie de tests unitaires en C. Cette librarie doit être utilisée dans le cadre de ce projet. Un petit
exemple de test est déjà disponible dans l'archive fournie.

CUnit n'est pas installé par défaut sur les machines des salles. Vous devez donc l'installer par vous même. Le reste de cette section à pour but de vous
aider dans l'installation de celle-ci.

La première étape consiste à récupérer les sources de CUnit sur `<http://sourceforge.net/projects/cunit/files/>`_. Les sources se trouvent dans une archive
``CUnit-*-src.tar.bz2`` et la dernière version devrait se nomer ``CUnit-2.1.2-src.tar.bz2``. Une fois l'archive téléchargée, ouvrez un terminal et placer
vous dans le dossier où se trouve celle-ci. Executez:

    .. code-block:: terminal

            $ tar xjvf CUnit-2.1.2-src.tar.bz2
            $ cd CUnit-2.1-2
            $ ./configure --prefix=$HOME/local
            $ make
            $ make install

Une fois ces commandes exécutées, la librarie ainsi que ses fichiers d'entêtes sont installés dans le dossier ``$HOME/local`` (``$HOME`` est en fait une
variable bash qui défini votre répertoire principal). Comme vous n'avez pas les droits administrateurs vous ne pouvez pas installer d'application ni de
libraries dans les chemins classiques (c-à-d, par exemple dans ``/usr/lib``, ``/usr/include``, ``/usr/bin``). C'est pour cela que nous installons la
librarie dans un dossier local.

Comme la libraire n'est pas installée dans les chemins classiques, il faut pouvoir dire à gcc où se trouve les fichier d'entête ainsi que la librarie afin
d'éviter les erreurs de compilations. Pour cela il faut spécifier à la compilation, l'argument ``-I$HOME/local/include`` afin de lui dire qu'il doit
également aller chercher des fichiers d'entête dans le dossier ``$HOME/local/include`` en plus des chemins classiques tel que ``/usr/include`` et
``/usr/local/include``.

Au linkage, il faut lui spécifier où se trouve la librarie dynamique afin de résoudre les symboles. Pour cela, il faut passer l'argument ``-lcunit`` pour
effectuer le linkage avec la librarie CUnit ainsi que lui spécifier ``-L$HOME/local/lib`` afin qu'il cherche également des libraries dans le dossier
``$HOME/local/lib``.

Lors de l'exécution, il faut également spécifier où se trouvent les libraries. Par exemple pour un binaire ``test`` qui utilise la librarie CUnit, on peut
exécuter:

  .. code-block:: terminal

          $ export LD_LIBRARY_PATH=$HOME/local/lib:$LD_LIBRARY_PATH
          $ ./test
