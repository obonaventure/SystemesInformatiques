#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N_THREADS 3

pthread_mutex_t global_mutex;

static void *thread_work(void *arg)
{
	pthread_mutex_lock(&global_mutex);

	/* Do some work here */

	pthread_exit(NULL);
	pthread_mutex_unlock(&global_mutex);
}


int main (int argc, char const *argv[])
{
	int i;
	pthread_t threads[N_THREADS];

	pthread_mutex_init(&global_mutex, NULL);

	for (i = 0; i < N_THREADS; ++i)
		pthread_create(&threads[i], NULL, thread_work, NULL);

	for (i = 0; i < N_THREADS; ++i)
		pthread_join(threads[i], NULL);

	return 0;
}