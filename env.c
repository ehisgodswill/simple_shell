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
	int l = strlen(cmd->arguments[1]) + strlen(cmd->arguments[2])
	char arg[l+1];

	sprintf(arg, "%s=%s", cmd->arguments[1], cmd->arguments[2]);

	cmd->name = "export";
	cmd->arguments[1] = arg;
	cmd->arguments[2] = '\0';
	 /*execute_command(cmd); */
	printf("%s %s %s %s", cmd->name, cmd->arguments[1], cmd->arguments[2], arg);
	
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
