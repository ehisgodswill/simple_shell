#include <sys/wait.h>
#include "shell.h"
/**
 * exec_line - executes the command
 * @cmd - pointer to command
 * Return: Nothing
*/
void exec_line(Command *cmd)
{

}

/**
 * execute_command - executes commands and fork the child process
 * @cmd: pointer to command
 * Return: void
 */
void execute_command(Command *cmd)
{
	pid_t child_pid;
	char *path, *path_copy, *arguments[2], *token, command_path[1024];

	if (cmd->name == NULL)
		return;
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
		if (strchr(cmd->name, '/') == NULL)
		{
			path = getenv("PATH");
			if (path != NULL)
			{
				path_copy = strdup(path);
				token = strtok(path_copy, ":");
				while (token != NULL)
				{
					snprintf(command_path, sizeof(command_path), "%s/%s", token, cmd->name);
					arguments[0] = command_path;
					arguments[1] = NULL;
					execve(command_path, arguments, environ);
					token = strtok(NULL, ":");
				}
				free(path_copy);
			}
		}
		else
		{
			arguments[0] = cmd->name;
			arguments[1] = NULL;
			execve(cmd->name, arguments, environ);
		}
		perror("execve");
		exit(1);
	}
	else
		wait(NULL);
}


