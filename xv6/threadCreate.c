#include "types.h"
#include "stat.h"
#include "user.h"

#define PAGESIZE 4096

int threadCreate(void (*fn)(void *), void *arg)
{
    void *pointer = malloc(2 * (PAGESIZE));
    void *stack;
    if (pointer == 0)
        return -1;
    int mod = (uint)pointer % PAGESIZE;
    if (mod == 0)
        stack = pointer;
    else
        stack = pointer + (PAGESIZE - mod);
    int thread_id = clone((void *)stack);
    if (thread_id < 0) 
        printf(1, "clone failed\n");
    else if (thread_id == 0)
    {
        (fn)(arg);
        free(stack);
        exit();
    }
    return thread_id;
}