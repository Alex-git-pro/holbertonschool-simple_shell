#include "main.h"
/**
 * read_line - Read line from stdin
 *
 * Return: Pointer that points to a string with the line content
 */
char *read_line(void)
{
	char *line = NULL; /*Pointer to store the line and initialize it to NULL*/
	size_t bufsize = 0;/* Variable to store the size og the allocated buffer*/

	/*Read line from stdin with getline*/
	if (getline(&line, &bufsize, stdin) == -1)/*getline() allocates mem for line*/
	{
		if (feof(stdin))/*Check if we've reached the EOF*/
		{
			free(line);/*If EOF, free the allocated memory and exit*/
			exit(EXIT_SUCCESS);
		}
		else
		{	/*If there's an error, free allocated mem and exit*/
			free(line);
			perror("error while reading the line from stdin");
			exit(EXIT_FAILURE); /*Exit with failure status*/
		}
	}
	return (line);/*Return pointer to the read line if getline() was successful*/
}
