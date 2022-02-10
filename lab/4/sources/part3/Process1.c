#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
  
int main(){
	//file descriptor
	int fd;

	// FIFO file path
	char * myfifo = "/tmp/myfifo";

	// Creating the named file(FIFO) 
	mkfifo(myfifo, 0666);

	fd = open(myfifo, O_WRONLY);

	char s1[] = "First process.";

	write(fd, s1, strlen(s1)+1);
	printf("p1->p2: %s\n", s1);
	close(fd);

	// Open FIFO for Read only
	fd = open(myfifo, O_RDONLY);

	// Read from FIFO
	char s2[100];
	read(fd, s2, sizeof(s2));

	// Print the read message
	printf("p2->p1: %s\n", s2);
	close(fd);
	return 0;
}
