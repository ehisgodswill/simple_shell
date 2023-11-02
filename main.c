#include "main.h"

/**
 * main - Entry point;
 * Return: 0 on success, -1 on fail
 */
int main(void)
{
	/*variable declaration*/
	size_t bufsize = BUFSIZ;
	ssize_t char_read;
	char *path;
	char *buffer;

	/*an infinite loop, that runs until exit*/
	while (1)
	{
		/*$buffer temporarily stores the current working directory 
		and stores it in $path variable*/
		buffer = (char *)malloc(sizeof(char) * bufsize);
		if (buffer == NULL)
		{
			perror("Unable to allocate buffer\n");
			exit(-1);
		}
		path = getcwd(buffer, PATH_MAX);
		if (path == NULL)
			return (-1);

		printf("%s>", path);
		/*$buffer now stores the shring input*/
		char_read = getline(&buffer, &bufsize, stdin);
		if (char_read == -1)
			return (-1);
		if (char_read == 1)
			continue;

		printf("%s", buffer);
		free(buffer);
		free(path);
	}

	return (0);
}
