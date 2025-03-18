#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#define SHMSIZE 1000

void shm_write(int key, int (*fi)(int)) {
	void *addr;
	int *addri, shmid, i;

	if ((shmid=shmget(key, SHMSIZE, IPC_CREAT | 0666)) == -1) {
		perror("shmget error");
		exit(EXIT_FAILURE);
	}

	if ((addr=shmat(shmid, NULL, 0)) == (void *) -1) {
		fprintf(stderr, "Couldn't attatch to shmid %d\n", shmid);
		perror("shmat error");
		exit(EXIT_FAILURE);
	}

	addri = (int *) addr;
	for (i = 1; i <= 100; ++i) {
		*addri++ = (*fi)(i);
	}

	if (shmdt(addr) == -1) {
		perror("shmdt error");
		exit(EXIT_FAILURE);
	}
}

void shm_read(int key, int buf[], int size) {
	void *addr;
	int *addri, shmid, i;

	if ((shmid=shmget(key, SHMSIZE, 0666)) == -1) {
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

char *target_program_name = "./solution";

#define KEY 123
#define BUFLEN 1000
#define LEN 100

int id(int i) { return i; }
int mul10(int i) { return i * 10; }

void delete_shmid(int key) {
	struct shmid_ds ds;
	int shmid;

	if ((shmid=shmget(key, SHMSIZE, IPC_CREAT | 0666)) == -1) {
		perror("shmget error");
		exit(EXIT_FAILURE);
	}

	if (shmctl(shmid, IPC_RMID, &ds) == -1) {
		perror("shmctl error");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]) {
	int key1, key2, key3, res[LEN], i;
	char buf[BUFLEN];
	FILE *f;

	key1 = KEY;
	key2 = key1 + 1;
	shm_write(key1, id);
	fprintf(stderr, "DEBUG: written key %d\n", key1);
	shm_write(key2, mul10);
	fprintf(stderr, "DEBUG: written key %d\n", key2);

	sprintf(buf, "%s %d %d", target_program_name, key1, key2);
	f = popen(buf, "re");
	fprintf(stderr, "DEBUG: called %s\n", buf);
	if (fgets(buf, BUFLEN, f) == NULL) {
		perror("Couldn't read output");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "DEBUG: received %s\n", buf);
	if ((key3 = atoi(buf)) == 0) {
		fprintf(stderr, "Couldn't parse shmid\n");
		exit(EXIT_FAILURE);
	}
	if (pclose(f) == -1) {
		perror("pclose");
		exit(EXIT_FAILURE);
	}

	shm_read(key3, res, LEN);
	for (i = 0; i < LEN; i += 5) {
		fprintf(stdout, "\t%d\t%d\t%d\t%d\t%d\n", res[i], res[i+1], res[i+2], res[i+3], res[i+4]);
	}

	delete_shmid(key1);
	delete_shmid(key2);
	delete_shmid(key3);

	fprintf(stderr, "DEBUG: SUCCESS\n");
	exit(EXIT_SUCCESS);
}
