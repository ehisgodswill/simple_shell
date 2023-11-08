#include "shell.h"

/**
 * _strtok - tokenoize a string
 * description: It breaks a string into a sequence of zero or more nonempty
 * tokens. On the first call to _strtok(), the string to be parsed should be
 * specified in str. In each subsequent call that should parse the same
 *  string, str must be NULL.
 * @str: pointer to string,
 * @delim: delimiter
 * Return: returns a pointer to a null-terminatedstring containing next token.
 * This string does not include the delimiting byte.
 * If no more tokens are found, strtok() returns NULL.
 */
char *_strtok(char *str, const char *delim)
{
	static char *end, *next;
	char *start;
	int i, j, b;

	if (str != NULL)
	{
		start = str;
		end = &str[strlen(str)];
		next = start;
	}
	else
		start = next;
	if (delim == NULL)
		return (NULL);
	b = 0;
	for (j = 0; start[j]; j++)
	{
		for (i = 0; delim[i]; i++)
			if (start[j] == delim[i])
			{
				start[j] = '\0';
				if (strlen(start) == 0)
				{
					start++;
					continue;
				}
				next = &start[j + 1];
				b = 1;
			}
		if (&start[j] >= end - 1)
			next = end;
		if (b == 1)
			break;
	}
	if ((end - start) <= 0)
		return (NULL);
	return (start);
}
