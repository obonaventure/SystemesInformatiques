.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Exercices
=========


#. Expliquez pourquoi la fonction `sem_wait(3)`_ doit prendre comme argument ``sem_t *``, un
   pointeur vers une structure ``sem_t``, et non une structure ``sem_t``.

   .. only:: staff

       Parceque la valeur du sémaphore doit être modifiée par la fonction ou la queue associée au sémaphore


#. Dans quels cas la fonction `sem_init(3)`_ risque-t-elle de retourner une erreur ?

   .. only:: staff

      valeur initiale trop grande


#. La librairie POSIX contient également une fonction `sem_timedwait(3)`_. Quel intérêt voyez-vous à cette fonction ? Dans quel cas pourrait-elle servir en pratique ?

   .. only:: staff

      en pratique cela permet d'éviter de rester bloqué longtemps, mais cela ne remplace pas une solution correcte qui évite les deadlocks. A priori, ce n'est pas une fonction à utiliser dans le code qu'ils rendent.


#. Un étudiant propose d'implémenter le producteur du problème des producteurs-consommateurs comme ci-dessous :

   .. code-block:: c

      // Producteur
      void producer(void)
      {
         int item;
         while(true)
         {
            item=produce(item);
            pthread_mutex_lock(&mutex);   // modification
            sem_wait(&empty);             // modification
            insert_item();
            pthread_mutex_unlock(&mutex);
            sem_post(&full);
         }
      }

   Que pensez-vous de cette solution (en supposant que le consommateur continue à fonctionner comme indiqué dans les notes) ?

   .. only:: staff

      On a inversé les locks dans le producteur. Cela peut causer un deadlock puisque le producteur ayant pris mutex, si empty est bloquant, ce qui est le cas lorsque le buffer est vide, le producteur empêchera tout consommateur d'accéder au buffer et donc le système sera en deadlock

#. Un étudiant propose d'implémenter le consommateur du problème des producteurs-consommateurs comme ci-dessous :

   .. code-block:: c

      // Consommateur
      void consumer(void)
      {
        int item;
        while(true)
        {
            sem_wait(&full);
            pthread_mutex_lock(&mutex);
            item=remove(item);
            sem_post(&empty);             // modification
            pthread_mutex_unlock(&mutex); // modification
        }
      }

   Que pensez-vous de sa solution (en supposant que le producteur n'a pas été modifié) ?

   .. only:: staff

      L'ordre des unlock a changé. Ici, cela n'a pas d'impact sur la solution.

#. Un étudiant propose de résoudre le problème du rendez-vous en utilisant le code ci-dessous. Comparez sa solution avec la solution qui a été vue au cours.

   .. code-block:: c

      premiere_phase();

      pthread_mutex_lock(&mutex);
      count++;
      pthread_mutex_unlock(&mutex);   // modification
      if(count==N)
         sem_post(&rendezvous);

      sem_wait(&rendezvous);
      sem_post(&rendezvous);

      seconde_phase();

   .. only:: staff

      Cela fonctionne aussi, voir [Downey2008]_. En gros, même si on place le test de ``count`` en dehors du mutex, ce n'est pas grave parce que lorsque count vaut N, il ne peut plus y avoir de thread qui soit en train de manipuler la variable count puisque tous les autres threads sont par définition bloqués. Le seul risque serait count=N-1, un thread fait unlock et est interrompu, le suivant rentre dans la section critique et increment count. Si le premier redémarre a ce moment, il verra que count==N et fera sem_post, ce que le dernier thread fera aussi. On aura donc un sem_post de trop, mais tous les threads auront atteints le rendez-vous


#. Considérons un problème du rendez-vous avec 13 threads. Lorsque tous les threads ont passé le rendez-vous, quelle sera la valeur du sémaphore ``rendezvous`` retournée par la fonction `sem_getvalue(3)`_ ?

   .. only:: staff

      1 puisque tous les threads ont fait wait puis post alors que le dernier a fait post avant de faire son wait

#. La librairie POSIX contient la fonction `sem_getvalue(3)`_ qui permet de récupérer la valeur d'un sémaphore sans pour autant effectuer d'opération `sem_wait(3)`_ sur ce sémaphore. Elle peut être utilisée pour observer l'évolution de la valeur d'un sémaphore. Modifiez le programme des philosophes contenant un deadlock (:download:`/Programmes/src/pthread-philo-sem.c`) et ajoutez-y un thread qui observe toutes les 10 secondes l'évolution des sémaphores et arrête tout le programme via `exit(3)`_ en affichant un message d'erreur si les valeurs des sémaphores n'ont pas changé.

#. Les mutex et les sémaphores peuvent être utilisés pour résoudre des problèmes d'exclusion mutuelle. Le programme :download:`/QCM/S7/src/pthread-mutex-perf.c` utilise des mutex. Modifiez-le pour utiliser des sémaphores à la place et comparez le coût en termes de performance entre les mutex et les sémaphores.

#. Faites l'exercice sur les `producteurs/consommateurs <https://inginious.info.ucl.ac.be/course/LSINF1252/PC>`_ sur `INGInious <https://inginious.info.ucl.ac.be>`_.

Outils
======

#. Si vous ne l'aviez pas fait durant la troisième semaine, prenez le temps pour faire l'exercice relatif à `gdb(1)`_ . Le debugger pourra vous être très utile pour le projet.

#. Un autre outil particulièrement intéressant est  :ref:`outils:valgrind-ref` qui permet de détecter différents problèmes d'allocation de la mémoire. Prenez le temps nécessaire pour comprendre comment ce logiciel fonctionne, cette compétence vous fera gagner du temps plus tard et vous évitera de perdre du temps pour corriger un problème d'allocation de mémoire difficile à détecter.