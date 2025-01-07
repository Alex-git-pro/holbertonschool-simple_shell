#include "main.h"
/**
 * oexit - Function that exits the program
 * @args: array of arguments passed to the function
 * Return: Exit status code
 */
int oexit(char **args)
{
	int status = 0;
	/* Check if an argument was provided to the exit command */
	if (args[1])
	{
		char *endptr;
	/* Convert the argument to an integer */
		status = strtol(args[1], &endptr, 10);
	/* Check if the entire string was converted*/
		if (*endptr != '\0')
		{
			/* If not a valid number, print an error message */
			fprintf(stderr, "exit: Illegal number: %s\n", args[1]);
			/* Return 1 to continue shell execution */
			return (1);
		}
	}
	/* Exit the shell with the specified status (or 0 if none provided) */
	exit(status);
}
