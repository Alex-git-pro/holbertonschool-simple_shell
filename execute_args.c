#include "main.h"

/**
 * execute_args - map if command is a builtin or a process
 * @args: command and its flag
 * Return: 1 on success or 0 if fail
 */

int execute_args(char **args)
{
	char *builtin_func_list[] =

	{
		"cd",
		"env",
		"help",
		"exit"
	};

	int (*builtin_func[])(char **) =

	{
		&ocd,
		&oenv,
		&ohelp,
		&oexit,
	};

	int i = 0;

	if (args[0] == NULL)
	{
		return (-1);
	}

	for (i = 0; i < num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_func_list[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}
	return (new_process(args));
}
