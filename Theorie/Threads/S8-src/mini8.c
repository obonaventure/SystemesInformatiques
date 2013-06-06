#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>

/* Necessary for the correct compilation */
#define _POSIX_C_SOURCE 199309L

#define N_ITERATIONS	(100)
#define N_CONSUMERS	(4)
#define N_PRODUCERS	(2)
#define N_RETRIEVES	((N_ITERATIONS) * (N_PRODUCERS) / (N_CONSUMERS))
#define MIN(a, b)	((a) > (b) ? (b) : (a))

/* A COMPLETER */

/*
 * Insert val in the bounded-buffer. Should wait if there are no empty spaces
 * available.
 */
void insert(int val)
{
	/* A COMPLETER */
}

/*
 * Returns and removes the next element from the bounded buffer.
 */
int retrieve(void)
{
	/* A COMPLETER */
	return -1;
}


void *producer(void *arg)
{
	int i, val;

	for (i = 0; i < N_ITERATIONS; ++i) {
		/* sleep for few miliseconds */
		struct timespec sleep;
		sleep.tv_sec = 0;
		sleep.tv_nsec = (long) rand() % 100000000;
		nanosleep(&sleep, NULL);

		/* generate a value and insert it in the buffer */
		val = abs(rand());
		insert(val);
	}
	return NULL;
}

void *consumer(void *arg)
{
	int i, *min = (int *)arg;

	for (i = 0; i < N_RETRIEVES; ++i) {
		/* sleep for few miliseconds */
		struct timespec sleep;
		sleep.tv_sec = 0;
		sleep.tv_nsec = (long) rand() % 100000000;
		nanosleep(&sleep, NULL);

		/* maintain the minimum value up to now */
		*min = MIN(*min, retrieve());
	}
	return (void *)min;
}

int main (int argc, char const *argv[])
{
	int i, min = INT_MAX, *ret;
	pthread_t producers[N_PRODUCERS];
	pthread_t consumers[N_CONSUMERS];
	int returns[N_CONSUMERS];
	int err;

	/* seed the PRNG */
	srand(time(NULL));

	/* A COMPLETER */

	for (i = 0; i < N_PRODUCERS; ++i) {
		err = pthread_create(&producers[i], NULL, producer, NULL);
		if (err)
			goto error;
	}

	for (i = 0; i < N_CONSUMERS; ++i) {
		err = pthread_create(&consumers[i], NULL, consumer, &returns[i]);
		if (err)
			goto error;
	}

	for (i = 0; i < N_PRODUCERS; ++i) {
		err = pthread_join(producers[i], NULL);
		if (err)
			goto error;
	}

	for (i = 0; i < N_CONSUMERS; ++i) {
		err = pthread_join(consumers[i], (void **)&ret);
		if (err)
			goto error;
		min = MIN(min, *ret);
	}

	printf("The minimal value generated is %d.\n", min);

	return (EXIT_SUCCESS);

error:
	perror("Error happened:\n");
	return (EXIT_FAILURE);
}
