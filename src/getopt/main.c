#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define MAXLEN 1024

char quote[] = "Wenn du lange in einen Abgrund blickst, blickt der Abgrund auch in dich hinein.";

int main(int argc, char *argv[]) {
	int is_brackets, optindex, opchar, length, test;
	char test_name[MAXLEN];
	test = is_brackets = optindex = opchar = length = 0;

	struct option opts[] = {
		/* set flag example */
		{ "brackets", no_argument, &is_brackets, 'b' },
		/* option args */
		{ "length", required_argument, 0, 'l' },
		/* longname option */
		{ "authornamesshouldbeprinted", no_argument, 0, 'a' },
		{ "test", optional_argument, NULL, 't' },
		{ 0, 0, 0, 0 },
	};

	while ((opchar=getopt_long(argc, argv, "bl:t:aq", opts, &optindex)) != -1) {
		switch (opchar) {
		case 0:
			fprintf(stdout, "0\n");
			break;
		case 'l':
			length = atoi(optarg);
			fprintf(stdout, "length=%d\n", length);
			break;
		case 'a':
			fprintf(stdout, "(c) Friedrich Nietzsche\n");
			break;
		case 't':
			test = 1;
			fprintf(stdout, "found option t, optarg=%s\n", optarg);
			strncpy(test_name, optarg, strlen(optarg));
			break;
		default:
			fprintf(stderr, "opchar: %c\n", opchar);
			exit(EXIT_FAILURE);
			break;
		}
	}

	if (test)
		fprintf(stdout, test_name);

	if (strlen(quote) > length && length != 0) {
		quote[length] = '\0';
	}

	if (is_brackets) {
		fprintf(stdout, "[%s]\n", quote);
	} else {
		fprintf(stdout, "%s\n", quote);
	}

	fprintf(stdout, "Done.\n");
	exit(EXIT_SUCCESS);
}
