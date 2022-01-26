#include "types.h"
#include "stat.h"
#include "user.h"

void run(int pid) {
    int i;
    for (i = 0; i < 10; ++i){
        for(long j = 0;; j++);
    }
    exit();
}

int main() {
    setPriority(1);
    for (int i = 0; i < 3; ++i)
        if (fork() == 0) {
            setPriority(6);
            run(getpid());
        }
    for (int i = 0; i < 3; ++i)
        if (fork() == 0) {
            setPriority(4);
            run(getpid());
        }
    for (int i = 0; i < 3; ++i)
        if (fork() == 0) {
            setPriority(2);
            run(getpid());
        }

    for (int i = 0; i < 9; ++i) {
        wait();
    }
    exit();
}