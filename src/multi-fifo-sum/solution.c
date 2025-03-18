#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXLEN 1024

char *name1 = "in1";
char *name2 = "in2";

int main(int argc, char *argv[]) {
	char line[MAXLEN];
	long int n;
	int r1, r2, f1, f2;
	fd_set fset;

	if ((f1=open(name1, O_RDONLY)) == -1 || (f2=open(name2, O_RDONLY)) == -1) {
		perror("ERROR: couldn't open file for read");
		exit(EXIT_FAILURE);
	}

	n = 0;
	do {
		FD_ZERO(&fset);
		FD_SET(f1, &fset);
		FD_SET(f2, &fset);


		switch (select(f2+1, &fset, NULL, NULL, NULL)) {
		case -1: case 0:	/* 0 for timeout */
			perror("ERROR: select");
			exit(EXIT_FAILURE);
			break;
		default:
			if (FD_ISSET(f1, &fset)) {
				if ((r1=read(f1, line, MAXLEN)) == -1) {
					perror("ERROR: couldn't read in1");
					exit(EXIT_FAILURE);
				}
				if (r1 > 0)
					n += atoll(line);
			}

			if (FD_ISSET(f2, &fset)) {
				if ((r2=read(f2, line, MAXLEN)) == -1) {
					perror("ERROR: couldn't read in2");
					exit(EXIT_FAILURE);
				}
				if (r2 > 0)
					n += atoll(line);
			}
			break;
		}
	} while (r1 != 0 && r2 != 0);

	if (close(f1) != 0 || close(f2) != 0) {
		perror("ERROR: couldn't close files");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "%ld\n", n);
}
