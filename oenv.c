#include "main.h"
/**
 * oenv - function to set the path
 * @args: arguments
 * Return: nothing
 */
char oenv(char **args)
{
	char **env = environ; /*Environ is a global var which contains env var */
	char *token;

	while (*env != NULL)
	{
		token = strtok(*env, "="); /*strtok separate string from 1st '='*/
		if (strcmp(token, args) == 0)
		{
			return (strtok(NULL, "\0")); /*return value of the var*/
		}
		env++;
	}
	return (NULL);
}
