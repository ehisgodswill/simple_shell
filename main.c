#include "shell.h"
void shell_loop(char *input);
int getfunction(Command *cmd);
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
	char *token[64];
	Command cmd;
	int i = 0;

	token[i] = _strtok(input, ";");
	while (token[i] != NULL)
	{
		i++;
		token[i] = _strtok(NULL, ";");
	}
	i = 0;
	while (token[i] != NULL)
	{
		if (*token[i] != '\0')
		{
			cmd.input_file = STDIN_FILENO;
			cmd.output_file = STDOUT_FILENO;

			tokenize_input(&cmd);
			printf("%s %d\n", cmd.name, cmd.argcount);
			if (getfunction(&cmd))
			{
				i++;
				token[i] = _strtok(NULL, ";");
				continue;
			}
			execute_command(&cmd);
		}
		i++;
		token[i] = _strtok(NULL, ";");
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
	return (0);
}
