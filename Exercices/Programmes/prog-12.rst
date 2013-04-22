.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices
---------


#. Considérons le disque dur ST31500341AS dont les caractéristiques techniques sont présentées dans les notes. Le constructeur annonce un débit de transfert de 300 MBytes par seconde au maximum. Sachant que chaque secteur fait 512 bytes, et que ce disque utilise 63 secteurs par piste, calculez le débit obtenu lors du transfert d'une piste complète et comparez ce débit à celui annoncé par le constructeur.

#. Considérons un ordinateur utilisant des pages de 1024 bytes et des adresses virtuelles encodées sur 13 bits et des adresses réelles également sur 13 bits. La table des pages actuellement utilisée est la suivante :
 
 ========  ========     =======
 Indice    Validité     Adresse
 ========  ========     =======
 [111]     true         001
 [110]     true		000
 [101]	   true         111
 [100]	   false	- 
 [011]	   true		011 
 [010]	   false	-
 [001]	   true         010
 [000]     true         100
 ========  ========     =======
 
 Sur base de cette table des pages, déterminez si les adresses suivantes correspondent à des données se trouvant en mémoire et le cas échéant l'adresse physique correspondante :
 
  - ``1100110111010``
  - ``0110000110010``
  - ``0000010010001`` 
  - ``1000010001001``
  - ``0000000000000``
 
#. Un processus est chargé en mémoire. L'output de ``/proc/pid/maps`` est le suivant :
 
 .. code-block:: console

    08047000-080f5000 r-xp 00000000 08:01 553302     /bin/bash
    080f5000-080fa000 rw-p 000ae000 08:01 553302     /bin/bash
    09047000-09107000 rw-p 09047000 00:00 0          [heap]
    bffaa000-bffbf000 rw-p bffe9000 00:00 0          [stack]
  
 En supposant que la mémoire RAM était initialement vide et que le processus a été chargée à partir de l'adresse ``0x00000000`` en mémoire physique, construisez la table des pages de ce processus si il utilise des pages de 4 KBytes.
 
#. Un ordinateur utilise de la mémoire virtuelle avec des adresses virtuelles sur 32 bits et des adresses physique sur 26 bits. Sa mémoire virtuelle est découpée en pages de 4 KBytes. Si chaque entrée de la table des pages occupe 32 bits, quelle est la zone mémoire occupée par la table des pages ? Le nombre de lignes dans la table des pages varie-t-il si les adresses physiques passent à 32 bits ou 36 bits ?

#. Un ordinateur dispose de 32 GBytes de mémoire RAM. Il utilise des adresses virtuelles de 64 bits et des pages de 4 KBytes. Combien de lignes doit contenir sa table des pages ? 

#. L'appel système `shmget(2)`_ supporte également le drapeau ``IPC_EXCL`` en plus du drapeau ``IPC_CREAT``. Expliquez à quoi ce drapeau peut servir et dans quel cas il peut être utile.

#. Un processus père ouvre un segment de mémoire partagée avec l'appel système ``shmget(key, 4096, IPC_CREAT | S_IRUSR | S_IWUSR )``. Un de ses processus fils peut-il exécuter ``shmget(key, 4096, S_IRUSR  )`` ? Si oui, ce processus peut-il ensuite attacher cette page en utilisant :
 
 - ``shmat(shm_id, NULL, SHM_RDONLY)``
 - ``shmat(shm_id, NULL, SHM_RDONLY)``
 
#. Lorsque l'on utilise l'appel système `shmat(2)`_ avec ``NULL`` come deuxième argument, le système d'exploitation choisit l'adresse à laquelle le segment de mémoire va être attaché. Cela pose des difficultés si l'on veut stocker des pointeurs en mémoire partagée. Un étudiant propose de d'abord allouer la zone mémoire avec `malloc(3)`_ et d'ensuite attacher le segment de mémoire à cet endroit. Il a réalisé un test avec un processus père et son fils et les deux segments de mémoire partagée se retrouvent à la même adresse. Il en conclut que cela permet de résoudre le problème. Qu'en pensez-vous ?

#. Deux processus utilisent un segment de mémoire partagée et doivent se partager une liste chaînée. Comment implémenteriez-vous cette liste simplement chaînée de façon à ce qu'elle puisse être utilisée dans cette mémoire partagée. On supposera que le segment de mémoire partagé est toujours plus grand que la zone mémoire nécessaire au stockage de la liste.

#. Le livre [Kerrisk2010]_ contient de nombreux exemples de programmes permettant de manipuler les segments de mémoire partagée [#fex]_. Compilez les programmes ``svshm_create``,  ``svshm_attach`` et ``svshm_rm`` pour créer, attacher et supprimer un segment de mémoire partagée. Les commandes `ipcs(1)`_ et `ipcrm(1)`_ permettent de visualiser et supprimer les segments de mémoire partagée. Pensez à utiliser ces commandes pour vérifier que vous n'avez pas laissé de segment de mémoire partagée qui traine.


.. rubric:: Footnotes

.. [#fex] Voir notamment http://www.man7.org/tlpi/code/online/all_files_by_chapter.html (chapitre 48) ou http://www.man7.org/tlpi/code/index.html
