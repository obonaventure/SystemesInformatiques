.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. raw:: html

  <script type="text/javascript" src="js/jquery-1.7.2.min.js"></script>
  <script type="text/javascript" src="js/jquery-shuffle.js"></script>
  <script type="text/javascript" src="js/rst-form.js"></script>
  <script type="text/javascript" src="js/prettify.js"></script>
  <script type="text/javascript">$nmbr_prop = 4</script>


================
Neuvième semaine
================


La matière couverte cette semaine porte sur le système de fichiers et sa manipulation par les processus.

Question 1. Accès aux fichiers
------------------------------

Les bits de permissions permettent de contrôler l'accès aux fichiers. Considérons le répertoire ci-dessous :

.. code-block:: console

  -rw-r--r--  1 obo  obo   0 23 mar 21:57 a
  -r-xr-x--x  1 obo  obo   0 23 mar 21:57 b
  -rw-------  1 obo  obo   0 23 mar 21:57 c
  -rw------x  1 obo  obo   0 23 mar 21:57 d
  --w-----w-  1 obo  obo   0 23 mar 21:57 e


Un seul des groupes d'affirmations ci-dessous est vrai. Lequel ?

.. class:: positive

-
 - l'utilisateur ``obo`` peut lire le fichier ``c``, exécuter le fichier ``b`` et modifier le contenu du fichier ``d``


-
 - l'utilisateur ``obo`` peut lire le fichier ``a``, exécuter le fichier ``b`` et modifier le contenu du fichier ``c``


.. class:: negative

-
 - l'utilisateur ``obo`` peut lire le fichier ``e``, exécuter le fichier ``b`` et modifier le contenu du fichier ``e``

   .. class:: comment

      Le fichier ``e`` n'est pas lisible par cet utilisateur.

-
 - l'utilisateur ``obo`` peut lire le fichier ``c``, exécuter le fichier ``d`` et modifier le contenu du fichier ``b``

   .. class:: comment

      Le fichier ``b`` n'est pas modifiable par cet utilisateur.

-
 - l'utilisateur ``obo`` peut lire le fichier ``c``, exécuter le fichier ``a`` et modifier le contenu du fichier ``d``

   .. class:: comment

      Le fichier ``a`` n'est pas exécutable par cet utilisateur.


Question 2. Fichiers et répertoires
-----------------------------------

Les permissions associées aux répertoires ont un rôle un peu différent de celles qui sont associées aux fichiers. Considérons le répertoire ci-dessous qui contient 4 sous-répertoires.

.. code-block:: console

   drw-------  2 obo  obo   68 23 mar 22:25 a
   dr-x------  2 obo  obo   68 23 mar 22:25 b
   d-wx------  3 obo  obo  102 23 mar 22:27 c
   drwx------  3 obo  obo  102 23 mar 22:26 d

Chacun de ces répertoires contient un fichier qui a comme nom ``f``. La commande `touch(1)`_ peut être utilisée pour créer un fichier vide. Ainsi, dans ce répertoire, la commande ``touch f`` va créer le fichier  ``f``

.. code-block:: console

   ls -l f
   -rw-r--r--  1 obo  obo  0 23 mar 22:30 f

Dans le répertoire ci-dessus, une seule séquence de commandes fonctionne sans erreur. Laquelle ?

.. class:: positive

-
 .. code-block:: console

    ls -l d
    touch c/x
    cd b

-
 .. code-block:: console

    ls -l b
    cat c/f
    cd d


.. class:: negative

-
 .. code-block:: console

    ls -l c
    touch d/x
    cd a

 .. class:: comment

    Il n'est pas possible d'aller dans le répertoire ``a``. En outre, le contenu du répertoire ``c`` ne peut pas être lu avec `ls(1)`_

-
 .. code-block:: console

    ls -l c
    touch a/x
    cd c

 .. class:: comment

    Il n'est pas possible de créer un fichier dans le répertoire ``a``.

-
 .. code-block:: console

    ls -l b
    touch b/x
    cd b

 .. class:: comment

    Il n'est pas possible de créer un fichier dans le répertoire ``b``.



Question 3. Permissions sur les fichiers
----------------------------------------

La page de manuel de `chmod(1posix)`_ décrit en détails les permissions relatives aux fichiers et répertoires. Ces permissions peuvent être représentées sous une forme numérique ou textuelle. Parmi les affirmations suivantes, relatives à des permissions pour des `fichiers`, un seul groupe est vrai. Lequel ?


.. class:: positive

-
  - Le fichier ayant ``00467`` comme permissions est exécutable par n'importe quel utilisateur
  - Le fichier ayant ``00777`` comme permissions est lisible par son propriétaire
  - Le fichier ayant ``00600`` ne peut être lu que par son propriétaire

-
  - Le fichier ayant ``00647`` comme permissions est exécutable par n'importe quel utilisateur
  - Le fichier ayant ``00700`` comme permissions est lisible par son propriétaire
  - Le fichier ayant ``00421`` comme permissions ne peut être lu que par son propriétaire

.. class:: negative

-
  - Le fichier ayant ``00476`` comme permissions est exécutable par n'importe quel utilisateur
  - Le fichier ayant ``00747`` comme permissions est lisible par son propriétaire
  - Le fichier ayant ``00601`` comme permissions ne peut être lu que par son propriétaire

  .. class:: comment

     Le fichier ayant ``00476`` comme permissions ne peut être exécuté que par un membre du groupe correspondant à ce fichier.

-
  - Le fichier ayant ``00677`` comme permissions est exécutable par n'importe quel utilisateur
  - Le fichier ayant ``00017`` comme permissions est lisible par son propriétaire
  - Le fichier ayant ``00400`` comme permissions ne peut être lu que par son propriétaire

  .. class:: comment

     Le fichier ayant ``00017`` comme permissions n'est pas lisible par son propriétaire


-
  - Le fichier ayant ``00755`` comme permissions est exécutable par n'importe quel utilisateur
  - Le fichier ayant ``00417`` comme permissions est lisible par son propriétaire
  - Le fichier ayant ``00222`` comme permissions ne peut être lu que par son propriétaire

  .. class:: comment

     Le fichier ayant ``00222`` comme permissions n'est pas lisible par son propriétaire


-
  - Le fichier ayant ``00666`` comme permissions est exécutable par n'importe quel utilisateur
  - Le fichier ayant ``00400`` comme permissions est modificale par son propriétaire
  - Le fichier ayant ``00400`` comme permissions ne peut être lu que par son propriétaire

  .. class:: comment

     Le fichier ayant ``00666`` comme permissions n'est pas exécutable



Question 4. Permissions sur les fichiers
----------------------------------------

Les bits de permissions associés à un fichiers sont généralement représentés sous forme textuelle lorsque la commande `ls(1)`_ affiche le contenu d'un répertoire. Considérons le répertoire ci-dessous :

 .. code-block:: console

   -rw-r--r--  1 obo  obo  0 23 mar 21:57 a
   -rwxr-x--x  1 obo  obo  0 23 mar 21:57 b
   -rw-------  1 obo  obo  0 23 mar 21:57 c
   -rw------x  1 obo  obo  0 23 mar 21:57 d
   --w-r--rw-  1 obo  obo  0 23 mar 21:57 e


Parmi les commandes suivantes, un seul groupe permet d'obtenir les mêmes permissions que ci-dessous. Lequel ?

.. class:: positive

-
 .. code-block:: console

    chmod 644 a
    chmod 751 b
    chmod 600 c
    chmod 601 d
    chmod 246 e

.. class:: negative


-
 .. code-block:: console

    chmod 446 a
    chmod 157 b
    chmod 006 c
    chmod 106 d
    chmod 642 e

 .. class:: comment

    Relisez la page de manuel de `chmod(1)`_

-
 .. code-block:: console

    chmod 444 a
    chmod 751 b
    chmod 600 c
    chmod 604 d
    chmod 123 e

 .. class:: comment

    Relisez la page de manuel de `chmod(1)`_

-
 .. code-block:: console

    chmod 322 a
    chmod 364 b
    chmod 300 c
    chmod 301 d
    chmod 123 e

 .. class:: comment

    Relisez la page de manuel de `chmod(1)`_


Question 5. Système de fichiers
-------------------------------


Le système de fichiers Unix utilise des `inode` pour stocker les meta-données relatives à un fichier/répertoire. Parmi les groupes d'affirmations suivants, un seul est correct. Lequel ?

.. class:: positive

-
 - deux fichiers se trouvant dans des répertoires différents sur le même disque peuvent avoir le même `inode`
 - le champ ``nlinks`` est toujours positif
 - un accès au fichier modifie le ``atime`` associé à ce fichier


.. class:: negative

-
  - deux fichiers ont toujours des `inode` différents
  - l'`inode` contient le nom du fichier
  - une écriture dans un fichier modifie le ``mtime`` associé à ce fichier

  .. class:: comment

     Les deux premières affirmations sont fausses.


-
  - un fichier et un répertoire se trouvant sur le même disque peuvent avoir le même `inode`
  - une lecture dans un fichier modifie le ``mtime`` associé à ce fichier
  - l'`inode` contient le nom du fichier

  .. class:: comment

     Toutes les affirmations sont fausses.


-
  - une copie d'un fichier incrémente la valeur du champ ``nlinks`` de son `inode`
  - une lecture dans un fichier modifie le ``atime`` associé à ce fichier
  - il n'y a jamais deux fichiers qui ont le même `inode`

  .. class:: comment

     La première et la troisième affirmation sont fausses.

Question 6. Manipulation des répertoires
----------------------------------------

Les répertoires sont des fichiers spéciaux. Pour les utiliser, il faut faire appel aux fonctions `opendir(3)`_, `readdir(3)`_  et `closedir(3)`_. Parmi les séquences d'instructions ci-dessous, laquelle permet de compter le nombre de fichiers se trouvant dans le répertoire courant ?

.. code-block:: c

   /*
    * name!=NULL
    * retourne le nombre de fichiers dans le répertoire name
    * et -1 en cas d'erreur
    */

.. class:: positive

-
 .. code-block:: c

    int nfiles(char * name) {

      DIR *dirp;
      struct dirent *dp;
      dp=malloc(sizeof(struct dirent));
      if(dp==NULL) {
        return -1;
      }
      dirp = opendir(name);
      if(dirp==NULL) {
        return -1;
      }
      int count=0;
      while ((dp = readdir(dirp)) != NULL) {
         if (dp->d_type==DT_REG) {
           count++;
         }
      }
      int err = closedir(dirp);
      if(err<0) {
         return -1;
      }
      return(count);
    }


-

.. class:: negative

-
 .. code-block:: c

    int nfiles(char * name) {

      DIR *dirp;
      struct dirent *dp;
      dirp = opendir(name);
      if(dirp==NULL) {
        return -1;
      }
      int count=0;
      while (readdir(dirp) != NULL) {
           count++;
      }
      int err = closedir(dirp);
      if(err<0) {
         return -1;
      }
      return(count);
    }

 .. class:: comment

    Ce code compte toutes les entrées dans le répertoire et pas seulement le fichiers.

-
 .. code-block:: c

     int nfiles2(char * name) {

      DIR dirp;
      struct dirent dp;
      dirp = opendir(name);
      if(dirp==-1) {
        return -1;
      }
      int count=0;
      while ((dp = readdir(dirp)) != -1) {
      	   count++;
      }

      int err = closedir(dirp);
      if(err<0) {
        return -1;
      }
      return(count);
    }

 .. class:: comment

    Ce code est erroné. `opendir(3)`_ retourne un pointeur et `readdir(3)`_ également.

-
 .. code-block:: c

    int nfiles(char * name) {

      DIR dirp;
      struct dirent dp;
      dirp = opendir(name);
      int count=0;
      while ((dp = readdir(dirp)) != NULL) {
         if (dp->d_type==DT_REG) {
           count++;
         }
      }
      int err = closedir(dirp);
      if(err<0) {
         return -1;
      }
      return(count);
    }

 .. class:: comment

    Ce code est erroné. `opendir(3)`_ retourne un pointeur et `readdir(3)`_ également.




Question 7. Liens symboliques
-----------------------------

Considérons un répertoire dans lequel les commandes suivantes sont exécutées :

.. code-block:: console

   touch a
   cp a b
   ln a c
   ln b d
   echo "test" > c
   ln -s  d e
   echo essai > e

Après exécution de ces commandes, un seul des groupes d'affirmations suivant est correct. Lequel ?

.. class:: positive

-
  - les fichiers ``a`` et ``c`` ont le même `inode`
  - les fichiers ``b`` et ``d`` ont la même taille
  - l'`inode` correspondant au fichier ``d`` indique qu'il y a deux liens vers lui


-
  - les fichiers ``d`` et ``e`` ont des `inode` différents
  - les fichiers ``a`` et ``c`` ont la même taille
  - l'`inode` correspondant au fichier ``b`` indique qu'il y a deux liens vers lui


.. class:: negative

-
  - les fichiers ``a`` et ``c`` ont des `inodes` différents
  - les fichiers ``e`` et ``d`` ont la même taille
  - l'`inode` correspondant au fichier ``d`` indique qu'il y a trois liens vers lui

-
  - les fichiers ``a`` et ``d`` ont des `inode` différents
  - les fichiers ``b`` et ``d`` ont la même taille
  - l'`inode` correspondant au fichier ``b`` indique qu'il y a trois liens vers lui

  .. class:: comment

     Il y a deux liens (hard) vers le fichier ``b``. Le fichier ``e`` est un lien symbolique vers ce fichier et non un lien `hard`.

-
  - les fichiers ``b``, ``d`` et ``e`` ont le même `inode`
  - les fichiers ``a`` et ``c`` ont la même taille
  - l'`inode` correspondant au fichier ``a`` indique qu'il y a deux liens vers lui


.. include:: ../../../links.rst
.. include:: ../../../man_links.rst
.. include:: ../../../incl_links.rst
