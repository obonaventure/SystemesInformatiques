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
       Représentation de nombre réels en virgule flottante (type ``double`` en C). La norme `IEEE754 <http://ieeexplore.ieee.org/xpl/mostRecentIssue.jsp?punumber=4610933>`_ définit le format de ces nombres sur 64 bits.

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
      Zone de mémoire contenant les instructions qui sont exécutées par le micro-processeur.

    segment des données initialisées
      Zone de mémoire contenant l'ensemble des variables globales explicitement initialisées ainsi que les constantes et chaînes de caractères utilisée par le programme.

    segment des données non-initialisées
      Zone de mémoire contenant les variables non-initialisées. Celles-ci sont initialisées à 0 par le système d'exploitation.

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
       Si une partie de la mémoire est utilisée par un programme à un moment donné, il est fort probable que les parties de mémoire proches soient utilisées prochainement par le programme (par exemple lors du parcours d'un tableau).

    localité temporelle
       Si une partie de la mémoire est utilisée par un programme à un moment donné, il est fort probable que cette partie soit réutilisée prochainement par le programme (par exemple lors de l'exécution d'une boucle).

    lignes de cache
       Plus petit élément de données qui peut être transféré entre la mémoire cache et la mémoire de niveau supérieur.

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
       Spécifie la façon dont est calculée l'adresse mémoire effective d'un opérande à partir de valeurs contenues dans des registres et de constantes contenues dans l'instruction ou ailleurs dans la machine.

    accumulateur
       Registre utilisé dans les premiers processeurs comme destination pour la plupart des opérations arithmétiques et logiques. Sur l'architecture [IA32]_, le registre ``%eax`` est le successeur de cet accumulateur.

    bus
       Composant central d'une architecture de :term:`von Neumann` semblable à un canal permettant de transporter de l'information d'un composant à un l'autre.

    program counter
       Registre du processeur qui contient l'adresse mémoire de l'instruction du programme en cours d'exécution. Il est incrémenté à chaque fois qu'une instruction est chargée et exécutée.

    makefile
       Fichier executable par le programme Make servant à produire des fichiers compilés à partir de code source ou plus généralement n'importe quel projet.

    fichier objet
       Fichier intermédiaire produit durant le processus de compilation. Il contient le code machine pour un module ou une librairie en particulier et n'a pas encore été lié avec le reste du code du projet pour former un exécutable.

    linker
       Programme qui prend en arguments un ou plusieurs fichiers objects et les combine pour former un fichier exécutable.

    errno
       Variable globale utilisée par de nombreux appels système et fonctions de la librairie standard C pour retourner un code d'erreur.

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
       Test de performance (relative) d'un programme ou système informatique.

    multi-coeurs
       Un processeur est multi-coeurs s'il contient deux ou plusieurs unités de calcul indépendantes qui peuvent travailler en parallèle.

    multi-threadé
       Un programme est multi-threadé s'il se composent de plusieurs threads d'exécution. Un processeur est dit multithread s'il est capable d'exécuter de manière efficace plusieurs threads d'exécution (chaque thread dispose par exemple de ses propres registres et compteur de programme).

    section critique
       Section de code dans laquelle il ne doit jamais y avoir plus d'un thread simultanément.

    exclusion mutuelle
       Primitive de synchronisation utilisée pour éviter que des ressources partagées d'un système ne soient utilisées en même temps.Voir :term:'mutex'

    sureté
    safety
       Deux processus ne peuvent pas utiliser la même section critique simultanément.

    liveness
    vivacité
       Toutes les requêtes d'accès à la section critique sont garanties.

    fairness
    équité
       Les requêtes d'accès sont effectuées dans l'ordre d'appel.


    multitâche
    multitasking
       Capacité de faire tourner plusieurs programmes simultanément en partageant les ressources de l'ordinateur.


    contexte
       Ensemble des données utilisées par le thread en question. Ces données sont situées dans les registres du processeur sur lequel la tâche est exécutée, dans la zone de la mémoire utilisée par la tâche ou pour certains systèmes d'exploitation, dans des registres de contrôle stockant les informations nécessaires au système pour gérer ce processus.

    changement de contexte
       Processus d'enregistrement et de restauration de l'état d'un thread ou processus par le noyau pour que son exécution puisse reprendre ultérieurement. Un changement de contexte est par exemple effectué lorsque le noyau/scheduler provoque la transition d'un processus à un autre, ou lorsqu'une interruption force l'exécution d'une routine du noyau.

    interruption
       Signal logiciel ou matériel envoyé au processeur pour l'informer d'un évènement qui requiert son attention immédiate. Lorsqu'il reçoit une interruption, le processeur sauvegarde son état (changement de contexte) et exécute une routine de traitement d'interruption. Lorsque la routine de traitement d'interruption termine, le processeur reprend son exécution normale.

    scheduler
       Algorithme du noyau du système d'exploitation qui décide à tout moment quel processus doit être exécuté.

    round-robin
       Dans le cadre du scheduler, il s'agit d'un algorithme qui alloue à tour de rôle un temps d'exécution égal à chaque processus sans distinction aucune.

    livelock
       Dans un programme concurrent, une situation de livelock est une situation de non-progression qui survient lorsque plusieurs threads ou processus concurrents changent continuellement d'état en simultanés et qu'aucuns ne progressent.

    opération atomique
       Opération élémentaire ne pouvant pas être divisée.

    deadlock
       Dans un programme concurrent, une situation de deadlock est une situation de blocage définitif qui survient lorsque que plusieurs threads ou processus concurrents s'attendent mutuellement. Chacun attend que l'autre finisse et donc aucun ne finit jamais.

    mutex
       Primitive de synchronisation entre threads basé sur le principe d'exclusion mutuelle. Quand plusieurs threads veulent accéder à la même ressource ou section critique, un mutex peut protéger cette ressource ou section critique et assurer qu'un seul thread ne puisse y accèder à tout moment.

    problème des philosophes
       Problème sur le partage de ressources en informatique. Il concerne l'ordonnancement des processus et l'allocation des ressouces à ces derniers.

    appel système
       Permet à un programme de demander l'exécution d'un service fourni par le noyau du système d'exploitation.

    appel système bloquant
       Un appel sysème bloquant mets un processus en attente (état W) et ne le réveillera (état R) que lorsque cet appel système sera prêt à retourner

    sémaphore
       Mécanisme de synchronisation entre threads inventé par Edsger Dijkstra pour limiter le nombre de threads qui peuvent accèder de manière concurrente à une ressource partagée.

    problèmes des readers-writers
       Modélise un problème qui survient lorsque des threads (readers et writers) doivent accèder à une base de données.

    inode
       Structure de données contenant des informations (méta-données) relatives à un fichier sur certains systèmes de fichiers (Unix par exemple). Ces informations comportent notamment les permissions associées au fichier, l'utilisateur propriétaire du fichier, le groupe du propriétaire du fichier.
       Pour plus d'informations, voir la section `Système de fichier <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Fichiers/fichiers.html#systemes-de-fichiers>`_ .

    thread-safe
       Un programme est considéré thread-safe s'il fonctionne correctement lors d'une éxecution simultannée par plusieurs threads.En particulier, le programme doit satisfaire le besoin pour plusieurs threads d'accéder à la même donnée partagée entre eux et le besoin pour une donnée partagée entre threads d'être accessible par un seul thread à un moment donné. En C, on utilise notamment les :term:`mutex` ou d'autres types de locks pour résoudre ce genre de problème.


    loi de Amdahl
       à compléter

    static library
    librairie statique
       Librairie destinée à être copiée dans les programmes qui l'utilisent lors de la constructions de ces derniers.

    shared library
    librairie dynamique
    librairie partagée
       Librairie destinée à être associée aux programmes où ils sont exécutés. Avec une librairie dynamique, la même copie de la librairie peut être utilisée par plusieurs programmes.

    kernel
       à compléter

    mode utilisateur
       En mode utilisateur, le code exécuté n'a pas la possibilité d'accéder directement au matériel ou à la mémoire. Il faut passer par les API du système pour accéder le matériel ou la mémoire. Grâce à cette protection, qui est une sorte d'isolation, les crashs en mode utilisateur sont toujours récupérable.

    mode protégé
       En mode protégé, le code exécuté a un accès complet au matériel sous-jacent. Il peut exécuter n'importe quelle instruction CPU et référencer n'importe quelle adresse mémoire.

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
       Facon de stocker les informations et de les organiser dans des fichiers sur ce que l'on appelle des mémoires secondaires (exemple : disque dur, SSD, CD-ROM, USB,...).

    descripteur de fichier
       Clés abstraite pour accéder à un fichier.

    répertoire
       Fichier spécial contenant les noms et inodes d'autres fichiers et répertoires.

    secteur
       Plus petite unité physique de stockage pour un support de données.

    répertoire courant
       Répertoire dans lequel le processus en cours d'exécution ouvrira les fichiers via open.

    offset pointer
       Valeur entière représentant le déplacement en mémoire nécessaire, par rapport à une adresse de référence pour atteindre une autre adresse. C'est la distance séparant deux emplacements mémoire.

    little endian
       L'octet de poids le plus faible est enregistré à l'adresse mémoire la plus petite, l'octet de poids supérieur est enregistré à l'adresse mémoire suivante et ainsi de suite.

    big endian
       L'octet de poids le plus fort est enregistré à l'adresse mémoire la plus petite, l'octet de poids inférieur est enregistré à l'adresse mémoire suivante et ainsi de suite.

    lien symbolique
       à compléter

    lock
       Permet à un processus d'obtenir l'accès exclusif à un fichier ou une partie de fichier.

    advisory lock
    advisory locking
       Les processus doivent vérifier eux-mêmes que les accès qu'ils effectuent ne violent pas les locks qui ont été associés aux différents fichier.

    mandatory lock
    mandatory locking
       Dans ce cas, les processus placent des locks sur certains fichiers ou zones de fichiers et le système d’exploitation vérifie qu’aucun accès fait aux fichiers avec les appels systèmes standards ne viole ces locks.

    open file object
       Contient toutes les informations qui sont nécessaires au noyau pour pouvoir effectuer les opérations de manipulation d'un fichier ouvert par un processus.

    sémaphore nommé
       Sémaphore utilisant une zone mémoire qui est gérée par le noyau et qui peut être utilisée par plusieurs processus.

    appel système lent
       Appel système dont l'exécution peut être interrompue par la réception d'un signal. (Exemple : open(2), write(2), sendto(2), recvfrom(2), sendmsg(2), recvmsg(2), wait(2) ioctl(2))

    handler
       Un handler est associé à un signal et est exécuté dès que ce signal survient.

    signal synchrone
       Signal qui a été directement causé par l'exécution  d'une instruction du processus.

    signal asynchrone
      Signal qui n’a pas été directement causé par l’exécution d’une instruction du processus.

    interpréteur
       Outil ayant pour tâche d'analyser, de traduire et d'exécuter les programmes écrits dans un langage informatique.

    MMU
    Memory Management Unit
       Traduit toute adresse virtuelle en adresse physique.

    adresse virtuelle
       Adresse qui est utilisée à l’intérieur d’un programme

    mémoire virtuelle
       Repose sur l'utilisation de traduction des adresses virtuelles en adresses physiques.

    SSD
    Solid State Drive
       Système de stockage de données s'appuyant uniquement sur de la mémoire flash.

    page
       Bloc de mémoire virtuelle.

    table des pages
       Structure de données utilisée pour stocker les liens entre adresses virtuelles et adresses physiques.

    bit de validité
       Permet de voir la validité ou non d'un numéro de frame à la page actuelle. Si celui-ci est à 0, cela signigie que le numéro de frame est invalide.

    TLB
    Translation Lookaside Buffer
       Mémoire cache du processeur utilisée par l'unité de gestion mémoire (:term:'MMU') dans le but d'accélérer la traduction des adresses virtuelles en adresses physiques.

    Mémoire partagée
       Moyen de partager des données entre différents processus : une même zone de la mémoire vive est accédée par plusieurs processus.

    copy-on-write
       à compléter

    adresse physique
       Adresse utilisée par des puces de RAM pour les opérations d'écriture et de lecture.

    page fault
    défaut de page
       Erreur de page introuvable en mémoire. Plus précisément, interruption qui suspend l'exécution d'un processus pour éventuellement lui libérer de la mémoire vive en la déchargeant dans la mémoire virtuelle, mais surtout le charger dans la RAM ensuite, en modifiant son bit de validation à un.

    file FIFO
       De "First In, First Out". Le premier élement à entrer dans la file sera le premier à en sortir. (!= LIFO, "Last In First Out")

    dirty bit
    bit de modification
       Bit indiquant si une page a été modifiée depuis son chargement en mémoire vive. Il est donc égal à zéro si un processus a déjà figuré dans la mémoire virtuelle, et à un si la page a été modifiée depuis son chargement ou si elle est nouvellement allouée.

    reference bit
    bit de référence
       Bit indiquant si une page a été accédée récemment, il est remis à 0 régulièrement.

    swapping
       Toutes  les données appartenant au processus seront stockées en mémoire de masse.

    pagination
       Technique permettant de découper la mémoire vive en zones (:term:'page') et change la correspondance entre mémoire virtuelle et mémoire physique.

    stratégie de remplace de pages
       Définit quelle page doit être préférentiellement retirée de la mémoire RAM et placée sur le dispositif de stockage.
