#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFSIZE 1024
#define WRITE_BUFSIZE 1024
#define BUFFLUSH -1

/* Command output */
#define SUCCESSFUL 1
#define NEUTRAL 0
#define FAILURE -1
/* for command chaining */
#define CMD_NORMAL	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct strlist - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct strlist
{
	int num;
	char *str;
	struct strlist *next;
} list_t;

/**
 *struct datainfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last executed command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct datainfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} data_t;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, \
NULL, 0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} builtin_table;


/* file shloop.c */
int hsh(data_t *, char **);
int find_builtin(data_t *);
void find_cmd(data_t *);
void fork_cmd(data_t *);

/* file parser.c */
int is_cmd(data_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(data_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* file errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* file string.c */
char *_strcat(char *, char *);
char *_strncat(char *, char *, int);
int _strcmp(char *, char *);
char *_strcpy(char *, char *);
char *_strncpy(char *, char *, int);

/* file string1.c */
char *_strchr(char *, char);
char *_strdup(const char *);
int _strlen(char *);
int _putchar(char);
void _puts(char *);

/* file string2.c */
int is_interactive(data_t *);
int isdelim(char, char *);
int isalphabeth(int);
int _atoi(char *);

/* file tokenizer.c */
char *starts_with(const char *, const char *);
char **strtowarr(char *, char *);

/* file realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* file memory.c */
int bfree(void **);

/* file errors1.c */
int _erratoi(char *);
void print_error(data_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* file builtin.c */
int _myexit(data_t *);
int _mycd(data_t *);
int _myhelp(data_t *);

/* file builtin1.c */
int _myhistory(data_t *);
int _myalias(data_t *);

/*file getline.c */
ssize_t get_input(data_t *);
int _getline(data_t *, char **, size_t *);
void sigintHandler(int);

/* file getinfo.c */
void cleardata(data_t *);
void setdata(data_t *, char **);
void freedata(data_t *, int);

/* file environ.c */
char *_getenv(data_t *, const char *);
int _myenv(data_t *);
int _mysetenv(data_t *);
int _myunsetenv(data_t *);
int populate_env_list(data_t *);

/* file getenv.c */
char **get_environ(data_t *);
int _unsetenv(data_t *, char *);
int _setenv(data_t *, char *, char *);

/* file history.c */
char *get_history_file(data_t *data);
int write_history(data_t *data);
int read_history(data_t *data);
int build_history_list(data_t *data, char *buf, int linecount);
int renumber_history(data_t *data);

/* file lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* file lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* file vars.c */
int ischain(data_t *, char *, size_t *);
void continue_chaining(data_t *, char *, size_t *, size_t, size_t);
int replace_alias(data_t *);
void replace_variable(data_t *);
int str_replace(char **, char *);

#endif
