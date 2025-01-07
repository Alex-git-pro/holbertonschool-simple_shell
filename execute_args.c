#include "main.h"


/**
 * execute_args - map if command is a builtin or a process
 * @args: command and its flag
 * Return: 1 on success or 0 if fail
 */

int execute_args(char **args)
{
	/*List of built-in command names*/
	char *builtin_func_list[] =

	{
		"cd",
		"env",
		"help",
		"exit"
	};

/*Array of function pointers to built-in commands*/
	int (*builtin_func[])(char **) =

	{
		&ocd,
		&oenv,
		&ohelp,
		&oexit,
	};

	unsigned long int i = 0;
	/*Check if command is NULL*/
	if (args[0] == NULL)
	{
		return (-1);
	}
	/*Iterate through built-in commands*/
	for (i = 0; i < sizeof(builtin_func_list) / sizeof(char *); i++)
	{
		/*If command matches a built-in, execute it*/
		if (strcmp(args[0], builtin_func_list[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}
	/*If not a built-in, execute as external command*/
	return (new_process(args));
}
