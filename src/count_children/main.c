#include <stdio.h>
#include <string.h>
#include <dirent.h>

long count_procs_byname(char *name);

int main() {
	long n;
	n = count_procs_byname("genenv");
	fprintf(stdout, "%ld\n", n);
}

#define NAME_LEN 267

/* count_children: count */
int process_name_matches(char name[], struct dirent *e) {
	char line[NAME_LEN], *l;
	char buffer[NAME_LEN];
	FILE *f;

	sprintf(buffer, "/proc/%s/comm", e->d_name);
	if ((e->d_type & DT_DIR) == 0 || strchr(e->d_name, '.') || (f=fopen(buffer, "r")) == NULL)
		return 0;

	l = fgets(line, NAME_LEN, f);
	fclose(f);
	if (l == NULL)
		return 0;

	sscanf(line, "%255s\n", buffer);
	/* fprintf(stderr, "DEBUG: read %s name\n", buffer); */
	return strcmp(buffer, name) == 0;
}

long count_procs_byname(char *name) {
	long result = 0;
	DIR *d;
	struct dirent *e;

	/* fprintf(stderr, "DEBUG: openning /proc\n"); */
	d = opendir("/proc");

	while ((e=readdir(d)) != NULL) {
		result += process_name_matches(name, e);
	}

	/* fprintf(stderr, "DEBUG: DONE\n"); */
	return result;
}
