#include "types.h"
#include "stat.h"
#include "user.h"

void run(int pid) {
    int i;
    for (i = 0; i < 10; ++i){
        printf(1, "%d : %d\n", pid, i);
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