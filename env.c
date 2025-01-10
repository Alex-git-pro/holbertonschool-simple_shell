#include "shell.h"

/**
 * print_env - Prints all the environment variables.
 */
void print_env(void)
{
	char **env = environ; /* Pointer to the global 'environ' variable. */

	/*Loop through all the variables until a NULL pointer is encountered.*/
	while (*env)
	{
		 /*Print the current environment variable followed by a newline.*/
		printf("%s\n", *env);
		env++; /* Move to the next environment variable in the array. */
	}
}
