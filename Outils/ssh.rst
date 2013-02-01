.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


.. _ssh:
	
SSH
---

`ssh(1)`_ est un outil qui permet de se connecter depuis l'Internet à la console d'une autre machine et donc d'y exécuter des commandes. Dans l'infrastructure INGI vous pouvez vous connecter via ssh aux différents machines des salles en utilisant votre login et mot de passe INGI. Pour savoir les noms de machines, visitez le `student-wiki <http://wiki.student.info.ucl.ac.be/index.php/Mat%E9riel>`_.

Depuis l'extérieur vous devez passer via ``sirius.info.ucl.ac.be`` pour ensuite pouvoir vous connecter sur les machines des salles. 

Quelques exemples d'utilisation de `ssh(1)`_ qui vous seront utiles:

	* ``ssh [username]@[hostname]``: Avec ceci vous pouvez vous connecter à la machine ``hostname``. Exemple: ``ssh myUserName@yunaska.info.ucl.ac.be`` pour vous connecter à la machine ``yunaska`` de la salle intel. Il faut d'abord se connecter à sirius avant de se connecter aux machines des salles.
	* ``ssh -X [username]@[hostname]``: L'option ``-X`` vous permet d'exécuter des programmes sur la machine distante mais en voyant l'interface graphique en local sur votre machine (pour autant qu'elle supporte :term:`X11`). Exemple: ``ssh -X myUserName@yunaska.info.ucl.ac.be`` et ensuite dans le terminal ``gedit test.c`` pour ouvrir l'éditeur de texte.
	* ``ssh [username]@[hostname] [commande]``: Pour exécuter la commande sur la machine distante. Exemple: ``ssh myUserName@sirius.info.ucl.ac.be cc test.c -o test`` pour exécuter ``cc test.c -o test`` sur sirius.
	* ``scp [local_file] [username]@[hostname]:[path]``: `scp(1)`_ permet de copier des fichiers localaux vers un répertoire distant (et l'inverse). Exemple: ``scp test.c myUserName@sirius.info.ucl.ac.be:SINF1252/projet_S2/`` copie test.c vers le dossier ``SINF1252/projet_S2/`` de la machine sirius.

Le site `Getting started with SSH <http://www.ibm.com/developerworks/aix/library/au-sshsecurity/>`_ contient une bonne description de l'utilisation de ssh. Notamment l'`utilisation de ssh sur des machines UNIX/Linux <http://www.ibm.com/developerworks/aix/library/au-sshsecurity/#SSH_for_UNIX>`_. Si vous utilisez Windows, il existe des clients `ssh(1)`_ comme `putty <http://www.putty.org/>`_


