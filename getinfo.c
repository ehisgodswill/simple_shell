#include "shell.h"

/**
 * cleardata - clears data_t structure
 * @data: struct address
 */
void cleardata(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * setdata - initializes data_t structure
 * @data: struct address
 * @av: argument vector
 */
void setdata(data_t *data, char **av)
{
	int i = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = strtowarr(data->arg, " \t");
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;
		replace_alias(data);
		replace_variable(data);
	}
}

/**
 * freedata - frees data_t struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void freedata(data_t *data, int all)
{
	ffree(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		ffree(data->environ);
			data->environ = NULL;
		bfree((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(BUFFLUSH);
	}
}
