#include "main.h"
/**
 * oexit - Function that exit the program
 * @args: empty args
 * Return: 0
 */
int oexit(char **args)
{
	if (args[1])
	{
		return (atoi(args[1]));
	}
	else
	{
		return (0);
	}
}
