.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices INGINIOUS
-------------------

Les exercices INGINIOUS de cette semaine ont comme objectif de vous familiariser avec
les appels systèmes `open(2)`_, `close(2)`_, `read(2)`_, `write(2)`_ et `stat(2)`_ qui
permettent de manipuler les fichiers contenant des données binaires.

1. Le `premier exercice <https://inginious.info.ucl.ac.be/course/LSINF1252/s5_file_exists>`_ est
une mise en jambe. En utilisant `open(2)`_ (et `close(2)`_), pouvez-vous vérifier si un
fichier dont le nom est passé en argument existe ?

2. L'avantage des fichiers binaires est qu'il est possible de sauvegarder directement un tableau stocké en mémoire dans le fichier en utilisant `write(2)`_ pour écrire chaque élément du tableau dans un fichier. En lisant les pages de manuel de `write(2)`_, vous verrez même qu'un seul appel à `write(2)`_ peut suffire à sauver tout un tableau dans un fichier. Ecrivez cette `fonction save <https://inginious.info.ucl.ac.be/course/LSINF1252/s4_file_save_struct>`_.

3. Un fichier binaire peut être utilisé pour stocker tous les éléments d'un tableau d'entiers. Ecrivez la `fonction sum_file <https://inginious.info.ucl.ac.be/course/LSINF1252/s4_read_file_array_integer>`_ qui prend comme argument un nom de fichier contenant un tel tableau et calcule la somme de tous les entiers stockés dans le fichier. Pensez aux cas d'erreurs possibles si le fichier n'a pas la bonne taille.

4. Vous continuez à explorer les fichiers binaires qui permettent de stocker tous les éléments d'un tableau d'entiers. Cette fois-ci vous devez écrire une `première fonction <https://inginious.info.ucl.ac.be/course/LSINF1252/s5_big_array_get_set>`_ pour récupérer la valeur d'un
élément du tableau stocké dans le fichier et une `seconde fonction <https://inginious.info.ucl.ac.be/course/LSINF1252/s5_big_array_get_set>`_ pour modifier la valeur d'un élément de ce tableau.

5. En ligne de commande, `cp(1)`_ vous permet de copier complètement un fichier quel que soit son contenu. Pouvez-vous implémenter l'équivalent de cette commande dans la `fonction copy <https://inginious.info.ucl.ac.be/course/LSINF1252/s5_file_copy>`_ que vous allez écrire en C.



Exercices
---------


1. Consultez la page de manuel de `chmod(1)`_ ou d'autres sources pour déterminer la signification des bits de permissions lorsqu'ils sont associés à un répertoire. Expliquez notamment à quoi sert le bit d'exécution sur un répertoire.

  .. only:: staff

     le bit x permet d'autoriser le parcours du répertoire

2. Quelles sont les permissions associées à votre répertoire de login ? Ces permissions permettent-elles à d'autres étudiants d'accéder à vos fichiers ? Si oui, utilisez `chmod(1)`_ pour supprimer cette autorisation de lecture par défaut dans votre répertoire.

3. Comment feriez-vous en utilisant `chmod(1)`_ pour créer un répertoire dans lequel vous pouvez lire et écrire, tout étudiant peut lire mais aucun membre du staff (à part l'administrateur système bien entendu) ne peut lire ?

 .. only:: staff

    il faut que l'étudiant soit dans le même groupe et que le répertoire soit accessible au groupe, au minimum 00750

4. Le répertoire ``/tmp`` est particulier car il est destiné à pouvoir contenir des fichiers de n'importe quel utilisateur. Pouvez-vous expliquer les permissions utilisées pour ce répertoire ?

  .. only:: staff

     pas besoin de parler du sticky bit sauf si les étudiants l'abordent

.. only:: staff 

   5. La commande `lsof(8)`_ permet de lister les fichiers ouverts par un processus. A votre avis, comment cette commande fonctionne-t-elle ?

      L'OS maintient une table de tous les fichiers ouverts avec leur inode. Cette table est accessible via /proc

   6. Lorsqu'un exécutable est lancé avec `execve(2)`_, il hérite des descripteurs de fichiers qui étaient ouverts dans le processus qui a exécuté `execve(2)`_. Comment feriez-vous en utilisant uniquement l'appel système `open(2)`_ pour déterminer combien de descripteurs de fichiers étaient ouverts au démarrage de votre programme ?

    Il suffit de regarder quelle est la valeur de retour de open. Si open retourne 3, cela indique que seuls stdin, stdout et stderr étaient ouverts

5. Est-il possible dans un processus d'exécuter ``int fd1=open("f",O_RDWR);`` et juste après ``int fd2=open("f",O_RDONLY);`` ? Si oui, quelles seront les valeurs des descripteurs de fichiers retournés lors des appels système. Si non, quelles seront les valeurs de ``errno``?

  .. only:: staff

     Oui, c'est possible. Dans ce cas, les offset pointers sont différents pour les deux copies du même fichier. Il est utile de faire un dessin pour que les étudiants visualisent bien la situation

.. only:: staff

          8. Dans un shell, on exécute la commande ``/bin/echo "1234" > /test.txt``. Quels sont les appels systèmes effectués par le shell avant l'exécution de ``/bin/echo`` ?



          fork, fermer stdout, ouvrir test.txt - par défaut il aura le premier fd libre, c-a-d celui de stdout qui vient d'être fermé et ensuite exécution avec execve

          9. Dans un shell, on exécute la commande ``./a.out < in.txt > out.txt``. Quelles sont les appels systèmes qui doivent être exécutés par le shell pour lancer cet exécutable comme demandé par l'utilisateur ?


          fork puis dans le fils
          close(stdin)
          open(in.txt,O_RDONLY)
          close(stdout)
          open(out.txt,O_WRONLY)
          execve (qui préserver les descripteurs ouverts)

          10. Dans un shell, on exécute la commande ``cat < in.txt | grep sinf1252``. Quelles sont les appels systèmes qui doivent être exécutés par le shell pour lancer cette commande comme demandé par l'utilisateur ?

          deux forks
          premier fils
          close(stdin)
          close(stdout)

          11. Dans un shel `bash(1)`_, lorsque l'on suffixe une commande avec ``2>&1``, le shell redirige la sortie d'erreur standard vers la sortie standard. Quels sont les appels systèmes utilisés par le shell pour réussir cette redirection ?

          le shell va faire fork pour exécuter le programme, mais avant il doit fermer stdout et le dupliquer avec dup ou dup2


6. Comment se comporte l'appel système `write(2)`_ lorsque le disque sur lequel on souhaite écrire des données est plein ? Peut-on distinguer cette erreur d'un problème d'écriture sur le disque ?

 .. only:: staff

    il retourne une erreur et met errno à ENOSPC

7. A quoi sert l'appel système `sync(2)`_ ?

  .. only:: staff

     A forcer l'écriture des données sur le disque

8. Le programme :download:`/Programmes/src/writeperf.c` permet de tester les performances des écritures dans write sur un système de fichiers. Compilez-le et exécutez le avec différents tailles de buffers passés à `write(2)`_. Mesurez le temps d'exécution avec la commande `time(1posix)`_ et comparez le temps qu'il faut pour écrire 100MB en blocs de 1 MB ou en blocs de 1 KB. Faites de même en activant la synchronisation avec le paramètre ``-s``.

  .. only:: staff

     Les performances décroissent car il y a plus d'appels systèmes qui sont effectués. sync force l'écriture et bypasse le buffer. Il est utile de mentionner l'existence de ce buffer

.. only:: staff

   15. Effectuez l'exercice sur la manipulation de fichiers sur `INGInious <https://inginious.info.ucl.ac.be/course/LSINF1252/fichiers>`_.

.. 17. `tee(1)`_ est un utilitaire qui permet de recopier son entrée standard vers un ou plusieurs fichiers et également vers sa sortie standard. Il peut être utile pour par exemple inspecter des données échangées entre deux processus à travers un :term:`pipe`. Quels sont les appels systèmes exécutés par `tee(1)`_ lors de l'exécution de la commande ``cat /tmp/t | tee /tmp/tee.out | grep "sinf1252" ``


