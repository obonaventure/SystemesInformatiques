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

 - `git <http://git-scm.com/>`_ développé initialement pour la gestion du code source du kernel Linux. git est aussi utilisé pour la gestion des sources de ce document depuis https://github.com/obonaventure/SystemesInformatiques
 - `subversion`_ qui est décrit ci-dessous
 - `mercurial <http://mercurial.selenic.com/>`_


`subversion`_ (ou abrégé `svn(1)`_) est un logiciel qui permet à plusieurs utilisateurs de travailler sur les mêmes documents de type texte. `Subversion`_ est fréquemment utilisé pour gérer du code source développé de façon collaborative, mais il peut aussi gérer à gérer n'importe quel ensemble de fichiers (de préférence textes) manipulés par plusieurs personnes. 

.. Dans le cadre du cours SINF1252 vous devez vous inscrire à subversion dans le projet ``SINF1252_2012`` en suivant le lien et les instructions sur http://wiki.student.info.ucl.ac.be/index.php/Svn

Pour commencer l'utilisation de `svn(1)`_ vous devriez faire d'abord un ``checkout`` du répertoire:

        .. code-block:: console
        
                $ svn checkout <url de votre répertoire>
                Checked out revision 1.

Ceci installe votre répertoire (ici, nommé ``my_rep``) dans le dossier courant. Vous pouvez vous déplacer dans le nouveau dossier et créer un nouveau dossier pour cet premier projet. Il faut explicitement ajouter ce dossier à svn avec la commande ``svn add [nom du dossier]``. Chaque fichier et dossier dont vous voulez qu'il fasse partie du contrôle de version doivent être ajoutés avec cette commande.

        .. code-block:: console
        
                $ cd my_rep
                $ mkdir projet_S1
                $ svn add projet_S1
                A       projet_S1

Ce dossier n'a pas encore été envoyé sur le serveur principal et n'est donc pas encore visible pour d'autres utilisateurs. Pour afficher l'état de votre répertoire utilisez ``svn status``. La lettre ``A`` indique que ceci est un nouveau dossier/fichier pas encore envoyé vers le serveur. ``?`` indique que les fichiers/dossiers ne font pas partie du répertoire svn (on peut les ajouter avec ``svn add``). ``M`` indique que les fichiers sont modifiés localement mais pas encore envoyés vers le serveur. Ces fichiers font partie du répertoire svn.

        .. code-block:: console
        
                $ svn status
                A       projet_S1
                $ svn commit -m "Projet S1: Initialisation"
                Adding  projet_S1
                Transmitting file data .
                Committed revision 2.

La commande ``svn commit`` permet de pousser les changements locaux et les nouveaux fichiers vers le serveur. La chaîne de charactères entre les ``"`` est le commentaire qu'il faut ajouter au commit. Il est important de commenter vos commits pour que vous puissiez vous retrouvez dans votre historique. L'historique de votre répertoire peut être affiché avec la commande ``svn log``.

Les autres utilisateurs de votre répertoire (c'est-à-dire dans le cadre de ce cours: vôtre binôme du groupe) peuvent à partir de maintenant accéder à ce nouveau dossier en mettant à jour son répertoire local.
Pour mettre à jour le répertoire local, on utilise la commande ``svn update``.

        .. code-block:: console
        
                $ svn update
                Updating '.':
                A       projet_S1
                Updated to revision 2.

Il est recommandé de toujours faire un ``update`` avant de faire un ``commit``. Lors d'un update il est possible qu'un conflit se crée dans votre dossier local. Ceci peut arriver si vous avez modifié une ligne dans un fichier localement et que cette ligne a aussi été modifiée par le commit d'un autre utilisateur. Pour résoudre le conflit, vous devez éditer le fichier que svn a indiqué être en conflit en cherchant des lignes qui commencent par ``<<<``. Corrigez ce fichier et retournez dans la console et tapez ``r`` pour indiquer à svn que ce conflit a été résolu.

Pour plus d'informations sur svn regardez les commandes ``svn help``, ``svn help [commande]`` ou http://svnbook.red-bean.com/. Une recherche sur Google vous aidera aussi pour résoudre vos problèmes avec subversion.

Compilateurs
============

Le compilateur C utilisé dans de nombreuses distributions Linux est `gcc(1)`_. C'est un compilateur open-source développé activement dans le cadre du projet |gnu| par la `Free Software Foundation <http://www.fsf.org>`_. Nous utiliserons principalement `gcc(1)`_ dans le cadre de ce cours.

Il existe des alternatives à `gcc(1)`_ comme llvm_ que nous utiliserons lorsque nous analyserons le code assembleur généré par un compilateur C. Les variantes commerciales de Unix utilisent généralement des compilateurs propriétaires, dont par exemple `Oracle Studio <http://www.oracle.com/technetwork/server-storage/solarisstudio/overview/index.html>`_ ou la `suite de compilateurs <http://software.intel.com/en-us/c-compilers>`_ développée par intel_.
