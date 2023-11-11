#include "shell.h"
/**
 * cd_command - changes the current directory, interpretes cd without arguments
 * as cd $HOME, handles cd - and updates the PWD
 * @cmd: pointer
 */
int cd_command(Command *cmd)
{
	char *target_dir = NULL;
	char *current_dir = getcwd(NULL, 0);
	char *oldpwd_value = _getenv("OLDPWD");

	if (current_dir == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	if (cmd->arguments[1] == NULL)
		target_dir = _getenv("HOME");
	else if (_strcmp(cmd->arguments[1], "-") == 0)
	{
		target_dir = _getenv("OLDPWD");
		if (target_dir == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			free(current_dir);
			return (-1);
		}
	}
	else
		target_dir = cmd->arguments[1];
	if (target_dir == NULL)
	{
		fprintf(stderr, "cd: No such environment variable\n");
		free(current_dir);
		return (-1);
	}
	if (chdir(target_dir) != 0)
	{
		perror("chdir");
		free(current_dir);
		return (-1);
	}
	if (setenv("PWD", current_dir, 1) != 0)
		perror("setenv");
	if (setenv("OLDPWD", oldpwd_value != NULL ? oldpwd_value : current_dir, 1) != 0)
		perror("setenv");
	free(current_dir);
	return 0;
}
