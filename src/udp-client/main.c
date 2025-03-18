#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSZ 1000

int main(int argc, char *argv[]) {
	struct sockaddr_in local;
	int s, result;
	char buf[BUFSZ];

	s = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, 0);
	fprintf(stdout, "socket=%d\n", s);

	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(1234);
	local.sin_family = AF_INET;

	/* client */
	result = connect(s, (struct sockaddr *) &local, sizeof(local));
	fprintf(stdout, "%d\n", result);

	write(s, "Hello!", 6);
	fprintf(stdout, "SENT");

	/* server */
	/* result = bind(s, (struct sockaddr *) &local, sizeof(local)); */
	/* fprintf(stdout, "%d\n", result); */

	/* read(s, buf, BUFSZ); */
	/* fprintf(stdout, "%s\n", buf); */
}
