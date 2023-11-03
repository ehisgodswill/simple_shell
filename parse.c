#include <string.h>
#include "shell.h"

/**
 * tokenize_input - splits user input into commands and their
 * their arguments
 * @input: pointer input
 * @cmd: pointer to the command
 */
void tokenize_input(char *input, Command *cmd)
{
	int i = 0;
	char *token = strtok(input, " \n\t");

	if (token == NULL)
	{
		cmd->name = NULL;
		return;
	}
	cmd->name = token;

	while  ((token = strtok(NULL, " ")) != NULL && i < 19)
	{
		cmd->arguments[i] = token;
		i++;
	}
	cmd->arguments[i] = NULL;
}
