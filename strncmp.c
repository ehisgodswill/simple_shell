#include "shell.h"
#include <stddef.h>
int _strncmp(const char *s1, const char *s2, size_t num)
{
	size_t  i;
	const char *shorter_str;

	if (_strlen(s1) <= _strlen(s2))
		shorter_str = s1;
	else
		shorter_str = s2;
	for (i = 0; i < num && i <= _strlen(shorter_str) && shorter_str[i] != '\0'; i++)
	{
		int diff = s1[i] - s2[i];
		if (diff != 0)
			return (diff);
	}
	return ((i == num) ? 0 : s1[i] - s2[i]);
}
