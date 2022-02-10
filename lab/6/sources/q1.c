//In The Name Of GOD
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_COUNT 5

typedef struct {
    int count;
    int reader_count;
    sem_t count_mutex;
    sem_t reader_count_mutex;
} Buffer;

int main(int argc, char* argv[])
{
    int status = 0;
    int parent_pid = getpid();

    Buffer *buffer;
    int sh_writer = shmget(0x125, 32, S_IRUSR | S_IWUSR | IPC_CREAT);
    int sh_reader = shmget(0x125, 32, S_IRUSR | IPC_CREAT);
    buffer = (Buffer *)shmat(sh_writer, NULL, 0);
    buffer->count = 0;
    buffer->reader_count = 0;
    sem_init(&(buffer->count_mutex), 1, 1);
    sem_init(&(buffer->reader_count_mutex), 1, 1);
    shmdt(buffer);

    for (int i = 0; i < 4; i++)
    {
        if (parent_pid == getpid())
        {
            fork();
            printf("forked\n");
        }
    }
    
    
    if (parent_pid == getpid())
    {     
        buffer = (Buffer *) shmat(sh_writer, NULL, 0);
        for (int i = 1; i <= MAX_COUNT; i++)
        {
            sem_wait(&(buffer->count_mutex));
            printf("Parent-%d: Writing %d\n", parent_pid, i);
            buffer->count = i;
            sem_post(&(buffer->count_mutex));
            sleep(0.1);
        }
        shmdt(buffer);
    }
    else
    {   
        int child = getpid();
        int flag = 1;
        buffer = (Buffer *) shmat(sh_reader, NULL, 0);

        while(flag)
        {
            sem_wait(&(buffer->reader_count_mutex)); 
            buffer->reader_count++;
            if (buffer->reader_count == 1)
            {
                sem_wait(&(buffer->count_mutex));
            }
            sem_post(&(buffer->reader_count_mutex)); 

            printf("Child-%d: %d\n", child, buffer->count);
            if (buffer->count >= MAX_COUNT)
            {
                flag = 0;
            }

            sem_wait(&(buffer->reader_count_mutex)); 
            buffer->reader_count--;
            if (buffer->reader_count == 0)
            {
                sem_post(&(buffer->count_mutex));
            }
            sem_post(&(buffer->reader_count_mutex)); 

            sleep(0.05);
        }
        shmdt(buffer);
    }

    if (parent_pid == getpid())
    {
        while (wait(&status) > 0);
        shmctl(sh_writer, IPC_RMID, NULL); 
    }

    return 0;
}
