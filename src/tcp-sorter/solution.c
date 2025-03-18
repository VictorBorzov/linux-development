#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define CONNUM 5		/* maximum number of simultaneous connections */
#define BUFSZ 100

static char *hostname = "127.0.0.1";

static int ccmp(const void *l, const void *r) {
	char cl, cr;

	cl = *(char *) l;
	cr = *(char *) r;

	return cr - cl;
}

int main(int argc, char *argv[]) {
	int port, ss, cs, n;
	char buf[BUFSZ];
	struct sockaddr_in addr;

	if (argc != 2 || (port=atoi(argv[1])) == 0) {
		fprintf(stdout, "Usage: %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (inet_aton(hostname, &addr.sin_addr) == 0) {
		fprintf(stderr, "Invalid addres");
		exit(EXIT_FAILURE);
	}
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	if ((ss=socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 0)) == -1) {
		perror("Creating socket");
		exit(EXIT_FAILURE);
	}
	if (bind(ss, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
		perror("Binding socket");
		exit(EXIT_FAILURE);
	}
	if (listen(ss, CONNUM) != 0) {
		perror("Listening");
		exit(EXIT_FAILURE);
	}

	if ((cs=accept(ss, NULL, NULL)) == -1) {
		perror("Accepting connection");
		exit(EXIT_FAILURE);
	}
	while (1) {
		if ((n=recv(cs, buf, BUFSZ, 0)) == -1) {
			perror("Receiving data");
			exit(EXIT_FAILURE);
		}

		if (strncmp(buf, "OFF", 3) == 0) {
			break;
		}

		qsort(buf, n, sizeof(char), ccmp);

		if (send(cs, buf, n, 0) == -1) {
			perror("Sending response");
			exit(EXIT_FAILURE);
		}
	}

	if (close(cs) != 0) {
		perror("Closing connection socket");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
