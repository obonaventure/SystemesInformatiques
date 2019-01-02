.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Exercices
=========

#. La fonction `pthread_join(3)`_ utilise un deuxième argument de type ``void **``. Pourquoi est-il nécessaire d'utiliser un pointeur vers un pointeur et pas simplement un pointeur ``void *`` ?

#. A votre avis, pourquoi le premier argument de la fonction `pthread_create(3)`_ est-il un pointeur de type `pthread_t *` alors que le premier argument de la fonction `pthread_join(3)`_ est lui simplement de type `pthread_t`?

#. Avec les threads POSIX, comment peut-on passer plusieurs arguments à la fonction démarrée par `pthread_create(3)`_ ? Ecrivez un petit exemple en C qui permet de passer un entier et un caractère à cette fonction.

.. only:: staff

   Ecrivez un code qui permet de récupérer un tableau d'entiers d'un thread. Exercice disponible sur `INGInious threads_1 <https://inginious.info.ucl.ac.be/course/LSINF1252-new/threads_1>`_.

#. Essayez de lancer un grand nombre de threads d'exécution sur votre machine. Quel est le nombre maximum de threads que `pthread_create(3)`_ vous autorise à lancer ?

#. Quelle différence voyez-vous entre `pthread_exit(3)`_ et `exit(3)`_ ?

#. Un étudiant souhaite passer un tableau d'entiers comme argument à un thread et écrit le code suivant. Qu'en pensez-vous ?

   .. literalinclude:: /Programmes/src/pthread-array.c
      :encoding: utf-8
      :language: c
      :start-after: ///AAA

#. Considérons le programme de test des threads POSIX ci-dessous. Ce programme utilise 4 threads qui incrémentent chacun un million de fois une variable globale.

   .. literalinclude:: /Programmes/src/pthread-test.c
      :encoding: utf-8
      :language: c
      :start-after: ///AAA

   Exécutez ce programme (:download:`/Programmes/src/pthread-test.c`) et observez le résultat qu'il affiche à l'écran. Pouvez-vous expliquer le comportement de ce programme ?

#. Lorsque l'on travaille avec des threads, il est important de bien se rappeler dans quelle zone de la mémoire les différents types d'information sont stockés dans un programme C. Le programme ci-dessous fournit quelques exemples de :

	* variable globale statique 
	* variable globale 
	* variable déclarée dans la fonction ``main`` et dont le pointeur est un des arguments aux threads 
	* variable statique déclarée à l'intérieur d'une fonction 
	* variable locale déclarée dans une fonction 


    .. code-block:: c 
                          
       #include <pthread.h>
       #include <stdio.h>
       #include <stdlib.h>
       
       #define N_THREADS 3 
       
       struct thread_args {
          int *ptr;
          int thread_num;
       };
       
       pthread_mutex_t mutex;
       
       static int global_static = 1;
       int global_int = 11;
                                
       static void *thread_work(void *ptr) 
       {
         struct thread_args *arg = (struct thread_args *)ptr;
	 int thr_num = arg->thread_num;
         
	 static int static_val = 111;
	 int local_val = 222;
	 int *main_val = arg->ptr;
         
	 pthread_mutex_lock(&mutex);
         
	 printf("thread no %d, global_static is %d\n", thr_num, global_static);
	 fflush(stdout);
	 global_static++;
         
	 printf("thread no %d, global_int is %d\n", thr_num, global_int);
	 fflush(stdout);
	 global_int++;
         
	 printf("thread no %d, static_val is %d\n", thr_num, static_val);
	 fflush(stdout);
	 static_val++;
         
	 printf("thread no %d, local_val is %d\n", thr_num, local_val);
	 fflush(stdout);
	 local_val++;
         
	 printf("thread no %d, main_val is %d\n", thr_num, *main_val);
	 fflush(stdout);
	 (*main_val)++;
         
	 pthread_mutex_unlock(&mutex);
         
	 pthread_exit(NULL);
       }
         
       int main (int argc, char const *argv[]) 
       {
         int i;
         int val = 22;
         struct thread_args args[N_THREADS];
         pthread_t threads[N_THREADS];

	 pthread_mutex_init(&mutex, NULL);

	 for (i = 0; i < N_THREADS; ++i) {
	   args[i].ptr = &val;
	   args[i].thread_num = i;
	   pthread_create(&threads[i], NULL, thread_work, (void *)&args[i]);
	 }

	 for (i = 0; i < N_THREADS; ++i) 
	    pthread_join(threads[i], NULL);

	 return 0;
	}

#. D'après vous (essayez d'expérimenter), que se passe-t-il si:

	* un thread exécute deux fois `pthread_mutex_lock(3posix)`_ sur le même mutex d'affilée ?
	* un thread exécute deux fois d'affilée `pthread_mutex_unlock(3posix)`_


#. Dans la partie théorie, nous avons vu comment s'assurer qu'un seul thread peut accéder à une zone critique à la fois. On vous propose deux solutions (dont une déjà vue dans la partie théorie):

	.. code-block:: c 

		pthread_mutex_lock(&mutex_global);
		global=increment(global);
		pthread_mutex_unlock(&mutex_global);

	et 

	.. code-block:: c 

		while (pthread_mutex_trylock(&mutex_global)) ;
		global=increment(global);
		pthread_mutex_unlock(&mutex_global);

	Discuter les avantages et inconvénients des ces deux solutions. (Regardez la man page de `pthread_mutex_trylock(3posix)`_) 

#. L'outil ``helgrind`` (décrit dans la section :ref:`outils:helgrind-ref`) permet de trouver des deadlocks ou autres problèmes. Exécutez-le sur le petit programme suivant :download:`/Programmes/src/pthread-philo.c` et analysez ce qu'il affiche. 



.. only:: staff

   Résolvez des sudokus. Exercice disponible sur `INGInious sudoku <https://inginious.info.ucl.ac.be/course/LSINF1252-new/sudoku>`_.

Mini-projet: Mesure de performance
==================================

On vous demande de transformer un code monothreadé en un code multithreadé. Vous devez vous baser sur le code présent dans l'archive: :download:`/Programmes/src/prog-5-measure/prog-5-measure.tar.gz`. Le programme permet de chiffrer ou déchiffrer des mots de passe passés en argument au programme. Ce dernier prend plusieurs arguments additionels:

    * ``-p`` définit le mot de passe à utiliser
    * ``-n`` définit le nombre de fois que chaque mot de passe est chiffré/déchiffré
    * ``-d`` définit que le programme doit déchiffrer les mots de passes (il chiffre par défaut)

Un exemple d'utilisation du programme est le suivant:

    .. code-block:: console

        $ ./crypt -p toto -n 10000 test Bonjour!
        CAC7EF483F90C988 0F5766990DFA0914
        $ ./crypt -p toto -n 10000 -d CAC7EF483F90C988 0F5766990DFA0914
        test Bonjour!

Vous devez donc vous baser sur le code existant afin de paralléliser le chiffrement/déchiffrement des mots de passe. Vous ne devez pas nécessairement afficher les mots de passe (ou chiffrés) dans l'ordre. Vous devez cependant ajouter un argument ``-t`` au programme qui définit le nombre de threads que le programme exécutera en parallèle.

On vous demande également d'évaluer l'impact des arguments ``-t`` et ``-n`` sur l'exécution du programme. Pensez à exécuter votre programme avec un argument ``-n`` suffisamment grand si vous voulez évaluer l'impact de ``-t``. On vous demande plus spécifiquement de générer un graphique qui montre pour différentes valeurs le temps de calcul. Vous pouvez utiliser `time(1posix)`_ afin de récupérer le temps d'exécution d'un programme:

    .. code-block:: console

        $ time ./crypt -p toto -n 10000 -d CAC7EF483F90C988 0F5766990DFA0914
        test Bonjour!

        real	0m0.019s
        user	0m0.016s
        sys	0m0.000s
        $ time ./crypt -p toto -n 9999999 -d 774069EB86ED86FA 7D1AC0A4CF56F942
        test Bonjour!

        real	0m16.104s
        user	0m16.101s
        sys	0m0.000s



.. exemple et tutoriel intéressant
.. https://computing.llnl.gov/tutorials/pthreads/

