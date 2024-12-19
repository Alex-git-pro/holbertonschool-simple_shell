#include "main.h"

/**
 * ohelp - print help
 * @args: arguments
 *
 * Return: 1 on success, 0 otherwise
 */

int ohelp(char **args)
{
	char *builtin_func_list[] =

	{
		"cd",
		"env",
		"help",
		"exit"
	};

	unsigned long int i = 0;
	(void)(**args);

	printf("\n---help simple_shell---\n");
	printf("Enter your command followed by arguments\n");
	printf("Built-in commands:\n");
	for (i = 0; i < sizeof(builtin_func_list) / sizeof(char *); i++)
	{
		printf("  -> %s\n", builtin_func_list[i]);
	}
	printf("Use the man command to get details on other programs.\n\n");
	return (-1);
}
