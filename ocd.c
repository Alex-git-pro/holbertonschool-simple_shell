#include "main.h"

/**
 * ocd - Modifies the current working directory of the shell
 * @args: Array containing the command and its arguments
 *
 * Return: -1 in all cases
 */

int ocd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "cd: no destination directory specified\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd: unable to switch to specified directory");
		}
	}
	return (1);
}
