#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>		/* pipe */

#define MAX_LEN 1024

char *file = "./test_data";

void start_server() {
	int pipios[2];

	if (pipe(pipios) == -1) {
		errx(EXIT_FAILURE"ERROR: couldn't open pipe");
	}
	
}

int main(int arc, char *argv[]) {
	write_data(argv[0]);
}
