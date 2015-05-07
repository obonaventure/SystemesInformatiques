.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices
---------

#. L'appel système `shmget(2)`_ supporte également le drapeau ``IPC_EXCL`` en plus du drapeau ``IPC_CREAT``. Expliquez à quoi ce drapeau peut servir et dans quel cas il peut être utile.

#. Un processus père ouvre un segment de mémoire partagée avec l'appel système ``shmget(key, 4096, IPC_CREAT | S_IRUSR | S_IWUSR )``. Un de ses processus fils peut-il exécuter ``shmget(key, 4096, S_IRUSR  )`` ? Si oui, ce processus peut-il ensuite attacher cette page en utilisant :

 - ``shmat(shm_id, NULL, SHM_RDONLY)``
 - ``shmat(shm_id, NULL, SHM_EXEC)``

#. Lorsque l'on utilise l'appel système `shmat(2)`_ avec ``NULL`` comme deuxième argument, le système d'exploitation choisit l'adresse à laquelle le segment de mémoire va être attaché. Cela pose des difficultés si l'on veut stocker des pointeurs en mémoire partagée. Un étudiant propose de d'abord allouer la zone mémoire avec `malloc(3)`_ et d'ensuite attacher le segment de mémoire à cet endroit. Il a réalisé un test avec un processus père et son fils et les deux segments de mémoire partagée se retrouvent à la même adresse. Il en conclut que cela permet de résoudre le problème. Qu'en pensez-vous ?

#. Deux processus utilisent un segment de mémoire partagée et doivent se partager une liste chaînée. Comment implémenteriez-vous cette liste simplement chaînée de façon à ce qu'elle puisse être utilisée dans cette mémoire partagée. On supposera que le segment de mémoire partagée est toujours plus grand que la zone mémoire nécessaire au stockage de la liste.

#. Le livre [Kerrisk2010]_ contient de nombreux exemples de programmes permettant de manipuler les segments de mémoire partagée [#fex]_. Compilez les programmes ``svshm_create``,  ``svshm_attach`` et ``svshm_rm`` pour créer, attacher et supprimer un segment de mémoire partagée. Les commandes `ipcs(1)`_ et `ipcrm(1)`_ permettent de visualiser et supprimer les segments de mémoire partagée. Pensez à utiliser ces commandes pour vérifier que vous n'avez pas laissé de segment de mémoire partagée qui traine.


.. rubric:: Footnotes

.. [#fex] Voir notamment http://www.man7.org/tlpi/code/online/all_files_by_chapter.html (chapitre 48) ou http://www.man7.org/tlpi/code/index.html
