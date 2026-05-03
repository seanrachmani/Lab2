#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
#include "LineParser.h"


//task 0a:
//receives a parsed line
//invokes the program specified in the cmdLine using the proper system call (see man execv).
execute(cmdLine *pCmdLine)




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
        
    }
}