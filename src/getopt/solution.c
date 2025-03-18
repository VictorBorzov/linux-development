#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static struct option opts[] = {
	{ "query", required_argument, NULL, 'q' },
	{ "longinformationrequest", no_argument, NULL, 'i' },
	{ "version", no_argument, NULL, 'v' },
};

int main(int argc, char *argv[]) {
	int op, iop;

	while ((op=getopt_long(argc, argv, "q:iv", opts, &iop)) != -1) {
		switch (op) {
		case 'q':
			if (!optarg) {
				fputc('-', stdout);
				exit(EXIT_FAILURE);
			}
			break;
		case 'i': case 'v':
			break;
		default:
			fputc('-', stdout);
			exit(EXIT_FAILURE);
		}
	}
	fputc('+', stdout);
	exit(EXIT_SUCCESS);
}
