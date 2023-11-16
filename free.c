#include "shell.h"

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * free_cmd - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_cmd(info_t *info, int all)
{
	ffree(info->arguments);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		/* if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		_putchar(BUF_FLUSH);
		bfree((void **)info->cmd_buf); */
		if (info->readfd > 2)
			close(info->readfd);
		ffree(info->environ);
			info->environ = NULL;
	}
}
