#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

void print_parents(int argc, char *argv[]) {
	unsigned long long ppid;
	char stat[32];
	char line[1024], *l;
	FILE *stat_file;

	if (argc < 2) {
		fprintf(stderr, "ERROR: expected pid\n");
		exit(EXIT_FAILURE);
	}

	ppid = atoll(argv[1]);
	printf("%lli\n", ppid);
	while (ppid != 1) {
		sprintf(stat, "/proc/%lli/stat", ppid);
		stat_file = fopen(stat, "r");
		if (stat_file == NULL) {
			fprintf(stderr, "ERROR: Couldn't open file %s", stat);
			exit(EXIT_FAILURE);
		}
		if ((l=fgets(line, 1024, stat_file)) == NULL) {
			fprintf(stderr, "ERROR: Couldn't read file %s", stat);
			exit(EXIT_FAILURE);
		}
		fclose(stat_file);
		sscanf(line, "%*i %*s %*c %lli", &ppid);
		printf("%lli\n", ppid);
	}
}

#define DIRNAME_LEN 1024
#define LINE_LEN 1024
long long unsigned count_children(long long unsigned pid);

int main(int argc, char *argv[]) {
	long long unsigned pc;

	if (argc < 2) {
		fprintf(stderr, "ERROR: expected pid\n");
		exit(EXIT_FAILURE);
	}

	pc = count_children(atoll(argv[1]));
	printf("%llu\n", pc);
}

#define LINE_LEN 1024
long long unsigned count_children(long long unsigned pid) {
	long long unsigned pc;
	char children[DIRNAME_LEN], *token, line[LINE_LEN], *l, *saveptr;
	FILE *f;

	pc = 1;

	/* read children file */
	sprintf(children, "/proc/%llu/task/%llu/children", pid, pid);
	if ((f=fopen(children, "r")) == NULL)
		return pc;

	/* count all children */
	l = fgets(line, LINE_LEN, f);
	if (l != NULL) {
		token = strtok_r(line, " ", &saveptr);

		while (token != NULL) {
			pc += count_children(atoll(token));
			token = strtok_r(NULL, " ", &saveptr);
		}
	}
	fclose(f);

	return pc;
}
