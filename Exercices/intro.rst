.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Introduction
============

Cette section comprend deux types d'exercices afin de permettre aux étudiants de mieux ancrer leur compréhension des bases des systèmes informatiques. Les premiers sont des questionnaires à choix multiples. Pour chaque module de cours, entre 5 et 10 questions à choix multiples seront proposées. Elles permettront à chaque étudiant(e) de valider sa compréhension de la matière. Ensuite, les étudiants seront invités à écrire de petits programmes, généralement en langage C. Ces programmes sont l'occasion de mettre en pratique les compétences acquises chaque semaine. La plupart des programmes ont un rôle formatif, ils permettront de guider la discussion avec les tuteurs durant les séances tutorées. Enfin, deux projets de groupe seront proposés aux étudiants. Leur évaluation contribuera à la cote finale.


Première semaine
----------------


.. toctree::
   :maxdepth: 1

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

La matière couverte cette semaine correspond aux sections relative à l'`organisation de la mémoire <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/C/malloc.html#organisation-de-la-memoire>`_

.. toctree::
   :maxdepth: 2
              
   mcq-ex/qcm-3           
   Programmes/prog-3


Quatrième semaine
-----------------

La matière couverte cette semaine correspond aux sections :

 - `Organisation des ordinateurs <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Assembleur/memory.html>`_
 - `Etude de cas : IA32 <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Assembleur/memory.html#etude-de-cas-architecture-ia32>`_

.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-4           
   Programmes/prog-4


Cinquième semaine
-----------------

La matière couverte cette semaine correspond aux sections :

 - :ref:`theorie:complementsC`
 - :ref:`theorie:threads`


.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-5           
   Programmes/prog-5

Sixième semaine
---------------

La matière de cette semaine porte sur la communication entre les threads. Elle est décrite dans la section  :

 - :ref:`theorie:comthreads`


.. toctree::
   :maxdepth: 2

   mcq-ex/qcm-6           
   Programmes/prog-6



Septième semaine
----------------

La matière de cette semaine porte sur l'utilisation des sémaphores et quelques compléments sur les threads. Elle est décrite dans la section  :

 - :ref:`theorie:coordinationthreads`

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

La matière de cette semaine porte sur l'utilisation du système de fichiers et les ``pipe``. Elle est décrite dans les sections  :

 - :ref:`theorie:utilisateurs`
 - :ref:`theorie:fichiers`
 - :ref:`theorie:pipe`

.. only:: html

   `QCM9 <http://sites.uclouvain.be/SystInfo/qcm/Mission-9-qcm.html>`_




Séance tutorée
^^^^^^^^^^^^^^

.. toctree::
   :maxdepth: 2

   Programmes/prog-9


Dixième semaine
---------------

La matière de cette semaine porte sur les signaux, les sémaphores nommés et le partage de fichiers :

 - :ref:`theorie:signaux`
 - :ref:`theorie:semname`
 - :ref:`theorie:fileshare`

Séance tutorée
^^^^^^^^^^^^^^

.. toctree::
   :maxdepth: 2

   Programmes/prog-10


Evaluation des performances des appels systèmes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Pour le troisième projet, vous devrez choisir un appel système, analyser la façon dont il doit être utilisé, sur base de sa page de manuel et de livres de référence et ensuite en évaluer ses performances. Pour cette évaluation de performances, vous devrez modifier le programme de benchmark développé par Benoît Legat, Nicolas Demol et Maxime Houtain :

 https://github.com/blegat/benchmark.git

Pour s'exécuter, ce programme nécessite une version récente de `gnuplot <http://www.gnuplot.info>`_ , un programme permettant d'afficher des données de façon graphique. Téléchargez les sources de ce programme et installez-le en faisant :

.. code:: console


   wget http://sourceforge.net/projects/gnuplot/files/gnuplot/4.6.5/gnuplot-4.6.5.tar.gz
   tar xzvf gnuplot-4.6.5.tar.gz
   cd gnuplot-4.6.5
   ./configure
   make

Le programme gnuplot est maintenant compilé et prêt à être utilisé. Le programme exécutable est dans le répertoire gnuplot-4.6.5/src/gnuplot

Chargez le programme de benchmark et compilez-le comme suit :

.. code:: console

   git clone https://github.com/blegat/benchmark.git
   cd benchmark
   PATH=~/src/gnuplot-4.6.5/src:${PATH} ./bootstrap.sh 
   make

La troisième commande permet de forcer l'utilisation de la version récente de gnuplot que vous avez installé à la place de la version par défaut du système qui n'est pas supportée par l'outil de benchmark. Une fois le benchmark compilé, vous pouvez l'exécuter et tester les benchmarks fournis. Commencez par ceux qui se trouvent dans les répertoires suivants :

 - ``tab``
 - ``thread`` 
 - ``amdahl`` 
 - ``types``

Pour exécuter un benchmark, lancez simplement ``make show`` dans le répertoire du benchmark. Il exécutera alors le benchmark et produira un fichier HTML contenant les résultats obtenus ainsi que des fichiers au format .csv avec les valeurs mesurées. Essayez d'interpréter les résultats obtenus. Pouvez-vous justifier l'évolution des performances que vous observez ?


Onzième semaine
---------------

La matière de cette semaine porte sur la mémoire virtuelle et les fichiers mappés en mémoire :

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


Douzième semaine
----------------

La matière de cette semaine porte sur les utilisations avancées de la mémoire virtuelle :

 - :ref:`theorie:shmem`
 - :ref:`theorie:forkmem`
 - :ref:`theorie:vmstat`
 - :ref:`theorie:execvmem`

Séance tutorée
^^^^^^^^^^^^^^

.. toctree::
   :maxdepth: 2

   Programmes/prog-12
