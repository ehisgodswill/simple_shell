#include "shell.h"
/**
 * cd_command - changes the current directory, interpretes cd without arguments
 * as cd $HOME, handles cd - and updates the PWD
 * @cmd: pointer
 * Return: integer
 */
int cd_command(Command *cmd)
{
	char *target_dir = NULL;
	char *current_dir = getcwd(NULL, 0);

	if (cmd->arguments[1] == NULL)
		target_dir = getenv("HOME");
	else if (_strcmp(cmd->arguments[1], "-") == 0)
	{
		target_dir = getenv("OLDPWD");
		if (target_dir == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (-1);
		}
	}
	else
		target_dir = cmd->arguments[1];
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (-1);
	}
	if (current_dir == NULL)
	{
		perror("cd");
		return (-1);
	}
	if (setenv("PWD", current_dir, 1) != 0)
		perror("cd");
	if (setenv("OLDPWD", getenv("PWD"), 1) != 0)
		perror("cd");
	free(current_dir);
	return (0);
}
