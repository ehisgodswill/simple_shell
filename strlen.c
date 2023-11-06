#include "shell.h"
/**
 * _strlen - returns the length o a string
 * @s: char pointer of the string
 * Return: integer length of the string
*/
int _strlen(char *s)
{
	int length = 0;

	while (s[length] != '\0')
		length++;

	return (length);
}
