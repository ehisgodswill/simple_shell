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
	int i = 1;
	char *token = _strtok(input, " \n\t");

	if (token == NULL)
	{
		cmd->name = NULL;
		return;
	}
	cmd->name = token;

	while  ((token = _strtok(NULL, " \n\t")) != NULL && i < 19)
	{
		cmd->arguments[i] = token;
		i++;
	}
	cmd->arguments[i] = NULL;
	cmd->argcount = i;
}
