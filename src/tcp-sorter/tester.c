#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define CONNUM 5		/* maximum number of simultaneous connections */
#define BUFSZ 100

static char *hostname = "127.0.0.1";
static char *data[] = { "test", "hehe", "ohohohoho", "aaaaaa", "OFF", NULL };

int main(int argc, char *argv[]) {
	int port, ss, n;
	char buf[BUFSZ], **d;
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
	if (connect(ss, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
		perror("Connecting to server socket");
		exit(EXIT_FAILURE);
	}

	for (d = data; *d; ++d) {
		sprintf(buf, "Sending %s\n", *d);
		fprintf(stdout, "DEBUG: buf=%s\n", buf);
		fprintf(stdout, "DEBUG: sending *d=%s to the socket %d\n", *d, ss);
		if ((n=send(ss, *d, strlen(*d), 0)) == -1) {
			fprintf(stderr, "ERROR: Couldn't send, result is %d\n", n);
			perror("Sending data");
			exit(EXIT_FAILURE);
		}

		fprintf(stdout, "DEBUG: sent %s with result %d, waiting the response\n", *d, n);
		if ((n=recv(ss, buf, BUFSZ, 0)) == -1) {
			perror("Receiving data");
			exit(EXIT_FAILURE);
		}
		fprintf(stdout, "DEBUG: received data: [ ");
		for (int i = 0; i <= n; ++i) {
			fprintf(stdout,	"%s%s",
				(buf[i] == '\n') ? "\\n" :
				(buf[i] == '\0') ? "\\0" :
				(char[2]) { buf[i], '\0' },
				(i == n) ? "]\n" : ", ");
		}

		/* fprintf(stdout, "DEBUG: received %s(%d)\n", buf, n); */
	}

	fprintf(stdout, "Success\n");
	exit(EXIT_SUCCESS);
}
