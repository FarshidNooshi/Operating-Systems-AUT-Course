#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int result = getReadCount();
    printf(1, "number of System calls for read is %d\n", result);
    exit();
}