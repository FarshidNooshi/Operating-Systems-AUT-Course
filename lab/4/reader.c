#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	const int SIZEFORLAB = 4096;
	const char *nameOS = "OS";
	int shmFD = shm_open(nameOS, O_RDONLY, 0666);
	ftruncate(shmFD, SIZEFORLAB);
	void *ptr = mmap(0, SIZEFORLAB, PROT_READ, MAP_SHARED, shmFD, 0);
	printf("Writer wrote: \' %s \'", (char *)ptr);
	shm_unlink(nameOS);
	return 0;
}
