#include "main.h"

/**
 * ocd - Modifies the current working directory of the shell
 * @args: Array containing the command and its arguments
 *
 * Return: -1 in all cases
 */

int ocd(char **args)
{
	char *home_dir;

	if (args[1] == NULL)/*Verify if an arg has been added to cd*/
	{
		/*If no args, try to change dir HOME*/
		home_dir = get_env("HOME");
		if (home_dir == NULL)
		{
			/*If the var HOME isn't define, print error*/
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
		/*try to change to HOME dir*/
		if (chdir(home_dir) != 0)
		{
			/*If it fails, print error*/
			perror("cd");
		}
	}
	else
	{
		/*If arg is given, try to change to this dir*/
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	}
	/*Return 1 to tell the shell to continue*/
	return (1);
}
