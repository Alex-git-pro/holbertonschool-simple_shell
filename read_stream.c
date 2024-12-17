#include "main.h"

/**
 * read_stream - read a line from the stream
 *
 * Return: pointer that points the read line
 */

char *read_stream(void)
{
	int bufsize = 1024; /*Size of the buffer*/
	int i = 0; /*Index to iterate inside the buffer*/
	char *line = malloc(sizeof(char) * bufsize); /*Allocation of the buffer*/
	int character; /*Character read*/

	if (line == NULL) /*Check if malloc succeeded*/
	{
		frpintf(stderr, "allocation error in read_stream");
		exit(EXIT_FAILURE);
	}
	while (1) /*Infinite loop while 1*/
	{
		character = getchar(); /* read the first char */
		if (character == EOF) /*If end of file, free and exit*/
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else if (character == '\n') /*If end of line*/
		{
			line[i] = '\0'; /*Finish the string*/
			return (line); /*Return the line readen*/
		}
		else
		{
			line[i] = character; /*Add character to the line*/
		}
		i++; /*Iterate through string*/

		if (i >= bufsize) /*If buffer is full, increase his size*/
		{
			bufsize += bufsize; /*Double the size of the buffer*/
			line = realloc(line, bufsize); /*Realloc the new size*/
			if (line == NULL) /*If allocation fails print error and exit*/
			{
				fprintf(stderr, "reallocation error in read_strem");
				exit(EXIT_FAILURE);
			}
		}
	}
}
