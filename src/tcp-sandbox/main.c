#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSZ 1000

char *hostname = "127.0.0.1";
int port = 1234;

int start_server() {
	struct sockaddr_in local;
	int cs, ss;
	char buf[BUFSZ];

	ss = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 0);

	inet_aton(hostname, &local.sin_addr);
	local.sin_port = htons(port);
	local.sin_family = AF_INET;

	bind(ss, (struct sockaddr *) &local, sizeof(local));
	listen(ss, 1);

	cs = accept(ss, NULL, NULL);

	read(cs, buf, BUFSZ);
	fprintf(stdout, "%s\n", buf);
	close(cs);
	close(ss);

	return 0;
}

int start_client() {
	struct sockaddr_in local;
	int s;
	char *text = "Hello from client!";

	s = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 0);

	inet_aton(hostname, &local.sin_addr);
	local.sin_port = htons(port);
	local.sin_family = AF_INET;

	connect(s, (struct sockaddr *) &local, sizeof(local));

	write(s, text, strlen(text) + 1);
	close(s);

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stdout, "Usage: %s [s|c]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	switch (*argv[1]) {
	case 's':
		start_server();
		break;
	case 'c':
		start_client();
		break;
	default:
		fprintf(stdout, "Usage: %s [s|c]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
