#include "types.h"
#include "stat.h"
#include "user.h"

void run(int pid) {
    int i;
    for (i = 0; i < 10; ++i)
        printf(1, "%d ----> %d\n", pid, i);
    exit();
}

int main() {
    int i;
    for (i = 0; i < 4; ++i) {
        if (fork() == 0 && setPriority(i+1)) {
            run(i+1);
            return 0;
        }
    }
    for (i = 0; i < 4; ++i) {
        wait();
    }
    exit();
}