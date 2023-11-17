#include "shell.h"

/**
 * ischain - tests if the characters in buffer is a chain delimeter
 * @data: data structure
 * @buffer: the characters buffer
 * @pos: address of current position in buffer
 *
 * Return: 1 if it is a chain delimeter, 
 * or 0 otherwise
 */
int ischain(data_t *data, char *buffer, size_t *pos)
{
	size_t j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (NEUTRAL);
	*pos = j;
	return (SUCCESSFUL);
}

/**
 * continue_chaining - checks we should continue chaining based on last status
 * @data: the data struct
 * @buffer: the character buffer
 * @pos: address of current position in buffer
 * @x: starting position in buffer
 * @len: total length of the buffer
 *
 * Return: Void
 */
void continue_chaining(data_t *data, char *buffer, size_t *pos, size_t x, size_t len)
{
	size_t p = *pos;

	if (data->cmd_buf_type == CMD_AND)
		if (data->status)
		{
			p = len;
			buffer[x] = 0;
		}
	if (data->cmd_buf_type == CMD_OR)
		if (!data->status)
		{
			buffer[x] = 0;
			p = len;
		}

	*pos = p;
}

/**
 * replace_alias - replaces an alias in a tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(data_t *data)
{
	char *pos;
	int x;
	list_t *node;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(data->alias, data->argv[0], '=');
		if (!node)
			return (NEUTRAL);
		free(data->argv[0]);
		pos = _strchr(node->str, '=');
		if (!pos)
			return (NEUTRAL);
		pos = _strdup(pos + 1);
		if (!pos)
			return (NEUTRAL);
		data->argv[0] = pos;
	}
	return (SUCCESSFUL);
}

/**
 * replace_variable - replaces variables in a tokenized string
 * @data: the parameter struct
 */
void replace_variable(data_t *data)
{
	int x = 0;
	list_t *node;

	for (x = 0; data->argv[x]; x++)
	{
		if (data->argv[x][0] != '$' || !data->argv[x][1])
			continue;

		if (!_strcmp(data->argv[x], "$?"))
		{
			str_replace(&(data->argv[x]),
				_strdup(convert_number(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->argv[x], "$$"))
		{
			str_replace(&(data->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(data->env, &data->argv[x][1], '=');
		if (node)
		{
			str_replace(&(data->argv[x]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		str_replace(&data->argv[x], _strdup(""));
	}
	return;
}

/**
 * str_replace - replaces string
 * @old: address of the old string
 * @new: address of the new string
 *
 * Return: 1 if replaced, or 0 otherwise
 */
int str_replace(char **old, char *new)
{
	free(*old);
	*old = new;
	return (SUCCESSFUL);
}
