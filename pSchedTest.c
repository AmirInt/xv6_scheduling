#include "types.h"
#include "stat.h"
#include "user.h"

void run(int pid) {
    int i;
    for (i = 0; i < 10; ++i){
        printf(1, "%d ----> %d\n", pid, i);
        sleep(10);
    }
    exit();
}

int main() {
    changePolicy(2);
    int i;
    for (i = 0; i < 20; ++i) {
        if (i>10){
            if (fork() == 0 && setPriority(2)) {
                run(2);
                return 0;
            }
        }else 
            if (fork() == 0 && setPriority(1)) {
                run(1);
                return 0;
            }
        
        
    }
    for (i = 0; i < 20; ++i) {
        wait();
    }
    exit();
}