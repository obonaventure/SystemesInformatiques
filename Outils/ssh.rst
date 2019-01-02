.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch, Grégory Detal et Maxime De Mol
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


.. _ssh:
	
SSH
---

`ssh(1)`_ est un outil qui permet de se connecter depuis l'Internet à la console d'une autre machine et donc d'y exécuter des commandes. Dans l'infrastructure INGI vous pouvez vous connecter via ssh aux différents machines des salles en utilisant votre login et mot de passe INGI. Pour savoir les noms de machines, visitez le `student-wiki <http://wiki.student.info.ucl.ac.be/Matériel/Matériel>`_.

Depuis l'extérieur vous devez passer via ``sirius.info.ucl.ac.be`` pour ensuite pouvoir vous connecter sur les machines des salles. 

Quelques exemples d'utilisation de `ssh(1)`_ qui vous seront utiles:

	* ``ssh [username]@[hostname]``: Avec ceci vous pouvez vous connecter à la machine ``hostname``. Exemple: ``ssh myUserName@yunaska.info.ucl.ac.be`` pour vous connecter à la machine ``yunaska`` de la salle intel. Il faut d'abord se connecter à sirius avant de se connecter aux machines des salles.
	* ``ssh -X [username]@[hostname]``: L'option ``-X`` vous permet d'exécuter des programmes sur la machine distante mais en voyant l'interface graphique en local sur votre machine (pour autant qu'elle supporte :term:`X11`). Exemple: ``ssh -X myUserName@yunaska.info.ucl.ac.be`` et ensuite dans le terminal ``gedit test.c`` pour ouvrir l'éditeur de texte.
	* ``ssh [username]@[hostname] [commande]``: Pour exécuter la commande sur la machine distante. Exemple: ``ssh myUserName@sirius.info.ucl.ac.be cc test.c -o test`` pour exécuter ``cc test.c -o test`` sur sirius.
	* ``scp [local_file] [username]@[hostname]:[path]``: `scp(1)`_ permet de copier des fichiers locaux vers un répertoire distant (et l'inverse). Exemple: ``scp test.c myUserName@sirius.info.ucl.ac.be:SINF1252/projet_S2/`` copie test.c vers le dossier ``SINF1252/projet_S2/`` de la machine sirius.

Le site `Getting started with SSH <http://www.ibm.com/developerworks/aix/library/au-sshsecurity/>`_ contient une bonne description de l'utilisation de ssh. Notamment l'`utilisation de ssh sur des machines UNIX/Linux <http://www.ibm.com/developerworks/aix/library/au-sshsecurity/#SSH_for_UNIX>`_. Si vous utilisez Windows, il existe des clients `ssh(1)`_ comme `putty <http://www.putty.org/>`_

Authentification par clé
^^^^^^^^^^^^^^^^^^^^^^^^

Face à la faiblesse au niveau sécurité de l'authentification par mot de passe, l'authentification par clé se révèle être un moyen nettement plus efficace.

L'authentification par clé consiste en un premier temps à générer une paire de clés et son mot de passe:

        * la ``clé publique`` que l'on exporte vers chaque hôte sur lequel on veut se connecter
        * la ``clé privée`` que l'on garde précieusement sur notre ordinateur, et qui sert à prouver à l'hôte notre identité
        * le ``mot de passe`` permet de sécuriser sa clé privée

Le mot de passe ne servant à rien sans les clé et vice versa, on devine aisément que le niveau de sécurité d'une telle connexion est largement accru par rapport à une simple authentification par mot de passe.

Pour générer ces clés et choisir votre mot de passe, il suffit d'entrer la commande

    .. code-block:: none

      $ ssh-keygen -t rsa -C "login"
      # remplacer "login" par votre nom d'utilisateur

      Generating public/private rsa key pair.
      Enter file in which to save the key (~/.ssh/id_rsa): 
      Enter passphrase (empty for no passphrase): 
      Enter same passphrase again: 
      Your identification has been saved in ~/.ssh/id_rsa.
      Your public key has been saved in ~/.ssh/id_rsa.pub.
      The key fingerprint is:
      17:bc:98:ab:39:f6:a2:db:1d:07:9a:63:d7:c7:9b:e0 "login"

Maintenant que les clés ont été crées, il faut communiquer votre clé publique à l'hôte sur lequel vous voulez vous connecter. Pour cela, le plus simple est d'utiliser la commande suivante

    .. code-block:: console
      
      $ cat ~/.ssh/id_rsa.pub | ssh [username]@[hostname] "cat - >> ~/.ssh/authorized_keys"

Cette commande va récupérer votre clé publique dans votre dossier ``~/.ssh``, se connecter en ssh à l'hôte et va placer votre clé dans son répertoire de clés autorisées. Maintenant nous pouvons utilisez en toute sérénité votre connexion ssh sécurisée!

Petit mot sur les permissions du dossier ``~/.ssh`` où sont stockées les clés:

    .. code-block:: console

      .ssh user$ ls -ld
      drwx------  6 user  staff  204 22 aoû 10:29 .


Les bits de permissions sont définis comme ``drwx------`` ce qui fait du propriétaire de ce dossier la seul personne capable de lire, d'écrire et d'exécuter le contenu de se dossier. La clé privée est donc belle et bien privée!

Synchronisation de fichiers entre ordinateurs
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Quand nous avons besoin de synchroniser des fichiers entre 2 ordinateurs différents, Unix nous vient en aide avec l'utilitaire `rsync <http://linux.about.com/library/cmd/blcmdl1_rsync.htm>`_.

L'utilisation la plus basique de `rsync <http://linux.about.com/library/cmd/blcmdl1_rsync.htm>`_ est:

    .. code-block:: console

      rsync *.c [hostname]:src/

`rsync <http://linux.about.com/library/cmd/blcmdl1_rsync.htm>`_ va copier tout les fichiers qui correspondent au pattern ``*.c`` du répertoire courant vers le dossier ``src/`` sur la machine hôte. De plus, si certains ou tout les fichiers sont déjà présents chez l'hôte, `rsync <http://linux.about.com/library/cmd/blcmdl1_rsync.htm>`_ va procéder à une mise à jour différentielle de ces fichiers (seuls les changements sont transférés).

L'ajout du drapeau ``-avz`` permet de synchroniser les fichiers en mode archive. Cela veut dire que tous les liens, permissions, propriétaires, etc de ces fichiers seront préservés durant le transfert. 

Nous pouvons aussi utiliser `rsync <http://linux.about.com/library/cmd/blcmdl1_rsync.htm>`_ dans l'autre sens:

    .. code-block:: console

      rsync -avz [hostname]:src/bar /data/tmp

Maintenant tout les fichiers de la machine hôte, dans le dossier src/bar vont être copiés vers le répertoire local /data/tmp.
