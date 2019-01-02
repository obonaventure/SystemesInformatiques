.. -*- coding: utf-8 -*-
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. sectionauthor:: Gregory Vander Schueren <gregory.vanderschueren@student.uclouvain.be>

Questions à choix multiples
===========================

:task_id: sinf1252-10

Question 1. Signaux synchrones et asynchrones
---------------------------------------------

Un signal est dit synchrone lorsqu'il est causé par l'exécution d'une instruction du processus. Un signal est dit asynchrone s'il n'a pas été causé directement par l'exécution d'un instruction du processus. 

.. question:: signal_sync_async
   :nb_prop: 4
   :nb_pos: 2

   Parmi les affirmations suivantes, lesquelles sont correctes ?

   .. positive::

      - Le signal SIGFPE est synchrone.

   .. positive::

      - Le signal SIGSEGV est synchrone.

   .. positive::

      - Le signal SIGALRM est asynchrone.

   .. negative::

      - Le signal SIGCHLD est synchrone.

      .. comment:: Ce signal indique qu'un processus fils s'est arrêté ou a fini son exécution. Il résulte d'une cause externe au programme.

   .. negative::

      - Le signal SIGINT est synchrone.

      .. comment:: Ce signal est envoyé par le shell lorsque l'utlisateur tape Ctrl-C pendant l'exécution d'un programme. Il résulte d'une cause externe au programme.

   .. negative::

      - Le signal SIGTERM est synchrone.

      .. comment:: Ce signal est le signal utilisé par défaut par la commande kill pour demander la fin d'un processus. Il résulte d'une cause externe au programme.

   .. negative::

      - Le signal SIGBUS est synchrone.

      .. comment:: Ce signal correspond à une erreur matérielle. Il résulte d'une cause externe au programme.



Question 2. Signaux pour arrêter un processus
---------------------------------------------



.. question:: signal_stop_process
   :nb_prop: 4
   :nb_pos: 2

   Trois signaux permettent d'arrêter un processus: SIGTERM, SIGINT et SIGKILL. Parmi les affirmations suivantes, lesquelles sont correctes ?

   .. positive::

      - Envoyer un signal SIGKILL à un processus le termine toujours immédiatement.

   .. positive::

      - Lorsque l'on tappe Ctrl-C dans le shell pendant l'exécution d'un programme, un signal SIGINT est envoyé au processus en cours d'exécution.

   .. positive::

      - Envoyer un signal SIGTERM ou SIGINT est préférable à SIGKILL car le processus peut prévoir une routine de traitement de signal pour se terminer proprement.

   .. negative::

      - Envoyer un signal SIGTERM à un processus le termine toujours immédiatement.

      .. comment:: Par défaut, la réception de ce signal provoque la terminaison du processus. Néanmoins, le processus peut prévoir une routine de traitement pour ce type de signal ou choisir d'ignorer ce type de signal.

   .. negative::

      - Lorsque l'on tappe Ctrl-C dans le shell pendant l'exécution d'un programme, un signal SIGTERM est envoyé au processus en cours d'exécution.

      .. comment:: C'est un signal SIGINT qui est envoyé au processus en cours d'exécution.

   .. negative::

      - Envoyer un signal SIGTERM ou SIGKILL est préférable à SIGTERM car le processus peut prévoir une routine de traitement de signal pour se terminer proprement.

      .. comment:: Un processus ne peut pas prévoir de routine de traitement pour SIGKILL ni choisir d'ignorer ce type de signal.

Question 3. Routines de traitement de signal
--------------------------------------------

Un étudiant a décidé d'implémenter un programme simulant une bombe à retardement qui détonne 1h après son intialisation. Pour accélérer le décompte, l'étudiant a enregistré un handler pour le signal SIGUSR1 qui divise par 2 le temps restant à décompter.

.. code-block:: c

  #include <stdio.h>
  #include <stdlib.h>
  #include <signal.h>
  #include <unistd.h>

  int counter = 3600;

  void counter_boost(int signum) {
      counter=counter/2;
      printf("Boost!\n");
  }

  int main () {
      if (signal(SIGUSR1,counter_boost)==SIG_ERR) {
          perror("signal");
          exit(EXIT_FAILURE);
      }

      while(counter>0) {
          counter--;
          printf("%d seconds left\n", counter);
          sleep(1);
      }

      printf("BOOM!");
      return(EXIT_SUCCESS);
  }



.. question:: signal_handlers
   :nb_prop: 3
   :nb_pos: 1

   Ce programme, bien qu'en apparence fonctionnel, contient plusieurs erreurs de programmation. Parmi les affirmations suivantes, laquelle est correcte ?

   .. positive::

      - Il y a un risque que la variable counter soit accédée en même temps par le processus et la routine de traitement de signal. Il est nécessaire de la déclarer sig_atomic_t pour résoudre ce problème.

      .. comment:: Avec sig_atomic_t, le compilateur garantit que tous les accès à la variable se feront de façon atomique.


   .. positive::

      - La fonction `printf(3)`_ n'est pas réentrante et ne doit pas être utilisée dans une routine de traitement de signal.

      .. comment:: La fonction `printf(3)`_ modifie des données globales (le buffer attaché au stream). Cette dernière est documentée comme non réentrante et ne doit donc pas être utilisée dans une routine de traitement de signal.


   .. negative::

      - Il y a un risque que la variable counter soit accédée en même temps par le processus et la routine de traitement de signal. Il est nécessaire de protéger cette variable par un mutex.

      .. comment:: Cette solution peut causer un deadlock. La routine de traitement de signal est asynchrone et peut être appelée à tout moment. Si le mutex est déjà utilisé à ce moment là, la routine de traitement de signal restera bloquée sur l'appel `pthread_mutex_lock(3posix)`_.


   .. negative::

      - Il y a un risque que la variable counter soit accédée en même temps par le processus et la routine de traitement de signal. Il est nécessaire de la déclarer volatile pour résoudre ce problème.

      .. comment:: Il est toujours possible que le processus exécute l'instruction de chargement de la valeur de la variable puis qu'un signal lui soit délivré. Lorsque le processus revient à son flux d'éxécution normal, la valeur de la variable a changé mais elle n'est pas rechargée depuis la mémoire.


   .. negative::

      - Il est interdit de modifier une variable globale (telle que counter) dans une routine de traitement de signal.

      .. comment:: La modification de variables globales dans une routine de traitement de signal est autorisée. Il est néanmoins nécessaire de prendre certaines précautions et la déclarer avec sig_atomic_t pour garantir que tous les accès à la variable se feront de façon atomique.



Question 4. Implémentation des signaux sous Unix
------------------------------------------------

Deux stratégies existent pour implémenter les signaux sous Unix: maintenir une queue de tous les signaux destinés à un processus donné ou représenter l'ensemble des signaux qu'un processus peut recevoir sous la forme de drapeaux binaires (un par signal). Linux utilise la seconde stratégie. 

.. question:: signal_implementation_strategies
   :nb_prop: 4
   :nb_pos: 1

   Parmi les affirmations suivantes, lesquelles sont correctes ?

   .. positive::

      - La solution sous forme de queue sans limite de taille permet de s'assurer que tout signal envoyé au processus est reçu par le processus.

   .. positive::

      - La solution sous forme de drapeaux binaires ne nécessite qu'un seul bit de mémoire par signal mais n'est pas forcément meilleure que la solution utilisant une queue.

      .. comment:: C'est une question de compromis. La solution sous forme de drapeaux binaires est plus économe en mémoire mais n'est pas fiable.

   .. negative::

      - La solution utilisant une queue permet de s'assurer que tout signal envoyé au processus est reçu par le processus. Elle est donc meilleure que la solution sous forme de drapeaux binaires.

      .. comment:: C'est une question de compromis. La solution utilisant une queue peut devenir très gourmande en mémoire s'il n'y a pas de limite sur la taille de la queue.


   .. negative::

      - Une solution intermédiaire utilisant 10 drapeaux par type de signal permettrait d'être à la fois fiable et économe en mémoire.

      .. comment:: Elle permettrait d'être fiable seulement pour les 10 premiers signaux de même type reçus.


   .. negative::

      - La solution utilisant des drapeaux binaires permet de s'assurer que tout signal envoyé au processus est reçu par le processus.

      .. comment:: Si le signal est envoyé 2 fois au processus avant l'exécution de la prochaine routine de traitement de signal, le drapeau sera mis à vrai et la routine de traitement de signal ne sera appelée qu'une seule fois.


   .. negative::

      - Avec la solution utilisant des drapeaux binaires, seul les signaux envoyés plusieurs fois avant l'exécution routine de traitement de signal seront perdus.

      .. comment:: Si un autre signal arrive durant l'exécution de la routine de traitement de signal, celui-ci sera perdu car bloqué par le système d'exploitation pour empêcher l'interruption de la routine de traitement du précédent signal.


