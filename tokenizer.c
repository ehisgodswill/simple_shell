#include "shell.h"

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

/**
 * strtowarr - splits a string into array of words. Repeat delimiters are ignored
 * @str: theinput string
 * @delim: thedelimeter string
 * Return: a pointer to an array of strings, or NULL if failure
 */

char **strtowarr(char *str, char *delim)
{
	int i, j, q, r, numofwords = 0;
	char **str_arr;

	if (*str == '\0' || str == NULL)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!isdelim(str[i], delim) && (isdelim(str[i + 1], delim) || !str[i + 1]))
			numofwords++;

	if (numofwords == 0)
		return (NULL);
	str_arr = malloc(sizeof(char *) * (numofwords + 1));
	if (!str_arr)
		return (NULL);
	for (i = 0, j = 0; j < numofwords; j++)
	{
		while (isdelim(str[i], delim))
			i++;
		q = 0;
		while (!isdelim(str[i + q], delim) && str[i + q])
			q++;
		str_arr[j] = malloc((q + 1) * sizeof(char));
		if (!str_arr[j])
		{
			for (q = 0; q < j; q++)
				free(str_arr[q]);
			free(str_arr);
			return (NULL);
		}
		for (r = 0; r < q; r++)
			str_arr[j][r] = str[i++];
		str_arr[j][r] = 0;
	}
	str_arr[j] = NULL;
	return (str_arr);
}
