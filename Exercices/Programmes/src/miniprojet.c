
/* Necessary for the correct compilation */
#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/** Global variables */

int file;
sem_t *readsem;
sem_t *writesem;

static void producer()
{
	int i = 0;
	while (1) {
		char buf[2];
		int val = rand() % 10;

		if (snprintf(buf, 2, "%d", val) < 0) {
			perror("Error with snprintf\n");
			return;
		}

		if (sem_wait(writesem) < 0) {
			perror("Error with sem_wait\n");
			return;
		}

		if (pwrite(file, buf, 1, i) < 0) {
			perror("Error with pwrite\n");
			return;
		}

		if (sem_post(readsem) < 0) {
			perror("Error with sem_post\n");
			return;
		}

		i++;
		sleep(val);
	}

	return;
}

static void consumer()
{
	int i = 0;

	while (1) {
		char buf[2];

		buf[1] = 0;

		if (sem_wait(readsem) < 0) {
			perror("Error with sem_wait\n");
			return;
		}

		if (pread(file, buf, 1, i) < 0) {
			perror("Error with pread\n");
			return;
		}

		if (sem_post(writesem) < 0) {
			perror("Error with sem_post\n");
			return;
		}

		printf("Read done of: %s\n", buf);

		i++;
	}

	return;
}

int main (int argc, char const *argv[])
{
	int pid, ret = 0;

	/* Open file */
	file = open("my_file.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file < 0) {
		ret = 1;
		goto err_open;
	}

	/* Create the shared read semaphore. */
	readsem = sem_open("minireader", O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (readsem == SEM_FAILED) {
		ret = 1;
		goto err_read;
	}

	/* Create the shared write semaphore.
	 * Init to 1, because the producer can directly write a value. */
	writesem = sem_open("miniwriter", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (writesem == SEM_FAILED) {
		ret = 1;
		goto err_write;
	}

	/* Now create the son-process and start producing/consuming */
	pid = fork();
	if (pid < 0) {
		ret = 1;
		goto err_fork;
	}

	/* Are we the parent? */
	if (pid)
		producer();
	else
		consumer();

err_fork:
	sem_close(writesem);
err_write:
	sem_close(readsem);
err_read:
	close(file);
err_open:
	if (ret)
		perror("Error happened!\n");
	return ret;
}
