#include "shell.h"
/**
 * print_environment - prints the current environment variables to the
 * standard output
 */
void print_environment(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * set_environment - sets an environment variable
 * @cmd: command structure
 */
void set_environment(Command *cmd)
{
	char arg[BUFSIZ], *line, *a;
	char **env = environ;
	int t = 0, found = 0;

	if (cmd->argcount != 3)
	{
		write(STDERR_FILENO, "Number of arguments not correct\n", 32);
		return;
	}
	sprintf(arg, "%s=%s", cmd->arguments[1], cmd->arguments[2]);
	while (*env)
	{
		line = __strdup(*env);
		if (line == NULL || cmd->argcount != 3)
		{
			write(STDERR_FILENO, "setenv failed\n", 14);
			return;
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
}

/**
 * unset_environment - sets an environment variable
 * @cmd: command structure
 */
void unset_environment(Command *cmd)
{
	char arg[BUFSIZ], *line, *a;
	char **env = environ;
	int t = 0;

	if (cmd->argcount != 2)
	{
		write(STDERR_FILENO, "Number of arguments not correct\n", 32);
		return;
	}
	sprintf(arg, "%s=%s", cmd->arguments[1], cmd->arguments[2]);
	while (*env)
	{
		line = __strdup(*env);
		if (line == NULL)
		{
			write(STDERR_FILENO, "unsetenv failed\n", 14);
			return;
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
}
