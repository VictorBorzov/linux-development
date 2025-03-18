#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSZ 5120

char *hostname = "127.0.0.1";

int main(int argc, char *argv[]) {
	int port, fd, off;
	char buf[BUFSZ];
	ssize_t n;
	struct sockaddr_in addr;

	if (argc != 2 || (port=atoi(argv[1])) == 0) {
		fprintf(stdout, "Usage: %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (inet_aton(hostname, &addr.sin_addr) == 0) {
		perror("Couldn't convert hostname to network address");
		exit(EXIT_FAILURE);
	}
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Couldn't open a socket");
		exit(EXIT_FAILURE);
	}

	if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
		perror("Binding socket");
		exit(EXIT_FAILURE);
	}

	off = 0;
	while (!off) {
		switch (n=recv(fd, buf, BUFSZ, 0)) {
		case 0:
			exit(EXIT_FAILURE);
			break;
		case -1:
			perror("Couldn't receive");
			exit(EXIT_FAILURE);
			break;
		default:
			buf[n] = '\0';
			if (!(off=strcmp(buf, "OFF\n") == 0)) {
				fprintf(stdout, "%s\n", buf);
			}
			break;
		}
	}

	exit(EXIT_SUCCESS);
}
