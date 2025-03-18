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

	fprintf(stdout, "Canonical name: %s\n", h->h_name);

	fprintf(stdout, "Aliases: [");
	for (a = h->h_aliases; *a != NULL; ++a) {
		fprintf(stdout, " %s", *a);
		if (*(a+1) != NULL) {
			fputc(',', stdout);
		}
	}
	fputs("]\n", stdout);
	fprintf(stdout, "Type = %s, len = %d\n", (h->h_addrtype == AF_INET) ? "ipv4" : "ipv6", h->h_length);

	fprintf(stdout, "Adresses: [");
	for (a = h->h_addr_list; *a != NULL; ++a) {
		addr = (struct in_addr *) (*a);
		fprintf(stdout, " %s", inet_ntoa(*addr));
		if (*(a+1) != NULL) {
			fputc(',', stdout);
		}
	}
	fputs(" ]\n", stdout);
}
