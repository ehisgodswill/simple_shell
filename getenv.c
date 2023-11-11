#include "shell.h"
/**
 * _getenv - custom implementation for retrieving
 * the value of an environment variable
 * @name: input parametr
 * Return: NULL
 */
char *_getenv(const char *name)
{
	char **env;

	if (name == NULL)
		return (NULL);
	for (env = environ; *env != NULL; env++)
	{
		char *variable = *env;
		char *equal_sign = _strchr(variable, '=');

		if (equal_sign != NULL)
		{
			size_t name_length = equal_sign - variable;

			if (_strncmp(variable, name, name_length) == 0 && name[name_length] == '\0')
				return (equal_sign + 1);
		}
	}
	return (NULL);
}
