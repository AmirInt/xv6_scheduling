#include "types.h"
#include "stat.h"
#include "user.h"
#include <stddef.h>

int x;

void incrementor(void* args) {
	sleep(100);
	for (int i = 0; i < 3; ++i) {
		printf(1, "Thread: %d\n", x);
		sleep(200);
		x += 5;
	}
}

void arger(void* args) {
	sleep(*(int*) args);
	printf(1, "Arger: args: %d\n", *(int*) args);
}

int main() {
	// Test Phase 1:
	x = 0;

	int thread_id = thread_creator(&incrementor, NULL);
	if (thread_id == -1)
		return -1;
	
	for (int i = 0; i < 3; ++i) {
		printf(1, "Parent: %d\n", x);
		sleep(200);
		x += 2;
	}

	thread_wait();

	// Test Phase 2:
	int args[2] = {2000, 1000};
	
	thread_id = thread_creator(&arger, (void*) args);
	if (thread_id == -1)
		return -1;
	thread_id = thread_creator(&arger, (void*) (args + 1));
	if (thread_id == -1)
		return -1;

	printf(1, "Currently %d processes running\n", getProcCount());

	while (thread_wait() > 0) {
		printf(1, "Waited once\n");
	}

	printf(1, "Currently %d processes running\n", getProcCount());

	exit();
}