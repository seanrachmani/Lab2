#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
#include "LineParser.h"
#include <unistd.h>




/*
==========execute==========
==========task 0a notes:==========
PRE:receives a parsed line
POST:invokes the program specified in the cmdLine using the proper system call
EXECV:int execv(const char* path,char* const argv[])
path is saved in argv[0](parse did it for us), returns only in case of an error
==========task 1b notes:==========
fork returns pid
if(!(pid=fork())) bc we want to save the son id or somethign like this, might understand later

==========task 1b theoretical:==========
Although if fork( ) fails you are in real trouble anyway (e.g. fork bomb!)

2)Q:If execvp fails, use _exit() (see man) to terminate the process. (Why?)
  A:
*/
void execute(cmdLine* pCmdLine){
    const char* path = pCmdLine->arguments[0];
    char* const argv[] = pCmdLine->arguments;
    int argCount = pCmdLine->argCount;
    pid_t pid;
    //code taken from lecture 2:
    if(!(pid=fork())){ //child
    //end of taken code
        execvp(path,argv);
        //if we got to these line we returned aka error:
        perror("error:");
        freeCmdLines(pCmdLine);
        _exit();
    }
    if(debug){
        fprintf(stderr,"PID: %ld\n file name: %s\n",pid,path);
        if(pCmdLine->blocking){
            fprintf(stderr,"background");
        }
        else{
            fprintf(stderr,"foreground");
        }   
    }
    //wait for child:
    while(1){
        sleep(1);
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
int debug = 0;
int main(int argc, char **argv){
    while(1){
        if(argv[sizeof(argv)] == 'd'){
            debug = 1;
        }
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