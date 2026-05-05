#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    if(argc == 1){
        fprintf(stdout,"no message was written\n");
        return 1;
    }
    char* message = argv[1];
    int fd[2]; 
    pipe(fd);
    //read is 0, write is 1, child reads, parent write
    pid_t pid;
    //code taken from lecture 2:
    if(!(pid=fork())){ //child
    //end of taken code
        close(fd[1]);
        //read(fd,buffer to put message,count)
        char buffer[256];
        int endChar = read(fd[0],buffer,256);
        if(endChar == -1){
            perror("read error:");
            _exit(1);
        }
        buffer[endChar] = 0;
        fprintf(stdout,"the message from father is: %s\n",buffer);
        close(fd[0]);
        _exit(0);
    }
    else{
        close(fd[0]);
        //write(fd,message to send,count)
        write(fd[1],message,strlen(message));
        close(fd[1]);
        waitpid(pid,NULL,0);
        _exit(0);/*  */
    }
    return 0;
}