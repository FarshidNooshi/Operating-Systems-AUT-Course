#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define PORT 8080
#define MAX_BUFFER 4096



int check(int val , char* message);
void receiver(int sock);
void sender(int sock , pid_t pid);



int main(int argc, char const *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    check(sock = socket(AF_INET, SOCK_STREAM, 0),"\n Socket creation error \n");
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, argv[2], &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
    check(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)),"\nConnection Failed \n");
    check(send(sock, argv[3], strlen(argv[3]), 0),"send");
    pid_t pid = fork();
    if(pid > 0)
        while (1)
            sender(sock,pid);
    else
        while (1)
            receiver(sock);

    return 0;
}

void receiver(int sock){
    char buffer[MAX_BUFFER] = {0};
    while(check(read(sock, buffer, MAX_BUFFER), "send")>0){
        printf("%s\n",buffer);
        memset(buffer , 0 , MAX_BUFFER);
    }
}

void sender(int sock , pid_t pid){
    char buffer[MAX_BUFFER] = {0};
    fgets(buffer ,sizeof(buffer) , stdin);
    check(send(sock, buffer, strlen(buffer), 0),"send");
    if(strcmp(buffer ,"quit\n")==0){
        kill(pid , SIGKILL);
        exit(EXIT_SUCCESS);
    }
}



int check(int val , char* message){
    if(val < 0){
        perror(message);
        exit(EXIT_FAILURE);
    }
    return val;
}