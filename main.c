#include "shell.h"
/**
 * main - main logic
 * Return: 0 success
 */
int main(void)
{
	char input[1024];
	Command cmd;

	signal(SIGINT, get_sigint);
	while (1)
	{
		printf("$ ");

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n");
				exit(0);
			}
			perror("fgets");
			exit(1);
		}
		input[strlen(input) - 1] = '\0';

		if (input[0] != '\0')
		{
			cmd.input_file = STDIN_FILENO;
			cmd.output_file = STDOUT_FILENO;

			tokenize_input(input, &cmd);
			if (cmd.name != NULL)
			{
				if (strcmp(cmd.name, "exit") == 0)
					exit(0);
				else if (strcmp(cmd.name, "env") == 0)
				{
					print_environment();
					continue;
				}
			}
			execute_command(&cmd);
		}
	}
	return (0);
}

/**
 * get_sigint - Handle the crtl + c call in prompt
 */
void get_sigint()
{
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

