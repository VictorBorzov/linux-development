#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <unistd.h>

#define STACK_SIZE 10000

char child_stack[STACK_SIZE+1];

/* child: every 0.5 second spam child turn %n (for child process test) */
int child(void *params) {
	int c = 0;
	while (1) {
		usleep(500000);
		fprintf(stdout, "child turn %d\n", c++);
	}
}

int main(void) {
	int c = 0;
	int result;

	/* use the end of a stack because its value is less than the beginning */
	result = clone(child, child_stack + STACK_SIZE, CLONE_PARENT, 0);
	fprintf(stdout, "clone result = %d\n", result);
	
	while (1) {
		usleep(500000);
		fprintf(stdout, "parent turn %d\n", c++);
	}
}
