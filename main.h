#ifndef _MAIN_SHELL
#define _MAIN_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

/**
 * structure data - all data needed at run time
 * @argv: Argument vector
 * @command: command written to execute
 * @pid: shell process id
 * @env: enviromental variable
 * 
*/
typedef struct data
{
    int argc;
    char **argv;
    char *command, *pid, *env;
} data;

void setdata(data shelldata,char **av);
#endif
