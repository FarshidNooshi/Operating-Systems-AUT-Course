#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
	const int SIZELAB = 4096;
	const char *nameOS = "OS";
	const char *messageToWrite = "Hi!";
	int shmFD = shm_open(nameOS, O_CREAT | O_RDWR, 0666);
	ftruncate(shmFD, SIZELAB);
	void *ptr = mmap(0, SIZELAB, PROT_WRITE, MAP_SHARED, shmFD, 0);
	sprintf(ptr, "%s", messageToWrite);
	printf("Writer wrote: \' %s \'", messageToWrite);
	return 0;
}
