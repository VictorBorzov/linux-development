#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
	char **a;
	struct in_addr *addr;
	struct hostent *h;

	if (argc != 2) {
		exit(EXIT_FAILURE);
	}

	if ((h=gethostbyname(argv[1])) == NULL) {
		perror("gethostbyname");
		exit(EXIT_FAILURE);
	}

	for (a = h->h_addr_list; *a != NULL; ++a) {
		addr = (struct in_addr *) (*a);
		fprintf(stdout, "%s\n", inet_ntoa(*addr));
	}
	exit(EXIT_SUCCESS);
}
