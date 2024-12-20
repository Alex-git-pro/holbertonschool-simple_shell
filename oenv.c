#include "main.h"
/**
 * oenv - function to set the path
 * @args: arguments
 * Return: nothing
 */
int oenv(char **args)
{
	char **env = environ; /*Environ is a global var which contains env var */
	char *token, *value;

	if (args[0] == NULL)
	{
		while (*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
		return (0);
	}
	while (*env != NULL)
	{
		token = strtok(*env, "=");

		if (strcmp(token, args[0]) == 0)
		{
			value = strtok(NULL, "\0");
			if (value != NULL)
			{
				printf("%s\n", value);
				return (0);
			}
		}
		env++;
	}
	fprintf(stderr, "Environment variable %s not found\n", args[0]);
	return (1);
}
