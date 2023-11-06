#include "shell.h"

/**
 * __strdup - A function that returns a pointer to a newly allocated
 * space in memory, which contains a copy of the string given as a
 * parameter.
 * @str: An input pointer of the string to copy.
 * Return: Apointer to new string or NULL if it str is NULL
 */
char *__strdup(char *str)
{
	char *newstr;
	unsigned int size = 0, i = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		size++;
	str -= ++size;
	newstr = malloc(size * sizeof(char));

	if (newstr == NULL)
		return (NULL);
	while (i < size)
		newstr[i++] = *str++;

	newstr[i] = '\0';
	return (newstr);
}
