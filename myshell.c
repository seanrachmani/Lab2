#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
#include "LineParser.h"
#include <unistd.h>




/*
==========task 0a:==========
==========execute==========
PRE:receives a parsed line
POST:invokes the program specified in the cmdLine using the proper system call
EXECV:int execv(const char* path,char* const argv[])
path is saved in argv[0](parse did it for us), returns only in case of an error
*/
void execute(cmdLine* pCmdLine){
    int error = execvp(pCmdLine->arguments[0],pCmdLine->arguments);
    if(error == -1){
        perror("error:");
        freeCmdLines(pCmdLine);
        exit(1);
    }
}
/*
==========0a theoretical==========
1)deleting main memory:
Q:Although you loop infinitely, the execution ends after execv. Why is that?
A:successful execv deletes current process memory includes our main & infinity loop,
and the current PID is changing to the code of the new command we parsed. 
2)full path:
Q:You must place the full path of an executable file in-order to run properly. why?
A:bc execv search the command in the directory we are currently in.
and there is no basic commands in the lab folder. 
3)execvp:
-after replacing to execvp no need for full path sunce execvp knows variable named PATH
that saving default folders for basic commands. so just ls working
-Q:Wildcards, as in "ls *", are not working. (Again, why?)
A:bc wildcards being maintained by shell and not by os,
and right now our shell doesnt have this feature. 
for example bash sending collecting file/folders names in current folder and 
sending the os ls command with this list so we get all subfolders too.
*/

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