#include "main.h"
/**
 * oexit - Function that exits the program
 * @args: array of arguments passed to the function
 * Return: Exit status code
 */
int oexit(char **args)
{
	if (args[1]) /*Check if there's a second argument*/
	{
		return (atoi(args[1]));
		/*If yes convert it to an int and return it as the exit status*/
	}
	else
	{
		return (0); /*If not, return 0 as the default exit status*/
	}
}
