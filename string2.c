#include "shell.h"

/**
 * is_interactive - returns true if shell is is_interactive mode
 * @data: struct address
 *
 * Return: 1 if is_interactive mode, 0 otherwise
 */
int is_interactive(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * isdelim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int isdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (SUCCESSFUL);
	return (NEUTRAL);
}

/**
 *isalphabeth - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int isalphabeth(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (SUCCESSFUL);
	else
		return (NEUTRAL);
}

/**
 *_atoi - converts a string of numbers to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;
		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
