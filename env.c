#include "shell.h"

/**
 * print_env - Prints all environment variables.
 *
 */
void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
