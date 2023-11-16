#include "shell.h"
/**
 * print_environment - prints the current environment variables to the
 * standard output
 * Return: 1
 */
int print_environment(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (1);
}

/**
 * set_environment - sets an environment variable
 * @cmd: command structure
 * Return: 1 on success -1 on failure
 */
int set_environment(Command *cmd)
{
	char arg[BUFSIZ], *line, *a;
	char **env = environ;
	int t = 0, found = 0;

	if (cmd->argcount != 3)
	{
		write(STDERR_FILENO, "Number of arguments not correct\n", 32);
		return (-1);
	}
	sprintf(arg, "%s=%s", cmd->arguments[1], cmd->arguments[2]);
	while (*env)
	{
		line = __strdup(*env);
		if (line == NULL || cmd->argcount != 3)
		{
			write(STDERR_FILENO, "setenv failed\n", 14);
			return (-1);
		}
		a = _strtok(line, "=");
		if (_strcmp(a, cmd->arguments[1]) == 0)
		{
			*env = arg;
			found++;
			break;
		}
		t++;
		env++;
	}
	free(line);
	if (found <= 0)
	{
		*env = arg;
		*++env = NULL;
	}
	return (1);
}

/**
 * unset_environment - sets an environment variable
 * @cmd: command
 * Return: 1 on success -1 on failure
 */
int unset_environment(Command *cmd)
{
	char arg[BUFSIZ], *line, *a;
	char **env = environ;
	int t = 0;

	if (cmd->argcount != 2)
	{
		write(STDERR_FILENO, "Number of arguments not correct\n", 32);
		return (-1);
	}
	sprintf(arg, "%s=%s", cmd->arguments[1], cmd->arguments[2]);
	while (*env)
	{
		line = __strdup(*env);
		if (line == NULL)
		{
			write(STDERR_FILENO, "unsetenv failed\n", 14);
			return (-1);
		}
		a = _strtok(line, "=");
		if (_strcmp(a, cmd->arguments[1]) == 0)
		{
			*env = '\0';
			break;
		}
		t++;
		env++;
	}
	free(line);
	return (1);
}

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(Command *info)
{
	/* if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	} */
	info->environ = environ;

	return (info->environ);
}
