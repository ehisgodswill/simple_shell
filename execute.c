#include "shell.h"
void find_cmd(Command *info);

/**
 * exec_line - executes the command
 * @cmd: pointer to command
 */
/* void exec_line(Command *cmd)
{
	char *path, *path_copy, *token, command_path[1024];

	if (_strchr(cmd->name, '/') == NULL)
	{
		path = _getenv("PATH");
		if (path != NULL)
		{
			path_copy = __strdup(path);
			token = _strtok(path_copy, ":");
			while (token != NULL)
			{
				snprintf(command_path, sizeof(command_path), "%s/%s", token, cmd->name);
				cmd->arguments[0] = command_path;
				execve(command_path, cmd->arguments, environ);
				token = _strtok(NULL, ":");
			}
			free(path_copy);
		}
	}
	else
	{
		cmd->arguments[0] = cmd->name;
		execve(cmd->name, cmd->arguments, environ);
	}
} */

/**
 * execute_command - executes commands and fork the child process
 * @cmd: pointer to command
 * Return: -1 on failure
 */
int execute_command(Command *cmd)
{
	int ret = 0;
	/* pid_t child_pid;

	errno = 0;
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
		exec_line(cmd);
		perror("./hsh");
		exit(-1);
	}
	else
		wait(&cmd->status); */
	find_cmd(cmd);
	ret = cmd->status;
	if (ret != 0)
		ret = -1;
	return (ret);
}



/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(Command *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(Command *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->name, info->arguments, get_environ(info)) == -1)
		{
			free_cmd(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				perror("Permission denied\n");
		}
	}
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(Command *info)
{
	char *path = NULL;

	info->arguments[0] = info->name;
	/* if (info->linecount_flag == 1)
	int i, k;
	{
		info->line_count++;
		info->linecount_flag = 0;
	} 
	for (i = 0, k = 0; info->arguments[i]; i++)
		if (!is_delim(info->n[i], " \t\n"))
			k++;
	if (!k)
		return;*/

	path = find_path(info, _getenv("PATH"), info->arguments[0]);
	if (path)
	{
		info->name = path;
		fork_cmd(info);
	}
	else
	{
		if ((isatty(STDIN_FILENO) || _getenv("PATH")
			|| info->arguments[0][0] == '/') && is_cmd(info, info->arguments[0]))
			fork_cmd(info);
		else if (*(info->name) != '\n')
		{
			info->status = 127;
			perror("not found\n");
		}
	}
}
