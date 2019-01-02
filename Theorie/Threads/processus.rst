.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. _processus:


Les processus
=============

Un système d'exploitation multitâche et multi-utilisateurs tel que Unix ou Linux permet d'exécuter de nombreux programmes simultanément. Sous Unix, les programmes sont exécutés sous la forme de :term:`processus`. Un processus peut être défini comme étant une instance de programme qui est en train d'être exécutée sur un ou plusieurs processeurs sous le contrôle d'un système d'exploitation. Un processus comprend donc un ensemble d'instructions pour le processeur, mais aussi des données qui sont stockées en mémoire et un contexte (si le processus utilise un seul thread d'exécution, plusieurs contextes sinon). En outre, le système d'exploitation maintient un certain nombre de structures de données qui sont nécessaires au bon fonctionnement du processus. Ces structures de données sont créées au démarrage du processus, mises à jour durant la vie du processus et supprimées lorsque le processus se termine.


Les librairies
--------------

Lorsqu'un programme s'exécute à l'intérieur d'un processus, il exécute des instructions qui ont différentes `origines`. Il y a bien entendu les instructions qui proviennent du code source du programme qui a été converti en assembleur par le compilateur. Ces instructions correspondent au code source développé par le programmeur. Il s'agit notamment de toutes les opérations mathématiques et logiques, les boucles et les appels de fonctions internes au programme. Comme nous l'avons vu précédemment, ces instructions peuvent provenir d'un seul module ou de plusieurs modules. Dans ce dernier cas, le linker intervient pour combiner différents modules en un exécutable complet.

A côté des instructions qui correspondent aux lignes de code écrites par le développeur du programme, un processus va également exécuter de nombreuses fonctions qui font partie d'une des librairies standard du système. Tout environnement de développement comprend des librairies qui permettent de faciliter le travail des programmeurs en leur fournissant des fonctions permettant de résoudre de nombreux problèmes classiques. Un système d'exploitation tel que Unix ou Linux contient de nombreuses librairies de ce type. Nous avons déjà eu l'occasion de discuter des fonctions provenant de la librairie standard comme `printf(3)`_ ou `malloc(3)`_ et celles de la librairie `pthreads(7)`_. Ce ne sont que deux librairies parmi d'autres. Un système Linux contient plusieurs centaines de librairies utilisables par le programmeur.

A titre d'exemple, considérons la librairie `math.h(7posix)`_. Cette librairie contient de nombreuses fonctions mathématiques. Pour les utiliser dans un programme, il faut non seulement y inclure le fichier header `math.h`_ qui contient les prototypes et constantes utilisées par la librairie, mais aussi indiquer au linker que l'exécutable doit être lié avec la librairie `math.h(7posix)`_. Cela se fait en utilisant le flag ``-l`` de `gcc(1)`_.

.. literalinclude:: /Threads/S8-src/math.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Le programme :download:`/Threads/S8-src/math.c` ci-dessus doit être compilé en utilisant la commande ``gcc -Wall -Werror math.c -o math -lm``. Le paramètre ``-lm`` indique au compilateur qu'il doit charger la librairie ``m``. Cette librairie, est une des librairies standard du système, elle réside généralement dans le répertoire ``/usr/lib`` [#flib]_. En pratique, `gcc(1)`_ charge automatiquement la librairie ``C`` standard lors de la compilation de tout programme. Cela revient à utiliser implicitement le paramètre ``-lc``.

Lors de l'utilisation de telles librairies, on s'attendrait à ce que toutes les instructions correspondant aux fonctions de la librairie utilisée soient présentes à l'intérieur de l'exécutable. En pratique, ce n'est pas exactement le cas. Même si notre programme d'exemple utilise `fmax(3)`_ de la librairie `math.h(7posix)`_ et `printf(3)`_ de la librairie standard, son exécutable ne contient que quelques milliers d'octets.

.. code-block:: console

  $ ls -l math*
  -rwxr-xr-x 1 obo stafinfo 6764 Mar 15  2012 math
  -rw-r--r-- 1 obo stafinfo  373 Mar 15  2012 math.c

Une analyse plus détaillée de l'exécutable avec `objdump(1)`_ révèle que si l'exécutable contient bien des appels à ces fonctions, leur code n'y est pas entièrement inclus.

.. code-block:: console

   $gcc -g -lm math.c -o math
   $objdump -S -d math
   math:     file format elf64-x86-64
   ...
   0000000000400468 <fmax@plt>:
   400468:	ff 25 fa 04 20 00    	jmpq   *0x2004fa(%rip)        # 600968 <
   _GLOBAL_OFFSET_TABLE_+0x28>
   40046e:	68 02 00 00 00       	pushq  $0x2
   400473:	e9 c0 ff ff ff       	jmpq   400438 <_init+0x18>
   ...
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    int main (int argc, char *argv[])  {
   400564:	55                   	push   %rbp
   400565:	48 89 e5             	mov    %rsp,%rbp
   400568:	48 83 ec 20          	sub    $0x20,%rsp
   40056c:	89 7d ec             	mov    %edi,-0x14(%rbp)
   40056f:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    double n1=1.0;
   400573:	48 b8 00 00 00 00 00 	mov    $0x3ff0000000000000,%rax
   40057a:	00 f0 3f
   40057d:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    double n2=-3.14;
   400581:	48 b8 1f 85 eb 51 b8 	mov    $0xc0091eb851eb851f,%rax
   400588:	1e 09 c0
   40058b:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    printf("Maximum : %f\n",fmax(n1,n2));
   40058f:	f2 0f 10 4d f8       	movsd  -0x8(%rbp),%xmm1
   400594:	f2 0f 10 45 f0       	movsd  -0x10(%rbp),%xmm0
   400599:	e8 ca fe ff ff       	callq  400468 <fmax@plt>
   40059e:	b8 b8 06 40 00       	mov    $0x4006b8,%eax
   4005a3:	48 89 c7             	mov    %rax,%rdi
   4005a6:	b8 01 00 00 00       	mov    $0x1,%eax
   4005ab:	e8 98 fe ff ff       	callq  400448 <printf@plt>
    return(EXIT_SUCCESS);
   4005b0:	b8 00 00 00 00       	mov    $0x0,%eax
    }

La taille réduite des exécutables sous Linux et de nombreuses variantes de Unix s'explique par l'utilisation de librairies partagées. Un programme peut utiliser deux types de librairies : des librairies statiques et des librairies partagées. Une :term:`librairie statique` (ou :term:`static library` en anglais) est une librairie de fonctions qui est intégrée directement avec le programme. Elle fait entièrement partie de l'exécutable. C'est la première solution pour intégrer des librairies dans un programme. Son avantage principal est que l'exécutable est complet et comprend toutes les instructions qui sont nécessaires au fonctionnement du programme. Malheureusement, tous les programmes qui utilisent des fonctions d'une librairie courante, comme par exemple la librairie standard, doivent inclure le code relatif à toutes les fonctions qu'ils utilisent. Sachant que chaque programme ou presque utilise des fonctions comme `printf(3)`_, cela conduit à sauvegarder de très nombreuses copies du même code. Ce problème peut être résolu en utilisant des librairies partagées [#fdynamic]_ . Une :term:`librairie partagée` (ou :term:`shared library` en anglais) est un ensemble de fonctions qui peuvent être appelées par un programme mais sont stockées dans un seul fichier sur disque. Ce fichier unique est utilisé automatiquement par tous les programmes qui utilisent des fonctions de la librairie.

Il est parfois intéressant de pouvoir créer une librairie qui peut être liée de façon statique avec des programmes, par exemple lorsque ceux-ci doivent être exécutés sur d'autres ordinateurs que ceux sur lesquels ils ont été compilés. A titre d'illustration, considérons une librairie minuscule contenant une seule fonction ``imax`` qui calcule le maximum entre deux entiers. L'implémentation de cette fonction est très simple.

.. literalinclude:: /Threads/S8-src/imax.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB


Cette fonction est déclarée dans le fichier header ``imax.h`` et peut être utilisée dans un programme comme ci-dessous.

.. literalinclude:: /Threads/S8-src/imath.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

En pratique, la construction d'une librairie se fait en deux étapes principales. Tout d'abord, il faut compiler les fichiers objet correspondant aux différents modules de la librairie. Cela peut se faire avec `gcc(1)`_ comme pour un programme C classique. Ensuite, il faut regrouper les différents modules dans une archive qui constituera la librairie qui peut être utilisée par des programmes. Par convention, toutes les librairies ont un nom qui commence par ``lib`` et se termine par l'extension ``.a``. Sous Linux, cette opération est réalisée par l'utilitaire `ar(1)`_. La page de manuel de `ar(1)`_ décrit plus en détails son utilisation. En pratique, les opérations les plus fréquentes avec `ar(1)`_ sont :

 - ajout d'un module objet à une librairie : ``ar r libname.a module.o``
 - suppression d'un module objet d'une librairie : ``ar d libname.a module.o``

Il est aussi possible de lister le contenu de la librairie ``libname.a`` avec la commande ``ar tv libname.a``.

L'archive contenant la librairie peut être liée en utilisant le linker à n'importe quel programme qui en utilise une ou plusieurs fonctions. Le linker de `gcc(1)`_ peut effectuer cette opération comme illustré par le ``Makefile`` ci-dessous. Il faut noter que l'argument ``--static`` permet de forcer le compilateur à inclure le code de la librairie dans l'exécutable.

.. literalinclude:: /Threads/S8-src/Makefile-lib
   :encoding: utf-8
   :language: makefile

Ce ``Makefile`` est un petit peu plus long que ceux que nous avons utilisés jusque maintenant. Il illustre une structure courante pour de nombreux fichiers ``Makefile``. La première partie définit des constantes qui sont utilisées dans le reste du ``Makefile``. Il s'agit tout d'abord du compilateur et du programme de construction de librairies qui sont utilisés. Définir ces programmes comme des constantes dans le ``Makefile`` permet de facilement en changer lorsque c'est nécessaire. Ensuite, trois constantes sont définies avec les arguments de base du compilateur et de ``ar``. A nouveau, définir ces constantes une fois pour toutes facilite leur modification. Ensuite, la première cible est la cible ``all:``. Comme c'est la première, c'est la cible par défaut qui sera utilisée lorsque `make(1)`_ est appelé sans argument. Elle dépend de l'exécutable ``imath`` qui est une des cibles du ``Makefile``. La cible ``clean:`` permet d'effacer les fichiers objet et exécutables construites par le ``Makefile``. Il est utile d'avoir une telle cible lorsque l'on doit diffuser un projet en C ou le rendre dans le cadre d'un cours. Enfin, les autres cibles correspondent aux fichiers objet, à la librairie et à l'exécutable qui sont construits. La commande ``@echo`` affiche ses arguments sur la sortie standard. Enfin, la chaîne de caractères ``$(GCC)`` est remplacée par le constante définie au début du fichier. Des compléments d'information sur `make(1)`_ peuvent être obtenus dans divers documents dont `make(1)`_, [Mecklenburg+2004]_ ou [GNUMake]_.

Lorsqu'un programme est compilé de façon à utiliser une librairie dynamique, c'est le système d'exploitation qui analyse le programme lors de son chargement et intègre automatiquement les fonctions des librairies qui sont nécessaires à son exécution. L'entête de l'exécutable contient de l'information générée par le compilateur qui permet de localiser les librairies dynamiques qui doivent être intégrées de cette façon. L'utilitaire `ldd(1)`_ permet de visualiser quelles sont les librairies partagées utilisées par un programme.

.. code-block:: console

        $ ldd imath
	linux-vdso.so.1 =>  (0x00007fffe41ff000)
	libc.so.6 => /lib64/libc.so.6 (0x0000003eb2400000)
	/lib64/ld-linux-x86-64.so.2 (0x0000003eb2000000)


Appels Système
---------------
.. index:: kernel

Outre l'utilisation de fonctions de librairies, les programmes doivent interagir avec le système d'exploitation. Un système d'exploitation tel que Unix comprend à la fois des utilitaires comme `grep(1)`_, `ls(1)`_, ... qui sont directement exécutables depuis le shell et un noyau ou :term:`kernel` en anglais. Le :term:`kernel` contient les fonctions de base du système d'exploitation qui lui permettent à la fois d'interagir avec le matériel mais aussi de gérer les processus des utilisateurs. En pratique, le kernel peut être vu comme étant un programme spécial qui est toujours présent en mémoire. Parmi l'ensemble des fonctions contenues dans le :term:`kernel`, il y en a un petit nombre, typiquement de quelques dizaines à quelques centaines, qui sont utilisables par les processus lancés par les utilisateurs. Ce sont les appels système. Un :term:`appel système` est une fonction du :term:`kernel` qui peut être appelée par n'importe quel processus. Comme nous l'avons vu lorsque nous avons décrit le fonctionnement du langage d'assemblage, l'exécution d'une fonction dans un programme comprend plusieurs étapes :

 1. Placer les arguments de la fonction à un endroit (la pile) où la fonction peut y accéder
 2. Sauvegarder sur la pile l'adresse de retour
 3. Modifier le registre ``%eip`` de façon à ce que la prochaine instruction à exécuter soit celle de la fonction à exécuter
 4. La fonction récupère ses arguments (sur la pile) et réalise son calcul
 5. La fonction sauve son résultat à un endroit (``%eax``) convenu avec la fonction appelante
 6. La fonction récupère l'adresse de retour sur la pile et modifie ``%eip`` de façon à retourner à la fonction appelante

L'exécution d'un appel système comprend les mêmes étapes avec une différence importante c'est que le flux d'exécution des instructions doit passer du programme utilisateur au noyau du système d'exploitation. Pour comprendre le fonctionnement et l'exécution d'un appel système, il est utile d'analyser les six points mentionnés ci-dessus.

Le premier problème à résoudre pour exécuter un appel système est de pouvoir placer les arguments de l'appel système dans un endroit auquel le :term:`kernel` pourra facilement accéder. Il existe de nombreux appels systèmes avec différents arguments. La liste complète des appels systèmes est reprise dans la page de manuel `syscalls(2)`_. La table ci-dessous illustre quelques appels systèmes et leurs arguments.

==============            =====================
Appel système             Arguments
==============            =====================
`getpid(2)`_              ``void``
`fork(2)`_                ``void``
`read(2)`_		  ``int fildes, void *buf, size_t nbyte``
`kill(2)`_		  ``pid_t pid, int sig``
`brk(2)`_ 		  ``const void *addr``
==============            =====================

Sous Linux, les arguments d'un appel système sont placés par convention dans des registres. Sur [IA32]_, le premier argument est placé dans le registre ``%ebx``, le second dans ``%ecx``, ... Le :term:`kernel` peut donc facilement récupérer les arguments d'un appel système en lisant le contenu des registres.

Le second problème à résoudre est celui de l'adresse de retour. Celle-ci est automatiquement sauvegardée lors de l'exécution de l'instruction qui fait appel au kernel, tout comme l'instruction ``calll`` sauvegarde directement l'adresse de retour d'une fonction appelée sur la pile.

.. index:: mode utilisateur, mode protégé

Le troisième problème à résoudre est de passer de l'exécution du processus utilisateur à l'exécution du :term:`kernel`. Les processeurs actuels peuvent fonctionner dans au minimum deux modes : le :term:`mode utilisateur` et le :term:`mode protégé`. Lorsque le processeur fonctionne en mode protégé, toutes les instructions du processeur et toutes les adresses mémoire sont utilisables. Lorsqu'il fonctionne en mode utilisateur, quelques instructions spécifiques de manipulation du matériel et certaines adresses mémoire ne sont pas utilisables. Cette  division en deux modes de fonctionnement permet d'avoir une séparation claire entre le système d'exploitation et les processus lancés par les utilisateurs. Le noyau du système d'exploitation s'exécute en mode protégé et peut donc utiliser entièrement le processeur et les dispositifs matériels de l'ordinateur. Les processus utilisateurs par contre s'exécutent en mode utilisateur. Ils ne peuvent donc pas directement exécuter les instructions permettant une interaction avec des dispositifs matériel. Cette interaction doit passer par le noyau du système d'exploitation qui sert de médiateur et vérifie la validité des demandes faites par un processus utilisateur.

.. index:: init

Les transitions entre les modes protégé et utilisateur sont importantes car elles rythment le fonctionnement du système d'exploitation. Lorsque l'ordinateur démarre, le processeur est placé en mode protégé et le :term:`kernel` se charge. Il initialise différentes structures de données et lance `init(8)`_ le premier processus du système. Dès que `init(8)`_ a été lancé, le processeur passe en mode utilisateur et exécute les instructions de ce processus. Après cette phase de démarrage, les instructions du :term:`kernel` seront exécutées lorsque soit une interruption matérielle surviendra ou qu'un processus utilisateur exécutera un appel système. L'interruption matérielle place automatiquement le processeur en mode protégé et le :term:`kernel` exécute la routine de traitement d'interruption correspondant à l'interruption qui est apparue. Un appel système démarre par l'exécution d'une instruction spéciale (parfois appelée interruption logicielle) qui place le processeur en mode protégé et puis démarre l'exécution d'une instruction placée à une adresse spéciale en mémoire. Sur certains processeurs de la famille [IA32]_, l'instruction ``int 0x80`` permet ce passage du mode utilisateur au mode protégé. Sur d'autres processeurs, c'est l'instruction ``syscall`` qui joue ce rôle. L'exécution de cette instruction est la seule possibilité pour un programme d'exécuter des instructions du :term:`kernel`. En pratique, cette instruction fait passer le processeur en mode protégé et démarre l'exécution d'une routine du :term:`kernel`. Cette routine commence par sauvegarder le contexte du processus qui exécute l'appel système demandé. Chaque appel système est identifié par un nombre entier et le :term:`kernel` contient une table avec pour chaque appel système l'adresse de la fonction à exécuter pour cet appel système. En pratique, le numéro de l'appel système à exécuter est placé par le processus appelant dans le registre ``%eax``.

L'appel système peut donc s'exécuter en utilisant les arguments qui se trouvent dans les différents registres. Lorsque l'appel système se termine, le résultat est placé dans le registre ``%eax`` et une instruction spéciale permet de retourner en mode utilisateur et d'exécuter dans le processus appelant l'instruction qui suit celle qui a provoqué l'exécution de l'appel système. Si l'appel système a échoué, le :term:`kernel` doit aussi mettre à jour le contenu de ``errno`` avant de retourner au processus appelant.

Ces opérations sont importantes pour comprendre le fonctionnement d'un système informatique et la différence entre un appel système et une fonction de la librairie. En pratique, la librairie cache cette complexité au programmeur en lui permettant d'utiliser des fonctions de plus haut niveau [#fsyscall]_ . Cependant, il faut être conscient que ces fonctions s'appuient elles-même sur des appels systèmes pour s'exécuter. Ainsi par exemple, la fonction `printf(3)`_ utilise l'appel système `write(2)`_ pour écrire sur la sortie standard. La commande `strace(1)`_ permet de tracer l'ensemble des appels systèmes faits par un processus. A titre d'exemple, voici les appels systèmes effectués par le programme ``imath`` présenté plus haut.

.. code-block:: console

 $ strace ./imath
 execve("./imath", ["./imath"], [/* 34 vars */]) = 0
 uname({sys="Linux", node="baluran.info.ucl.ac.be", ...}) = 0
 brk(0)                                  = 0xa31000
 brk(0xa32180)                           = 0xa32180
 arch_prctl(ARCH_SET_FS, 0xa31860)       = 0
 brk(0xa53180)                           = 0xa53180
 brk(0xa54000)                           = 0xa54000
 fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0)  = 0x7f1f8fd44000
 write(1, "Maximum : 1\n", 12Maximum : 1
 )           = 12
 exit_group(0)                           = ?


.. Ces opérations sont réalisées en utilisant des appels systèmes. Lors de son exécution un programme exécute non seulement des instructions qui ont été compilées sur base du code source du programme, mais aussi des fonctions faisant partie d'une des librairies standard du système. Certaines librairies contiennent des fonctions indépendantes, comme la librairie mathématique, d'autres font appel au système d'exploitation directement ou indirectement. font partie du programme, ce sont les peut faire appels à trois petits de fonctions prin Dans les chapitres précédents, nous avons développé des programmes qui d'abord utilisaient des fonctions faisant partie Jusque maintenant, nous


.. index:: fork

Création d'un processus
-----------------------

Pour comprendre le fonctionnement de Unix, il est utile d'analyser plus en détails toutes les opérations qui sont effectuées à chaque fois que l'on lance un programme depuis un shell tel que `bash(1)`_. Considérons l'exécution de la commande ``/bin/true`` depuis le shell.

Schématiquement, l'exécution de ce programme se déroule comme suit. Le shell va d'abord localiser [#fpath]_ l'exécutable ``/bin/true`` qui est stocké dans le système de fichiers. Ensuite, il va créer un processus et y exécuter l'exécutable. Le shell va ensuite attendre la fin de l'exécution du programme ``true`` et récupérer sa valeur de retour (retournée par `exit(2)`_) pour ensuite poursuivre son exécution.


.. todo:: figure à ajouter plus tard pour illustrer ce fonctionnement

Comme nous l'avons expliqué plus haut, le :term:`kernel` Linux gère l'ensemble des processus qui sont utilisés à un moment. Il intervient pour toutes les opérations de création et de fin d'un processus. La création d'un processus est un événément important dans un système d'exploitation. Elle permet notamment l'exécution de programmes. Ces opérations nécessitent une interaction avec le :term:`kernel` et se font donc en utilisant des appels systèmes. Avant d'analyser en détails comment Linux supporte précisément la création de processus, il est intéressant de réfléchir aux opérations qui doivent être effectuées lors de l'exécution d'un programme. Considérons par exemple un utilisateur qui exécute la commande ``/usr/bin/expr 1 + 2`` depuis un shell `bash(1)`_ interactif. Pour exécuter cette commande, il va falloir exécuter un nouveau processus contenant les instructions assembleur se trouvant dans l'exécutable ``/usr/bin/expr``, lui passer les arguments ``1 + 2``, l'exécuter, récupérer sa valeur de retour et la retourner au shell qui pourra l'utiliser et poursuivre son exécution.

.. index:: processus père, processus fils

Les designers de Unix ont choisi de construire un appel système pour chacune de ces opérations. Le premier est l'appel système `fork(2)`_. C'est l'appel système qui permet de créer un processus. Schématiquement, cet appel système crée une copie complète du processus qui l'a exécuté. Après exécution de `fork(2)`_, il y a deux copies du même processus en mémoire. Le processus qui a exécuté `fork(2)`_ est considéré comme étant le :term:`processus père` tandis que celui qui a été créé par l'exécution de `fork(2)`_ est le :term:`processus fils`.

.. code-block:: c

   #include <unistd.h>

   pid_t fork(void);


L'appel système `fork(2)`_ est atypique car il est exécuté par un processus mais provoque la création d'un second processus qui est identique au premier. Après l'exécution de l'appel système `fork(2)`_, il y a donc deux séquences d'instructions qui vont s'exécuter, l'une dans le processus père et l'autre dans le processus fils. Le processus fils démarre son exécution à la récupération du résultat de l'appel système `fork(2)`_ effectué par son père. Le processus père et le processus fils récupèrent une valeur de retour différente pour cet appel système. Cette valeur de retour est d'ailleurs la seule façon de distinguer le :term:`processus père` du :term:`processus fils` lorsque celui-ci démarre.

 - l'appel système `fork(2)`_ retourne la valeur ``-1`` en cas d'erreur et met à jour la variable ``errno``. En cas d'erreur, aucun processus n'est créé.
 - l'appel système `fork(2)`_ retourne la valeur ``0`` dans le processus fils.
 - l'appel système `fork(2)`_ retourne une valeur positive dans le processus père. Cette valeur est l'identifiant du processus fils créé.

Pour bien comprendre le fonctionnement de `fork(2)`_, analysons l'exemple :download:`/Threads/S8-src/fork.c` ci-dessous :

.. literalinclude:: /Threads/S8-src/fork.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Lors de son exécution, ce programme affiche les deux lignes suivantes sur sa sortie standard :

.. literalinclude:: /Threads/S8-src/fork.out
   :encoding: utf-8
   :language: console

Lors de l'exécution de ce programme, deux variables sont initialisées en mémoire. La variable globale ``g`` est initialisée à la valeur ``0`` tandis que le variable locale ``l`` est initialisée à la valeur ``1252``. `malloc(3)`_ est utilisé pour réserver une zone mémoire sur le :term:`heap` et son contenu est initialisé à ``-1``. Lorsque le processus père fait appel à `fork(2)`_ le noyau du système d'exploitation crée une copie identique à celui-ci en mémoire. Cette copie contient tous les segments du processus père (code, données, heap et stack) dans l'état exact dans lequel ils étaient au moment de l'exécution de l'appel système `fork(2)`_. Le contexte du processus père est copié et devient le contexte du processus fils. A cet instant, les deux processus sont complètement identiques à l'exception de certaines données qui sont maintenues par le système d'exploitation, comme l'identifiant de processus. Chaque processus qui s'exécute sur un système Unix a un identifiant unique et est retourné par l'appel système `getpid(2)`_. Le processus père et le processus fils ont un identifiant différent.

Les deux processus vont se différencier dès la fin de l'exécution de l'appel système `fork(2)`_. Comme tout appel système, `fork(2)`_ place sa valeur de retour dans le registre ``%eax``. Comme indiqué plus haut, cette valeur sera positive dans le processus père. Celui-ci exécute ``sleep(2);`` et reste donc bloqué pendant deux secondes avant d'afficher un message sur sa sortie standard. Le processus fils de son côté incrémente les variables ``l`` et ``g`` et modifie la zone mémoire pointée par ``*m`` puis affiche leur contenu sur sa sortie standard puis se termine.

L'exécution de ce programme illustre bien que le processus fils démarre avec une copie du processus père lorsque l'appel système `fork(2)`_ se termine. Le processus fils peut modifier les variables qui ont été initialisées par le processus mais ces modifications n'ont aucun impact sur les variables utilisées dans le processus père. Même si le processus père et le processus fils sont identiques au moment de la création du processus fils, ils sont complètement indépendants par après. C'est une différence importante avec les threads. Contrairement à ce qu'il se passe avec les threads, un processus père et un processus fils ne partagent ni le segment de données, ni le heap ni le stack. Ces zones mémoires ne peuvent pas être utilisées directement pour permettre à un processus père de communiquer avec son fils.


.. note:: Quel est le processus qui s'exécute en premier après `fork(2)`_ ?

 Après l'exécution de l'appel système `fork(2)`_ et la création du processus fils, le :term:`kernel` se trouve face à deux processus qui sont dans l'état `Ready`. Si il y a deux processeurs libres, le :term:`kernel` pourra les démarrer quasi simultanément. Par contre, si un seul processeur est disponible, le :term:`kernel` devra exécuter l'un des deux processus en premier. En pratique, rien ne permet de contrôler si le :term:`kernel` commencera d'abord l'exécution du processus père ou l'exécution du processus fils. Tout programme utilisant `fork(2)`_ doit pouvoir fonctionner correctement quel que soit l'ordre d'exécution des processus père et fils.

Le :term:`kernel` gère les processus et attribue un identifiant à chaque processus. Le type ``pid_t`` est utilisé pour les identifiants de processus sous Unix. Ce type correspond à un nombre entier généralement non-signé. Le nombre maximum de processus qui peuvent être lancés sur un système Linux est un des paramètres fixés à la compilation ou au démarrage du kernel. L'appel système `getpid(2)`_ retourne l'identifiant du processus courant tandis que l'appel système `getppid(2)`_ retourne l'identifiant du processus père.

.. literalinclude:: /Threads/S8-src/getpid.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Après l'exécution de `fork(2)`_ le processus père et le processus fils ont un identifiant de processus différent mais ils partagent certaines ressources qui sont gérées par le :term:`kernel`. C'est le cas notamment des flux standard :term:`stdin`, :term:`stdout` et :term:`stderr`. Lorsque le :term:`kernel` crée un processus fils, il conserve la même sortie standard que le processus père. C'est ce qui nous permet de visualiser le résultat de l'exemple précédent. Cependant, le processus père et le processus fils sont en concurrence pour écrire sur la sortie standard. Si aucune précaution n'est prise, ces deux processus risquent d'écrire de façon désordonnée sur la sortie standard.

Pour mieux comprendre le problème, analysons l'exécution du programme ci-dessous. Il crée un processus fils puis le père et le fils écrivent sur :term:`stdout`.

.. literalinclude:: /Threads/S8-src/fork-buf.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Lors de son exécution, il affiche les lignes suivantes sur :term:`stdout`.

.. code-block:: console

 $ ./fork-buf
 Processus : 852
 Processus : 853
 PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
 ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff

A première vue, on pourrait penser qu'il n'y a pas de problèmes d'accès concurrents à :term:`stdout` puisque la sortie produite par ce programme semble claire. Cependant, la fonction ``output`` utilisée par le père et le fils pour afficher les caractères ``P`` et ``f`` devrait permettre aux deux processus d'afficher des caractères ``P`` et ``f`` avec une certaine alternance. Il n'en est rien et la sortie standard semble indiquer que le processus père a affiché tous les caractères ``P`` simultanément. Ce n'est pas possible si l'on regarde le code source de la fonction ``output``.

L'utilitaire `strace(1)`_ qui permet de tracer tous les appels systèmes effectués par un processus nous permet d'analyser comment le processus père et le processus fils écrivent sur :term:`stdout`. Lorsqu'ils utilisent les fonctions `printf(3)`_ et `putchar(3)`_ de la librairie standard, ils utilisent des fonctions qui finalement utilisent l'appel système `write(2)`_ qui est le seul permettant d'écrire sur un flux tel que :term:`stdout`. L'exécution de `strace(1)`_ montre que chaque processus effectue deux appels systèmes `write(2)`_. Le premier correspond à l'appel à `printf(3)`_ et le second à tous les appels à `putchar(3)`_ fait par le processus.

.. code-block:: console

 strace -f -e trace=write ./fork-buf
 Process 1398 attached
 [pid  1398] write(1, "Processus : 1398\n", 17 <unfinished ...>
 [pid  1397] write(1, "Processus : 1397\n", 17Processus : 1397
 ) = 17
 Processus : 1398
 [pid  1398] <... write resumed> )       = 17
 [pid  1398] write(1, "ffffffffffffffffffffffffffffffff"..., 60ffffffffff ffffffffffffffffffffffffffffffffffffffffffffffffff) = 60
 Process 1398 detached
 --- SIGCHLD (Child exited) @ 0 (0) ---
 write(1, "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"..., 61PPPPPPPPPPPPPPPPPPPPPP PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
 ) = 61

L'exécution d'un appel système tel que `write(2)`_ peut être couteux au niveau des performances. Une règle de bonne pratique est d'essayer de minimiser le nombre d'appels systèmes effectués par un programme. La librairie standard prend en compte cette règle et utilise un buffer dans lequel elle stocke temporairement les données produites par les fonctions telles que `printf(3)`_ ou `putchar(3)`_ avant de les écrire via `write(2)`_. Ce buffer peut être contrôlé via les fonctions `setvbuf(3)`_ et `setbuf(3)`_. Ces fonctions permettent de fixer la taille du buffer utilisé par la librairie standard.

Lorsque le buffer de la librairie `stdio(3)`_ est désactivé en faisant ``setbuf(stdout,NULL);``, le processus père et le processus fils écrivent bien de façon entrelacée sur la sortie standard.

.. code-block:: console

 $ ./fork-buf 1
 Processus : 1419
 PProcessus : 1420
 fffPffPffPffPfPfffPPfPPPfPfffPfPfPPfffPfPffPPfPPPPfPPfPPfPfPPfPfPffPfPfPffffPPfPPffPffPPfPfPfPPfPfPfPfPfPPffPPfffPfPPPP

L'utilisation de `strace(1)` lors de cette exécution montre effectivement que chaque appel à la fonction `putchar(3)`_ provoque une exécution de l'appel système `write(2)`_ :

.. code-block:: console

 [pid  1420] write(1, "f", 1f)            = 1
 [pid  1419] write(1, "P", 1P)            = 1
 [pid  1419] write(1, "P", 1P)            = 1
 [pid  1420] write(1, "f", 1f)            = 1


.. note:: Faut-il modifier le buffer de la librairie `stdio(3)`_ ?

 En pratique, il est préférable de ne pas désactiver le buffer utilisé par la librairie `stdio(3)`_ car cela peut avoir des conséquences négatives sur les performances des programmes. Par contre, lorsque l'on développe des programmes qui utilisent plusieurs processus il est important de se souvenir de l'existence de ce buffer car il peut expliquer certains comportements qui pourraient apparaître comme étant bizarres lorsque l'on observe l'exécution de processus via les messages qu'ils affichent sur :term:`stderr` ou :term:`stdout`. Lorsque l'on soupçonne un comportement bizarre qui pourrait être expliqué par des interactions avec ce buffer, il est possible d'ajouter dans le programme des appels explicites à la fonction `fflush(3)`_ qui a pour effet de vider immédiatement le buffer de `stdio(3)`_.


.. note:: Génération de nombres aléatoires

 Le programme :download:`/Threads/S8-src/fork-buf.c` présenté ci-dessus est un exemple d'utilisation de nombres aléatoires. Ceux-ci sont générés avec la fonction `rand(3)`_ de la librairie standard. Cette fonction utilise un générateur de nombres aléatoires qui génère toujours la même séquence de nombres aléatoires lorsqu'elle est initialisée avec la même semence par la fonction `srand(3)`_. Souvent, les programmeurs qui utilisent des nombres aléatoires cherchent à ce que la séquence générée diffère d'une exécution du programme à l'autre. Une façon simple de procéder est d'utiliser comme semence la somme entre le temps courant retourné par `time(3posix)`_ et l'identifiant du processus obtenu via `getpid(2)`_. Une telle semence n'est cependant pas suffisante pour toutes les applications. Certaines applications cryptographiques notamment nécessitent des nombres aléatoires qui ne peuvent pas être facilement prédits. Pour ces applications, il est nécessaire d'utiliser des semences qui sont parfaitement aléatoires, comme `random(4)`_.

.. index:: atexit, exit, wait, waitpid

Fin d'un processus
------------------

Il y a deux événements importants dans la vie d'un processus sous Unix. Sa création avec l'appel système `fork(2)`_ et sa terminaison. Nous avons déjà vu qu'un programme C (et donc un processus) pouvait se terminer de deux façons principales [#fthread]_ :

 - par l'exécution de ``return(...)`` dans la fonction ``main``
 - par un appel explicite à la fonction `exit(3)`_ dans la fonction ``main`` ou n'importe quelle fonction du processus

Ces fonctions appellent en fait la fonction de la librairie `exit(3)`_. Cette fonction permet de faire plus que simplement terminer le processus en cours d'exécution et retourner sa valeur de retour. Il est en effet possible d'associer une ou plusieurs fonctions de terminaison à `exit(3)`_ via la fonction `atexit(3)`_. Lorsque `exit(3)`_ est appelée, elle lance d'abord les fonctions enregistrées par `atexit(3)`_ puis termine correctement le processus. Ces fonctions de terminaison d'un processus sont utilisées lorsque par exemple un processus utilise des services particuliers du système d'exploitation comme par exemple une mémoire partagée entre plusieurs processus. Ces services consomment des ressources et il est nécessaire de les libérer correctement lorsqu'un processus se termine comme nous le verrons ultérieurement.

L'exemple ci-dessous illustre brièvement l'utilisation de `atexit(3)`_.

.. literalinclude:: /Threads/S8-src/atexit.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

.. index:: _exit

Après avoir exécuté les fonctions de terminaison, la fonction `exit(3)`_ appelle `fflush(3)`_ sur tous les flux existants puis les ferme proprement. Ensuite, la fonction `exit(3)`_ exécute l'appel système `exit(2)`_. Cet appel système est particulier. C'est le seul appel système qui n'a pas de valeur de retour, et pour cause ! Il ferme tous les fichiers qui étaient encore ouverts (normalement un processus devrait fermer proprement tous ses fichiers avant de s'arrêter) et libère les ressources qui étaient associées au processus.

.. code-block:: c

   #include <unistd.h>

   void _exit(int status);

L'appel système `exit(2)`_ permet au processus qui se termine de retourner un statut à son processus père. Pour récupérer le statut de son fils, un processus père doit utiliser l'appel système `waitpid(2)`_.


.. code-block:: c

   #include <sys/types.h>
   #include <sys/wait.h>

   pid_t waitpid(pid_t pid, int *status, int options);

L'appel système `waitpid(2)`_ prend trois arguments. C'est un appel système bloquant. Le premier argument permet de spécifier quel est le processus fils dont la terminaison est attendue. Un premier argument négatif indique que `waitpid(2)`_ attend la terminaison de n'importe quel processus fils. Si le premier argument est positif, alors il contient un identifiant de processus fils et `waitpid(2)`_ attendra la terminaison de ce processus [#fwaitpid]_. Le second argument est un pointeur vers un entier qui après le retour de `waitpid(2)`_ contiendra le statut retourné par le processus fils. Le troisième argument permet de spécifier des options à `waitpid(2)`_ que nous n'utiliserons pas. La fonction `wait(2)`_ est une simplification de `waitpid(2)`_ qui permet d'attendre n'importe quel processus fils. ``wait(p)`` est en pratique équivalent à ``waitpid(-1,p,0)``.

Un processus qui lance un processus fils avec `fork(2)`_ *doit* attendre la terminaison de son processus fils en utilisant `waitpid(2)`_. Le programme ci-dessous illustre l'utilisation de `waitpid(2)`_.

.. literalinclude:: /Threads/S8-src/fork-wait.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB


Dans ce programme, le processus père récupère la valeur retournée par le fils qu'il a créé. Lors de l'exécution de ``waitpid(pid,&status,0);``, la valeur de retour du fils est placée dans l'entier dont l'adresse est ``status``. Cet entier contient non-seulement la valeur de retour du processus fils (dans les 8 bits de poids faible), mais aussi une information permettant de déterminer si le processus fils s'est terminé correctement ou a été terminé de façon abrupte via l'utilisation de `kill(1)`_. Les macros ``WEXITSTATUS`` et ``WTERMSIG`` utilisées pour extraire la valeur de retour et la raison de la terminaison abrupte sont décrites dans `waitpid(2)`_.

Même si un processus *doit* attendre la terminaison de tout processus fils qu'il a lancé, il arrive parfois qu'un processus n'attende pas ses fils. Cela peut arriver lorsqu'un processus s'arrête suite à une erreur avant de pouvoir récupérer ses fils. Ce cas est illustré par l'exemple ci-dessous dans lequel le processus père se termine sans attendre son fils.

.. literalinclude:: /Threads/S8-src/fork-orphan.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Du point de vue du :term:`kernel` cette situation est ennuyeuse car il maintient pour chaque processus non seulement son identifiant de processus mais également l'identifiant de son processus père qui est retourné par `getpid(2)`_. Lorsque le père se termine avant son fils, le processus fils est dit `orphelin` et le kernel modifie ses structures de données pour que le père de ce :term:`processus orphelin` soit le processus dont l'identifiant est ``1``. Ce processus est le processus `init(8)`_ qui est lancé au démarrage du système et n'est jamais arrêté.

.. literalinclude:: /Threads/S8-src/fork-orphan.out
   :encoding: utf-8
   :language: console

A côté des processus orphelins dont nous venons de parler, un système Unix peut également héberger des :term:`processus zombie`. Un :term:`processus zombie` est un processus qui s'est terminé mais dont la valeur de retour n'a pas encore été récupérée par son père. Dans ce cas, le :term:`kernel` libère l'ensemble des ressources associées au processus fils et ne conserve de ce processus qu'une petite structure de données contenant notamment son identifiant, l'identifiant de son processus père et sa valeur de retour. En pratique, il est préférable d'éviter les processus zombie car ils consomment quand même un peu de ressources.

.. index:: execve

Exécution d'un programme
------------------------

`fork(2)`_ et `waitpid(2)`_ permettent respectivement de créer et de terminer des processus. Pour comprendre la façon dont les programmes sont exécutés, il nous reste à expliquer le fonctionnement de l'appel système `execve(2)`_. Cet appel système permet l'exécution d'un programme. Lors de son exécution, l'image en mémoire du processus qui effectue `execve(2)`_ est remplacée par l'image de l'exécutable passé en argument à `execve(2)`_ et son exécution démarre à sa fonction ``main``.

.. code-block:: c

   #include <unistd.h>

   int execve(const char *path, char *const argv[], char *const envp[]);

`execve(2)`_ prend trois arguments. Le premier est le nom complet du fichier exécutable qui doit être lancé. Le second est un pointeur vers un tableau de chaines de caractères contenant les arguments à passer à l'exécutable. Le troisième est un pointeur vers l'environnement qui sera nécessaire à l'exécution du programme. Comme `execve(2)`_ remplace l'image mémoire du programme en cours d'exécution, il ne retourne une valeur de retour que si l'appel système échoue. Cela peut être le cas si son premier argument n'est pas un fichier exécutable accessible par exemple.

`execve(2)`_ s'utilise souvent juste après l'exécution de `fork(2)`_, mais il est aussi possible de l'utiliser directement dans un programme. Dans ce cas, le programme qui exécute avec succès `execve(2)`_ disparaît et est remplacé par le programme appelé. Le programme ci-dessous illustre une utilisation simple de `execve(2)`_.

.. literalinclude:: /Threads/S8-src/execve.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA

Lors de son exécution, ce programme affiche sur sa sortie standard les lignes suivantes :

.. literalinclude:: /Threads/S8-src/execve.out
   :encoding: utf-8
   :language: console

Il y a quelques points importants à noter concernant l'utilisation de `execve(2)`_. Tout d'abord, `execve(2)`_ remplace l'entièreté de l'image mémoire du processus qui exécute cet appel système, y compris les arguments, les variables d'environnement. Par contre, le :term:`kernel` conserve certaines informations qu'il maintenait pour le processus. C'est le cas notamment de l'identifiant du processus et de l'identifiant du processus père. Si le processus qui a effectué `execve(2)`_ avait lancé des threads, ceux-ci seraient immédiatement supprimés puisque l'image du processus en cours d'exécution est remplacé lors de l'exécution de `execve(2)`_.  Les flux standard (:term:`stdin`, :term:`stdout` et :term:`stderr`) sont utilisables par le programme exécuté via `execve(2)`_. Il faut cependant noter que lors de l'appel à `execve(2)`_, les données qui se trouveraient éventuellement dans le buffer de la librairie :term:`stdio` ne sont pas automatiquement envoyées vers leurs flux respectifs. Cela pourrait paraître étonnant puisque lorsqu'un processus se termine avec `exit(3)`_, `exit(3)`_ vide les buffers de :term:`stdio` avant d'appeler `exit(2)`_. `execve(2)`_ est un appel système qui est exécuté par le kernel. Celui-ci ne peut pas savoir si il y a des données en attente d'écriture dans :term:`stdio`. Il ne peut donc pas automatiquement vider les buffers maintenus par la librairie :term:`stdio`. Si des données ont été écrites avec `printf(3)`_ avant l'exécution de `execve(2)`_, il est préférable de forcer leur écriture via `fflush(3)`_ avant d'appeler `execve(2)`_.

L'appel système `execve(2)`_ est très souvent exécuté dans un shell tel que `bash(1)`_. Lorsqu'un shell lance un programme externe, il doit d'abord utiliser `fork(2)`_ pour créer une copie de lui-même. Ensuite, le processus père se met en attente via `waitpid(2)`_ de la valeur de retour du processus fils créé. Le processus fils quant à lui utilise `execve(2)`_ pour exécuter le programme demandé.

La programme ci-dessous est un exemple un peu plus complexe de l'utilisation de `fork(2)`_, `execve(2)`_ et `waitpid(2)`_. Ce programme prend comme argument une liste d'exécutables et il essaye de les exécuter l'un à la suite de l'autre. Pour cela, il parcourt ses arguments et essaye pour chaque argument de créer un processus fils et d'y exécuter le programme correspondant. Si le programme a pu être exécuté, sa valeur de retour est récupérée par le processus père. Si l'appel à `execve(2)`_ a échoué, le processus fils se termine avec ``127`` comme valeur de retour. Comme celle-ci est stockée sur 8 bits, c'est la plus grande valeur de retour positive qu'il est possible de retourner depuis un processus fils. Cette valeur indique au processus père que le fils n'a pas réussi à exécuter `execve(2)`_.

.. literalinclude:: /Threads/S8-src/fork-manyexec.c
   :encoding: utf-8
   :language: c
   :start-after: ///AAA


Lors de son exécution, ce programme affiche sur sa sortie standard les lignes suivantes :

.. literalinclude:: /Threads/S8-src/fork-manyexec.out
   :encoding: utf-8
   :language: console

En pratique, il existe plusieurs fonctions de la librairie standard qui apportent de petites variations à `execve(2)`_. Il s'agit de `execl(3)`_, `execlp(3)`_, `execle(3)`_, `execv(3posix)`_ et `execv(3)`_. Ces fonctions utilisent toutes l'appel système `execve(2)`_. Elles permettent de spécifier de différentes façons le programme à exécuter ou les variables d'environnement. Enfin, la fonction `system(3)`_ de la librairie permet d'exécuter une commande du shell directement depuis un programme.

Outre les exécutables compilés, Unix et Linux supportent également l'exécution de programmes interprétés. Contrairement aux programmes compilés que nous avons manipulé jusque maintenant, un programme interprété est un programme écrit dans un langage qui doit être utilisé via un :term:`interpréteur`. Un :term:`interpréteur` est un programme qui lit des commandes sous la forme de texte et exécute directement les instructions correspondant à ces commandes. Unix supporte de nombreux interpréteurs et comme nous allons le voir il est très facile de rajouter de nouveaux interpréteurs de commande. L'interpréteur le plus connu est `bash(1)`_ et ses nombreuses variantes. En voici quelques autres :

 - `awk(1)`_ est un langage de programmation interprété qui permet de facilement manipuler des textes
 - `perl(1)`_ est un langage de programmation complet qui a été initialement développé pour la manipulation de textes, mais est utilisé dans de nombreuses autres applications
 - `python(1)`_ est un langage de programmation complet

Pour comprendre la façon dont Unix interagit avec les interpréteurs de commande, il est bon de voir en détails comment `execve(2)`_ reconnaît qu'un fichier contient un programme qui peut être exécuté. Tout d'abord, le système de fichiers contient pour chaque fichier des métadonnées qui fournissent de l'information sur le possesseur du fichier, sa date de création, ... Une de ces métadonnées est un bit [#fchmod]_ qui indique si le fichier est exécutable ou non. Ce bit peut être manipulé en utilisant la commande `chmod(1)`_. Lorsqu'un programme est compilé avec `gcc(1)`_, celui-ci utilise `chmod(1)`_ pour marquer le programme comme étant exécutable.

.. code-block:: console

 $ ls -l a.out
 -rwxr-xr-x 1 obo stafinfo 8178 Mar 16 13:42 a.out
 $ chmod -x a.out
 $ ./a.out
 -bash: ./a.out: Permission denied
 $ chmod +x a.out
 $ ./a.out
   exécution de a.out
 $ ls -l a.out
 -rwxr-xr-x 1 obo stafinfo 8178 Mar 16 13:42 a.out


Lorsqu'`execve(2)`_ est appelé, il vérifie d'abord ce bit de permission. Si il n'indique pas que le programme est exécutable, `execve(2)`_ retourne une erreur. Ensuite, `execve(2)`_ ouvre le fichier dont le nom a été passé comme premier argument. Par convention, le début du fichier contient une séquence d'octets ou de caractères qui indiquent le type de fichier dont il s'agit. La commande `file(1)`_ permet de tester le type d'un fichier inconnu.

.. code-block:: console

   $ file fork-execve.c
   fork-execve.c: UTF-8 C program text
   $ file script.sh
   script.sh: Bourne-Again shell script text executable
   $ file a.out
   a.out: ELF 64-bit LSB executable, x86-64, version 1 (GNU/Linux),   dynamically linked (uses shared libs), for GNU/Linux 2.6.18, not stripped

Pour les exécutables, deux cas de figure sont possibles:

 1. le fichier contient un programme compilé et directement exécutable. Sur les systèmes Linux actuels, ce fichier sera au format `elf(5)`_. Il débute par une entête qui contient une chaîne de caractères utilisée comme marqueur ou chaîne magique. L'entête fournit de l'information sur le type d'exécutable et sa structure. Voici à titre d'illustration le contenu de l'entête d'un programme compilé décortiqué par l'utilitaire `readelf(1)`_ :

  .. code-block:: console

   $ readelf -h a.out
   ELF Header:
    Magic:   7f 45 4c 46 02 01 01 03 00 00 00 00 00 00 00 00
    Class:                             ELF64
    Data:                              2's complement, little endian
    Version:                           1 (current)
    OS/ABI:                            UNIX - Linux
    ABI Version:                       0
    Type:                              EXEC (Executable file)
    Machine:                           Advanced Micro Devices X86-64
    Version:                           0x1
    Entry point address:               0x4006e0
    Start of program headers:          64 (bytes into file)
    Start of section headers:          3712 (bytes into file)
    Flags:                             0x0
    Size of this header:               64 (bytes)
    Size of program headers:           56 (bytes)
    Number of program headers:         8
    Size of section headers:           64 (bytes)
    Number of section headers:         30
    Section header string table index: 27

 2. Le fichier contient un programme en langage interprété. Dans ce cas, la première ligne débute par ``#!`` suivi du nom complet de l'interpréteur à utiliser et de ses paramètres éventuels. Le programme interprété commence sur la deuxième ligne. A titre d'exemple, voici un petit script `bash(1)`_ qui permet de tester si un fichier est interprétable ou non en testant la valeur des deux premiers caractères du fichier et ses métadonnées.

 .. literalinclude:: /Threads/S8-src/script.sh
    :encoding: utf-8
    :language: bash


Sous Unix et Linux, n'importe quel programmeur peut définir son propre interpréteur. Il suffit qu'il s'agisse d'un exécutable compilé et que le nom de cet interpréteur soit présent dans la première ligne du fichier à interpréter. Lors de l'exécution d'un programme utilisant cet interpréteur, celui-ci recevra le contenu du fichier et pourra l'interpréter. Ainsi, par exemple le programme interprété ci-dessous est tout à fait valide.

.. literalinclude:: /Threads/S8-src/test.tail
   :encoding: utf-8
   :language: bash

Lors de son exécution via `execve(2)`_, l'interpréteur `tail(1)`_ va être chargé avec comme arguments ``-n +1`` et il affichera sur :term:`stdout` la ligne ``SINF1252``.

Cette facilité d'ajouter de nouveaux interpréteurs de commande est une des forces des systèmes d'exploitation de la famille Unix.

.. index:: table des processus

Table des processus
-------------------

Un système d'exploitation tel que Linux maintient certaines informations concernant chaque processus dans sa :term:`table des processus`. Une description complète du contenu de cette table des processus sort du cadre de ce chapitre. Par contre, il est intéressant de noter que sous Linux il existe de nombreux utilitaires qui permettent de consulter le contenu de la table des processus et notamment :

 - `ps(1)`_ qui est l'utilitaire de base pour accéder à la table de processus et lister les processus en cours d'exécution
 - `top(1)`_ qui affiche de façon interactive les processus qui consomment actuellement du temps CPU, de la mémoire, ...
 - `pstree(1)`_ qui affiche l'arbre des processus avec les relations père-fils

Tous ces utilitaires utilisent les informations contenues dans le répertoire ``/proc``. Il s'agit d'un répertoire spécial qui contient de l'information à propos du système d'exploitation y compris la table de processus. Son contenu est détaillé dans la page de manuel qui lui est consacrée : `proc(5)`_.

A titre d'illustration, considérons le shell d'un utilisateur en cours. Les informations maintenues dans la table des processus pour ce processus sont accessibles depuis ``/proc/pid`` où ``pid`` est l'identifiant du processus en cours d'exécution. Linux stocke de très nombreuses informations sur chaque processus. Celles-ci sont structurées dans des fichiers et des répertoires :

.. code-block:: console

 $ ls -l /proc/18557
 total 0
 dr-xr-xr-x 2 obo stafinfo 0 Mar 18 16:37 attr
 -r-------- 1 obo stafinfo 0 Mar 18 16:37 auxv
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 cgroup
 --w------- 1 obo stafinfo 0 Mar 18 16:37 clear_refs
 -r--r--r-- 1 obo stafinfo 0 Mar 18 14:56 cmdline
 -rw-r--r-- 1 obo stafinfo 0 Mar 18 16:37 coredump_filter
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 cpuset
 lrwxrwxrwx 1 obo stafinfo 0 Mar 18 16:37 cwd ->  /etinfo/users2/obo/sinf1252/SINF1252/
 -r-------- 1 obo stafinfo 0 Mar 18 16:37 environ
 lrwxrwxrwx 1 obo stafinfo 0 Mar 18 16:37 exe -> /bin/bash
 dr-x------ 2 obo stafinfo 0 Mar 18 14:56 fd
 dr-x------ 2 obo stafinfo 0 Mar 18 16:37 fdinfo
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 io
 -rw------- 1 obo stafinfo 0 Mar 18 16:37 limits
 -rw-r--r-- 1 obo stafinfo 0 Mar 18 16:37 loginuid
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 maps
 -rw------- 1 obo stafinfo 0 Mar 18 16:37 mem
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 mountinfo
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 mounts
 -r-------- 1 obo stafinfo 0 Mar 18 16:37 mountstats
 dr-xr-xr-x 6 obo stafinfo 0 Mar 18 16:37 net
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 numa_maps
 -rw-r--r-- 1 obo stafinfo 0 Mar 18 16:37 oom_adj
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 oom_score
 -r-------- 1 obo stafinfo 0 Mar 18 16:37 pagemap
 -r-------- 1 obo stafinfo 0 Mar 18 16:37 personality
 lrwxrwxrwx 1 obo stafinfo 0 Mar 18 16:37 root -> /
 -rw-r--r-- 1 obo stafinfo 0 Mar 18 16:37 sched
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 schedstat
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 sessionid
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 smaps
 -r-------- 1 obo stafinfo 0 Mar 18 16:37 stack
 -r--r--r-- 1 obo stafinfo 0 Mar 18 14:56 stat
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 statm
 -r--r--r-- 1 obo stafinfo 0 Mar 18 14:56 status
 -r-------- 1 obo stafinfo 0 Mar 18 16:37 syscall
 dr-xr-xr-x 3 obo stafinfo 0 Mar 18 15:59 task
 -r--r--r-- 1 obo stafinfo 0 Mar 18 16:37 wchan

Certaines des entrées dans ``/proc`` sont des fichiers, d'autres sont des répertoires. A titre d'exemple, voici quelques unes des entrées utiles à ce stade de notre exploration de Linux.

 - ``cmdline`` est un fichier texte contenant la ligne de commande utilisée pour lancer le processus
 - ``environ`` est un fichier texte contenant les variables d'environnement passées au processus

   .. code-block:: console

      $ (cat /proc/18557/environ; echo) | tr '\000' '\n'
      USER=obo
      LOGNAME=obo
      HOME=/etinfo/users2/obo
      PATH=/usr/local/bin:/bin:/usr/bin
      MAIL=/var/mail/obo
      SHELL=/bin/bash

 - ``status`` est une indication sur l'état actuel du processus. Les premières lignes indiquent dans quel état le processus se trouve ainsi que son identifiant, l'identifiant de son père, ...

  .. code-block:: console

      $ cat /proc/$$/status | head -5
      Name:	bash
      State:	S (sleeping)
      Tgid:	18557
      Pid:	18557
      PPid:	18556

 - ``limits`` est un fichier texte contenant les limites actuelles imposées par le système sur le processus. Ces limites peuvent être modifiées en utilisant `ulimit(1)` à l'intérieur de `bash(1)`_ ou via les appels systèmes `getrlimit(2)`_/`setrlimit(2)`_.

   .. code-block:: console

      $ cat /proc/18557/limits
      Limit                     Soft Limit           Hard Limit           Units
      Max cpu time              unlimited            unlimited            seconds
      Max file size             unlimited            unlimited            bytes
      Max data size             unlimited            unlimited            bytes
      Max stack size            10485760             unlimited            bytes
      Max core file size        0                    unlimited            bytes
      Max resident set          unlimited            unlimited            bytes
      Max processes             1024                 24064                processes
      Max open files            1024                 1024                 files
      Max locked memory         65536                65536                bytes
      Max address space         unlimited            unlimited            bytes
      Max file locks            unlimited            unlimited            locks
      Max pending signals       24064                24064                signals
      Max msgqueue size         819200               819200               bytes
      Max nice priority         0                    0
      Max realtime priority     0                    0
      Max realtime timeout      unlimited            unlimited            us

 - ``task`` est un répertoire qui contient pour chaque thread lancé par le processus un sous-répertoire avec toutes les informations qui sont relatives à ce thread.

Nous aurons l'occasion de présenter ultérieurement d'autres éléments utiles se trouvant dans ``/proc``. Une description plus détaillée est disponible dans la page de manuel `proc(5)`_ et des livres de référence tels que [Kerrisk2010]_.



.. rubric:: Footnotes

.. [#fdynamic] Dans certains cas, on parle également de librairies dynamiques car ces librairies sont chargées dynamiquement à l'exécution du programme.

.. [#fpath] La variable d'environnement ``PATH`` contient la liste des répertoires que le shell parcoure afin de localiser un exécutable à lancer lorsque l'utilisateur ne fournit par le chemin complet de l'exécutable à lancer.

.. [#fsyscall] En pratique, il correspond une fonction de la librairie à chaque appel système. Cette fonction a le même nom que l'appel système et les mêmes arguments et fait appel à `syscall(2)`_ pour l'exécution de l'appel système.

.. [#flib] Par défaut, `gcc(1)`_ cherche après les librairies spécifiées dans les répertoires de librairies standards, mais aussi dans les répertoires listés dans la variable d'environnement ``LD_LIBRARY_PATH``. Il est également possible de spécifier des répertoires supplémentaires contenant les librairies avec l'argument ``-L`` de `gcc(1)`_.

.. [#fthread] Si le processus a été découpé en threads, le processus peut aussi se terminer lorsque son dernier thread se termine en exécutant ``return(...)`` dans sa fonction de démarrage ou par un appel explicite à `pthread_exit(3)`_.

.. [#fwaitpid] Si le processus dont l'identifiant est passé comme argument s'est déjà terminé, alors `waitpid(2)`_ retourne en indiquant une erreur.

.. [#fchmod] En pratique, il y a trois bits qui jouent ce rôle en fonction du possesseur du fichier et de l'utilisateur qui souhaite l'exécuter. Nous décrirons ces bits en détails dans un prochain chapitre.


