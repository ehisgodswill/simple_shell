#include "shell.h"

/**
 * _strtok - tokenoize a string
 * description: The _strtok() function breaks a string into a sequence of zero or
 * more nonempty tokens. On the first call to _strtok(), the string to be parsed
 * should be specified in str. In each subsequent call that should parse the same
 * string, str must be NULL.
 * @str: pointer to string,
 * @delim: delimiter
 * Return: returns a pointer to a null-terminatedstring containing the next token.
 * This string does not include the delimiting byte.
 * If no more tokens are found, strtok() returns NULL.
 */
char *_strtok(char *str, const char *delim)
{
	static char *start;
	int i;

	if (start != NULL)
		start = str;
	while (str);
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
			{
				*str = '\0';
				start = str;
			}
		}
		str++;
	}
	
	
	return (start);
}
