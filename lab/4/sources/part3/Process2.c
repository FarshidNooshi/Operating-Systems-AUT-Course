#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
  
void convert(char* s){
	for(int i = 0; i < strlen(s); i ++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] - 'A' + 'a';
        }
        else if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = s[i] - 'a' + 'A';
        }
	}  
}
  
int main(){
	// file descriptor
	int fd1;

	// FIFO file path
	char * myfifo = "/tmp/myfifo";

	// Creating the named file(FIFO)
	mkfifo(myfifo, 0666);

	// open in read only and read
	char s1[100];
	fd1 = open(myfifo,O_RDONLY);


	// read string and close
	read(fd1, s1, sizeof(s1));
	close(fd1);

	convert(s1);

	// open in write mode then write string taken.
	fd1 = open(myfifo,O_WRONLY);
	write(fd1, s1, strlen(s1)+1);
	close(fd1);
	return 0;
}
