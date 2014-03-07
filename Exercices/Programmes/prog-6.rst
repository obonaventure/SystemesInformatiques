.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Exercices
=========


#. Ecrivez un petit programme qui vous permet de montrer quelles variables sont accessibles à différents threads. Les variables à montrer sont:

	* variable globale statique
	* variable globale
	* variable déclarée dans la fonction ``main`` et dont le pointeur est un des arguments aux threads
	* variable statique déclarée à l'intérieur d'une fonction
	* variable locale déclarée dans une fonction

	.. only:: staff

		.. note::

			.. code-block:: c

			        // note : fflush n'a pas encore été vu, ne pas en parler
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

#. L'outil ``helgrind`` (décrit dans la section :ref:`theorie:helgrind-ref`) permet de trouver des deadlocks ou autres problèmes. Exécutez-le sur le petit programme suivant :download:`/Programmes/src/pthread-philo.c` et analysez ce qu'il affiche.

#. Faites l'exercice sur les vecteurs thread-safe sur `pythia <http://pythia.info.ucl.ac.be/module/13/problem/45>`_.


.. exemple et tutoriel intéressant
.. https://computing.llnl.gov/tutorials/pthreads/

