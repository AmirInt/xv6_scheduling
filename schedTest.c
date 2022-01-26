#include "types.h"
#include "stat.h"
#include "user.h"
#include <stddef.h>

void run(int pid) {
    int i;
    for (i = 0; i < 100; ++i) {
        for(long j = 0;; j++);
    }
    exit();
}

int main() {
    // changePolicy(1);

    int i;
    for (i = 0; i < 4; ++i) {
        if (fork() == 0) {
            run(getpid());
            return 0;
        }
    }
    for (i = 0; i < 4; ++i) {
        wait();
    }
    exit();
}