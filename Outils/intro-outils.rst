.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Introduction
============

Outre des compétences théoriques qui sont abordées dans d'autres parties de ce document, la maitrise d'une système informatique implique également une excellente connaissance des outils informatiques qui sont inclus dans ce système. Cette connaissance se construit bien entendu en utilisant activement ces logiciels. Cette section comprend les informations de bases sur quelques logiciels importants qui sont utilisés dans le cadre du cours. Elle est volontairement réduite car de nombreux logiciels pourraient faire l'objet de livres complets. Les étudiants sont invités à proposer des améliorations à cette section sous la forme de patches via https://github.com/obonaventure/SystemesInformatiques


Editeurs
========

De nombreux éditeurs sont utilisables pour manipuler efficacement du code source en langage C. Chaque étudiant doit choisir l'éditeur qui lui convient le mieux. En voici quelques uns :

 - `vi(1)`_ est un des premiers éditeurs à avoir été écrit pour Unix. Il a fortement évolué, et reste un outil de choix pour de nombreux administrateurs systèmes. De nombreux tutoriels permettent d'apprendre rapidement `vi(1)`_, dont http://www.ibm.com/developerworks/linux/tutorials/l-vi/
 - `emacs <http://www.gnu.org/software/emacs/>`_ est un autre éditeur fréquemment utilisé sous Unix. Il existe de très nombreuses extensions à emacs qui lui permettent de faire tout ou presque, y compris de jouer à des jeux comme Tetris. Son extensibilité peut rebuter certains utilisateurs. De nombreux tutoriels sont disponibles sur Internet, dont http://www.gnu.org/software/emacs/tour/
 - `gedit <http://projects.gnome.org/gedit/>`_ est l'éditeur de base dans l'environnement graphique `GNOME <http://www.gnome.org>`_ utilisé dans les distributions Linux.
 - `eclipse <http://www.eclipse.org>`_ est un environnement complet de développement écrit en Java pour supporter initialement ce langage. De nombreuses extensions à `eclipse <http://www.eclipse.org>`_ existent, dont `CDT <http://www.eclipse.org/cdt/>`_ qui permet la manipulation efficace de code source en langages C et C++.


.. _svn:

Gestionnaires de code partagé
=============================

Dans de nombreux projets informatiques, il est nécessaire d'utiliser des outils qui permettent d'organiser efficacement le partage du code source entre plusieurs développeurs. Les plus anciens gestionnaires de code sont `cvs <http://cvs.nongnu.org/>`_ ou `rcs <http://www.gnu.org/software/rcs/>`_. Ces logiciels ont été créés lorsque Unix était utilisé sur des mini-ordinateurs qui servaient tout un département. Aujourd'hui, les logiciels de gestion de code source s'utilisent en combinaison avec des serveurs Internet pour permettre un partage large du code source. Les plus connus sont :

 - `Git`_ qui est décrit ci-dessous
   Il est aussi décrit dans plein d'autres ressources comme
   `git-scm <http://git-scm.com/>`_ contenant le livre Pro Git,
   `git-ref <http://git-ref.com/>`_ mais aussi une
   `vidéo <http://www.youtube.com/watch?v=ZDR433b0HJY>`_ faite par le créateur
   de ces deux sites et
   `Try Git <http://try.github.io/levels/1/challenges/1>`_ qui permet
   de découvrir `Git`_ en 15 minutes interactivement à travers le site.
 - `subversion`_ qui est décrit ci-dessous également
 - `mercurial <http://mercurial.selenic.com/>`_
 - `bazaar <http://bazaar.canonical.com/>`_


Compilateurs
============

Le compilateur C utilisé dans de nombreuses distributions Linux est `gcc(1)`_. C'est un compilateur open-source développé activement dans le cadre du projet GNU par la `Free Software Foundation <http://www.fsf.org>`_. Nous utiliserons principalement `gcc(1)`_ dans le cadre de ce cours.

Il existe des alternatives à `gcc(1)`_ comme llvm_ que nous utiliserons lorsque nous analyserons le code assembleur généré par un compilateur C. Les variantes commerciales de Unix utilisent généralement des compilateurs propriétaires, dont par exemple `Oracle Studio <http://www.oracle.com/technetwork/server-storage/solarisstudio/overview/index.html>`_ ou la `suite de compilateurs <http://software.intel.com/en-us/c-compilers>`_ développée par intel_.
