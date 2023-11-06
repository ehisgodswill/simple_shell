#include "shell.h"

/**
 * _strcat - appends the src string to the dest string
 * @dest: destination
 * @src: source string
 * Return: return pointer to dest
*/
char *_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}
