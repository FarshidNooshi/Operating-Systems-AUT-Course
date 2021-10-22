#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int result = getProcCount();
    printf(1, "The number of processes in the system is %d\n", result);
    exit();
}