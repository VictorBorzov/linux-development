#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void hdnl(int signo) {
	switch (signo) {
	case SIGURG:
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[]) {
	sigset_t set;

	if (sigemptyset(&set) == -1 || 	sigaddset(&set, SIGINT) == -1) {
		perror("Couldn't set sigset");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGURG, hdnl) == SIG_ERR) {
		perror("Couldn't set SIGURG handler");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "%d\n", getpid());

	chdir("/");
	setsid();
	fclose(stdin);
	fclose(stderr);
	fclose(stdout);

	sigsuspend(&set);
}
