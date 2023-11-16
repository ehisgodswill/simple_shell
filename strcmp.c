#include "shell.h"

/**
 * _strcmp - compares two string together
 * @s1: string
 * @s2: string
 * Return: integer
*/
int _strcmp(char *s1, char *s2)
{
int r = 0, i = 0;

	while (r == 0)
	{
		if (s1[i] == '\0')
			break;
		r = s1[i] - s2[i];
		i++;
	}
	return (r);
}


/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
