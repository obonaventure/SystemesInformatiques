.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Introduction
============

Cette section comprend deux types d'exercices afin de permettre aux étudiants de mieux ancrer leur compréhension des bases des systèmes informatiques. Les premiers sont des questionnaires à choix multiples. Pour chaque module de cours, entre 5 et 10 questions à choix multiples seront proposées. Elles permettront à chaque étudiant(e) de valider sa compréhension de la matière. Ensuite, les étudiants seront invités à écrire de petits programmes, généralement en langage C. Ces programmes sont l'occasion de mettre en pratique les compétences acquises chaque semaine. La plupart des programmes ont un rôle formatif, ils permettront de guider la discussion avec les tuteurs durant les séances tutorées. Enfin, deux projets de groupe seront proposés aux étudiants. Leur évaluation contribuera à la cote finale.


Première semaine
----------------

La matière couverte cette semaine correspond à l'`introduction aux systèmes informatiques <https://sites.uclouvain.be/SystInfo/notes/Theorie/html/intro.html>`_ et au `langage C <https://sites.uclouvain.be/SystInfo/notes/Theorie/html/C/intro-C.html>`_ . Le volet pratique est important et les sections relatives au `shell <https://sites.uclouvain.be/SystInfo/notes/Outils/html/shell.html>`_ et aux `processus <https://sites.uclouvain.be/SystInfo/notes/Outils/html/processus.html>`_ de la section dédiée aux `autres outils <https://sites.uclouvain.be/SystInfo/notes/Outils/html>`_ devraient vous être utiles.


.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-1
   Programmes/prog-1


Deuxième semaine
----------------

La matière couverte cette semaine correspond à la section relative aux `types de données <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/C/datatypes.html#les-expressions-de-manipulation-de-bits>`_ (jusque et y compris la section relative aux `expressions de manipulation de bits <http://sites.uclouvain.be/SystInfo/notes/Theorie/C/datatypes/#les-expressions-de-manipulation-de-bits>`_) 

.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-2
   Programmes/prog-2


Troisième semaine
-----------------

La matière couverte cette semaine correspond aux sections relative à l'`organisation de la mémoire <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/C/malloc.html#organisation-de-la-memoire>`_ Vous commencez à développer des programmes complets, le debugger `gdb <https://sites.uclouvain.be/SystInfo/notes/Outils/html/gdb.html>`_ pourrait vous aider. Il est décrit dans la section `gdb  <https://sites.uclouvain.be/SystInfo/notes/Outils/html/gdb.html>`_

.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-3
   Programmes/prog-3


Quatrième semaine
-----------------

Durant les dernières semaines, vous avez appris les bases de l'écriture de fonctions en C. L'objectif de cette semaine est de vous amener à être capable d'écrire des programmes comprenant plusieurs fonctions. 
La matière couverte cette semaine correspond aux sections :

 - :ref:`theorie:ordinateurs`
 - :ref:`theorie:complementsC`

En outre, vous devrez aussi lire les sections de la partie Outils qui sont relatives à 

-  :ref:`outils:make`
-  :ref:`outils:ref_cunit`


.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-4
   Programmes/prog-4


Cinquième semaine
-----------------


La matière de cette semaine porte sur l'utilisation du système de fichiers et les ``pipe``. Elle est décrite dans les sections  :

 - :ref:`theorie:utilisateurs`
 - :ref:`theorie:fichiers`
 - :ref:`theorie:pipe`


.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-9
   Programmes/prog-5


Sixième semaine
---------------

La matière couverte cette semaine correspond aux sections :


 - :ref:`theorie:threads` (sauf la section `Utilisation d'instruction atomique`)
 - :ref:`theorie:comthreads` (jusqu'à la section `Le problème des philosophes`) 

.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-6
   Programmes/prog-6


Septième semaine
----------------

La matière de cette semaine porte sur l'utilisation des mutex et des sémaphores et quelques compléments sur les threads. Elle est décrite dans la section  :

 - :ref:`theorie:comthreads` (à partir de la section `Le problème des philosophes`) 
 - :ref:`theorie:coordinationthreads`

En outre, vous devrez aussi lire les sections de la partie Outils qui sont relatives à 

-  :ref:`outils:valgrind-ref`
-  :ref:`outils:gdb-ref`

.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-7
   Programmes/prog-7

Huitième semaine
----------------

La matière de cette semaine porte sur le fonctionnement des processus. Elle est décrite dans la section  :

 - :ref:`theorie:processus`

.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-8
   Programmes/prog-8



Neuvième semaine
----------------

La matière de cette semaine porte sur les pipes, la mémoire virtuelle et les fichiers mappés en mémoire :

 - :ref:`theorie:pipe`
 - :ref:`theorie:vmem`
 - :ref:`theorie:fctvmem`
 - :ref:`theorie:stockage`
 - :ref:`theorie:remplacement`
 - :ref:`theorie:mmap`


.. only:: html

   `QCM11 <http://sites.uclouvain.be/SystInfo/qcm/Mission-11-qcm.html>`_


Séance tutorée
^^^^^^^^^^^^^^

.. toctree::
   :maxdepth: 2

   Programmes/prog-11


Dixième semaine
---------------

La matière de cette semaine porte sur les utilisations avancées de la mémoire virtuelle, les sméaphores nommés et le partage de fichiers :

 - :ref:`theorie:shmem`
 - :ref:`theorie:forkmem`
 - :ref:`theorie:vmstat`
 - :ref:`theorie:execvmem`
 - :ref:`theorie:semname`
 - :ref:`theorie:fileshare`

Séance tutorée
^^^^^^^^^^^^^^

.. toctree::
   :maxdepth: 2

   Programmes/prog-12

Onzième semaine
---------------

La matière de cette semaine porte sur l'utilisation du processeur intel 32 bits en langage assembleur

 - `Organisation des ordinateurs <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Assembleur/memory.html>`_
 - `Etude de cas : IA32 <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Assembleur/memory.html#etude-de-cas-architecture-ia32>`_


Séance tutorée
^^^^^^^^^^^^^^

.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-4-asm
   Programmes/prog-4-asm


Douzième semaine 
----------------

La matière de cette semaine porte sur les signaux, les sémaphores nommés et le partage de fichiers :

 - :ref:`theorie:signaux`


Séance tutorée 
^^^^^^^^^^^^^^

.. toctree::
   :maxdepth: 2 

   mcq-ex/qcm-10 
   Programmes/prog-10 

