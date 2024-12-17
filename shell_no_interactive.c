#include "main.h"

/**
 * shell_no_interactive - command line interpreter in no interactive
 *
 * Return: void
 */

void shell_no_interactive(void)
{
	char *line; /*Stock the line of command*/
	char **args; /*Stock the arguments of the command*/
	int status = -1; /*Follow the status of execution of the command*/

	do {
		line = read_stream(); /*Read the line from the input*/
		args = split_line(line); /*Tokenize line*/
		status = execute_args(args); /*Execute the command with the arguments*/

		free(line);
		free(args);

		if (status >= 0) /*If status is non-negative, exit*/
		{
			exit(status);
		}
	} while (status == 1); /*Infinite loop while it's 1*/
}
