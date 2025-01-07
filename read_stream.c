#include "main.h"

/**
 * read_stream - read a line from the stream
 *
 * Return: pointer that points the read line
 */

char *read_stream(void)
{
	int bufsize = 1024;
	int i = 0;
	char *line = malloc(sizeof(char) * bufsize);
	int character;
	/*Check if memory allocation was successful*/
	if (line == NULL)
	{
		perror("allocation error in read_stream");
		exit(EXIT_FAILURE);
	}
	while (1) /*Infinite loop to read characters*/
	{
		character = getchar(); /*Read a character*/
		/*Check for end of input*/
		if (character == EOF || character == '\n')
		{
			line[i] = '\0'; /*Null-terminate the string*/
			return (line); /*Return the completed line*/
		}
		else
		{
			line[i] = character;
		}
		i++;
		if (i >= bufsize)
		{
			bufsize += 1024;
			line = realloc(line, bufsize);
			if (line == NULL)
			{
				perror("reallocation error in read_stream");
				exit(EXIT_FAILURE);
			}
		}
	}
}
