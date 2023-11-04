#include "shell.h"

/**
 * readline - reads a line
 * @buffer: buffer to store line read
 * @position: position of buffer
 * @stream: file stream
 * 
 * Return: -1 on failure
*/
int readline(char *buffer, int *position, FILE *stream)
{
	char c;
	int rd, pos = *position;
	do
	{
		if (pos == 0)
			fflush(stream);

		rd = read(STDIN_FILENO, &c, 1);
		if (rd == -1 || (pos== 0 && rd == 0))
		{
			free(buffer);
			*position = pos;
			return (-1);
		}
		if (pos >= BUFSIZ)
			buffer = realloc(buffer, pos + 1);
		if (pos > 0 && (rd == 0 || rd == -1))
		{
			pos++;
			break;
		}
		buffer[pos] = c;
		pos++;
	} while (c != '\n');

	buffer[pos] = '\0';
	*position = pos;
	return (rd);
}

/**
 * _getline - reads the buffer
 * @lineptr: pointer to the line read
 * @n: number of characters to read
 * @stream: where to read from
 *
 * Return: number of characters read, -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char *buffer;
	int position, rd;

	buffer = malloc(sizeof(char) * BUFSIZ);
	if (buffer == NULL)
		return (-1);
	position = 0;
	rd = readline(buffer, &position, stream);
	if (rd == -1)
		return (-1);

	if (*lineptr == NULL || position > *n)
	{
		if (position > BUFSIZ)
			*n = position;
		else
			*n = BUFSIZ;
		*lineptr = buffer;
	}
	else
	{
		strcpy(*lineptr, buffer);
		free(buffer);
	}
	return (position);
}
