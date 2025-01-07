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

	if (args[0] == NULL) /*If no args provided, print all environment var*/
	{
		while (*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
		return (0);
	}
	while (*env != NULL) /*Search for specific env variable*/
	{
		token = strtok(*env, "="); /*Split env string into name and value*/

		if (strcmp(token, args[0]) == 0)
		/*Check current var matches the requested one*/
		{
			value = strtok(NULL, "\0"); /*Get the value part*/
			if (value != NULL)
			{
				printf("%s\n", value);
				return (0);
			}
		}
		env++;
	}
	/*If var not found, print error message*/
	fprintf(stderr, "Environment variable %s not found\n", args[0]);
	return (1);
}
