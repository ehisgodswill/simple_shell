#include "shell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/**
 * readline - reads a line
 * @buffer: buffer to store line read
 * @position: position of buffer
 * @stream: file stream
 *
 * Return: -1 on failure
*/
ssize_t readline(char *buffer, size_t *position, FILE *stream)
{
	char c;
	ssize_t nread = 0;
	size_t pos = *position;
	int fd = open(stream, O_RDONLY);
    
    if(fd == -1){
        printf("\nError Opening File!!\n");
        exit(1);
    }
	do{
		if (pos == 0)
			fflush(stream);

		fd = read(fd, &c, 1);
		if (fd == -1 || (pos == 0 && fd == 0))
		{
			free(buffer);
			*position = pos;
			close(fd);
			return (-1);
		}
		if (pos >= BUFSIZ)
			buffer = realloc(buffer, pos + 1);
		if (pos > 0 && (fd == 0 || fd == -1))
		{
			nread++;
			pos++;
			break;
		}
		buffer[pos] = c;
		pos++;
	} while (c != '\n');

	buffer[pos] = '\0';
	*position = pos;
	close(fd);
	return (nread);
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
	ssize_t rd;
	size_t position; 

	buffer = malloc(sizeof(char) * BUFSIZ);
	if (buffer == NULL)
		return (-1);
	position = 0;
	rd = readline(buffer, &position, stream);
	if (rd == -1)
		return (rd);

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
