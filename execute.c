#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * execute_command - executes commands and fork the
 * child process
 * @cmd: pointer to command
 */
void execute_command(Command *cmd)
{
	pid_t child_pid;

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
		execvp(cmd->name, cmd->arguments);
		perror("execvp");
		exit(1);
	}
	else
		wait(NULL);
}
