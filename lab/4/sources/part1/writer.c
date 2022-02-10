#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main (int argc, char *argv[])
{
    int segment_id;
    char* shared_memory;
    int shared_segment_size = 100;

    struct shmid_ds shmbuffer;
    int segment_size;


    segment_id = shmget(IPC_PRIVATE, shared_segment_size, S_IRUSR | S_IWUSR);

    shared_memory = (char*) shmat (segment_id, NULL, 0);
    printf("shared memory attached at address %p\n", shared_memory);

    shmctl(segment_id, IPC_STAT, &shmbuffer);
    segment_size = shmbuffer.shm_segsz;
    printf("segment size: %d\n", segment_size);

    sprintf(shared_memory, "%s", argv[1]);
    printf("This string inserted in shared memory: %s\n\n", argv[1]);

    shmdt(shared_memory);
    
    //read
    char *shm;
    if((shm = (char*)shmat(segment_id, NULL, 0)) == (char *) -1) {
    	perror("Error occured.");
    }
    else {
    	printf("Read from shared memory: %s\n", shm);
    }
    printf("program completed.\n");

    return 0;
}
