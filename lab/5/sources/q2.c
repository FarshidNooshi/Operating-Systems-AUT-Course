#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void print(int *hist, int sample) {
    for (int i = 0; i < 25; i++) 
    {
        printf("%d\t", i - 12);
        if(sample <= 400) {
            for (int j = 0; j < hist[i]; j++){
                printf("*");
            }
            printf("\n");
        }
        else
            printf(" %d\n", hist[i]);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Enter sample number.\n");
        return 0;
    }
    int sample, counter, random, hist[25] = {0}, pid, status = 0;
    int segment_id = shmget(IPC_PRIVATE, 32, S_IRUSR | S_IWUSR);
    int *shared_memory = (int *)shmat(segment_id, NULL, 0);
    sscanf(argv[1], "%d", &sample);

    clock_t begin = clock();
    //5 processes
    pid = fork();
    if(pid == 0) {
        fork();
        fork();
    }
    srand(time(0));    
    for (int i = 0; i < sample / 5; i++)
    {
        counter = 12;
        for (int j = 0; j < 12; j++)
        {
            random = rand() % (100 + 1 - 0);
            if (random >= 49 && counter <= 23)
                counter++;
            else if (random < 49 && counter >= 1)
                counter--;
        }
        shared_memory[counter]++;
    }

    if (pid != 0){
        while (wait(&status) > 0);
        clock_t end = clock();
        printf("Runtime = %f s\n", ((double)end - begin) / CLOCKS_PER_SEC);
        print(shared_memory, sample);
        shmdt(shared_memory);
    }
    else{
        shmdt(shared_memory);
    }
    return 0;
}
