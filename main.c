#include "main.h"

/**
 * main - Entry point of the shell program.
 * @argc: Number of arguments.
 * @argv: Array of arguments.
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread = 0;
	int status = 0;

	/* Check for non-interactive mode */
	if (argc == 1)
	{
		while (1)
		{
			/* Prompt user for input */
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "$> ", 2);

			/* Read the input line */
			nread = getline(&line, &len, stdin);
			if (nread == -1)
			{
				free(line);
				break;
			}
			/* Remove newline character if present */
			line[nread - 1] = '\0';
			/* Process the command */
			status = execute_command(argv[0], line);
		}
	}
	else
	{
		/* Non-interactive mode - process commands from stdin */
		while (getline(&line, &len, stdin) != -1)
		{
			line[nread - 1] = '\0';
			status = execute_command(argv[0], line);
		}
	}
	free(line);
	return (status);
}
