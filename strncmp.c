#include "shell.h"
#include <stddef.h>
/**
 *  _strncmp - compares string
 *  @s1: first paremeter
 *  @s2: second parameter
 *  @num: number of characters
 *  Return: the comparison
 */
int _strncmp(const char *s1, const char *s2, size_t num)
{
	size_t  i;
	const char *short_str;

	if (_strlen(s1) <= _strlen(s2))
		short_str = s1;
	else
		short_str = s2;
	for (i = 0; i < num && i <= _strlen(short_str) && short_str[i] != '\0'; i++)
	{
		int diff = s1[i] - s2[i];

		if (diff != 0)
			return (diff);
	}
	return ((i == num) ? 0 : s1[i] - s2[i]);
}
