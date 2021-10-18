#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    printf(1, "Since kernel boot there has been %d read calls\n", getReadCount());
    exit();
}