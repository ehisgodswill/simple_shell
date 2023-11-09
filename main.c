#include "shell.h"

void shell_loop(char *input);
int getfunction(Command *cmd);
int run_function(Command *cmd);

/**
 * main - main logic
 * Return: 0 success
 */
int main(void)
{
	char *input;
	size_t bufsize = 1024;
	/*int exit_status = 0;*/

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		input = (char *)malloc(bufsize * sizeof(char));
		if (_getline(&input, &bufsize, stdin) == -1)
		{
			free(input);
			if (feof(stdin))
			{
				/* printf("\n"); */
				exit(0);
			}
			/* perror("getline"); */
			exit(1);
		}
		input[_strlen(input) - 1] = '\0';
		shell_loop(input);
		free(input);
	}
	return (0);
}

/**
 * shell_loop - seperate line by ';' and loops
 * @input: line
 */
void shell_loop(char *input)
{
	list array[64];
	Command cmd;
	int i, r;

	parse_input(array, input);
	i = 0;
	while (array[i].input != NULL)
	{
		if (array[i].input[0] != '\0')
		{
			cmd.input_file = STDIN_FILENO;
			cmd.output_file = STDOUT_FILENO;
			cmd.input = array[i].input;

			r = run_function(&cmd);
			if (r == -1 && array[i].type == 2)
			{
				while (array[i].type != 0)
					i++;
			}
			else if (r != -1 && array[i].type == 1)
			{
				while (array[i].type != 0)
					i++;
				
			}
		}
		i++;
	}
}

/**
 * getfunction - finds the function needed
 * @cmd: command structure
 */
int getfunction(Command *cmd)
{
	if (cmd->name != NULL)
	{
		if (_strcmp(cmd->name, "exit") == 0)
			exit(0);
		else if (_strcmp(cmd->name, "env") == 0)
			return (print_environment());
		else if (_strcmp(cmd->name, "setenv") == 0)
			return (set_environment(cmd));
		else if (_strcmp(cmd->name, "unsetenv") == 0)
			return (unset_environment(cmd));
	}
	return (0);
}

int run_function(Command *cmd)
{
	tokenize_input(cmd);
	if (getfunction(cmd))
		return getfunction(cmd);
	return (execute_command(cmd));
}