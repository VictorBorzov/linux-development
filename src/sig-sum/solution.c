#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_sa_handler(int signo) {
	static long unsigned n1 = 0, n2 = 0;

	switch (signo) {
	case SIGUSR1:
		++n1;
		break;
	case SIGUSR2:
		++n2;
		break;
	case SIGTERM:
		fprintf(stdout, "%lu %lu\n", n1, n2);
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}

int main(int argc, char *argv[]) {
	signal(SIGUSR1, my_sa_handler);
	signal(SIGUSR2, my_sa_handler);
	signal(SIGTERM, my_sa_handler);

	while (1);
}
