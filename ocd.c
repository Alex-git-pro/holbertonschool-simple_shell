#include "main.h"

/**
 * ocd - Modifies the current working directory of the shell
 * @args: Array containing the command and its arguments
 *
 * Return: -1 in all cases
 */

int ocd(char **args)
{
	/* Check if a directory argument is provided */
	if (args[1] == NULL)
	{
		/* Print error message if no directory is specified */
		fprintf(stderr, "cd: no destination directory specified\n");
	}
	else
	{
		/* Attempt to change directory */
		if (chdir(args[1]) != 0)
		{
			/* Print error message if directory change fails */
			perror("cd: unable to switch to specified directory");
		}
	}
	/* Return 1 to continue shell execution */
	return (1);
}
