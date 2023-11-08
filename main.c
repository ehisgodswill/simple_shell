#include "shell.h"
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
		{
			print_environment();
			return (1);
		}
		else if (_strcmp(cmd->name, "setenv") == 0)
		{
			set_environment(cmd);
			return (1);
		}
		else if (_strcmp(cmd->name, "unsetenv") == 0)
		{
			unset_environment(cmd);
			return (1);
		}
	}
	return(0);
}
/**
 * main - main logic
 * Return: 0 success
 */
int main(void)
{
	char *input;
	size_t bufsize = 1024;
	Command cmd;
	/*int exit_status = 0;*/

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		input = (char *)malloc(bufsize * sizeof(char));
		if (_getline(&input, &bufsize, stdin) == -1)
		{
			if (feof(stdin))
			{
				/* printf("\n"); */
				exit(0);
			}
			free(input);
			/* perror("getline"); */
			exit(1);
		}
		input[_strlen(input) - 1] = '\0';

		if (input[0] != '\0')
		{
			cmd.input_file = STDIN_FILENO;
			cmd.output_file = STDOUT_FILENO;

			tokenize_input(input, &cmd);
			if (getfunction(&cmd))
				continue;
			execute_command(&cmd);
			free(input);
		}
	}
	return (0);
}
