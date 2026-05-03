#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
#include "LineParser.h"
#include <unistd.h>




/*task 0a:
==========execute==========
PRE:receives a parsed line
POST:invokes the program specified in the cmdLine using the proper system call
EXECV:int execv(const char* path,char* const argv[])
path is saved in argv[0](parse did it for us), returns only in case of an error
*/
void execute(cmdLine* pCmdLine){
    int error = execv(pCmdLine->arguments[0],pCmdLine->arguments);
    if(error == -1){
        perror("error:");
        freeCmdLines(pCmdLine);
        exit(1);
    }
}



/*
===========myNotes==========
1)cant use == for strings
*/
int main(int argc, char **argv){
    while(1){
        char buf[PATH_MAX];
        char* path = getcwd(buf,PATH_MAX);
        fprintf(stdout,"current working directory is:%s\n",path);
        char input[2048];
        //read from user
        fgets(input,2048,stdin);
        //parse:
        cmdLine* line = parseCmdLines(input);
        //if the user clicked enter etc the parsing is NULL
        if(line != NULL){
            if(strcmp(line->arguments[0],"quit") == 0){
                freeCmdLines(line);
                exit(0);
            }
            execute(line);
        }
    }
}