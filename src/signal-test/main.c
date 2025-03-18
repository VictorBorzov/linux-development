#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void my_signal_handler(int signalno) {
	fprintf(stdout, "Called with signal %d\n", signalno);
}

int main(void) {

	signal(SIGINT, my_signal_handler);
	while (1) {
		fprintf(stdout, "Hello, World\n");
		usleep(500000);
	}
}
