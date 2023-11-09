#include <sys/wait.h>
#include "shell.h"

/**
 * exec_line - executes the command
 * @cmd: pointer to command
 */
int exec_line(Command *cmd)
{
	char *path, *path_copy, *token, command_path[1024];
	int ret = -1;

	if (_strchr(cmd->name, '/') == NULL)
	{
		path = getenv("PATH");
		if (path != NULL)
		{
			path_copy = strdup(path);
			token = _strtok(path_copy, ":");
			while (token != NULL)
			{
				snprintf(command_path, sizeof(command_path), "%s/%s", token, cmd->name);
				cmd->arguments[0] = command_path;
				ret = execve(command_path, cmd->arguments, environ);
				token = _strtok(NULL, ":");
			}
			free(path_copy);
		}
	}
	else
	{
		cmd->arguments[0] = cmd->name;
		ret = execve(cmd->name, cmd->arguments, environ);
	}
	return (ret);
}

/**
 * execute_command - executes commands and fork the child process
 * @cmd: pointer to command
 */
int execute_command(Command *cmd)
{
	pid_t child_pid;
	int ret = -1;

	if (cmd->name == NULL)
		return (-1);
	child_pid = fork();
	if (child_pid == -1)
		perror("fork");
	else if (child_pid == 0)
	{
		if (cmd->input_file != STDIN_FILENO)
		{
			dup2(cmd->input_file, STDIN_FILENO);
			close(cmd->input_file);
		}
		if (cmd->output_file != STDOUT_FILENO)
		{
			dup2(cmd->output_file, STDOUT_FILENO);
			close(cmd->output_file);
		}
		ret = exec_line(cmd);
		perror("execve");
		exit(-1);
	}
	else
		wait(NULL);
	return (ret)
}
