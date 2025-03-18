#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define MAXLEN 1024

int main(int argc, char *argv[]) {
	char c, s[MAXLEN];
	long unsigned n;
	FILE *f;

	if (argc < 3) {
		fprintf(stdout, "ERROR: Not enough arguments\nUsage: %s <command> <arg>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	sprintf(s, "%s %s", argv[1], argv[2]);

	if ((f=popen(s, "re")) == NULL) {
		errx(EXIT_FAILURE, "coudln't open stream for %s\n", argv[1]);
	}

	for (n = 0; (c=getc(f)) != EOF; n += (c == '0'));

	if (pclose(f) != 0) {
		errx(EXIT_FAILURE, "command %s failed\n", argv[1]);
	}

	fprintf(stdout, "%d\n", n);
}
