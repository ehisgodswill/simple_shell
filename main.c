#include "main.h"

/**
 * main - Entry point;
 * Return: 0 on success, -1 on fail
 */
int main(void)
{
	/**/ size_t bufsize = BUFSIZ;
	ssize_t char_read;
	char *path;
	char *buffer;

	while (1)
	{
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
		char_read = getline(&buffer, &bufsize, stdin);
		if (char_read == -1)
			return (-1);

		printf("%s", buffer);
		free(buffer);
		free(path);
	}

	return (0);
}