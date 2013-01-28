.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Les sémaphores
==============

.. todo:: Mieux introduire les sémaphores et leur intérêt en comparant avec les moniteurs, la synchronisation par messages, etc. 

Le problème de la coordination entre threads est un problème majeur. Outre les :term:`mutex` que nous avons présenté, d'autres solutions à ce problème ont été développées. Historiquement, une des premières propositions de coordination sont les sémaphores [Dijkstra1965b]_. Un :term:`sémaphore` est une structure de données qui est maintenue par le système d'exploitation et contient :

 - un entier qui stocke la valeur, positive ou nulle, du sémaphore.
 - une queue qui contient les pointeurs vers les threads qui sont bloqués en attente sur ce sémaphore.

Tout comme pour les :term:`mutex`, la queue associée à un sémaphore permet de bloquer les threads qui sont en attente d'une modification de la valeur du sémaphore.

Une implémentation des sémaphores se compose en général de quatre fonctions :

 - une fonction d'initialisation qui permet de créer le sémaphore et de lui attribuer une valeur initiale nulle ou positive. 
 - une fonction permettant de détruire un sémaphore et de libérer les ressources qui y sont associées.
 - une fonction ``post`` qui est utilisée par les threads pour modifier la valeur du sémaphore. Si il n'y a pas de thread en attente dans la queue associée au sémaphore, sa valeur est incrémentée d'une unité. Sinon, un des threads en attente est libéré et passe à l'état `Ready`.
 - une fonction ``wait`` qui est utilisée par les threads pour tester la valeur d'un sémaphore. Si la valeur du sémaphore est positive, elle est décrémentée d'une unité et la fonction réussit. Si le sémaphore a une valeur nulle, le thread est bloqué jusqu'à ce qu'un autre thread le débloque en appelant la fonction ``post``.

.. [Dijkstra1965b]_

Les sémaphores sont utilisés pour résoudre de nombreux problèmes de coordination [Downey2008]_. Comme ils permettent de stocker une valeur entière, ils sont plus flexibles que les :term:`mutex` qui sont utiles surtout pour les problèmes d'exclusion mutuelle.


Sémaphores POSIX
----------------

La libraire POSIX comprend une implémentation des sémaphores [#fSysV]_ qui expose plusieurs fonctions aux utilisateurs. La page de manuel `sem_overview(7)`_ présente de façon sommaire les fonctions de la librairie relatives aux sémaphores. Les quatre principales sont les suivantes :

.. code-block:: c

 #include <semaphore.h>

 int sem_init(sem_t *sem, int pshared, unsigned int value); 
 int sem_destroy(sem_t *sem); 
 int sem_wait(sem_t *sem);
 int sem_post(sem_t *sem);

Le fichier `semaphore.h`_ contient les différentes définitions de structures qui sont nécessaires au bon fonctionnement des sémaphores ainsi que les signatures des fonctions de l'API. Un sémaphore est représenté par une structure de données de type ``sem_t``. Toutes les fonctions de manipulation des sémaphores prennent comme argument un pointeur vers le sémaphore concerné.

Pour pouvoir utiliser un sémaphore, il faut d'abord l'initialiser. Cela se fait en utilisant la fonction `sem_init(3)`_ qui prend comme argument un pointeur vers le sémaphore à initialiser. Nous n'utiliserons pas le second argument dans ce chapitre. Le troisième argument est la valeur initiale, positive ou nulle du sémaphore.

La fonction `sem_destroy(3)`_ permet de libérer un sémaphore qui a été initialisé avec `sem_init(3)`_. Les sémaphores consomment des ressources qui peuvent être limitées dans certains environnements. Il est important de détruire proprement les sémaphores dès qu'ils ne sont plus nécessaires.

Les deux principales fonctions de manipulation des sémaphores sont `sem_wait(3)`_ et `sem_post(3)`_. Certains auteurs utilisent ``down`` ou ``P`` à la place de `sem_wait(3)`_  et ``up`` ou ``V`` à la place de `sem_post(3)`_ [Downey2008]_. Schématiquement, l'opération ``sem_wait`` peut s'implémenter en utilisant le pseudocode suivant :

.. code-block:: c

 int sem_wait(semaphore *s)
 {
  s->val=s->val-1;
  if(s->val<0)
  {
   // Place this thread in s.queue;
   // This thread is blocked;
  }
 } 

La fonction `sem_post(3)`_ quant à elle peut schématiquement s'implémenter comme suit :


.. code-block:: c

  int sem_post(semaphore *s)
  {
    s->val=s->val+1;
    if(s.val<=0)
    {
      // Remove one thread(T) from s.queue;
      // Mark Thread(T) as ready to run;
    }
  }
  
Ces deux opérations sont bien entendu des opérations qui ne peuvent s'exécuter simultanément. Leur implémentation réelle comprend des sections critiques qui doivent être construites avec soin. Le pseudocode ci-dessus ignore ces sections critiques. Des détails complémentaires sur l'implémentation des sémaphores peuvent être obtenus dans un textbook sur les systèmes d'exploitation [Stallings2011]_ [Tanenbaum+2009]_ .

La meilleure façon de comprendre leur utilisation est d'analyser des problèmes classiques de coordination qui peuvent être résolus en utilisant des sémaphores.

Exclusion mutuelle
------------------

Les sémaphores permettent de résoudre de nombreux problèmes classiques. Le premier est celui de l'exclusion mutuelle. Lorsqu'il est initialisé à ``1``, un sémaphore peut être utilisé de la même façon qu'un :term:`mutex`. En utilisant des sémaphores, une exclusion mutuelle peut être protégée comme suit :


.. code-block:: c

   #include <semaphore.h>

   //...

   sem_t semaphore;

   sem_init(&semaphore, 0, 1);
   
   sem_wait(&semaphore);
   // section critique
   sem_post(&semaphore);

   sem_destroy(&semaphore); 

Les sémaphores peuvent être utilisés pour d'autres types de synchronisation. Par exemple, considérons une application découpée en threads dans laquelle la fonction ``after`` ne peut jamais être exécutée avant la fin de l'exécution de la fonction ``before``. Ce problème de coordination peut facilement être résolu en utilisant un sémaphore qui est initialisé à la valeur ``0``. La fonction ``after`` doit démarrer par un appel à `sem_wait(3)`_ sur ce sémaphore tandis que la fonction ``before`` elle doit se terminer par un appel à la fonction `sem_post(3)`_ sur ce sémaphore. De cette façon, si le thread qui exécute la fonction ``after`` est trop rapide, il sera bloqué sur l'appel à `sem_wait(3)`_. Si il arrive à cette fonction après la fin de la fonction ``before`` dans l'autre thread, il pourra passer sans être bloqué. Le programme ci-dessous illustre cette utilisation des sémaphores POSIX.

.. literalinclude:: /S7/src/pthread-sem-before.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB


Si conceptuellement un sémaphore initialisé à la valeur ``1`` est généralement utilisé comme un :term:`mutex`, il y a une différence importante entre les implémentations des sémaphores et des :term:`mutex`. Un sémaphore est conçu pour être manipulé par différents threads et il est très possible qu'un thread exécute `sem_wait(3)`_ et qu'un autre exécute `sem_post(3)`_. Pour les mutex, certaines implémentations supposent que c'est le même thread qui exécute `pthread_mutex_lock(3posix)`_ et `pthread_mutex_unlock(3posix)`_. Lorsque ces opérations doivent être effectuées dans des threads différents, il est préférable d'utiliser des sémaphores à la place de mutex.


Problème du rendez-vous
-----------------------

Le problème du rendez-vous [Downey2008]_ est un problème assez courant dans les applications multithreadées. Considérons une application découpée en `N` threads. Chacun de ces threads travaillent en deux phases. Durant la première phase, tous les threads sont indépendants et peuvent s'exécuter simultanément. Cependant, un thread ne peut démarrer sa seconde phase que si tous les `N` threads ont terminé leur première phase. L'organisation de chaque thread est donc :

.. code-block:: c

   premiere_phase();
   // rendez-vous
   seconde_phase();

Chaque thread doit pouvoir être bloqué à la fin de la première phase en attendant que tous les autres threads aient fini d'exécuter leur première phase. Cela peut s'implémenter en utilisant un mutex et un sémaphore.


.. code-block:: c

   sem_t rendezvous;
   pthread_mutex_t mutex;
   int count=0;

   sem_init(&rendezvous,0,0);


La variable ``count`` permet de compter le nombre de threads qui ont atteint le point de rendez-vous. Le ``mutex`` protège les accès à la variable ``count`` qui est partagée entre les différents threads. Le sémaphore ``rendezvous`` est initialisé à la valeur ``0``. Le rendez-vous se fera en bloquant les threads sur le sémaphore ``rendezvous`` tant que les ``N`` threads ne sont pas arrivés à cet endroit.

.. code-block:: c

   premiere_phase();

    // section critique
    pthread_mutex_lock(&mutex);
    count++;
     if(count==N) {
       // tous les threads sont arrivés
       sem_post(&rendezvous);
       }
    pthread_mutex_unlock(&mutex);
   // attente à la barrière 
   sem_wait(&rendezvous);
   // libération d'un autre thread en attente
   sem_post(&rendezvous);

   seconde_phase();

Le pseudocode ci-dessus présente une solution permettant de résoudre ce problème du rendez-vous. Le sémaphore étant initialisé à ``0``, le premier thread qui aura terminé la première phase sera bloqué sur ``sem_wait(&rendezvous);``. Les ``N-1`` premiers threads qui auront terminé leur première phase seront tous bloqués à cet endroit. Lorsque le dernier thread finira sa première phase, il incrémentera ``count`` puis exécutera ``sem_post(&rendezvous);`` ce qui libèrera un premier thread. Le dernier thread sera ensuite bloqué sur ``sem_wait(&rendezvous);`` mais il ne restera pas bloqué longtemps car chaque fois qu'un thread parvient à passer ``sem_wait(&rendezvous);``, il exécute immédiatement ``sem_post(&rendezvous);`` ce qui permet de libérer un autre thread en cascade.

Cette solution permet de résoudre le problème du rendez-vous avec un nombre fixe de threads. Certains implémentations de la librairie threads POSIX implémentent une barrière qui peut s'utiliser de la même façon que la solution ci-dessus. Une barrière est une structure de données de type ``pthread_barrier_t``. Elle s'initialise en utilisant la fonction `pthread_barrier_init(3posix)`_ qui prend trois arguments : un pointeur vers une barrière, des attributs optionnels et le nombre de threads qui doivent avoir atteint la barrière pour que celle-ci s'ouvre. La fonction `pthread_barrier_destroy(3posix)`_ permet de détruire une barrière. Enfin, la fonction `pthread_barrier_wait(3posix)`_ qui prend comme argument un pointeur vers une barrière.


Problème des producteurs-consommateurs
--------------------------------------

Le problème des producteurs consommateurs est un problème extrêmement fréquent et important dans les applications découpées en plusieurs threads. Il est courant de structurer une telle application, notamment si elle réalise de longs calculs en deux types de threads :

 - les `producteurs`. Ce sont des threads qui produisent des données et placent le résultat de leurs calculs dans une zone mémoire accessible aux consommateurs.
 - les `consommateurs`. Ce sont des threads qui utilisent les valeurs calculées par les producteurs. 

Ces deux types de threads communiquent en utilisant un buffer qui a une capacité limité à `N` slots comme illustré dans la figure ci-dessous.

.. figure:: /S7/fig/figures-S7-001-c.png
   :align: center
   :scale: 80

   Problème des producteurs-consommateurs

La difficulté du problème est de trouver une solution qui permet aux producteurs et aux consommateurs d'avancer à leur rythme sans que les producteurs ne bloquent inutilement les consommateurs et inversement. Le nombre de producteurs et de consommateurs ne doit pas nécessairement être connu à l'avance et ne doit pas être fixe. Un producteur peut arrêter de produire à n'importe quel moment.

Le buffer étant partagé entre les producteurs et les consommateurs, il doit nécessairement être protégé par un :term:`mutex`. Les producteurs doivent pouvoir ajouter de l'information dans le buffer partagé tant qu'il y a au moins un slot de libre dans le buffer. Un producteur ne doit être bloqué que si tout le buffer est rempli. Inversement, les consommateurs doivent être bloqués uniquement si le buffer est entièrement vide. Dès qu'une donnée est ajoutée dans le buffer, un consommateur doit être réveillé pour traiter cette donnée.

Ce problème peut être résolu en utilisant deux sémaphores et un mutex. L'accès au buffer, que ce soit par les consommateurs ou les producteurs est une section critique. Cet accès doit donc être protégé par l'utilisation d'un mutex. La solution au problème des producteurs-consommateurs utilise deux sémaphores. Le premier, baptisé ``empty`` dans l'exemple ci-dessous, sert à compter le nombre de slots qui sont vides dans le buffer partagé. Ce sémaphore doit être initialisé à la taille du buffer puisqu'initialement celui-ci est vide. Le second sémaphore est baptisé ``full`` dans le pseudocode ci-dessous. Sa valeur représente le nombre de slots du buffer qui sont occupés. Il doit être initialisé à la valeur ``0``.

.. code-block:: c

   // Initialisation 
   #define N 10 // slots du buffer
   pthread_mutex_t mutex;	
   sem_t empty;
   sem_t full;

   pthread_mutex_init(&mutex, NULL);
   sem_init(&empty, 0 , N);  // buffer vide
   sem_init(&full, 0 , 0);   // buffer vide

Le fonctionnement général d'un producteur est le suivant. Tout d'abord, le producteur est mis en attente sur le sémaphore ``empty``. Il ne pourra passer que si il y a au moins un slot du buffer qui est non-vide. Lorsque la ligne ``sem_wait(&empty);`` réussi, le producteur s'approprie le ``mutex`` et modifie le buffer de façon à insérer l'élément produit (dans ce cas un entier). Il libère ensuite le ``mutex`` pour sortir de sa section critique

.. code-block:: c

   // Producteur
   void producer(void)
   {
     int item;
     while(true)
     {   
       item=produce(item);
       sem_wait(&empty); // attente d'un slot libre
       pthread_mutex_lock(&mutex);
        // section critique
        insert_item();
       pthread_mutex_unlock(&mutex);
       sem_post(&full); // il y a un slot rempli en plus
     }
   }


Le consommateur quant à lui essaye d'abord de prendre le sémaphore ``full``. Si celui-ci est positif, cela indique la présence d'au moins un élément dans le buffer partagé. Ensuite il entre dans la section critique protégée par le ``mutex`` et récupère la donnée se trouvant dans le buffer. Ensuite, il incrémente la valeur du sémaphore ``empty`` de façon à indiquer à un producteur qu'un nouveau slot est disponible dans le buffer.

.. code-block:: c

  // Consommateur
  void consumer(void)
  {
   int item;
   while(true)
   {
     sem_wait(&full); // attente d'un slot rempli
     pthread_mutex_lock(&mutex);
      // section critique
      item=remove(item);
     pthread_mutex_unlock(&mutex);
     sem_post(&empty); // il y a un slot libre en plus
   }    
  }

.. Durant l'exécution du programme le sémaphore les valeurs des sémaphores 

De nombreux programmes découpés en threads fonctionnent avec un ensemble de producteurs et un ensemble de consommateurs. 


Problème des readers-writers
----------------------------

Le :term:`problème des readers-writers` est un peu différent du précédent. Il permet de modéliser un problème qui survient lorsque des threads doivent accéder à une base de données [Courtois+1971]_. Les threads sont généralement de deux types.

 - les lecteurs (`readers`) sont des threads qui lisent une structure de données (ou une base de données) mais ne la modifient pas. Comme ces threads se contentent de lire de l'information en mémoire, rien ne s'oppose à ce que plusieurs `readers` s'exécutent simultanément. 
 - les écrivains (`writers`). Ce sont des threads qui modifient une structure de données (ou une base de données). Pendant qu'un `writer` manipule la structure de données, il ne peut y avoir aucun autre `writer` ni de `reader` qui accède à cette structure de données. Sinon, la concurrence des opérations de lectures et d'écritures donnerait un résultat incorrect.

Une première solution à ce problème est d'utiliser un mutex et un sémaphore [Courtois+1971]_. 

.. code-block:: c

 pthread_mutex_t mutex;
 sem_t db;  // accès à la db
 int readcount=0; // nombre de readers
 
 sem_init(&db, NULL, 1).

La solution utilise une variable partagée : ``readcount``. L'accès à cette variable est protégé par ``mutex``. Le sémaphore ``db`` sert à réguler l'accès des `writers` à la base de données. Le mutex est initiliasé comme d'habitude par la fonction `pthread_mutex_init(3posix)`_. Le sémaphore ``db`` est initialisé à la valeur ``1``. Le `writer` est assez simple :

.. code-block:: c

 void writer(void)
 {
  while(true)
  {
    prepare_data();
    sem_wait(&db);
      // section critique, un seul writer à la fois
      write_database();
    sem_post(&db);
    }
  }
 }


Le sémaphore ``db`` sert à assurer l'exclusion mutuelle entre les `writers` pour l'accès à la base de données. Le fonctionnement des `readers` est plus intéressant. Pour éviter un conflit entre les `writers` et les `readers`, il est nécessaire d'empêcher aux `readers` d'accéder à la base de données pendant qu'un `writer` la modifie. Cela peut se faire en utilisant l'entier `readcount` qui permet de compter le nombre de `readers` qui manipulent la base de données. Cette variable est testée et modifiée par tous les `readers`, elle doit donc être protégée par un :term:`mutex`. Intuitivement, lorsque le premier `reader` veut accéder à la base de données (``readcount==0``), il essaye de décrémenter le sémaphore ``db``. Si ce sémaphore est libre, le `reader` accède à la base de données. Sinon, il bloque sur ``sem_wait(&db);`` et comme il possède ``mutex``, tous les autres `readers` sont bloqués sur ``pthread_mutex_lock(&mutex);``. Dès que le premier `reader` est débloqué, il autorise en cascade l'accès à tous les autres `readers` qui sont en attente en libérant ``pthread_mutex_unlock(&mutex);``. Lorsqu'un `reader` arrête d'utiliser la base de données, il vérifie si il était le dernier `reader`. Si c'est le cas, il libère le sémaphore ``db`` de façon à permettre à un `writer` d'y accéder. Sinon, il décrémente simplement la variable ``readcount`` pour tenir à jour le nombre de `readers` qui sont actuellement en train d'accéder à la base de données.


.. code-block:: c

  void reader(void)
  {
   while(true)
   {
     pthread_mutex_lock(&mutex);
       // section critique
       readcount++;
       if (readcount==1) 
       { // arrivée du premier reader
         sem_wait(&db);
       }
     pthread_mutex_unlock(&mutex);
     read_database();
     pthread_mutex_lock(&mutex);
       // section critique
       readcount--;
       if(readcount==0)
       { // départ du dernier reader 
         sem_post(&db);
       }
     pthread_mutex_unlock(&mutex);
     process_data();
   }
  }

.. Cette solution est un exemple atypique de l'utilisation de :term:`mutex` puisque le :term:`mutex` ``db`` peut être réservé par un thread `reader` et libérer par un tout autre thread. D'habitude, c'est généralement le même thread qui exécute `pthread_mutex_lock(3)`_ et `pthread_mutex_unlock(3)`_ pour un mutex donné.

Cette solution fonctionne et garantit qu'il n'y aura jamais qu'un seul `writer` qui accède à la base de données. Malheureusement, elle souffre d'un inconvénient majeur lorsqu'il y a de nombreux `readers`. Dans ce cas, il est très possible qu'il y aie en permanence des `readers` qui accèdent à la base de données et que les `writers` soient toujours empêchés d'y accéder. En effet, dès que le premier `reader` a effectué ``sem_wait(&db);``, aucun autre `reader` ne devra exécuter cette opération tant qu'il restera au moins un `reader` accédant à la la base de données. Les `writers` par contre resteront bloqués sur l'exécution de ``sem_wait(&db);``.

En utilisant des sémaphores à la place des :term:`mutex`, il est possible de contourner ce problème. Cependant, cela nécessite d'utiliser plusieurs sémaphores. Intuitivement, l'idée de la solution est de donner priorité aux `writers` par rapport aux `readers`. Dès qu'un `writer` est prêt à accéder à la base de données, il faut laisser empêcher de nouveaux `readers` d'y accéder tout en permettant aux `readers` présents de terminer leur lecture.

Cette solution utilise trois mutex, deux sémaphores et deux variables partagées : ``readcount`` et ``writecount``. Ces deux variables servent respectivement à compter le nombre de `readers` qui accèdent à la base de données et le nombre de `writers` qui veulent y accéder. Le sémaphore ``wsem`` est utilisé pour bloquer les `writers` tandis que le sémaphore ``rsem`` sert à bloquer les `readers`. Le mutex ``z`` a un rôle particulier qui sera plus clair lorsque le code des `readers` aura été présenté. Les deux sémaphores sont initialisés à la valeur ``1``.
 
.. code-block:: c

  /* Initialisation */
  pthread_mutex_t mutex_readcount; // protège readcount
  pthread_mutex_t mutex_writecount; // protège writecount
  pthread_mutex_t z; // un seul reader en attente
  sem_t wsem;       // accès exclusif à la db
  sem_t rsem;       // pour bloquer des readers
  int readcount=0;
  int writecount=0;
  
  sem_init(&wsem, 0, 1);
  sem_init(&rsem, 0, 1);


Un `writer` utilise la variable ``writecount`` pour compter le nombre de `writers` qui veulent accéder à la base de données. Cette variable est protégée par ``mutex_writecount``. Le sémaphore ``wsem`` est utilisé pour garantir qu'i n'y a qu'un seul `writer` qui peut accéder à un moment donné à la base de données. Cette utilisation est similaire à celle du sémaphore ``db`` dans la solution précédente.

.. code-block:: c

   /* Writer */
   while(true)
   {
     think_up_data();

     pthread_mutex_lock(&mutex_writecount);
       // section critique - writecount
       writecount=writecount+1;
       if(writecount==1) {
         // premier writer arrive
	 sem_wait(&rsem); 
       }
     pthread_mutex_unlock(&mutex_writecount);
     
     sem_wait(&wsem);
       // section critique, un seul writer à la fois
       write_database();
     sem_post(&wsem);

     pthread_mutex_lock(&mutex_writecount);
        // section critique - writecount
        writecount=writecount-1;
        if(writecount==0) {
	  // départ du dernier writer
	  sem_post(&rsem); 
        }
     pthread_mutex_unlock(&mutex_writecount);
    }


Pour comprendre le reste du fonctionnement des `writers`, il faut analyser en parallèle le fonctionnement des `readers` car les deux types de threads interagissent de façon importante. Un `reader` utilise la variable ``readcount`` protégée par le ``mutex_readcount`` pour compter le nombre de `readers` en attente. Un `reader` utilise deux sémaphores. Le premier est ``wsem`` qui joue un rôle similaire au sémaphore ``db`` de la solution précédente. Le premier `reader` qui veut accéder à la base de données (``readcount==1``) effectue ``sem_wait(&wsem)`` pour garantir qu'il n'y aura pas de `writer` qui accède à la base de données pendant qu'il y lit. Lorsque le dernier `reader` n'a plus besoin d'accéder à la base de données (``readcount==0``), il libère les `writers` qui étaient potentiellement en attente en exécutant ``sem_post(&wsem)``. 

Le sémaphore ``rsem`` répond à un autre besoin. Il permet de bloquer les `readers` en attente lorsqu'un `writer` veut accéder à la base de données. En effet, le premier `writer` qui veut accéder à la base de données exécute ``sem_wait(&rsem)``. Cela a pour effet de bloquer les nouveaux `readers` qui voudraient accéder à la base de données sur ``sem_wait(&rsem)``. Ils ne seront débloqués que lorsque le dernier `writer` (``writecount==0``) quittera la base de données et exécutera ``sem_post(&rsem)``. Lorsqu'aucun writer n'accède à la base de données, les readers peuvent facilement exécuter ``sem_wait(&rsem)`` qui sera rapidement suivi de ``sem_post(&rsem)``.


.. code-block:: c

  /* Reader */
  while(true)
  {
    pthread_mutex_lock(&z);
      // exclusion mutuelle, un seul reader en attente sur rsem
      sem_wait(&rsem);

      pthread_mutex_lock(&mutex_readcount);
         // exclusion mutuelle, readercount
         readcount=readcount+1;
         if (readcount==1) { 
	    // arrivée du premier reader
	    sem_wait(&wsem); 
         }
    pthread_mutex_unlock(&mutex_readcount);
    sem_post(&rsem);  // libération du prochain reader
    pthread_mutex_unlock(&z);

    read_database();

    pthread_mutex_lock(&mutex_readcount);
       // exclusion mutuelle, readcount
       readcount=readcount-1;
       if(readcount==0) {
            // départ du dernier reader
            sem_post(&wsem); 
       }
    pthread_mutex_unlock(&mutex_readcount);
    use_data_read();
  }

Pour comprendre l'utilité du mutex ``z``, il faut imaginer une solution dans laquelle il n'est pas utilisé. Dans ce cas, imaginons que plusieurs `readers` accèdent à la base de données et que deux `readers` et deux `writers` veulent y accéder. Le premier `reader` exécute ``sem_wait(&rsem);``. Le premier `writer` va exécuter ``sem_wait(&rsem);`` et sera bloqué en attendant que le premier `reader` exécute ``sem_post(&rsem);``. Le deuxième `writer` sera bloqué sur ``pthread_mutex_lock(&mutex_writecount);``. Lorsque le premier `reader` exécute ``pthread_mutex_unlock(&mutex_readcount);``, il permet au second `reader` de passer le mutex et d'exécuter ``sem_wait(&rsem);``. Lorsque le premier `reader` exécute finalement ``sem_post(&rsem);``, le système devra libérer un des threads en attente, c'est-à-dire le second `reader` ou le premier `writer`. Cette solution ne donne pas complètement la priorité aux `writers`. Le mutex ``z`` permet d'éviter ce problème en n'ayant qu'un seul `reader` à la fois qui peut exécuter la séquence ``sem_wait(&rsem); ...  sem_post(&rsem);``. Avec le mutex ``z``, le second `reader` est nécessairement en attente sur le mutex ``z`` lorsque le premier `reader` exécute ``sem_post(&rsem);``. Si un `writer` est en attente à ce moment, il sera nécessairement débloqué.


.. note:: Read-Write locks

 Certaines implémentations de la libraire threads POSIX contiennent des  Read-Write locks. Ceux-ci constituent une API de plus haut niveau qui s'appuie sur des sémaphores pour résoudre le problème des Readers-Writers. Les fonctions de création et de suppression de ces locks sont : `pthread_rwlock_init(3posix)`_, `pthread_rwlock_destroy(3posix)`_. Les fonctions `pthread_rwlock_rdlock(3posix)`_ et `pthread_rwlock_unlock(3posix)`_ sont réservées aux readers tandis que les fonctions `pthread_rwlock_wrlock(3posix)`_ et `pthread_rwlock_unlock(3posix)`_ sont utilisables par les writers. Des exemples d'utilisation de ces Read-Write locks peuvent être obtenus dans [Gove2011]_.


Compléments sur les threads POSIX
=================================

Il existe différentes implémentations des threads POSIX. Les mécanismes de coordination utilisables varient parfois d'une implémentation à l'autre. Dans les sections précédentes, nous nous sommes focalisés sur les fonctions principales qui sont en général bien implémentées. Une discussion plus détaillée des fonctions implémentées sous Linux peut se trouver dans [Kerrisk2010]_. [Gove2011]_ présente de façon détaillée les mécanismes de coordination utilisables sous Linux, Windows et Oracle Solaris. [StevensRago2008]_ comprend également une description des threads POSIX mais présente des exemples sur des versions plus anciennes de Linux, FreeBSD, Solaris et MacOS.

Il reste cependant quelques concepts qu'il est utile de connaître lorsque l'on développe des programmes multithreadés en langage C. 


Variables ``volatile``
----------------------

Normalement, dans un programme C, lorsqu'une variable est définie, ses accès sont contrôlés entièrement par le compilateur. Si la variable est utilisée dans plusieurs calculs successifs, il peut être utile d'un point de vue des performances de stocker la valeur de cette variable dans un registre pendant au moins le temps correspondant à l'exécution de quelques instructions [#fregister]_. Cette optimisation peut éventuellement poser des difficultés dans certains programmes utilisant des threads puisqu'une variable peut être potentiellement modifiée ou lue par plusieurs threads simultanément.

Les premiers compilateurs C avaient pris en compte un problème similaire. Lorsqu'un programme ou un système d'exploitation interagit avec des dispositifs d'entrée-sortie, cela se fait parfois en permettant au dispositif d'écrire directement en mémoire à une adresse connue par le système d'exploitation. La valeur présente à cette adresse peut donc être modifiée par le dispositif d'entrée-sortie sans que le programme ne soit responsable de cette modification. Face à ce problème, les inventeurs du langage C ont introduit le qualificatif ``volatile``. Lorsqu'une variable est ``volatile``, cela indique au compilateur qu'il doit recharger la variable de la mémoire chaque fois qu'elle est utilisée.

Pour bien comprendre l'impact de ce qualificatif, il est intéressant d'analyser le code assembleur générée par un compilateur C dans l'exemple suivant.

.. code-block:: c

    int x=1;
    int v[2];

    void f(void ) {
      v[0]=x;
      v[1]=x;
    }

Dans ce cas, la fonction ``f`` est traduite en la séquence d'instructions suivante :

.. code-block:: nasm 
 
   f: 
 	movl	x, %eax
	movl	%eax, v
	movl	%eax, v+4
	ret

Si par contre la variable ``x`` est déclarée comme étant ``volatile``, le compilateur ajoute une instruction ``movl x, %eax`` qui permet de recharger la valeur de ``x`` dans un registre avant la seconde utilisation.

.. code-block:: nasm

   f:
	movl	x, %eax
	movl	%eax, v
	movl	x, %eax
	movl	%eax, v+4
	ret

Le qualificatif ``volatile`` force le compilateur à recharger la variable depuis la mémoire avant chaque utilisation. Ce qualificatif est utile lorsque le contenu stocké à une adresse mémoire peut être modifié par une autre source que le programme lui-même. C'est le cas dans les threads, mais marquer les variables partagées par des threads comme ``volatile`` ne suffit pas. Si ces variables sont modifiées par certains threads, il est nécessaire d'utiliser des :term:`mutex` ou d'autres techniques de coordination pour réguler l'accès en ces variables partagées. En pratique, la documentation du programme devra spécifier quelles variables sont partagées entre les threads et la technique de coordination éventuelle qui est utilisée pour en réguler les accès. L'utilisation du qualificatif ``volatile`` permet de forcer le compilateur à recharger le contenu de la variable depuis la mémoire avant toute utilisation. C'est une règle de bonne pratique qu'il est utile de suivre. Il faut cependant noter que dans l'exemple ci-dessus, l'utilisation du qualificatif ``volatile`` augmente le nombre d'accès à la mémoire et peut donc dans certains cas réduire les performances. 


Variables spécifiques à un thread
---------------------------------

Dans un programme C séquentiel, on doit souvent combiner les variables globales, les variables locales et les arguments de fonctions. Lorsque le programme est découpé en threads, les variables globales restent utilisables, mais il faut faire attention aux problèmes d'acceptance concurrent. En pratique, il est parfois utile de pouvoir disposer dans chaque thread de variables qui  tout en étant accessibles depuis toutes les fonctions du thread ne sont pas accessibles aux autres threads. Il y a différentes solutions pour résoudre ce problème. 

Une première solution serait d'utiliser une zone mémoire qui est spécifique au thread et d'y placer par exemple une structure contenant toutes les variables auxquelles on souhaite pouvoir accéder depuis toutes les fonctions du thread. Cette zone mémoire pourrait être créée avant l'appel à `pthread_create(3)`_  et un pointeur vers cette zone pourrait être passé comme argument à la fonction qui démarre le thread. Malheureusement l'argument qui est passé à cette fonction n'est pas équivalent à une variable globale et n'est pas accessible à toutes les fonctions du thread. 

Une deuxième solution serait d'avoir un tableau global qui contiendrait des pointeurs vers des zones de mémoires qui ont été allouées pour chaque thread. Chaque thread pourrait alors accéder à ce tableau sur base de son identifiant. Cette solution pourrait fonctionner si le nombre de threads est fixe et que les identifiants de threads sont des entiers croissants. Malheureusement la libraire threads POSIX ne fournit pas de tels identifiants croissants. Officiellement, la fonction `pthread_self(3)`_ retourne un identifiant unique d'un thread qui a été créé. Malheureusement cet identifiant est de type ``pthread_t`` et ne peut pas être utilisé comme index dans un tableau. Sous Linux, l'appel système non-standard `gettid(2)`_ retourne l'identifiant du thread, mais il ne peut pas non plus être utilisé comme index dans un tableau.

Pour résoudre ce problème, deux solutions sont possibles. La première combine une extension au langage C qui est supportée par `gcc(1)`_ avec la librairie threads POSIX. il s'agit du qualificatif ``__thread`` qui peut être utilisé avant une déclaration de variable. Lorsqu'il est utilisé dans la déclaration d'une variable globale, il indique au compilateur et à la libraire POSIX qu'une copie de cette variable doit être créée pour chaque thread. Cette variable est initialisée au démarrage du thread et est utilisable uniquement à l'intérieur de ce thread. Le programme ci-dessous illustre cette utilisation du qualificatif ``__thread``.

.. literalinclude:: /S7/src/pthread-specific.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Lors de son exécution, ce programme affiche la sortie suivante sur :term:`stdout`. Cette sortie illustre bien que les variables dont la déclaration est précédée du qualificatif ``__thread`` sont utilisables uniquement à l'intérieur d'un thread.

.. literalinclude:: /S7/src/pthread-specific.out
   :encoding: iso-8859-1
   :language: console


La seconde solution proposée par la librairie POSIX est plus complexe. Elle nécessite l'utilisation des fonctions `pthread_key_create(3posix)`_, `pthread_setspecific(3posix)`_, `pthread_getspecific(3posix)`_ et `pthread_key_delete(3posix)`_. Cette API est malheureusement plus difficile à utiliser que le qualificatif ``__thread``, mais elle illustre ce qu'il se passe en pratique lorsque ce qualificatif est utilisé.

Pour avoir une variable accessible depuis toutes les fonctions d'un thread, il faut tout d'abord créer une clé qui identifie cette variable. Cette clé est de type ``pthread_key_t`` et c'est l'adresse de cette structure en mémoire qui sert d'identifiant pour la variable spécifique à chaque thread. Cette clé ne doit être créée qu'une seule fois. Cela peut se faire dans le programme qui lance les threads ou alors dans le premier thread lancé en utilisant la fonction `pthread_once(3posix)`_. Une clé est créée grâce à la fonction `pthread_key_create(3posix)`_. Cette fonction prend deux arguments. Le premier est un pointeur vers une structure de type ``pthread_key_t``. Le second est la fonction optionnelle à appeler lorsque le thread utilisant la clé se termine. 

Il faut noter que la fonction `pthread_key_create(3posix)`_ associe en pratique le pointeur ``NULL`` à la clé qui a été créée dans chaque thread. Le thread qui veut utiliser la variable correspondant à cette clé doit réserver la zone mémoire correspondante. Cela se fait en général en utilisant `malloc(3)`_ puis en appelant la fonction `pthread_setspecific(3posix)`_. Celle-ci prend deux arguments. Le premier est une clé de type ``pthread_key_t`` qui a été préalablement créée. Le second est un pointeur (de type ``void *``) vers la zone mémoire correspondant à la variable spécifique. Une fois que le lien entre la clé et le pointeur a été fait, la fonction `pthread_getspecific(3posix)`_ peut être utilisée pour récupérer le pointeur depuis n'importe quelle fonction du thread. L'implémentation des fonctions `pthread_setspecific(3posix)`_ et `pthread_getspecific(3posix)`_ garantit que chaque thread aura sa variable qui lui est propre. 

L'exemple ci-dessous illustre l'utilisation de cette API. Elle est nettement plus lourde à utiliser que le qualificatif ``__thread``. Dans ce code, chaque thread démarre par la fonction ``f``. Celle-ci crée une variable spécifique de type ``int`` qui joue le même rôle que la variable ``__thread int count;`` dans l'exemple précédent. La fonction ``g`` qui est appelée sans argument peut accéder à la zone mémoire créée en appelant ``pthread_getspecific(count)``. Elle peut ensuite exécuter ses calculs en utilisant le pointeur ``count_ptr``. Avant de se terminer, la fonction ``f`` libère la zone mémoire qui avait été allouée par `malloc(3)`_. Une alternative à l'appel explicite à `free(3)`_ aurait été de passer ``free`` comme second argument à `pthread_key_create(3posix)`_ lors de la création de la clé ``count``. En effet, ce second argument est la fonction à appeler à la fin du thread pour libérer la mémoire correspondant à cette clé.

.. literalinclude:: /S7/src/pthread-specific2.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

En pratique, on préfèrera évidemment d'utiliser le qualificatif ``__thread`` à la place de l'API explicite lorsque c'est possible. Cependant, il ne faut pas oublier que lorsque ce qualificatif est utilisé, le compilateur doit introduire dans le programme du code permettant de faire le même genre d'opérations que les fonctions explicites de la librairie.


Fonctions thread-safe
---------------------

Dans un programme séquentiel, il n'y a qu'un thread d'exécution et de nombreux programmeurs, y compris ceux qui ont développé la librairie standard, utilisent cette hypothèse lors de l'écriture de fonctions. Lorsqu'un programme est découpé en threads, chaque fonction peut être appelée par plusieurs threads simultanément. Cette exécution simultanée d'une fonction peut poser des difficultés notamment lorsque la fonction utilise des variables globales ou des variables statiques.

Pour comprendre le problème, il est intéressant de comparer plusieurs implémentations d'une fonction simple. Considérons le problème de déterminer l'élément maximum d'une structure de données contenant des entiers. Si la structure de données est un tableau, une solution simple est de le parcourir entièrement pour déterminer l'élément maximum. C'est ce que fait la fonction ``max_vector`` dans le programme ci-dessous. Dans un programme purement séquentiel dans lequel le tableau peut être modifié de temps en temps, parcourir tout le tableau pour déterminer son maximum n'est pas nécessairement la solution la plus efficace. Une alternative est de mettre à jour la valeur du maximum chaque fois qu'un élément du tableau est modifié. Les fonctions ``max_global`` et ``max_static`` sont deux solutions possibles. Chacune de ces fonctions doit être appelée chaque fois qu'un élément du tableau est modifié. ``max_global`` stocke dans une variable globale la valeur actuelle du maximum du tableau et met à jour cette valeur à chaque appel. La fonction ``max_static`` fait de même en utilisant une variable statique. Ces deux solutions sont équivalentes et elles pourraient très bien être intégrées à une librairie utilisée par de nombreux programmes.


.. literalinclude:: /S7/src/reentrant.c
   :encoding: iso-8859-1
   :language: c
   :start-after: ///AAA
   :end-before: ///BBB

Considérons maintenant un programme découpé en plusieurs threads qui chacun maintient un tableau d'entiers dont il faut connaître le maximum. Ces tableaux d'entiers sont distincts et ne sont pas partagés entre les threads. La fonction ``max_vector`` peut être utilisée par chaque thread pour déterminer le maximum du tableau. Par contre, les fonctions ``max_global`` et ``max_static`` ne peuvent pas être utilisées. En effet, chacune de ces fonctions maintient *un* état (dans ce cas le maximum calculé) alors qu'elle peut être appelée par différents threads qui auraient chacun besoin d'un état qui leur est propre. Pour que ces fonctions soient utilisables, il faudrait que les variables ``s_max`` et ``g_max`` soient spécifiques à chaque thread.

En pratique, ce problème de l'accès concurrent à des fonctions se pose pour de nombreuses fonctions et notamment celles de la librairie standard. Lorsque l'on développe une fonction qui peut être réutilisée, il est important de s'assurer que cette fonction peut être exécutée par plusieurs threads simultanément sans que cela ne pose de problèmes à l'exécution. 

Ce problème affecte certaines fonctions de la librairie standard et plusieurs d'entre elles ont dû être modifiées pour pouvoir supporter les threads. A titre d'exemple, considérons la fonction `strerror(3)`_. Cette fonction prend comme argument le numéro de l'erreur et retourne une chaîne de caractères décrivant cette erreur. Cette fonction ne peut pas être utilisée telle quelle par des threads qui pourraient l'appeler simultanément. Pour s'en convaincre, regardons une version simplifiée d'une implémentation de cette fonction [#fstrerror]_. Cette fonction utilise le tableau `sys_errlist(3)`_ qui contient les messages d'erreur associés aux principaux codes numériques d'erreur. Lorsque l'erreur est une erreur standard, tout se passe bien et la fonction retourne simplement un pointeur vers l'entrée du tableau ``sys_errlist`` correspondante. Par contre, si le code d'erreur n'est pas connu, un message est généré dans le tableau ``buf[32]`` qui est déclaré de façon statique. Si plusieurs threads exécutent ``strerror``, ce sera le même tableau qui sera utilisé dans les différents threads. On pourrait remplacer le tableau statique par une allocation de zone mémoire faite via `malloc(3)`_, mais alors la zone mémoire créée risque de ne jamais être libérée par `free(3)`_ car l'utilisateur de `strerror(3)`_ ne doit pas libérer le pointeur qu'il a reçu, ce qui pose d'autres problèmes en pratique.

.. code-block:: c

 char * strerror (int errnoval)
 {
  char *msg;
  static char buf[32];
  if ((errnoval < 0) || (errnoval >= sys_nerr))
    { /* Out of range, just return NULL */
      msg = NULL;
    }
  else if ((sys_errlist == NULL) || (sys_errlist[errnoval] == NULL))
    { /* In range, but no sys_errlist or no entry at this index. */
      sprintf (buf, "Error %d", errnoval);
      msg = buf;
    }
  else
    { /* In range, and a valid message.  Just return the message. */
      msg = (char *) sys_errlist[errnoval];
    }
  return (msg);
 }


La fonction `strerror_r(3)`_ évite ce problème de tableau statique en utilisant trois arguments : le code d'erreur, un pointeur ``char *`` vers la zone devant stocker le message d'erreur et la taille de cette zone. Cela permet à `strerror_r(3)`_ d'utiliser une zone mémoire qui lui est passée par le thread qu'il appelle et garantit que chaque thread disposera de son message d'erreur. Voici une implémentation possible de `strerror_r(3)`_ [#fstrerror_r]_.


.. code-block:: c

    strerror_r(int num, char *buf, size_t buflen)
    {
      #define UPREFIX "Unknown error: %u"
      unsigned int errnum = num;
      int retval = 0;
      size_t slen;
      if (errnum < (unsigned int) sys_nerr) {
         slen = strlcpy(buf, sys_errlist[errnum], buflen);
      } else {
         slen = snprintf(buf, buflen, UPREFIX, errnum);
         retval = EINVAL;
      }
      if (slen >= buflen)
           retval = ERANGE;
      return retval;
    }

Lorsque l'on intègre des fonctions provenant de la librairie standard ou d'une autre librairie dans un programme découpé en threads, il est important de vérifier que les fonctions utilisées sont bien :term:`thread-safe`. La page de manuel `pthreads(7)`_ liste les fonctions qui ne sont pas :term:`thread-safe` dans la librairie standard. 


Loi de Amdahl
=============

En découpant un programme en threads, il est théoriquement possible d'améliorer les performances du programme en lui permettant d'exécuter plusieurs threads d'exécution simultanément. Dans certains cas, la découpe d'un programme en différents threads est naturelle et relativement facile à réaliser. Dans d'autres cas, elle est nettement plus compliquée. Pour s'en convaincre, il suffit de considérer un grand tableau contenant plusieurs centaine de millions de nombres. Considérons un programme simple qui doit trouver dans ce tableau quel est l'élément du tableau pour lequel l'application d'une fonction complexe ``f`` donne le résultat minimal. Une implémentation purement séquentielle se contenterait de parcourir l'entièreté du tableau et d'appliquer la fonction ``f`` à chacun des éléments. A la fin de son exécution, le programme retournera l'élément qui donne la valeur minimale. Un tel problème est très facile à découper en threads. Il suffit de découper le tableau en ``N`` sous-tableaux, de lancer un thread de calcul sur chaque sous-tableau et ensuite de fusionner les résultats de chaque thread. 

Un autre problème est de trier le contenu d'un tel tableau dans l'ordre croissant. De nombreux algorithmes séquentiels de tri existent pour ordonner un tableau. La découpe de ce problème en thread est nettement moins évidente que dans le problème précédent et les algorithmes de tri adaptés à une utilisation dans plusieurs threads ne sont pas une simple extension des algorithmes séquentiels.

Dans les années 1960s, à l'époque des premières réflexions sur l'utilisation de plusieurs processeurs pour résoudre un problème, Gene Amdahl [Amdahl1967]_ a analysé quelles étaient les gains que l'on pouvait attendre de l'utilisation de plusieurs processeurs. Dans sa réflexion, il considère un programme ``P`` qui peut être découpé en deux parties :

 - une partie purement séquentielle. Il s'agit par exemple de l'initialisation de l'algorithme utilisé, de la collecte des résultats, ...
 - une partie qui est parallélisable. Il s'agit en général du coeur de l'algorithme. 

Plus les opérations réalisées à l'intérieur d'un programme sont indépendantes entre elles, plus le programme est parallélisable et inversement. Pour Amdahl, si le temps d'exécution d'un programme séquentiel est `T` et qu'une fraction `f` de ce programme est parallélisable, alors le gain qui peut être obtenu de la parallélisation est :math:`\frac{T}{T \times( (1-f)+\frac{f}{N})}=\frac{1}{ (1-f)+\frac{f}{N}}` lorsque le programme est découpé en `N` threads. Cette formule, connue sous le nom de la :term:`loi de Amdahl` fixe une limite théorique sur le gain que l'on peut obtenir en parallélisant un programme. La figure ci-dessous [#famdahl]_ illustre le gain théorique que l'on peut obtenir en parallélisant un programme en fonction du nombre de processeur et pour différentes fractions parallélisables.

.. figure:: /S7/fig/500px-AmdahlsLaw.png 
   :align: center
   :scale: 80

   Loi de Amdahl

La loi de Amdahl doit être considérée comme un maximum théorique qui est difficile d'atteindre. Elle suppose que la parallélisation est  parfaite, c'est-à-dire que la création et la terminaison de threads n'ont pas de coût en terme de performance. En pratique, c'est loin d'être le cas et il peut être difficile d'estimer a priori le gain qu'une parallélisation permettra d'obtenir. En pratique, avant de découper un programme séquentiel en threads, il est important de bien identifier la partie séquentielle et la partie parallélisable du programme. Si la partie séquentielle est trop importante, le gain dû à la parallélisation risque d'être faible. Si par contre la partie purement séquentielle est faible, il est possible d'obtenir théoriquement des gains élevés. Le tout sera de trouver des solutions efficaces qui permettront aux threads de fonctionner le plus indépendamment possible. 

En pratique, avant de s'attaquer à la découpe d'un programme séquentiel en threads, il est important de bien comprendre quelles sont les parties du programme qui sont les plus consommatrices de temps CPU. Ce seront souvent les boucles ou les grandes structures de données. Si le programme séquentiel existe, il est utile d'analyser son exécution avec des outils de profiling tels que `gprof(1)`_  [Graham+1982]_ ou `oprofile <http://oprofile.sourceforge.net/>`_. Un profiler est un logiciel qui permet d'analyser l'exécution d'un autre logiciel de façon à pouvoir déterminer notamment quelles sont les fonctions ou parties du programmes les plus exécutées. Ces parties de programme sont celles sur lesquelles l'effort de paraléllisation devra porter en pratique. 

Dans un programme découpé en threads, toute utilisation de fonctions de coordination comme des sémaphores ou des mutex, bien qu'elle soit nécessaire pour la correction du programme, risque d'avoir un impact négatif sur les performances. Pour s'en convaincre, il est intéressant de réfléchir au problème des producteurs-consommateurs. Il correspond à de nombreux programmes réels. Les performances d'une implémentation du problème des producteurs consommateurs dépendront fortement de la taille du buffer entre les producteurs et les consommateurs et de leur nombre et/ou vitesses relatives. Idéalement, il faudrait que le buffer soit en moyenne rempli à moitié. De cette façon, chaque producteur pourra déposer de l'information dans le buffer et chaque consommateur pourra en retirer. Si le buffer est souvent vide, cela indique que les consommateurs sont plus rapides que les producteurs. Ces consommateurs risquent d'être inutilement bloqués, ce qui affectera les performances. Il en va de même si le buffer était plein. Dans ce cas, les producteurs seraient souvent bloqués.

.. rubric:: Footnotes

.. [#fSysV] Les systèmes Unix supportent également des sémaphores dits `System V` du nom de la version de Unix dans laquelle ils ont été introduits. Dans ces notes, nous nous focalisons sur les sémaphores POSIX qui ont une API un peu plus simple que l'API des sémaphores `System V`. Les principales fonctions pour les sémaphores `System V` sont `semget(3posix)`_, `semctl(3posix)`_ et `semop(3posix)`_.


.. [#fregister] Les premiers compilateurs C permettaient au programmeur de donner des indications au compilateur en faisant précéder les déclarations de certaines variables avec le qualificatif ``register`` [KernighanRitchie1998]_. Ce qualificatif indiquait que la variable était utilisée fréquemment et que le compilateur devrait en placer le contenu dans un registre. Les compilateurs actuels sont nettement plus performants et ils sont capables de détecter quelles sont les variables qu'il faut placer dans un registre. Il est inutile de chercher à influencer le compilateur en utilisant le qualificatif ``register``. Les compilateurs actuels, dont `gcc(1)`_ supportent de nombreuses `options <http://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html>`_ permettant d'optimiser les performances des programmes compilés. Certaines ont comme objectif d'accélérer l'exécution du programme, d'autres visent à réduire sa taille. Pour les programmes qui consomment beaucoup de temps CPU, il est utile d'activer l'optimisation du compilateur.

.. [#fstrerror] Cette implémentation est adaptée de http://opensource.apple.com/source/gcc/gcc-926/libiberty/strerror.c et est dans le domaine public.

.. [#fstrerror_r] Cette implémentation est adaptée de https://www-asim.lip6.fr/trac/netbsdtsar/browser/vendor/netbsd/5/src/lib/libc/string/strerror_r.c?rev=2 et est `Copyright (c) 1988 Regents of the University of California.`

.. [#famdahl] Source : http://en.wikipedia.org/wiki/Amdahl's_law


