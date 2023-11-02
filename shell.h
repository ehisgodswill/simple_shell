#ifndef SHELL_H
#define SHELL_H
extern char **environ;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
	char *name;
	char *arguments[20];
	int input_file;
	int output_file;
} Command;

void tokenize_input(char *input, Command *cmd);
void execute_command(Command *cmd);
void print_environment(void);

#endif
