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
 * @argcount: number of arguments
 * @input: input
 * @input_file: input fd
 * @output_file: output fd
 *
 * Description: struct that holds all relevant command and argument
 */
typedef struct command
{
	char *name;
	char *arguments[20];
	char *input;
	int argcount;
	int input_file;
	int output_file;
} Command;

/**
 * list - list of commands to run
 * @input: pointer to command statement
 * @next: next command;
 * @type: type of command sequence, 1 = OR, 2 = AND, 0 = END
 * Description: struct that holds an input line info
 */
typedef struct list
{
	char *input;
	char *next;
	int type;

} list;

void tokenize_input(Command *cmd);
int execute_command(Command *cmd);
int print_environment(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int set_environment(Command *cmd);
int unset_environment(Command *cmd);
int cd_command(Command *cmd);
void parse_input(list *array, char *input);

/* helper functions */

char *_strchr(char *s, char c);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *__strdup(char *str);
char *_strtok(char *str, const char *delim);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);

#endif
