#include "shell.h"
/**
 * _strlen - returns the length o a string
 * @s: char pointer of the string
 * Return: integer length of the string
*/
size_t _strlen(const char *s)
{
	size_t length = 0;

	while (s[length] != '\0')
		length++;

	return (length);
}
