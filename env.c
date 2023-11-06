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
 * cmd - command structure
*/
void set_environment(Command *cmd)
{
	char *arg = _strcat(cmd->arguments[1],"=");
	arg = _strcat(arg, cmd->arguments[2]);

	/* cmd->name = "export";
	cmd->arguments[1] = arg;
	cmd->arguments[2] = NULL;
	printf("%s %s %s", cmd->name, cmd->arguments[1], cmd->arguments[2]);
	execute_command(cmd); */
}

/**
 * unset_environment - sets an environment variable
 * cmd - command structure
*/
void unset_environment(Command *cmd)
{
	cmd->name = "unset";
	/* execute_command(cmd); */
}
