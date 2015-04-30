.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices
---------


#. Considérons le disque dur ST31500341AS dont les caractéristiques techniques sont présentées dans les notes (1.5TB, 7200 RPM, 32MB Cache, la datasheet est disponible `ici <http://www.seagate.com/staticfiles/support/disc/manuals/desktop/Barracuda%207200.11/100507013e.pdf>`_). Le constructeur annonce un débit de transfert de 300 MBytes par seconde au maximum. Sachant que chaque secteur fait 512 bytes, et que ce disque utilise 63 secteurs par piste, calculez le débit obtenu lors du transfert d'une piste complète et comparez ce débit à celui annoncé par le constructeur.

#. Considérons un ordinateur utilisant des pages de 1024 bytes et des adresses virtuelles encodées sur 13 bits et des adresses réelles également sur 13 bits. La table des pages actuellement utilisée est la suivante :

   ========  ========     =======
   Indice    Validité     Adresse
   ========  ========     =======
   [111]     true         001
   [110]     true         000
   [101]     true         111
   [100]     false        -
   [011]     true         011
   [010]     false        -
   [001]     true         010
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

   En supposant que la mémoire RAM était initialement vide et que le processus a été chargé à partir de l'adresse ``0x00000000`` en mémoire physique, construisez la table des pages de ce processus si il utilise des pages de 4 KBytes.

#. Un ordinateur utilise de la mémoire virtuelle avec des adresses virtuelles sur 32 bits et des adresses physique sur 26 bits. Sa mémoire virtuelle est découpée en pages de 4 KBytes. Si chaque entrée de la table des pages occupe 32 bits, quelle est la zone mémoire occupée par la table des pages ? Le nombre de lignes dans la table des pages varie-t-il si les adresses physiques passent à 32 bits ou 36 bits ?

#. Un ordinateur dispose de 32 GBytes de mémoire RAM. Il utilise des adresses virtuelles de 64 bits et des pages de 4 KBytes. Combien de lignes doit contenir sa table des pages ?

#. Comparez les performances du programme :download:`/../Theorie/MemoireVirtuelle/src/cp2.c` avec l'utilitaire `cp(1)`_ standard de Linux.

#. Un programme construit en mémoire un gros tableau contenant 10 millions d'entiers. Initialisez ce tableau avec des entiers ayant des valeurs croissante. Pour sauvegarder le fichier sur disque, trois solutions s'offrent à vous :

   - écrire directement les entiers sur disque sous forme binaire en utilisant l'appel système `write(2)`_ en passant un pointeur vers chaque entier à cet appel système
   - écrire les entiers sur disque sous forme d'un fichier texte avec un entier par ligne
   - écrire les entiers directement sur disque, mais en utilisant `mmap(2)`_ plutôt que `write(2)`_

   Dans les salles informatiques, vous pouvez stocker les données dans trois répertoires qui risquent d'avoir des performances différentes :

   - votre répertoire de login qui est accessible depuis un serveur de fichiers
   - le répertoire ``/tmp`` qui sous Linux est en général stocké directement en mémoire RAM
   - un clé USB

   Ecrivez un programme qui permet de comparer les performances de ces trois méthodes permettant d'écrire sur disque sur les trois dispositifs de stockage. Quelle est la solution la plus rapide et pourquoi (pensez à utiliser `fsync(2)`_ ou `msync(2)`_ pour forcer le système à écrire vos données sur disque à la fin de l'exécution de votre programme).

#. Ecrivez un programme similaire au précédent mais qui permet de comparer les performances en lecture. Utilisez `fscanf(3)`_ par exemple pour lire les données du fichier texte.

#. git est un outil permettant de générer intelligemment les projets informatiques dans lesquels plusieurs développeurs participent à l'écriture du code source. Il existe de nombreux livres et sites web concernant subversion. Cet exercice a pour objectif de vous présenter un workflow classique utilisant ``git``. Pour réaliser cet exercice, vous avez besoin d'un répertoire partagé géré par ``git``.

   - `git(1)`_ supporte de nombreuses sous-commandes. Pour accéder au manuel relatif à une de ces sous-commandes, il faut utiliser ``git help commande``
   - Créez un répertoire de test que vous pourrez supprimer par après, ``mkdir test``
   - Ajoutez ce répertoire à votre repository subversion ``git add test``
   - Enregistrez cette modification sur le serveur en utilisant ``git commit -m "Ajout du répertoire de test"``. L'argument ``-m`` permet de spécifier un commentaire à votre ``commit``. Prenez l'habitude d'expliquer en une ou quelques lignes la modification que vous avez fait, cela vous permettra de revenir plus facilement en arrière si nécessaire. Envoyez ensuite votre modification sur le serveur via ``git push``.
   - Créez un fichier texte nommé ``test.txt`` dans votre répertoire. Ce fichier contiendra une ligne de ``aaaaa`` et une deuxième ligne de ``bbbbbb``. Ajoutez ce fichier avec ``git add``  puis faites le ``git commit`` suivi du ``git push``
   - Depuis un autre compte étudiant, faites ``git pull`` pour charger ce nouveau répertoire et le fichier le contenant.
   - Un étudiant utilisant le répertoire modifie la première ligne du fichier et la remplace par ``aaXaa``. En même temps, l'autre étudiant modifie la deuxième ligne du fichier et la remplace par ``bbbYbbb``. Une fois ces modifications faites, utilisez ``git commit`` puis ``git push`` pour pousser la modification sur le serveur.
   - Faites ``git log test.txt`` pour voir la liste des modifications faites sur ce fichier
   - Utilisez ``git diff test.txt`` pour voir la différence entre votre version du fichier et celle du serveur
   - Essayez maintenant de faire des modifications à la même ligne du fichier, par exemple en ajoutant chacun une ligne supplémentaire. Ce faisant, vous allez créer un conflit. Utilisez ``git merge`` pour résoudre ce conflit.


.. rubric:: Footnotes


