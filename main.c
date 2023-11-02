#include "main.h"

/**
 * main - a program that prints its name, followed by a new line
 * @argc: arguement count
 * @argv: argument value, a strings that come after calling function
 * Return: 0 (Success) or -1 (Failure)
 */
int main(int argc, char *argv[])
{
	/*variable declaration*/
	size_t bufsize = BUFSIZ;
	ssize_t char_read;
	char *temp, *buffer, *token;
	int num = 0;
	char *s = " ";

	(void)argc;
	(void)argv;
	/*an infinite loop, that runs until exit*/
	while (1)
	{
		buffer = (char *)malloc(sizeof(char) * bufsize);
		if (buffer == NULL)
		{
			perror("Allocate buffer failed\n");
			exit(-1);
		}
		temp= getcwd(buffer, PATH_MAX);
		if (temp == NULL)
			return (-1);

		printf("#cisfun$ ");
		char_read = getline(&buffer, &bufsize, stdin);
		if (char_read == -1)
			return (-1);
		if (char_read == 1)
			continue;
		temp = malloc(sizeof(char) * char_read);
		if (temp == NULL)
		{
			perror("Allocate buffer failed\n");
			exit(-1);
		}
		strcpy(temp, buffer);
		token = strtok(temp, s);
		num = 0;
		while (token != NULL)
		{
			num++;
			token = strtok(NULL, s);
		}
		strcpy(temp, buffer);
		token = strtok(temp, s);
		argv = malloc(sizeof (char *) * num);
		for (num = 0; token != NULL; num++)
		{
			argv[num] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[num], token);
			token = strtok(NULL, s);
		}
		argv[num] = NULL;
		free(buffer);
		free(temp);
		free(token);
	}

	return (0);
}
