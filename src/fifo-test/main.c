#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

const char *f1_name = "./f1.fifo";
const char *f2_name = "./f2.fifo";

void read_and_report(int fd) {
	char buf[100];
	int n;

	fprintf(stdout, "FD %d is ready for read\n", fd);

	n = read(fd, buf, 100);
	buf[n] = 0;

	fprintf(stdout, "Got %d bytes from %d: %s\n", n, fd, buf);
}

int main(void) {
	int fd1, fd2, result;
	fd_set read_set;

	fd1 = open(f1_name, O_RDWR);
	fd2 = open(f2_name, O_RDWR);
	if (fd1 == -1 || fd2 == -1) {
		perror("ERROR: openning pipes:");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "Descriptors: %d %d\n", fd1, fd2);

	while (1) {
		FD_ZERO(&read_set);
		FD_SET(fd1, &read_set);
		FD_SET(fd2, &read_set);

		result = select(fd2+1, &read_set, NULL, NULL, NULL);

		switch (result) {
		case -1:
			perror("ERROR: select");
			close(fd1);
			close(fd2);
			exit(EXIT_FAILURE);
			break;
		case 0:
			fprintf(stdout, "WARN: select returned 0\n");
			break;
		default:
			if (FD_ISSET(fd1, &read_set)) {
				read_and_report(fd1);
			}
			if (FD_ISSET(fd2, &read_set)) {
				read_and_report(fd2);
			}
			break;
		}
	}

	close(fd1);
	close(fd2);
}
