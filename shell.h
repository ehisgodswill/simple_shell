#ifndef SHELL_H
#define SHELL_H
extern char **environ;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/**
 * struct command - command structure
 * @name: name of the command
 * @arguments: array of argument vector
 * @argcount: number of arguments
 * @input: input
 * @input_file: input fd
 * @output_file: output fd
 * @status: exit status of last command
 * @environ: custom modified copy of environ from LL env
 *
 * Description: struct that holds all relevant command and argument
 */
typedef struct command
{
	char *name;
	char **arguments;
	char *input;
	int argcount;
	int input_file;
	int output_file;
	int status;
	char **environ;
} Command;

#define CMD_INIT                       \
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL}

/**
 * struct list - list of commands to run
 * @input: pointer to command statement
 * @next: next command;
 * @type: type of command sequence, 1 = OR, 2 = AND, 0 = END
 *
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
void replace_argument(char *argument, Command *cmd);
int is_cmd(Command *info, char *path);
char **get_environ(Command *info);
void free_cmd(Command *info, int all);

/* helper functions */

char *_strchr(char *s, char c);
size_t _strlen(const char *s);
int _strcmp(char *s1, char *s2);
char *__strdup(char *str);
char *_strtok(char *str, const char *delim);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
void tostring(char str[], int num);
char *_getenv(const char *name);
int _strncmp(const char *s1, const char *s2, size_t num);
char *starts_with(const char *haystack, const char *needle);
int is_delim(char c, char *delim);
char *dup_chars(char *pathstr, int start, int stop);

#endif
