#include "shell.h"

/**
 * tostring - converts an integer to string
 * @str: string
 * @num: number
*/
void tostring(char str[], int num)
{
	int i, rem, len = 0, n;

	n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	if (n == 0)
		len = 1;
	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
}

/**
 * replace_argument - replace an argument with variable
 * @argument: argument
 * @cmd: cmd structure
*/
void replace_argument(char *argument, Command *cmd)
{
	if (argument[1] == '$')
		tostring(argument, getpid());
	else if (argument[1] == '?')
		tostring(argument, cmd->status);
	else
        argument = "";
}