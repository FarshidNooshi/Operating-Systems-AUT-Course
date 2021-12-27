#include "types.h"
#include "stat.h"
#include "user.h"

void childPrint(void *args)
{
    printf(1, "childs function executed properly with args: %d\n", *(int *)args);
}

int main(void)
{
    int argument = 0x0FA1; // 4001 in decimal
    int thread_id = threadCreate(&childPrint, (void *)&argument);
    
    if (thread_id < 0)
        printf(1, "thread_create failed!\n");
    join();
    printf(1, "thread_id is : %d\n", thread_id);
    exit();
}