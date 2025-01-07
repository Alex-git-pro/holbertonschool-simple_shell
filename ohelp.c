#include "main.h"

/**
 * ohelp - print help
 * @args: arguments
 *
 * Return: 1 on success, 0 otherwise
 */

int ohelp(char **args)
{
	/* Array of built-in command names */
	char *builtin_func_list[] =

	{
		"cd",
		"env",
		"help",
		"exit"
	};

	unsigned long int i = 0;
	/* Avoid unused parameter warning */
	(void)(**args);

	/* Print help header */
	printf("\n---help simple_shell---\n");
	/* Print general usage instruction */
	printf("Enter your command followed by arguments\n");
	/* Print built-in commands header */
	printf("Built-in commands:\n");
	/* Loop through and print each built-in command */
	for (i = 0; i < sizeof(builtin_func_list) / sizeof(char *); i++)
	{
		printf("  -> %s\n", builtin_func_list[i]);
	}
	/* Print additional help information */
	printf("Use the man command to get details on other programs.\n\n");
	return (-1);
}
