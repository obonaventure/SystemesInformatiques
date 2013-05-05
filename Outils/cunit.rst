.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. _ref_cunit:

CUnit: librairie de tests
------------------------

`CUnit <http://cunit.sourceforge.net>`_ est une librairie de tests unitaires en C. Cette librairie doit être utilisée dans le cadre de ce projet. Un petit
exemple de test est déjà disponible dans l'archive fournie dans le projet :ref:`projet1`.

CUnit n'est pas installé par défaut sur les machines des salles. Vous devez donc l'installer par vous-même. Le reste de cette section a pour but de vous aider dans l'installation de celle-ci.

La première étape consiste à récupérer les sources de CUnit sur `<http://sourceforge.net/projects/cunit/files/>`_. Les sources se trouvent dans une archive
``CUnit-*-src.tar.bz2`` et la dernière version devrait se nommer ``CUnit-2.1.2-src.tar.bz2``. Une fois l'archive téléchargée, ouvrez un terminal et placez-vous dans le dossier où se trouve celle-ci. Exécutez:

    .. code-block:: console

            $ tar xjvf CUnit-2.1.2-src.tar.bz2
            $ cd CUnit-2.1-2
            $ ./configure --prefix=$HOME/local
            $ make
            $ make install

Une fois ces commandes exécutées, la librairie ainsi que ses fichiers d'entête sont installés dans le dossier ``$HOME/local`` (``$HOME`` est en fait une
variable bash qui définit votre répertoire principal). Comme vous n'avez pas les droits administrateur, vous ne pouvez pas installer d'application ni de
librairie dans les chemins classiques (c-à-d, par exemple dans ``/usr/lib``, ``/usr/include``, ``/usr/bin``). C'est pour cela que nous installons la
librairie dans un dossier local.

Comme la librairie n'est pas installée dans les chemins classiques, il faut pouvoir dire à gcc où se trouvent les fichiers d'entête ainsi que la librairie afin
d'éviter les erreurs de compilation. Pour cela, il faut spécifier à la compilation l'argument ``-I$HOME/local/include`` afin de lui dire qu'il doit
également aller chercher des fichiers d'entête dans le dossier ``$HOME/local/include`` en plus des chemins classiques tels que ``/usr/include`` et
``/usr/local/include``.

Lors de l'édition des liens avec le linker, il faut spécifier où se trouve la librairie dynamique afin de résoudre les symboles. Pour cela, il faut passer l'argument ``-lcunit`` pour
effectuer la liaison avec la librairie CUnit ainsi que lui spécifier ``-L$HOME/local/lib`` afin qu'il cherche également des librairies dans le dossier
``$HOME/local/lib``.

Lors de l'exécution, il faut également spécifier où se trouvent les librairies. Par exemple pour un binaire ``test`` qui utilise la librairie CUnit, on peut
exécuter:

  .. code-block:: console

          $ export LD_LIBRARY_PATH=$HOME/local/lib:$LD_LIBRARY_PATH
          $ ./test
