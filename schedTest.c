#include "types.h"
#include "stat.h"
#include "user.h"
#include <stddef.h>

void run(int pid) {
    int i;
    for (i = 0; i < 1000; ++i)
        printf(1, "%d, %d\n", pid, i);
    exit();
}

int main() {
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