.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


*********
Glossaire
*********

.. glossary::
    :sorted:

 CPU
    Central Processing Unit

 C
    Langage de programmation permettant d'interagir facilement avec le matériel.

 RISC
    Reduced Instruction Set Computer

 CISC
    Complex Instruction Set Computer

 x86
    Famille de microprocesseurs développée par intel_. Le 8086 est le premier processeur de cette famille. Ses successeurs (286, 386, Pentium, Centrino, Xeon, ...) sont restés compatibles avec lui tout en introduisant chacun de nouvelles instructions et de nouvelles fonctionnalités. Aujourd'hui, plusieurs fabricants développent des processeurs qui supportent le même langage machine que les processeurs de cette famille.

 Unix
    Système d'exploitation développé initialement par AT&T Bell Labs.

 gcc
    Compilateur pour la langage C développé par un groupe de volontaires qui est diffusé depuis http://gcc.gnu.org gcc est utilisé dans plusieurs systèmes d'exploitation de type Unix, comme MacOS, Linux ou FreeBSD. Il existe d'autres compilateurs C. Une liste non-exhaustive est maintenue sur http://en.wikipedia.org/wiki/List_of_compilers#C_compilers

 llvm
    Ensemble de compilateurs pour différents langages de programmation et différents processeurs développé par un groupe de volontaire. llvm est distrubé depuis http://llvm.org/

 cpp
 préprocesseur
    Le préprocesseur C est un programme de manipulation de texte sur base de macros qui est utilisé avec le compilateur. Le préprocesseur de :term:`gcc` est http://gcc.gnu.org/onlinedocs/cpp/

 microprocesseur
 processeur
    à compléter

 CPU
    Central Processing Unit. Voir :term:`microprocesseur`

 stdin
    Entrée standard sur un système Unix (par défaut le clavier)

 stdout
    Sortie standard sur un système Unix (par défaut l'écran)

 stderr
    Sortie d'erreur standard sur un système Unix (par défaut l'écran)

 X11
    Aussi appelé X Window System, est la définition d'un ensemble de protocoles et de programmes servant à gérer les fenêtres et autres composants constituants une interface graphique sur un système Unix. XQuartz http://xquartz.macosforge.org et X.Org http://www.x.org en sont des implémentations open source.

 Gnome
    Un environnement de bureau.

 CDE
    Un environnement de bureau.

 shell
    Interpréteur de commandes sur un système Unix. `bash(1)`_ est l'interpréteur de commandes le plus utilisé de nos jours.

 bit
    Plus petite unité d'information. Par convention, un bit peut prendre les valeurs ``0`` et ``1``.

 nibble
    Un bloc de quatre bits consécutifs.

 byte
 octet
    Un bloc de huit bits consécutifs.

 BSD Unix
    Variante de Unix développée à l'Université de Californie à Berkeley.

 FreeBSD
    Variante de BSD Unix disponible depuis http://www.freebsd.org

 OpenBSD
    Variante de BSD Unix disponible depuis http://www.openbsd.org

 MacOS
    Système d'exploitation développé par Apple Inc. comprenant de nombreux composantes provenant de :term:`FreeBSD`

 Minix
    Famille de noyaux de systèmes d'exploitation inspiré de :term:`Unix` développée notamment par :term:`Andrew Tanenbaum`. Voir http://www.minix3.org pour la dernière version de Minix.

 Linux
    Noyau de système d'exploitation compatible Unix développé initialement par Linus Torvalds.

 Solaris
    Système d'exploitation compatible Unix développé par Sun Microsystems et repris par Oracle. La version open-source, OpenSolaris, est disponible depuis http://www.opensolaris.org

 Application Programming Interface
 API
    Un API est généralement un ensemble de fonctions et de structures de données qui constitue l'interface entre deux composants logiciels qui doivent collaborer. Par exemple, l'API du noyau d'un système Unix est composée de ses appels systèmes. Ceux-ci sont décrits dans la section 2 des pages de manuel (voir `intro(2)`_).

 GNU is not Unix
 GNU
    GNU est un projet open-source de la Free Software Foundation qui a permis le développement d'un grand nombre d'utilitaires utilisés par les systèmes d'exploitation de la famille Unix actuellement.

 GNU/Linux
    Nom générique donné à un système d'exploitation utilisant les utilitaires :term:`GNU` notamment et le noyau :term:`Linux` .

 Andrew Tanenbaum
    Andrew Tanenbaum est professeur à la VU d'Amsterdam.

 Linus Torvalds
    Linus Torvalds est le créateur et le mainteneur principal du noyau :term:`Linux`.

 Aqua
    Aqua est une interface graphique spécifique à :term:`MacOS`.

 pipe
    Mécanisme de redirection des entrées-sorties permettant de relier la sortie standard d'un programme à l'entrée standard d'un autre pour créer des pipelines de traitement.

 assembleur
    Programme permettant de convertir un programme écrit en langage d'assemblage dans le langage machine correspondant à un processeur donné.

 warning
    Message d'avertissement émis par un compilateur C. Un :term:`warning` n'empêche pas la compilation et la génération du code objet. Cependant, la plupart des warnings indiquent un problème dans le programme compilé et il est nettement préférable de les supprimer du code.

 bit de poids fort
    Par convention, le bit le plus à gauche d'une séquence de n bits.

 bit de poids faible
    Par convention, bit le plus à droite d'une séquence de n bits.

 simple précision
    Représentation de nombre réels en virgule flottante (type ``float`` en C). La norme `IEEE754 <http://ieeexplore.ieee.org/xpl/mostRecentIssue.jsp?punumber=4610933>`_ définit le format de ces nombres sur 32 bits.

 double précision
    Représentation de nombre réels en virgule flottante (type ``double`` en C). La norme  définit le format de ces nombres sur 64 bits.

 buffer overflow
    Erreur survenante lorsqu'un processus tente d'écrire dans une zone mémoire tampon qui ne lui est pas allouée. Le processus peut écrire dès lors par dessus des informations pouvant être nécessaires au :term:`CPU` ou au système d'exploitation, le rendant par l'occasion imprévisible.

 garbage collector
    Algorithme permettant de libérer la mémoire qui n'est plus utilisée notamment dans des langages tels que Java.

 pointeur
    Une variable contenant une adresse mémoire.

 adresse
    Identifiant (typiquement représenté par un nombre entier) qui désigne une zone particulière de la mémoire physique où des données peuvent être lues et stockées.

 C99
    Standard international définissant le langage C [C99]_

 fichier header
    Fichier .h annexé à un fichier .c où sont en autres incluses les directives :term:`préprocesseur`, les définitions de structures, les typedef et les prototypes des fonctions.

 segmentation fault
    Erreur à l'exécution lorsque le programme réclame un accès en zone mémoire qui ne lui est pas allouée. Dés lors, le système d'exploitation termine le programme.

 NOT
 négation
    Opération binaire logique.

 AND
 conjonction logique
    Opération binaire logique.

 OR
 disjonction logique
    Opération binaire logique.

 XOR
 ou exclusif
    Opération binaire logique.

 libc
    Librairie C standard. Contient de nombreuses fonctions utilisables par les programmes écrits en langage C et décrites dans la troisième section des pages de manuel. Linux utilise la librairie GNU `glibc <http://www.gnu.org/software/libc/manual/>`_ qui contient de nombreuses extensions par rapport à la libraire standard.

 FSF
    Free Software Foundation, http://www.fsf.org

 portée
    Zone dans le code source dans lequel un identificateur est assuré de pointer vers la même adresse mémoire.

 portée locale
    :term:`portée` d'un identificateur se limitant à son bloc parent, généralement défini par des accolades.

 portée globale
    :term:`portée` d'un identificateur valable dans tout le fichier auquel il se trouve.

 debugger
    Logiciel interprétant les erreurs d'exécution dans le but d'aider le programmeur à corriger son programme.

 text
 segment text
    à compléter

 segment des données initialisées
    à compléter

 segment des données non-initialisées
    à compléter

 heap
 tas
    Zone de mémoire dans laquelle un programme peut réserver de l'espace, notamment via les fonctions `malloc(3)`_ et `calloc(3)`_ , pour stocker de l’information.

 stack
 pile
    Zone de mémoire dans laquelle sont stockés les arguments, l’ensemble des variables locales et les valeurs de retour des fonctions qui sont en cours d'exécution.

 etext
    Variable indiquant le sommet du :term:`segment text` d’un processus.

 memory leak
    Defaut d'un programme gourmand en ressource, augmentant sa mémoire allouée au lieu de la recycler, au point de consommer une quantité irraisonnable de mémoire amenant des réactions imprévisibles du système d'exploitation.

 processus
    Ensemble cohérent d'instructions utilisant une partie de la mémoire, initié par le système d'exploitation et exécuté sur un des processeurs du système. Le système d'exploitation libère les ressources qui lui sont allouées à la fin de son exécution.

 pid
 process identifier
    identifiant de processus. Sous Unix, chaque processus est identifié par un entier unique. Cet identifiant sert de clé d'accès à la :term:`table des processus`. Voir `getpid(2)`_ pour récupérer l'identifiant du processus courant.

 table des processus
    Table contenant les identifiants (:term:`pid`) de tous les processus qui s'exécutent à ce moment sur un système Unix. Outre les identifiants, cette table contient de nombreuses informations relatives à chaque :term:`processus`. Voir également :term:`/proc`

 /proc
    Sous Linux, représentation de l'information stockée dans la :term:`table des processus` sous la forme d'une arborescence directement accessible via les commandes du :term:`shell`. Voir `proc(5)`_

 signal
    Mécanisme permettant la communication entre processus. Utilisé notamment pour arrêter un processus via la commande `kill(1)`_

 von Neumann
    Un des inventeurs des premiers ordinateurs. A défini l'architecture de base des premiers ordinateurs qui est maintenant connue comme le modèle de von Neumann [Krakowiak2011]_

 mémoire
    Composant essentiel d'une architecture de type :term:`von Neumann` permettant le stockage d'information.

 SRAM
 static RAM
    Un des deux principaux types de mémoire. Dans une SRAM, l'information est mémorisée comme la présence ou l'absence d'un courant électrique. Les mémoires SRAM sont généralement assez rapides mais de faible capacité. Elles sont souvent utilisées pour construire des mémoires caches.

 DRAM
 dynamic RAM
    Un des deux principaux types de mémoire. Dans une DRAM, l'information est mémorisée comme la présence ou l'absence de charge dans un minuscule condensateur. Les mémoires DRAM sont plus lentes que les :term:`SRAM` mais ont une plus grande capacité.

 RAM
 Random Access Memory
    Mémoire vive à accès aléatoire. Mémoire permettant au processeur d'accéder à n'importe quelle donnée directement en connaissant son adresse. Voir :term:`DRAM` et :term:`SRAM`.

 registre
    Unité de mémoire intégrée au processeur. Les registres sont utilisés comme source ou destination pour la plupart des opérations effectuées par un processeur.

 hiérarchie de mémoire
    Ensemble des mémoires utilisées sur un ordinateur. Depuis les registres jusqu'à la mémoire virtuelle en passant par la mémoire centrale et les mémoires caches.

 mémoire cache
    Mémoire rapide de faible capacité. La mémoire cache peut stocker des données provenant de mémoires de plus grande capacité mais qui sont plus lentes, et exploite le :term:`principe de localité` en stockant de manière transparente les instructions et les données les plus récemment utilisées. Elle fait office d'interface entre le processeur et la mémoire principale et toutes les demandes d'accès à la mémoire principale passent par la mémoire cache, ce qui permet d'améliorer les performances de nombreux systèmes informatiques.

 principe de localité
    Voir :term:`localité spatiale` et :term:`localité temporelle`.

 localité spatiale
    à compléter

 localité temporelle
    à compléter

 lignes de cache
    à compléter

 write through
    Technique d'écriture dans les mémoires caches. Toute écriture est faite simultanément en mémoire cache et en mémoire principale. Cela garantit la cohérence entre les deux mémoires mais réduit les performances.

 write back
    Technique d'écriture dans les mémoires caches.  Toute écriture est faite en mémoire cache. La mémoire principale n'est mise à jour que lorsque la donnée modifiée doit être retirée de la cache. Cette technique permet d'avoir de meilleures performances que :term:`write through` mais il faut faire parfois attention aux problèmes qui pourraient survenir sachant que la mémoire cache et la mémoire principale ne contiennent pas toujours exactement la même information.

 eip
 pc
 compteur de programme
 instruction pointer
    Registre spécial du processeur qui contient en permanence l'adresse de l'instruction en cours d'exécution. Le contenu de ce registre est incrémenté après chaque instruction et modifié par les instructions de saut.

 mode d'adressage
    à compléter

 accumulateur
    Registre utilisé dans les premiers processeurs comme destination pour la plupart des opérations arithmétiques et logiques. Sur l'architecture [IA32]_, le registre ``%eax`` est le successeur de cet accumulateur.

 bus
    Composant central d'une architecture de :term:`von Neumann` semblable à un canal permettant de transporter de l'information d'un composant à un l'autre.

 ligne de cache
    à compléter. Voir notamment [McKenney2005]_ et  [Drepper2007]_

 write-back
    à compléter

 program counter
    à compléter

 makefile
    Fichier executable par le programme Make servant à produire des fichiers compilés à partir de code source ou plus généralement n'importe quel projet.

 fichier objet
    à compléter

 linker
    à compléter

 errno
    à compléter

 loi de Moore
    Loi empirique énoncée par Gordon E. Moore constatant que dans les microprocesseurs, le nombre de transistors sur une puce de circuit intégré double tous les dix-huit mois.

 kHz
    Fréquence de :math:`10^3` Hertz.

 MHz
    Fréquence de :math:`10^6` Hertz.

 GHz
    Fréquence de :math:`10^9` Hertz.

 MIPS
    Million d'instructions par seconde

 benchmark
    à compléter

 multi-coeurs
    à compléter

 multi-threadé
    à compléter

 section critique
    à compléter

 exclusion mutuelle
    à compléter

 sureté
 safety
    à compléter

 liveness
 vivacité
    à compléter

 multitâche
 multitasking
    à compléter

 contexte
    à compléter

 changement de contexte
    à compléter

 interruption
    à compléter

 scheduler
    à compléter

 round-robin
    à compléter

 livelock
    à compléter

 opération atomique
    Opération élémentaire ne pouvant pas être divisée.

 deadlock
    à compléter

 mutex
    à compléter

 problème des philosophes
    à compléter

 appel système
    à compléter

 appel système bloquant
    à compléter

 sémaphore
    à compléter

 problèmes des readers-writers
    à compléter

 inode
    Structure de données contenant des informations (méta-données) relatives à un fichier sur certains systèmes de fichiers (Unix par exemple). Ces informations comportent notamment les permissions associées au fichier, l'utilisateur propriétaire du fichier, le groupe du propriétaire du fichier.
    Pour plus d'informations, voir la section `Système de fichier <https://github.com/obonaventure/SystemesInformatiques/blob/master/Theorie/Fichiers/fichiers.rst#syst%C3%A8mes-de-fichiers>`_ .


 segment de données
    à compléter

 problème des readers-writers
    à compléter

 thread-safe
    Un programme est considéré thread-safe s'il fonctionne correctement lors d'une éxecution simultannée par plusieurs threads.En particulier, le programme doit satisfaire le besoin pour plusieurs threads d'accéder à la même donnée partagée entre eux et le besoin pour une donnée partagée entre threads d'être accessible par un seul thread à un moment donné. En C, on utilise notamment les :term:`mutex` ou d'autres types de locks pour résoudre ce genre de problème.


 loi de Amdahl
    à compléter

 static library
 librairie statique
    à compléter

 shared library
 librairie dynamique
 librairie partagée
    à compléter

 kernel
    à compléter

 mode utilisateur
    à compléter

 mode protégé
    à compléter

 processus père
    Processus ayant lancé un autre processus (:term:`processus fils`) suite à un appel à la fonction fork().

 processus fils
    Processus lancé suite à un appel à la fonction fork().

 processus orphelin
    :term:`Processus fils` dont le père est mort, terminé. Il est adopté par le processus numéro 1, généralement init.

 processus zombie
    :term:`Processus fils` qui a terminé son exécution mais dont le :term:`processus père` n'a pas encore récupérer le code de retour à l'aide de waitpid().

 filesystem
 système de fichiers
    à compléter

 descripteur de fichier
    à compléter

 répertoire
    à compléter

 secteur
    à compléter

 répertoire courant
    à compléter

 offset pointer
    à compléter

 little endian
    à compléter

 big endian
    à compléter

 lien symbolique
    à compléter

 lock
    à compléter

 advisory lock
 advisory locking
    à compléter

 mandatory lock
 mandatory locking
    à compléter

 open file object
    à compléter

 sémaphore nommé
    à compléter

 appel système lent
    à compléter

 handler
    à compléter

 signal synchrone
    à compléter

 signal asynchrone
    à compléter

 interpréteur
    à compléter

 MMU
 Memory Management Unit
    à compléter

 adresse virtuelle
    à compléter

 mémoire virtuelle
    à compléter

 SSD
 Solid State Drive
    Système de stockage de données s'appuyant uniquement sur de la mémoire flash.

 page
    à compléter

 table des pages
    à compléter

 bit de validité
    à compléter

 TLB
 Translation Lookaside Buffer
    à compléter

 Mémoire partagée
    à compléter

 copy-on-write
    à compléter

 adresse physique
    à compléter

 page fault
 défaut de page
    à compléter

 file FIFO
    De "First In, First Out". Le premier élement à entrer dans la file sera le premier à en sortir. (!= LIFO, "Last In First Out")

 dirty bit
 bit de modification
    à compléter

 reference bit
 bit de référence
    à compléter

 swapping
    à compléter

 pagination
    à compléter






