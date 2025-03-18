#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#define SHMSIZE 1000

void shm_read(key_t key, int buf[], int size) {
	void *addr;
	int *addri, shmid, i;

	if ((shmid=shmget(key, SHMSIZE, 0666)) == -1) {
		fprintf(stderr, "Getting shmid for %d key\n", key);
		perror("shmget error");
		exit(EXIT_FAILURE);
	}

	if ((addr=shmat(shmid, NULL, SHM_RDONLY)) == (void *) -1) {
		fprintf(stderr, "Couldn't attatch to shmid %d\n", shmid);
		perror("shmat error");
		exit(EXIT_FAILURE);
	}
	addri = (int *) addr;

	for (i = 0; i < size; ++i) {
		*buf++ = *addri++;
	}

	if (shmdt(addr) == -1) {
		perror("shmdt error");
		exit(EXIT_FAILURE);
	}
}

#define KEY 4321

int shm_write(int buf[], int size) {
	void *addr;
	int *addri, i, shmid;

	if ((shmid=shmget(KEY, SHMSIZE, IPC_CREAT | 0666)) == -1) {
		perror("shmget error");
		exit(EXIT_FAILURE);
	}


	if ((addr=shmat(shmid, NULL, 0)) == (void *) -1) {
		fprintf(stderr, "Couldn't attatch to key %d\n", shmid);
		perror("shmat error");
		exit(EXIT_FAILURE);
	}

	addri = (int *) addr;
	for (i = 0; i < size; ++i) {
		*addri++ = buf[i];
	}

	if (shmdt(addr) == -1) {
		perror("shmdt error");
		exit(EXIT_FAILURE);
	}

	return shmid;
}

#define LEN 100

int main(int argc, char *argv[]) {
	int shmid1, shmid2, buf1[LEN], buf2[LEN], i;

	if (argc < 3 || (shmid1=atoi(argv[1])) == 0 || (shmid2=atoi(argv[2])) == 0) {
		fprintf(stderr, "Couldn't parse shmid");
		fprintf(stderr, "Usage: %s <shmid1> <shmid2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	shm_read(shmid1, buf1, LEN);
	shm_read(shmid2, buf2, LEN);

	for (i = 0; i < LEN; ++i) {
		buf2[i] += buf1[i];
	}

	shm_write(buf2, LEN);

	fprintf(stdout, "%d\n", KEY);
	exit(EXIT_SUCCESS);
}
