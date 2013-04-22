.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

La mémoire virtuelle
====================

Le modèle d'interaction entre le processeur et la mémoire que nous avons utilisé jusqu'à présent est le modèle traditionnel. Dans ce modèle, illustré sur la figure ci-dessous, la mémoire est divisée en octets qui sont chacun identifiés par une adresse encodée sur :math:`n` bits. Une telle mémoire peut donc contenir au maximum :math:`2^n` octets de données. Aujourd'hui, les processeurs utilisent généralement des adresses sur 32 bits ou 64 bits. Avec des adresses sur 32 bits, la mémoire peut stocker :math:`4.294.967.296` octets de données. Avec des adresses sur 64 bits, la capacité de stockage de la mémoire monte à :math:`18.446.744.073.709.551.616` octets. Si on trouve facilement aujourd'hui des mémoires avec une capacité de :math:`4.294.967.296` octets, il n'en existe pas encore qui sont capables de stocker :math:`18.446.744.073.709.551.616` et il faudra probablement quelques années avant que de telles capacités ne soient utilisables en pratique.

.. figure:: /S11/fig/figures-11-001-c.png
   :align: center
   :scale: 60

   Modèle simple d'interaction entre le processeur et la mémoire

Ce modèle correspond au fonctionnement de processeurs simples tels que ceux que l'on trouve sur des systèmes embarqués comme une machine à lessiver. Malheureusement, il ne permet pas d'expliquer et de comprendre le fonctionnement des ordinateurs actuels. Pour s'en convaincre, il suffit de réfléchir à quelques problèmes liés à l'utilisation de la mémoire sur un ordinateur fonctionnant sous Unix.

Le premier problème est lié à l'organisation d'un processus en mémoire. Sous Unix, le bas de la mémoire est réservé au code, le milieu au heap et le haut au stack. Le modèle simple d'organisation de la mémoire ne permet pas facilement de comprendre comment un tel processus peut pouvoir utiliser la mémoire sur un processus 64 bits qui est placé dans un ordinateur qui ne dispose que de 4 GBytes de mémoire. Avec une telle quantité de mémoire, le sommet de la pile devrait se trouver à une adresse proche de :math:`2^{32}` et non :math:`2^{64}`. 

Un deuxième problème est lié à l'utilisation de plusieurs processus simultanément en mémoire. Lorsque deux processus s'exécutent, ils utilisent nécessairement la même mémoire physique. Si un processus utilise l'adresse `x` et y place des instructions ou des données, cette adresse ne peut pas être utilisée par un autre processus. Physiquement, ces deux processus doivent utiliser des zones mémoires distinctes. Pourtant, le programme ci-dessous affiche les adresses de ``argc``, la fonction ``main`` et la fonction ``printf`` de la librairie standard puis effectue ``sleep(20);``. Lors de l'exécution de deux instances de ce programmes simultanément, on observe ceci sur la sortie standard.

.. code-block:: console

   $ ./simple &
   [pid=32955] Adresse de argc : 0x7fff5fbfe18c
   [pid=32955] Adresse de main : 0x100000e28
   [pid-32955] Adresse de printf : 0x7fff8a524f3a
   $ ./simple 
   [pid=32956] Adresse de argc : 0x7fff5fbfe18c
   [pid=32956] Adresse de main : 0x100000e28
   [pid-32956] Adresse de printf : 0x7fff8a524f3a


Manifestement, les deux programmes utilisent exactement les mêmes adresses en mémoire. Pourtant, ces deux programmes doivent nécessairement utiliser des zones mémoires différents pour pouvoir s'exécuter correctement. Ceci est possible grâce à l'utilisation de la :term:`mémoire virtuelle`. 


Le :term:`Memory Management Unit`
---------------------------------


Manifestement, les deux programmes utilisent exactement les mêmes adresses en mémoire. Pourtant, ces deux programmes doivent nécessairement utiliser des zones mémoires différents pour pouvoir s'exécuter correctement. Ceci est possible grâce à l'utilisation de la :term:`mémoire virtuelle`. Avec la :term:`mémoire virtuelle`, deux types d'adresses sont utilisées sur le système : les adresses virtuelles et les adresses réelles ou physiques. Une :term:`adresse virtuelle` est une adresse qui est utilisée à l'intérieur d'un programme. Les adresses des variables ou des fonctions de notre programme d'exemple ci-dessous sont des adresses virtuelles. Une :term:`adresse physique` est l'adresse qui utilisée au niveau des puces de RAM pour les opérations d'écriture et de lecture. Ce sont les adresses physiques qui sont échangées sur le bus auquel la mémoire est connectée. Pour que les programmes puissent accéder aux instructions et données qui se trouvent en mémoire, il est nécessaire de pouvoir traduire les adresses virtuelles en adresses physiques. C'est le rôle du :term:`MMU` ou :term:`Memory Management Unit`. Historiquement, le :term:`MMU` était implémenté sous la forme d'un chip séparé qui était placé entre le processeur (qui utilisait alors des adresses virtuelles) et la mémoire (qui utilise elle toujours des adresses physiques). Aujourd'hui, le :term:`MMU` est généralement intégré au processeur pour des raisons de performances, mais conceptuellement son rôle reste essentiel comme nous allons le voir.

La mémoire virtuelle
--------------------

Avec la :term:`mémoire virtuelle`, deux types d'adresses sont utilisées sur le système : les adresses virtuelles et les adresses réelles ou physiques. Une :term:`adresse virtuelle` est une adresse qui est utilisée à l'intérieur d'un programme. Les adresses des variables ou des fonctions de notre programme d'exemple ci-dessous sont des adresses virtuelles. Une :term:`adresse physique` est l'adresse qui utilisée au niveau des puces de mémoire RAM pour les opérations d'écriture et de lecture. Ce sont les adresses physiques qui sont échangées sur le bus auquel la mémoire est connectée. Pour que les programmes puissent accéder aux instructions et données qui se trouvent en mémoire, il est nécessaire de pouvoir traduire les adresses virtuelles en adresses physiques. C'est le rôle du :term:`MMU` ou :term:`Memory Management Unit`. Historiquement, le :term:`MMU` était implémenté sous la forme d'un chip séparé qui était placé entre le processeur (qui utilisait alors des adresses virtuelles) et la mémoire (qui utilise elle toujours des adresses physiques). Aujourd'hui, le :term:`MMU` est généralement intégré au processeur pour des raisons de performances, mais conceptuellement son rôle reste essentiel comme nous allons le voir.


.. figure:: /S11/fig/figures-11-002-c.png
   :align: center
   :scale: 60

   :term:`MMU` et :term:`mémoire virtuelle`


Le rôle principal du :term:`MMU` est de traduire les adresses virtuelles en adresses physiques. Avant d'expliquer comment le :term:`MMU` peut être implémenté en pratique, il est utile de passer en revue plusieurs avantages de l'utilisation des adresses virtuelles.

Un premier avantage de l'utilisation de la mémoire virtuelle est qu'elle permet de découpler les adresses virtuelles des adresses physiques. Celles-ci ne doivent pas nécessairement avoir la même longueur. La longueur des adresses dépend généralement de l'architecture du processeur et de la taille des registres qu'il utilise. Une organisation possible de la mémoire virtuelle est d'utiliser des adresses virtuelles qui sont encodées sur autant de bits que les adresses physiques, mais ce n'est pas la seule. Il est tout à fait possible d'avoir un ordinateur sur lequel les adresses virtuelles sont plus longues que les adresses physiques. C'est le cas par exemple sur les ordinateurs bon marché qui utilisent une quantité réduite de mémoire RAM. Inversement, grâce à la mémoire virtuelle un serveur peut utiliser des adresses physiques qui sont plus longues que les adresses virtuelles. Cela lui permet d'utiliser une capacité de mémoire plus importante que celle autorisée par l'architecture de son processeur. Dans ce cas, un processus ne peut pas utiliser plus de mémoire que l'espace d'adressage virtuel disponible. Mais ensemble, tous les processus fonctionnant sur l'ordinateur peuvent utiliser tout l'espace d'adressage physique disponible.

Un deuxième avantage de la mémoire virtuelle est qu'elle permet, à condition de pouvoir réaliser une traduction spécifique à chaque processus, de partager efficacement la mémoire entre plusieurs processus tout en leur permettant d'utiliser les mêmes adresses virtuelles. C'est cette particularité de la mémoire virtuelle qui nous a permis dans l'exemple précédente d'avoir deux processus qui en apparence utilisent les mêmes adresses. En effectuant une traduction spécifique à chaque processus, le :term:`MMU` permet d'autres avantages qui sont encore plus intéressants.

Le :term:`MMU` est capable d'effectuer des traductions d'adresses virtuelles qui sont spécifiques à chaque processus. Cela implique qu'en général la traduction de l'adresse `x` dans le processus `P1` ne donnera pas la même adresse physique que la traduction de l'adresse `x` dans le processus `P2`. Par contre, il est tout à fait possible que la traduction de l'adresse `w` (resp. `y`) dans le processus `P1` (resp. `P2`) donne l'adresse physique `z` dans les deux processus. Comme nous le verrons ultérieurement, cela permet à deux processus distincts de partager de la mémoire. Cette propriété est aussi à la base du fonctionnement des librairies partagées dans un système Unix. Dans notre exemple, la fonction ``printf`` qui est utilisée par les deux processus fait partie de la librairie standard. Celle-ci doit être chargée en mémoire lors de l'exécution de chacun des processus. Grâce à l'utilisation du :term:`MMU` et de la mémoire virtuelle, une seule copie physique de la librairie standard est chargée en mémoire et tous les processus qui y font appel utilisent les instructions se trouvant dans cette copie physique. Cela permet de réduire fortement la consommation de mémoire lorsque de nombreux processus s'exécutent simultanément, ce qui est souvent le cas sur un système Unix.

Le dernier avantage de l'utilisation de la mémoire virtuelle est qu'il est possible de combiner ensemble la mémoire RAM et un ou des dispositifs de stockage tels que des disques durs ou des disques SSD pour constituer une mémoire virtuelle de plus grande capacité que la mémoire RAM disponible. Pour cela, il suffit, conceptuellement, que le :term:`MMU` soit capable de supporter deux types d'adresses physiques : les adresses physiques en RAM et les adresses physiques qui correspondent à des données stockées sur un dispositif de stockage [#fmmu]_.

.. figure:: /S11/fig/figures-11-003-c.png
   :align: center
   :scale: 60

   Organisation de la :term:`mémoire virtuelle`

Cette possibilité de combiner la mémoire RAM et les dispositifs de stockage offre encore plus de possibilités. Comme nous le verrons, grâce à la mémoire virtuelle, un processus pourra accéder à des fichiers via des pointeurs et des écriture/lectures en mémoire. Le chargement d'un programme pourra s'effectuer en passant par la mémoire virtuelle de façon à charger uniquement les parties du programme qui sont nécessaire en mémoire. Nous verrons également qu'il existe plusieurs appels système qui permettent à des processus de contrôler leur utilisation de la mémoire virtuelle.


Fonctionnement de la mémoire virtuelle
--------------------------------------

Avant d'analyser comment la mémoire virtuelle peut être utilisée par les processus, il est important de bien comprendre son organisation et les principes de base de fonctionnement du :term:`MMU`. La mémoire virtuelle combine la mémoire RAM et les dispositifs de stockage. Comme la mémoire RAM et les dispositifs de stockage ont des caractéristiques fort différentes, il n'est pas trivial de les combiner pour donner l'illusion d'une mémoire virtuelle unique.

Au niveau de l'adressage, la mémoire RAM permet d'adresser des octets et supporte des lectures et des écritures à n'importe quelle adresse. La mémoire RAM permet au processeur d'écrire et de lire des octets ou des mots à une position déterminée en mémoire

Un dispositif de stockage quant à lui contient un ensemble de secteurs. Chaque secteur peut être identifié par une adresse, comprenant par exemple le numéro du plateau, le numéro de la piste et le numéro du secteur sur la piste. Sur un dispositif, le secteur est l'unité de transfert de l'information. Cela implique que la moindre lecture/écriture sur un dispositif de stockage nécessite la lecture/écriture d'au moins 512 octets, même pour modifier un seul bit. Enfin, la dernière différence importante entre ces deux technologies est leur temps d'accès. Au niveau des mémoires RAM, les temps d'accès sont de l'ordre de quelques dizaines de nanosecondes. Pour un dispositif de stockage, les temps d'accès peuvent être de quelques dizaines de microsecondes pour un dispositif de type :term:`Solid State Drive` ou :term:`SSD` et jusqu'à quelques dizaines de millisecondes pour un disque dur. Les tableaux ci-dessous présentent les caractéristiques techniques de deux dispositifs de stockage [#fintel]_  [#fseagate]_ )`_. 

.. code-block:: c

   #include <unistd.h>
   int sz = getpagesize();

Lorsqu'un programme est chargé en mémoire, par exemple lors de l'exécution de l'appel système `execve(2)`_, il est automatiquement découpé en pages. Ces pages peuvent être stockée dans n'importe quelle zone de la mémoire RAM. La seule contrainte est que tous les octets qui font partie de la même page doivent être stockés à des adresses qui sont contigües. Cette contrainte permet de structurer les adresses virtuelles en deux parties comme représenté dans la figure ci-dessous. Une :term:`adresse virtuelle` est donc un ensemble de bits. Les bits de poids fort servent à identifier la :term:`page` dans laquelle une donnée est stockée. Les bits de poids faible (12 lorsque l'on utilise des pages de 4 KBytes), identifient la position de la donnée par rapport au début de la page. 


.. figure:: /S11/fig/figures-11-004-c.png
   :align: center
   :scale: 60

   Adresse virtuelle

Grâce à cette organisation des adresses virtuelles, il est possible de construire un mécanisme efficace qui permet de traduire une adresse réelle en une adresse virtuelle. La première solution qui a été proposée pour réaliser cette traduction est d'utiliser une :term:`table des pages`. La :term:`table des pages` est stockée en mémoire RAM et contient une ligne pour chaque page existant dans la mémoire virtuelle. A titre d'exemple, une système utilisant des adresses virtuelles de 32 bits et des pages de 4 KBytes contient :math:`2^{32-12}=2^{20}` pages. La table des pages de ce système contient :math:`2^{20}` lignes. Une ligne de la table des pages contient différentes informations que nous détaillerons par après. Les deux plus importantes sont :

 - le :term:`bit de validité` qui indique si la page est présente en mémoire RAM ou non
 - l'adresse en mémoire RAM à laquelle la page est actuellement stockée (si elle est présente en mémoire RAM)

La table des page est stockée en mémoire RAM. Elle est stockée comme un tableau en C. L'information correspondant à la page `0` est stockée à l'adresse de début de la table des pages. Cette adresse de début de la table des pages (``P``) est généralement stockée dans un registre du processeur pour être facilement accessible. Si une entrée [#fentree]_ de la table des pages comprend `n` bytes, l'information correspondant à la page `1` sera stockée à l'adresse ``P+n``, celle relative à la page `2`  à l'adresse ``P+2*n``, ... Cette organisation permet d'accéder facilement à l'entrée de la table des pages relative à la page `z`. Il suffit en effet d'y accéder depuis l'adresse ``P+z*n``.

Grâce à cette table des pages, il est possible de traduire directement les adresses virtuelles en adresses physiques. Cette traduction est représentée dans la figure ci-dessous. Pour réaliser cette traduction, il faut tout d'abord extraire de l'adresse virtuelle le numéro de la page. Celui-ci se trouve dans les bits de poids fort de l'adresse virtuelle. Le numéro de la page sert d'index pour récupérer l'entrée correspondant à cette page dans la table des pages. Cette entrée contient l'adresse en mémoire RAM à laquelle la page débute. Pour finaliser la traduction de l'adresse virtuelle, il suffit de concaténer les bits de poids faible de l'adresse virtuelle avec l'adresse de la page en mémoire RAM. Cette concaténation donne l'adresse réelle à laquelle la donnée est stockée en mémoire RAM. Cette adresse physique permet au processeur d'accéder directement à la donnée en mémoire.

.. [#fentree] Une entrée de la table de pages occupe généralement 32 ou 64 bits suivant les architectures de processeurs.

.. figure:: /S11/fig/figures-11-005-c.png
   :align: center
   :scale: 60

   Traduction d'adresses avec une table des pages 

La table des pages permet de traduire les adresses virtuelles en adresses physiques. Ce faisant, elle introduit un mécanisme d'indirection entre les adresses (virtuelles) qui sont utilisées par les programmes et les adresses (réelles) qui sont utilisées par le hardware. Ce mécanisme d'indirection a de nombreuses applications comme nous le verrons par la suite. Un point important à mentionner concernant l'utilisation d'un mécanisme de traduction des adresses est qu'il permet de  découpler le choix de la taille des adresses (virtuelles) utilisées par les programmes des contraintes matérielles qui sont liées directement aux mémoires RAM utilisées. En pratique, il est très possible d'avoir des systèmes informatiques dans lesquels les adresses virtuelles sont plus longues, plus courtes ou ont la même longueur que les adresses physiques. Sur un ordinateur 32 bits actuel équipé de 4 GBytes de mémoire, il est naturel d'utiliser des adresses virtuelles de 32 bits et des adresses physiques de 32 bits également pour pouvoir accéder à l'ensemble de la mémoire. Dans ce cas, la mémoire virtuelle permet d'accéder à toute la mémoire physique. Aujourd'hui, il existe des serveurs 64 bits. Ceux-ci utilisent des adresses virtuelles de 64 bits, mais aucun ordinateur ne contient :term:`2^64` bytes de mémoire. Par exemple, un serveur disposant de 128 GBytes de mémoire physique pourrait se contenter d'utiliser des adresses physiques de 37 bits. Dans ce cas, la mémoire virtuelle donne l'illusion qu'il est possible d'accéder à plus de mémoire que celle qui est réellement disponible. D'un autre côté, il est aussi possible de construire des serveurs qui utilisent des adresses virtuelles de 32 bits, mais disposent de plus de 4 GBytes de mémoire RAM. Dans ce cas, les adresses physiques pourront être plus longues que les adresses réelles. Quelles que soient les longueurs respectives des adresses virtuelles et physiques, la table des pages, sous le contrôle du système d'exploitation, permettra de réaliser efficacement les traductions entre les adresses virtuelles et les adresses physiques. 

Pour bien comprendre la traduction des adresses virtuelles en utilisant la table des pages, considérons un système imaginaire qui utilise des adresses virtuelles encodées sur 7 bits et des adresses physiques qui sont elles encodées sur 6 bits. La table des pages correspondante est reprise dans le tableau ci-dessous. Comme dans la figure précédente, la ligne du bas du tableau est relative à la page `0`.

========     =======
Validité     Adresse
========     =======
true         00
false	     -
true         11
false	     - 
false	     - 
false	     -
true         01
true         10
========     =======

Cette mémoire virtuelle contient quatre pages. La première couvre les adresses physiques allant de ``000000`` à ``001111``, la seconde de ``010000`` à ``011111`` et la dernière de ``110000`` à ``111111``. Les adresses virtuelles elles vont de ``0000000`` à ``1111111``. La traduction s'effectue sur base de la table des pages. Ainsi, l'adresse ``1010001`` correspond à l'octet ``0001`` dans la page virtuelle ``101``. Sur base la table des pages, cette page se trouve en mémoire RAM (sont bit de validité est vrai) et elle démarre à l'adresse ``110000``. L'adresse virtuelle ``1010001`` est donc traduite en l'adresse réelle ``110001``. L'adresse virtuelle ``0110111`` correspond elle à une page qui n'est pas actuellement en mémoire RAM puisque le bit de validité correspondant à la page ``011`` est faux.

Si on analyse la table des pages ci-dessus, on peut remarquer que la page contenant les adresses virtuelles les plus hautes se trouve dans la page avec les adresses physiques les plus basses. Inversement, la page qui est en mémoire RAM à l'adresse la plus élevée correspond à des adresses virtuelles qui se trouvent au milieu de l'espace d'adressage. Ce découplage entre l'adresse virtuelle et la localisation physique de la page en mémoire est un des avantages importantes de la mémoire virtuelle.

La mémoire virtuelle a aussi un rôle important à jouer lorsque plusieurs processus s'exécutent simultanément. 
Comme indiqué ci-dessus, l'adresse de la table des pages est stockée dans un des registre du processeur. L'utilisation de ce registre permet d'avoir une table des pages pour chaque processus. Pour cela, il suffit qu'une zone de mémoire RAM soit réservée pour chaque processus et que le système d'exploitation y stocke la table des pages du processus. Lors d'un changement de contexte, le système d'exploitation modifie le registre de table des pages de façon à ce qu'il pointe vers la table des pages du processus qui s'exécute. Ce mécanisme est particulièrement 

A titre d'exemple, considérons un système imaginaire utilisant des adresses virtuelles sur 6 bits et des adresses physiques sur 8 bits. Deux processus s'exécutent sur ce système et ils utilisent chacun trois pages, deux pages dans le bas de l'espace d'adressage virtuel qui correspondent à leur segment de code et une page dans le haut de l'espace d'adressage virtuel qui correspond à leur pile. Le premier tableau ci-dessous présente la table des pages du processus P1.

========     =======
Validité     Adresse
========     =======
true         0011
false	     -
true         1001
true         1000
========     =======

Le processus P2 a lui aussi sa table des pages. Celle-ci pointe vers des adresses physiques qui sont différentes de celle utilisées par le processus P1. L'utilisation d'une table des pages par processus permet à deux processus distincts d'utiliser les mêmes adresses virtuelles.

========     =======
Validité     Adresse
========     =======
true         0000
false	     -
true         1111
true         1110
========     =======

Lorsque le processus P1 s'exécute, c'est sa table des pages qui est utilisée par le processeur pour la traduction des adresses virtuelles en adresses physiques. Ainsi, l'adresse ``011101`` est traduite en l'adresse ``10011101``. Par contre, lorsque le processus P2 s'exécuté, cette adresse ``011101`` est traduite grâce à  la table des pages de ce processus en l'adresse ``11111101``.



La table des pages d'un processus contrôle les adresses physiques auxquelles le processus a accès. Pour garantir la sécurité d'un système informatique, il faut bien entendu éviter qu'un processus ne puisse modifier lui-même et sans contrôle sa table des pages. Toutes les manipulations de la table des pages ou du registre de table des pages se font sous le contrôle du système d'exploitation. La modification du registre de table des pages est une opération privilégiée qui ne peut être exécutée que par le système d'exploitation.

En termes de sécurité, une entrée de la table des pages contient également des bits de permission qui sont contrôlés par le système d'exploitation et spécifient quelles opérations peuvent être effectuées sur chaque page. Une entrée de la table des pages contient trois bits de permissions :

 - `R` bit. Ce bit indique si le processus peut accéder en lecture à la page se trouvant en mémoire physique.
 - `W` bit. Ce bit indique si le processus peut modifier le contenu de la page se trouvant en mémoire physique
 - `X` bit. Ce bit indique si la page contient des instructions qui peuvent être exécutées par le processeur ou des données.

Ces bits de protection sont généralement fixés par le système d'exploitation. Par exemple, le segment code qui ne contient que des instructions à exécuter pourra être stocké dans des pages avec les bits `R` et `X` mais pas le bit `W` pour éviter que le processus ne modifie les instructions qu'il exécute. Le stack par contre sera placé dans des pages avec les bits `R` et `W` mais pas le bit `X`. Cette technique est utilisée dans les systèmes d'exploitation récents pour éviter qu'un buffer overflow sur le stack ne conduise à l'exécution d'instructions qui ne font pas partie du processus. Le heap peut utiliser les mêmes bits de protection. Enfin, les pages qui n'ont pas été allouées au processus, notamment celles se trouvant entre le heap et le stack auront tous leurs bits de protection mis à faux. Cela permet au processeur de détecter les accès à de la mémoire qui n'a pas été allouée au processus. Un tel accès provoquera la génération d'une segmentation fault et l'envoi du signal correspondant.

Même si ces bits de protection sont contrôlés par le système d'exploitation, il est parfois utile à un processus de modifier les bits de permissions qui sont associés à certaines de ses pages. Cela peut se faire via l'appel système `mprotect(2)`_. 

.. code-block:: c

   #include <sys/mman.h>

   int mprotect(const void *addr, size_t len, int prot);
 
Cette appel système prend trois arguments. Le première est un pointeur vers le début de la zone mémoire dont il faut modifier les bits de protection. Le second est la longueur de la zone mémoire concernée et le dernier la protection souhaitée. Celle-ci est spécifiée en utilisant les constantes ``PROT_NONE``, ``PROT_READ``, ``PROT_WRITE`` et ``PROT_EXEC`` qui peuvent être combinées en utilisant une disjonction logique. La protection demandée ne peut pas être plus libérale que la protection qui est déjà fixée par le système d'exploitation. Dans ce cas, le système d'exploitation génère un signal ``SIGSEGV``.

.. todo:: TLB


Mémoire partagée
----------------

Dans les exemples précédents, nous avons supposé qu'il existe une correspondance biunivoque entre chaque page de la mémoire virtuelle et une page en mémoire RAM. C'est souvent le cas, mais ce n'est pas nécessaire. Il est tout à fait possible d'avoir plusieurs pages de la mémoire virtuelle qui appartiennent à des processus différents mais pointent vers la même page en mémoire physique. Ce partage d'une même page physique entre plusieurs pages de la mémoire virtuelle a plusieurs utilisations en pratique.

Revenons aux threads POSIX. Lorsqu'un processus crée un nouveau thread d'exécution, celui-ci a un accès complet au segment code, aux variables globales et au heap du processus. Par contre, le thread et le processus ont chacun un stack qui leur est propre. Comme nous l'avons indiqué lors de la présentation des threads, ceux-ci peuvent être implémentés en utilisant une libraire ou avec l'aide du système d'exploitation. Du point de vue de la mémoire, lorsqu'une librairie telle que `gnuth` est utilisée pour créer un thread, la librairie réserve une zone de mémoire sur le heap pour ce thread. Cette zone mémoire contient le stack qui est spécifique au thread. Celui-ci a été alloué en utilisant `malloc(3)`_ et a généralement une taille fixe. Avec la mémoire virtuelle, il est possible d'implémenter les threads plus efficacement avec l'aide du système d'exploitation. Lors de la création d'un thread, celui-ci va tout d'abord créer une nouvelle table des pages pour le thread. Celui-ci sera initialisée en copiant toutes les entrées de la table des pages du processus, sauf celles qui correspondent au stack. De cette façon, le processus "père" et le thread auront accès aux mêmes segment de code, aux même variables globales et au même heap. Toute modification faite par le processus père à une variable globale ou à une information stockée sur le heap sera immédiatement accessible au thread et inversement. L'entrée de la table des pages du thread correspondant à son stack pointera vers une page qui sera spécifique au thread. Cette page aura été initialisée par le système d'exploitation avec l'argument passé par le processus à la fonction `pthread_create(3)`_. La figure ci-dessous illustre ce partage de table des pages après la création d'un thread.

.. figure:: /S11/fig/figures-11-008-c.png
   :align: center
   :scale: 60

   Tables des pages après création d'un thread

.. todo:: mieux montrer comment cela fonctionne en la représentant en mémoire

En exploitant intelligemment la table des pages, il est également possible de permettre à deux processus distincts d'avoir accès à la même zone de mémoire physique. Si deux processus peuvent accéder simultanément à la même zone de mémoire, ils peuvent l'utiliser pour communiquer plus efficacement qu'en utilisant des pipes par exemple. Cette technique porte le nom de :term:`mémoire partagée`. Elle nécessite une modification de la table des pages des processus qui veulent partager la même zone mémoire. Pour comprendre le fonctionnement de cette :term:`mémoire partagée`, considérons le cas de deux processus : `P1` et `P2` qui veulent pouvoir utiliser une page commune en mémoire. Pour cela, plusieurs interactions entre les processus et le système d'exploitation sont nécessaires comme nous allons le voir.

Avant de permettre à deux processus d'accéder à la même page en mémoire physique, il faut d'abord se poser la question de l'origine de cette page physique. Deux solutions sont possibles. La première est de prendre cette page parmi les pages qui appartiennent à l'un des processus, par exemple `P1`. Lorsque la page est partagée, le système d'exploitation peut modifier la table des pages du processus `P2` de façon à lui permettre d'y accéder. La seconde est que le noyau du système d'exploitation fournisse une nouvelle page qui pourra être partagée. Cette page "appartient" au noyau mais celui-ci la rend accessible aux processus `P1` et `P2` en modifiant leurs tables des pages. Linux utilise la seconde technique. Elle a l'avantage de permettre un meilleur contrôle par le système d'exploitation du partage de pages entre processus. De plus, lorsqu'une zone de mémoire partagée a été créée par un processus, elle survit à la terminaison de ce processus. Une mémoire partagée créée par un processus peut donc être utilisée par d'autres processus. 

Sous Linux, la mémoire partagée peut s'utiliser via les appels système `shmget(2)`_, `shmat(2)`_ et `shmdt(2)`_. L'appel système `shmget(2)`_ permet de créer un segment de mémoire partagée. Le premier argument de  `shmget(2)`_ est une clé qui identifie le segment de mémoire partagée. Cette clé est en pratique encodée sous la forme d'un entier qui identifie le segment de mémoire partagée. Elle sert d'identifiant du segment de mémoire partagée dans le noyau. Un processus doit connaître la clé qui identifie un segment de mémoire partagée pour pouvoir y accéder. Le deuxième argument de `shmget(2)`_ est la taille du segment. En pratique, celle-ci sera arrondie au multiple entier supérieur de la taille d'une page. Enfin, le troisième argument sont des drapeaux qui contrôlent la création du segment et les permissions qui y sont associées.

.. code-block:: c

   #include <sys/ipc.h> 
   #include <sys/shm.h>
   int shmget(key_t key, size_t size, int shmflg); 

L'appel système `shmget(2)`_ retourne un entier qui identifie le segment de mémoire partagée à l'intérieur du processus si elle réussi et ``-1`` sinon. Elle peut être utilisée de deux façons. Un processus peut appeler `shmget(2)`_ pour créer un nouveau segment de mémoire partagée. Pour cela, il choisit une clé unique qui identifie se segment et utilise le drapeau ``IPC_CREAT``. Celui-ci peut être combiné avec les drapeaux qui sont supportés par l'appel système `open(2)`_. Ainsi, le fragment de code ci-dessous permet de créer une page de mémoire partagée qui a comme ``1252`` et est accessible en lecture et en écriture par tous les processus qui appartiennent au même utilisateur ou au même groupe que ceux du processus courant. Si cet appel à `shmget(2)`_ réussi, le segment de mémoire est initialisé à la valeur 0.

.. code-block:: c
    
   key_t key=1252;
   int shm_id = shmget(key, 4096, IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP ); 
   if (shm_id == -1) {
     perror("shmget");
     exit(EXIT_FAILURE);
   }

La fonction `shmget(2)`_ peut aussi être utilisée par un processus pour obtenir l'autorisation d'accéder à un segment de mémoire partagée qui a été créé par un autre processus. Dans ce cas, le drapeau `ÌPC_CREAT`` n'est pas passé en argument.

.. todo:: question IPC_EXCL
.. todo:: question peut-ton avoir un processus qui l'ouvre en read/write et l'autre en read ?

Il est important de noter que si l'appel à `shmget(2)`_, cela indique que le processus dispose des permissions pour accéder au segment de mémoire partagée, mais à ce stade il n'est pas accessible depuis la table des pages du processus. Cette modification à la table des pages du processus se fait en utilisant `shmat(2)`_. Celle-ci permet d'attacher un segment de mémoire partagée à un processus. Elle prend comme premier argument l'identifiant du segment de mémoire retourné par `shmget(2)`_. Le deuxième argument est un pointeur vers la zone mémoire via laquelle le segment doit être accessible dans l'espace d'adressage virtuel du processus. Généralement, c'est la valeur ``NULL`` qui est spécifiée comme second argument et le noyau choisit l'adresse à laquelle le segment de mémoire est attachée dans le processus. Il est aussi possible de spécifier une adresse dans l'espace d'adressage du processus. Le troisième argument permet en utilisant le drapeau ``SHM_RDONLY`` d'attacher le segment en lecture seule. `shmat(2)`_ retourne l'adresse à laquelle le segment a été attaché en cas de succès et `` (void *) -1 `` en cas d'erreur.

.. code-block:: c

   #include <sys/types.h>
   #include <sys/shm.h>

   void *shmat(int shmid, const void *shmaddr, int shmflg);

   int shmdt(const void *shmaddr);

L'appel système `shmdt(2)`_ permet de détacher un segment de mémoire qui avait été attaché en utilisant `shmat(2)`_. L'argument passé à `shmdt(2)`_ doit être une adresse d'un segment de mémoire attaché préalablement par `shmat(2)`_. Lorsqu'un processus se termine, tous les segments auxquels il était attachés sont détachés lors de l'appel à `_exit(2)`_. Cela n'empêche qu'un programme doit détacher correctement tous les segments de mémoire qu'il utilise avant de se terminer. 

Le fragment de code ci-dessous présente comment un segment de mémoire peut être attaché et détaché après avoir été créé avec `shmget(3)`_. 

.. code-block:: c

   void * addr = shmat(shm_id, NULL, 0); 
   if (addr == (void *) -1) {
     perror("shmat");
     exit(EXIT_FAILURE);
   }
   // ...
   if(shmdt(addr)==-1) {
     perror("shmdt");
     exit(EXIT_FAILURE);
   } 

.. note:: Attention aux pointeurs en mémoire partagée

  Lorsque deux processus partagent le même segment de mémoire partagée, ils ont tous les deux accès directement à la mémoire. Il est ainsi possible de stocker dans cette mémoire un tableau de nombres ou de caractères. Chacun des processus pourra facilement accéder aux données stockées dans ce tableau. Il faut cependant être vigilant lorsque l'on veut stocker une structure de donnée utilisant des pointeurs dans un segment de mémoire partagée. Considérons une liste simplement chaînée. Cette liste peut être implémentée en utilisant une structure contenant la donnée stockée dans l'élément de la liste (par exemple un entier) et un pointeur vers l'élément suivant dans la liste (et ``NULL`` en fin de liste). Imaginons que les deux processus ont attaché le segment de mémoire destiné à contenir la liste avec l'appel à `shmat(2)`_ présenté ci-dessus et que l'adresse retournée par `shmat(2)`_ est celle qui correspond au premier élément de la liste. Comme le système d'exploitation choisit l'adresse à laquelle le segment de mémoire partagée est stocké dans chaque processus, l'appel à `shmat(2)`_ retourne une adresse différente dans les deux processus. Si ils peuvent tous les deux accéder au premier élément de la liste, il n'en sera pas de même pour le second élément. En effet, si cet élément a été créé par le premier processus, ce pointeur contiendra l'adresse du second élément dans l'espace d'adressage virtuel du premier processus. Cette adresse ne correspond en général pas à celle du second élément dans l'espace d'adressage du second processus. En pratique, il est préférable de ne pas utiliser de pointeurs dans un segment de mémoire partagé. 

.. todo:: exercice, comment implémenter cette liste chaînée


Les segments de mémoire partagée étant gérés par le noyau du système d'exploitation, ils persistent après la terminaison du processus qui les a créé. C'est intéressant lorsque l'on veut utiliser des segments de mémoire partagée pour la communication entre plusieurs processus dont certains peuvent se crasher. Malheureusement, le nombre de segments de mémoire partagée qui peuvent être utilisés sur un système Unix est borné. Lorsque la limite fixée par la configuration du noyau est atteinte, il n'est plus possible de créer de nouveau segment de mémoire partagée. Sous Linux ces limites sont visibles dans les fichiers ``/proc/sys/kernel/shmni`` (nombre maximum d'identifiants de segments de mémoire partagée) et ``/proc/sys/kernel/shmall`` (taille totale maximale de la mémoire partagée) ou via `shmctl(2)`_. Cet appel système permet de réaliser de nombreuses fonctions de contrôle de la mémoire partagée et notamment la destruction de segments de mémoire partagée qui ont été créés par `shmget(2)`_. `shmctl(2)`_ s'appuie sur les structures de données qui sont maintenues par le noyau pour les segments de mémoire partagée. Lorsqu'un segment de mémoire partagée est crée, le noyau lui associe une structure de type ``shdim_ds``. 

.. code-block:: c

  struct shmid_ds {
    struct ipc_perm shm_perm;    /* Propriétaire et permissions */
    size_t          shm_segsz;   /* Taille du segment (bytes) */
    time_t          shm_atime;   /* Instant de dernier attach */
    time_t          shm_dtime;   /* Instant de dernier detach */
    time_t          shm_ctime;   /* Instant de dernière modification */
    pid_t           shm_cpid;    /* PID du créateur */
    pid_t           shm_lpid;    /* PID du dernier `shmat(2)`_ / `shmdt(2)`_ */
    shmatt_t        shm_nattch;  /* Nombre de processus attachés */
  };

Ce descripteur de segment de mémoire partagée, décrit dans `shmctl(2)`_ contient plusieurs informations utiles. Son premier élément est une structure qui reprend les informations sur le propriétaire et les permissions qui ont été définies ainsi que la taille du segment. Le descripteur de segment comprend ensuite les instants auxquels les dernières opérations `shmat(2)`_, `shmdt(2)`_ et la dernière modification au segment ont été faites. Le dernier élément contient le nombre de processus qui sont actuellement attachés au segment. L'appel système `shmctl(2)`_ prend trois arguments. Le premier est un identifiant de segment de mémoire partagée retourné par `shmget(2)`_. Le deuxième est une constante qui spécifie une commande. Nous utiliseront uniquement la commande ``IPC_RMID`` qui permet de retirer le segment de mémoire partagée dont l'identifiant est passé comme premier argument. Si il n'y a plus de processus attaché au segment de mémoire partagée, celui-ci est directement supprimé. Sinon, il est marqué de façon à ce que le noyau retire le segment dès que le dernier processus s'en détache. `shmctl(2)`_ retourne ``0`` en cas de succès et ``-1`` en cas d'échec.

.. code-block:: c

    #include <sys/ipc.h> 
    #include <sys/shm.h>

    int shmctl(int shmid, int cmd, struct shmid_ds *buf);  

Le segment de mémoire partagée qui a été créé dans les exemples précédents peut être supprimé avec le fragment de code ci-dessous.

.. code-block:: c

    if (shmctl(shm_id, IPC_RMID, 0) != 0) {
       perror("shmctl");
       exit(EXIT_FAILURE);
    }

En pratique, comme le noyau ne détruit un segment de mémoire partagée que lorsqu'il n'y a plus de processus qui y est attaché, il peut être utile de détruire le segment de mémoire partagée juste après avoir effectué l'appel `shmat(2)`_. C'est ce que l'on fera par exemple si un processus père utilise un segment de mémoire partagée pour communiquer avec son processus fils. 


La mémoire partagée est utilisée non seulement pour permettre la communication entre processus, mais également avec les librairies partagées. Celles-ci sont chargées automatiquement lors de l'exécution d'un processus qui les utilise. Les instructions qui font partie de ces librairies partagées sont chargées dans la même zone mémoire que celle qui est utilisée pour la mémoire partagée. Sous Linux, cette zone mémoire est située entre le heap et le stack comme illustré dans la figure ci-dessous.

.. figure:: /S11/fig/figures-11-012-c.png
   :align: center
   :scale: 60

   Organisation en mémoire d'un processus 


Lorsqu'il exécute un processus, le noyau maintient dans les structures de données qui sont relatives à ce processus la liste des segments de mémoire partagée et des librairies partagées qu'il utilise. Sous Linux, cette information est visible via le pseudo-système de fichiers ``/proc``. Le fichier ``/proc/PID/maps`` représente de façon textuelle la table des segments de mémoire qui sont partagés dans le processus ``PID``.


Un exemple d'un tel fichier `maps` est présenté ci-dessous. Il contient une carte de l'ensemble des pages qui appartiennent à un processus. Le fichier comprend six colonnes. La première est la zone de mémoire virtuelle. La seconde sont les bits de permission avec `r` pour la permission de lecture, `w` d'écriture et `x` pour l'exécution. Le dernier bit de permission est à la valeur `p` lorsque la page est en :term:`copy-on-write` et `s` lorsqu'il s'agit d'un segment de mémoire partagé. Les trois dernières colonnes sont relatives au stockage des pages sur le disque. Nous y reviendrons ultérieurement. 

.. code-block:: console

   00400000-00402000 r-xp 00000000 00:1a 49485798      /tmp/a.out   
   00602000-00603000 rw-p 00002000 00:1a 49485798      /tmp/a.out       
   3d3f200000-3d3f220000 r-xp 00000000 08:01 268543    /lib64/ld-2.12.so
   3d3f41f000-3d3f420000 r--p 0001f000 08:01 268543    /lib64/ld-2.12.so
   3d3f420000-3d3f421000 rw-p 00020000 08:01 268543    /lib64/ld-2.12.so
   3d3f421000-3d3f422000 rw-p 00000000 00:00 0 
   3d3f600000-3d3f786000 r-xp 00000000 08:01 269510    /lib64/libc-2.12.so
   3d3f786000-3d3f986000 ---p 00186000 08:01 269510    /lib64/libc-2.12.so
   3d3f986000-3d3f98a000 r--p 00186000 08:01 269510    /lib64/libc-2.12.so
   3d3f98a000-3d3f98b000 rw-p 0018a000 08:01 269510    /lib64/libc-2.12.so
   3d3f98b000-3d3f990000 rw-p 00000000 00:00 0 
   3d3fa00000-3d3fa83000 r-xp 00000000 08:01 269516    /lib64/libm-2.12.so
   3d3fa83000-3d3fc82000 ---p 00083000 08:01 269516    /lib64/libm-2.12.so
   3d3fc82000-3d3fc83000 r--p 00082000 08:01 269516    /lib64/libm-2.12.so
   3d3fc83000-3d3fc84000 rw-p 00083000 08:01 269516    /lib64/libm-2.12.so
   7f7c57e42000-7f7c57e45000 rw-p 00000000 00:00 0 
   7f7c57e60000-7f7c57e61000 rw-s 00000000 00:04 66355276 /SYSV00000000 
   7f7c57e61000-7f7c57e63000 rw-p 00000000 00:00 0 
   7fffc479c000-7fffc47b1000 rw-p 00000000 00:00 0            [stack]


L'exemple ci-dessus présente la carte de mémoire d'un processus qui utilise trois librairies partagées. Le segment de mémoire partagée se trouve aux adresses virtuelles  ``7f7c57e60000-7f7c57e61000``. Il est accessible en lecture et en écriture.


Implémentation de `fork(2)`_
----------------------------

Enfin, pour terminer cette première présentation de la mémoire virtuelle, il est intéressant de revenir à l'appel système `fork(2)`_. Cet appel est fondamental sur un système Unix. Au fil des années, les développeurs de Unix et Linux ont cherché à optimiser les performances de cet appel système. Une implémentation naïve de l'appel système `fork(2)`_ est de copier physiquement toutes les pages utilisées en mémoire RAM par le processus père. Ensuite, le noyau peut créer une table des pages pour le processus fils qui pointe vers les copies des pages du processus père. De cette façon, le processus père et le processus fils utilisent exactement les mêmes instructions et poursuivront leur exécution à partir des mêmes données en mémoire. Mais chaque processus pourra faire les modifications qu'il souhaite aux données stockées en mémoire. Cette implémentation était utilisée par les premières versions de Unix, mais elle est inefficace, notamment pour les processus qui consomment beaucoup de mémoire et le shell qui généralement exécute `fork(2)`_ et juste après `execve(2)`_. Dans ce dernier cas, copier l'entièreté de la mémoire du processus père est un gaspillage de ressources. 

La mémoire virtuelle permet d'optimiser l'appel système `fork(2)`_ et de le rendre nettement plus rapide. Lors de la création d'un processus fils, le noyau du système d'exploitation commence par créer une table des pages pour le processus fils. En initialisant cette table avec les mêmes entrées que celles du processus père, le noyau permet aux deux processus d'accéder aux mêmes instructions et aux mêmes données. Pour les instructions se trouvant dans le segment code et dont les entrées de la table des pages sont généralement en `read-only`, cette solution fonctionne correctement. Le processus père et le processus fils peuvent exécuter exactement les mêmes instructions tout en n'utilisant qu'une seule copie de ces instructions en mémoire. 

Malheureusement, cette solution ne fonctionne pas pour les pages contenant les données globales, le stack et le heap. En effet, ces pages doivent pouvoir être modifiées de façon indépendante par le processus père et le processus fils. C'est notamment le cas pour la zone mémoire qui contient la valeur de retour de l'appel système `fork(2)`_. Par définition, cette zone mémoire doit contenir une valeur différente dans le processus père et le processus fils. Pour éviter ce problème, le noyau pourrait copier physiquement les pages contenant les variables globales, le heap et le stack. Cela permettrait, notamment dans le cas de l'exécution de `fork(2)`_ par le shell d'améliorer les performances de `fork(2)`_ sans pour autant compromettre la sémantique de cet appel système. Il existe cependant une alternative à cette copie physique. Il s'agit de la technique du :term:`copy-on-write`.

Sur un système qui utilise :term:`copy-on-write`, l'appel système `fork(2)`_ est implémenté comme suit. Lors de l'exécution de `fork(2)`_, le noyau copie toutes les entrées de la table des pages du processus père vers la table des pages du processus fils. Ce faisant, le noyau modifie également les permissions de toutes les pages utilisées par le processus père. Les pages correspondant au segment de code sont toutes marquées en lecture seule. Les pages correspondant aux données globales, heap et stack sont marquées avec un statut spécial (:term:`copy-on-write`). Celui-ci autorise les accès en lecture à la page sans restriction. Si un processus tente un accès en écriture sur une de ces pages, le MMU interrompt l'exécution du processus et force l'exécution d'une routine d'interruption du noyau. Celle-ci analyse la tentative d'accès à la mémoire qui a échoué. Si la page était en lecture seule (par exemple une page du segment de code), un signal ``SIGSEGV`` est envoyé au processus concerné. Si par contre la page était marquée :term:`copy-on-write`, alors le noyau alloue une nouvelle page physique et y recopie la page où la tentative d'accès a eu lieu. La table des pages du processus qui a fait la tentative d'accès est modifiée pour pointer vers la nouvelle page avec une permission en lecture et écrite. La permission de l'entrée de la table des pages de l'autre processus est également modifiée de façon à autoriser les écritures et les lectures. Les deux processus disposent donc maintenant d'une copie différente de cette page et ils peuvent la modifier à leur guise. Cette technique de :term:`copy-on-write` permet de ne copier que les pages qui sont modifiées par le processus père ou le processus fils. C'est un gain de temps appréciable par rapport à la copie complète de toutes les pages.

Dans le pseudo fichier ``/proc/PID/maps`` présenté avant, le bit `p` indique que les pages correspondantes sont en `copy-on-write`.

.. todo: faire exemple avec un processus père qui fait fork puis le fils accède à 100, 1000 pages (qui seront copiées), montrer l'évolution du temps d'accès à ces pages 

.. rubric:: Footnotes

.. [#fmmu] En pratique, les adresses sur le disque dur ne sont pas stockées dans le :term:`MMU` mais dans une table maintenue par le système d'exploitation. C'est le noyau qui est responsable des transferts entre le dispositif de stockage et la mémoire RAM.

.. [#fintel] Source : http://www.intel.com/content/www/us/en/solid-state-drives/ssd-320-specification.html

.. [#fseagate] Source : http://www.seagate.com/staticfiles/support/disc/manuals/desktop/Barracuda%207200.11/100507013e.pdf

.. [#fentree] Une entrée de la table de pages occupe généralement 32 ou 64 bits suivant les architectures de processeurs.
