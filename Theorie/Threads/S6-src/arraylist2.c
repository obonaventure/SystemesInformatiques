#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N_THREADS 4
#define LIST_SIZE 1000
#define N_RAND    100000

pthread_mutex_t mutex;
static int list[LIST_SIZE];

static void *thread_random(void *arg)
{
	int i, r;

	for (i = 0; i < N_RAND; ++i) {
		r = rand() % LIST_SIZE;

		pthread_mutex_lock(&mutex);
		list[r]++;
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}


int main (int argc, char const *argv[])
{
	int i, sum;
	pthread_t threads[N_THREADS];

	// init elements mutex
	pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < N_THREADS; ++i)
		pthread_create(&threads[i], NULL, thread_random, NULL);

	for (i = 0; i < N_THREADS; ++i)
		pthread_join(threads[i], NULL);

	sum = 0;
	pthread_mutex_destroy(&mutex);
	for (i = 0; i < LIST_SIZE; ++i)
		sum += list[i];

	printf("Sum of all elements: %d =?= %d\n", sum, N_THREADS * N_RAND);

	return 0;
}
