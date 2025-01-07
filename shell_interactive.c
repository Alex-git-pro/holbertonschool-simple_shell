#include "main.h"
/**
 * shell_interactive - command line interpreter
 *
 * Return: void
 */

void shell_interactive(void)
{
	char *line; /*Stock the line of command*/
	char **args; /*Stock the arguments of the command*/
	int status = -1; /*Follow the status of execution of the command*/

	do {
		printf("$> "); /*Print prompt symbol */
		line = read_line(); /*Read line from input */
		args = split_line(line); /*Tokenize line */
		status = execute_args(args); /*Execute the command with the arguments*/

		free(line);
		free(args);

		if (status >= 0) /*If status is non-negative, exit*/
		{
			exit(status);
		}
	} while (status == 1); /*Infinite loop while it's 1*/
}
