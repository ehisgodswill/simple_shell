#include <string.h>
#include "shell.h"

void parse(list *array, int *i, char *token, int type, int *j)
{
	*token = '\0';
	array[*i].type = type;
	if (type != 0)
		token++;
	array[*i].next = token + 1;
	*j = -1;
	*i++;
}
/**
 * parse_input - format commands into a list
 * @array: array list of command
 * @input: input line read
 */
void parse_input(list *array, char *input)
{
	char *token = input;
	int j = 0, i = 0;

	for (j = 0; *token; j++)
	{
		array[i].input = token - j;
		if (*token == '&' && token[1] == '&')
			parse(array, &i, token, 2, token + 2, &j);
		else if (*token == '|' && token[1] == '|')
			parse(array, &i, token, 1, token + 2, &j);
		else if (*token == ';')
			parse(array, &i, token, 0, token + 2, &j);
		else if (*token == '#')
		{
			parse(array, &i, token, 0, NULL, &j);
			array[i - 1].next = NULL;
			break;
		}
		token++;
	}
	array[i + 1].input = NULL;
}

/**
 * tokenize_input - splits user input into commands and their
 * their arguments
 * @cmd: pointer to the command
 */
void tokenize_input(Command *cmd)
{
	int i = 1;
	char *token = _strtok(cmd->input, " \n\t");

	if (token == NULL)
	{
		cmd->name = NULL;
		return;
	}
	cmd->name = token;

	while ((token = _strtok(NULL, " \n\t")) != NULL && i < 19)
	{
		cmd->arguments[i] = token;
		i++;
	}
	cmd->arguments[i] = NULL;
	cmd->argcount = i;
}
