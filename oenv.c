#include "main.h"
/**
 * oenv - function to set the path
 * @name: name of the string
 * Return: nothing
 */
char *oenv(const char *name)
{
	char **env = environ; /*Environ is a global var which contains env var */
	char *token;

	while (*env != NULL)
	{
		*token = strtok(*env, "="); /*strtok separate string from 1st '='*/
		if (strcmp(token, name) == 0)
		{
			return (strtok(NULL, "\0")); /*return value of the var*/
		}
		env++;
	}
	return (NULL);
}
