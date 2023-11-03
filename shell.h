#ifndef SHELL_H
#define SHELL_H
extern char **environ;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

/**
 * struct command - command structure
 * @name: name of the command
 * @arguments: array of argument vector
 * @input_file: input fd
 * @output_file: output fd
 *
 * Description: struct that holds all relevant command and argument
 */
typedef struct command
{
	char *name;
	char *arguments[20];
	int input_file;
	int output_file;
} Command;

void tokenize_input(char *input, Command *cmd);
void execute_command(Command *cmd);
void print_environment(void);
void get_sigint();

#endif
