#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    printf(1, "There are currently %d processes running\n", getProcCount());
    exit();
}