#include "shell.h"
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
			if (cmd.name != NULL)
			{
				if (_strcmp(cmd.name, "exit") == 0)
				{
					int exit_status = 0;
					if (cmd.arguments[1] != NULL)
						exit_status = atoi(cmd.arguments[1]);
					exit(exit_status);
				}
				else if (_strcmp(cmd.name, "env") == 0)
				{
					print_environment();
					continue;
				}
			}
			execute_command(&cmd);
			free(input);
		}
	}
	return (0);
}
