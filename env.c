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
	char arg[BUFSIZ], *a, *b;
	char **env = environ; 
	sprintf(arg, "%s=%s", cmd->arguments[1], cmd->arguments[2]);

	a = _strtok(*env, "=");
	b = _strtok(NULL, "=");
	printf("%s\n%s\n%s\n%s\n", a, b, *env, arg);
	
	/*cmd->name = "export";
	while (*env)
	{
	}
	cmd->arguments[1] = arg;
	cmd->arguments[2] = '\0';*/
	
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
